// STW (Shoot Throw Wall) — легальное «проброс»-перенаправление снаряда к ближайшей
// точке на модели цели, если пуля прошла бы рядом с игроком сквозь препятствие.
//
// Объединённая и улучшенная реализация из двух источников:
//   - "kiero (last)"  : BulletTP / PlayerProjectileUpdate + безопасная проверка попадания (check_hit)
//   - "222333666"     : STW by vidodoggy / .banqai (closest point + коррекция траектории)
//
// Улучшения относительно оригиналов:
//   * жёсткие guard-проверки (цель, снаряд, ненулевая скорость, alive/authoritative);
//   * ограничение числа итераций цикла коррекции траектории (в оригинале — бесконечный while);
//   * единый объект PlayerProjectileUpdate вместо создания нового на каждую отправку;
//   * повторная проверка LOS перед финальным DoHit;
//   * distance check по образцу check_hit() из BulletTP для защиты от античита.

#ifndef STW_MAX_ITERATIONS
#define STW_MAX_ITERATIONS 8
#endif

namespace stw_impl
{
	inline PlayerProjectileUpdate* get_ppu()
	{
		static PlayerProjectileUpdate* ppu = nullptr;
		if (!ppu)
			ppu = (PlayerProjectileUpdate*)methods::object_new(il2cpp::_init_class(("PlayerProjectileUpdate"), ("ProtoBuf")));
		return ppu;
	}

	inline bool send_update(Projectile* projectile, Vector3 pos, int& rpc_budget)
	{
		PlayerProjectileUpdate* ppu = get_ppu();
		if (!ppu || rpc_budget <= 0)
			return false;

		ppu->projectileID() = projectile->projectileID();
		ppu->travelTime() = projectile->traveledTime();
		ppu->curVelocity() = projectile->currentVelocity();
		ppu->curPosition() = pos;

		LocalPlayer::Entity()->SPU(ppu);
		RPC_Counter.Increment();
		rpc_budget--;
		return true;
	}

	// Проверка легальности финальной точки попадания (адаптация check_hit из bullet_tp.h)
	inline bool check_hit(Vector3 hit_position_world, Projectile* projectile, BasePlayer* target_ply)
	{
		float time_since_last_tick = Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime();
		float last_tick_time = Mathf::Max(0.f, Mathf::Min(time_since_last_tick, 1.f));
		float num2 = 1.f + 0.5f;
		float num9 = 2.f / 60.f;
		float num10 = 2.f * Mathx::Max(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());
		float num12 = (last_tick_time + num9 + num10) * num2;

		float num14 = projectile->currentPosition().Distance(hit_position_world) + 0.01f;
		float num16 = target_ply->MaxVelocity() + target_ply->GetParentVelocity().Magnitude();
		float num22 = num12 * num16;
		float num24 = projectile->traveledDistance() + 1.f + projectile->currentPosition().Magnitude() + num22;

		return num14 <= num24;
	}
}

bool stw(Projectile* projectile, float deltaTime)
{
	BasePlayer* target_player = reinterpret_cast<BasePlayer*>(settings::closestPlayer);

	if (!projectile || !target_player)
		return false;

	if (projectile->projectileID() == 0)
		return false;

	if (projectile->integrity() <= 0.f)
		return false;

	if (!projectile->isAuthoritative() || !projectile->isAlive())
		return false;

	Vector3 cur_pos = projectile->currentPosition();
	Vector3 cur_vel = projectile->currentVelocity();

	float speed = cur_vel.Magnitude();
	if (speed < 1e-5f || deltaTime <= 0.f)
		return false;

	// Точка, куда снаряд долетит на этом тике, и линия полёта
	Vector3 traveled = cur_vel * deltaTime;
	Vector3 next_pos = cur_pos + traveled;

	Vector3 line_dir = (next_pos - cur_pos).Normalized();
	float line_len = traveled.Magnitude();

	// Проекция оси цели на линию полёта этого тика
	Vector3 center_pos = target_player->PivotPoint();
	Vector3 to_target = center_pos - cur_pos;
	float d = to_target.DotSero(line_dir);
	if (d < 0.f) d = 0.f;
	else if (d > line_len) d = line_len;

	Vector3 closest_on_line = cur_pos + line_dir * d;
	Vector3 closest_point = utils::ClosestPoint(target_player, closest_on_line);

	float distance = target_player->Distance(closest_on_line);
	if (distance <= 0.f)
		return false;

	int rpc_budget = 4; // не спамим RPC больше, чем в оригинальных версиях

	for (int iter = 0; iter < STW_MAX_ITERATIONS; ++iter)
	{
		Vector3 hit_point_world = closest_point;

		// Если цель далеко за радиусом «прощения» — сдвигаем точку прицела ближе
		if (distance > 1.2f)
		{
			float amount_needed = (distance - 1.2f + 0.01f) / distance;
			Vector3 direction = hit_point_world + closest_on_line;
			Vector3 new_position = closest_on_line + direction * amount_needed;

			if (closest_on_line.Distance(new_position) > 1.f ||
				!GamePhysics::LineOfSight_(closest_on_line, new_position, ProjectileLineOfSightCheck | Terrain | Vehicle_Large, 0.f, 0))
				return false;

			closest_on_line = new_position;
			distance = target_player->Distance(closest_on_line);
		}

		if (distance > 1.f)
		{
			float player_distance_usage = minm(0.19f, distance - 1.f);
			float amount_needed = 1.f - player_distance_usage / distance;
			Vector3 direction = hit_point_world + closest_on_line;
			hit_point_world = closest_on_line + direction * amount_needed;
		}

		// Телепорт позиции снаряда на точку линии полёта + отправка обновления
		projectile->previousPosition() = cur_pos;
		projectile->currentPosition() = closest_on_line;
		projectile->traveledDistance() += projectile->previousPosition().Distance(projectile->currentPosition());
		projectile->traveledTime() += projectile->previousPosition().Distance(projectile->currentPosition()) / speed;

		if (!stw_impl::send_update(projectile, projectile->currentPosition(), rpc_budget))
			return false;

		cur_pos = projectile->currentPosition();

		// Финальная позиция — смещаем по направлению к хитбоксу (как в оригинале)
		Transform* head_transform = target_player->transform_(head);
		if (!head_transform)
			return false;

		Vector3 head_pos = target_player->transform()->position() + Vector3(0.f, 1.49f, 0.f);
		Vector3 dir_to_head = (head_pos - cur_pos).Normalized();

		if (!stw_impl::send_update(projectile, cur_pos + dir_to_head * 0.97f, rpc_budget))
			return false;

		// Проверяем, что путь от текущей позиции до точки попадания легален
		if (!utils::LineOfSight(cur_pos, hit_point_world))
			return false;

		HitTest* ht = projectile->hitTest();
		if (!ht)
			return false;

		projectile->transform()->set_position(hit_point_world);

		ht->AttackRay() = Ray(cur_pos, (hit_point_world - cur_pos).Normalized());
		ht->HitTransform() = head_transform;
		ht->HitEntity() = target_player;
		ht->HitPoint() = head_transform->InverseTransformPoint(hit_point_world);
		ht->HitNormal() = head_transform->InverseTransformDirection(hit_point_world);
		ht->BestHit() = true;
		ht->MultiHit() = true;
		ht->DidHit() = true;
		ht->HitDistance() = distance;
		ht->MaxDistance() = 999.f;
		ht->Forgiveness() = 1.f;
		ht->damageProperties() = projectile->damageProperties();

		Vector3 final_hit = ht->HitPointWorld();

		// Защита от нелегальных дистанций (аналог check_hit из BulletTP)
		if (!stw_impl::check_hit(final_hit, projectile, target_player))
			return false;

		projectile->DoHit(ht, final_hit, ht->HitNormalWorld());
		return true;
	}

	return false;
}
