void ak47fix(Projectile* projectile) {
	projectile->swimScale() = Vector3(0, 0, 0);
	projectile->swimSpeed() = Vector3(0, 0, 0);
	projectile->swimRandom() = 0.f;
	projectile->ricochetChance() = 0.f;
}

Vector3 SimulateProjectile_(Vector3 position, Vector3 velocity, float& partialTime, float& travelTime, Vector3 gravity, float drag)
{
	float timestep = 0.003f;
	Vector3 origin = position;
	if (partialTime > 0)
	{
		float num2 = timestep - partialTime;
		if (travelTime < num2)
		{
			origin = position;
			position += velocity * travelTime;
			partialTime += travelTime;
			return origin;
		}
		origin = position;
		position += velocity * num2;
		velocity += gravity * timestep;
		velocity -= velocity * drag * timestep;
		travelTime -= num2;
	}

	int num3 = (int)std::floor(travelTime / timestep);

	for (int i = 0; i < num3; i++)
	{
		origin = position;
		position += velocity * timestep;
		velocity += gravity * timestep;
		velocity -= velocity * drag * timestep;
	}
	partialTime = travelTime - timestep * (float)num3;
	if (partialTime > 0)
	{
		origin = position;
		position += velocity * partialTime;
	}

	return origin;
}

void SimulateProjectile(Vector3 position, Vector3 velocity, float partialTime, float travelTime, Vector3 gravity, float drag, Vector3 prevPosition, Vector3 prevVelocity)
{
	float num = 0.03125f;
	prevPosition = position;
	prevVelocity = velocity;
	if (partialTime > 0)
	{
		float num2 = num - partialTime;
		if (travelTime < num2)
		{
			prevPosition = position;
			prevVelocity = velocity;
			position += velocity * travelTime;
			partialTime += travelTime;
			return;
		}
		prevPosition = position;
		prevVelocity = velocity;
		position += velocity * num2;
		velocity += gravity * num;
		velocity -= velocity * drag * num;
		travelTime -= num2;
	}
	int num3 = Mathf::FloorToInt(travelTime / num);
	for (int i = 0; i < num3; i++)
	{
		prevPosition = position;
		prevVelocity = velocity;
		position += velocity * num;
		velocity += gravity * num;
		velocity -= velocity * drag * num;
	}
	partialTime = travelTime - num * (float)num3;
	if (partialTime > 0)
	{
		prevPosition = position;
		prevVelocity = velocity;
		position += velocity * partialTime;
	}
}

bool LineCircleIntersection(Vector3 center, float radius, Vector3 rayStart, Vector3 rayEnd, Vector3 direction, float& offset)
{
	Vector2 P(rayStart.x, rayStart.z);
	Vector2 Q(rayEnd.x, rayEnd.z);

	float a = Q.y - P.y;
	float b = P.x - Q.x;
	float c = (a * (P.x) + b * (P.y)) * -1.f;

	float x = center.x;
	float y = center.z;

	float c_x = (b * ((b * x) - (a * y)) - a * c) / (std::pow(a, 2) + std::pow(b, 2));
	float c_y = (a * ((-b * x) + (a * y)) - (b * c)) / (std::pow(a, 2) + std::pow(b, 2));

	Vector2 closestPoint(c_x, c_y);

	float distance = P.distance(Q);

	if (P.distance(closestPoint) > distance || Q.distance(closestPoint) > distance)
	{
		return false;
	}

	if (radius > closestPoint.distance(Vector2(center.x, center.z)))
	{
		Vector2 P(rayStart.x, rayStart.y);
		Vector2 Q(rayEnd.x, rayEnd.y);

		float a = Q.y - P.y;
		float b = P.x - Q.x;
		float c = (a * (P.x) + b * (P.y)) * -1.f;

		float x = center.x;
		float y = center.y;

		float c_x = (b * ((b * x) - (a * y)) - a * c) / (std::pow(a, 2) + std::pow(b, 2));
		float c_y = (a * ((-b * x) + (a * y)) - (b * c)) / (std::pow(a, 2) + std::pow(b, 2));

		Vector2 closestPoint(c_x, c_y);
		if (radius > closestPoint.distance(Vector2(center.x, center.y)))
		{
			return true;
		}
		else
		{
			offset += std::fabs(center.y - closestPoint.y);
			return false;
		}
	}

	return false;
};

bool check_hit(Vector3 HitPositionWorld, Projectile* projectile)
{
	auto* target_ply = reinterpret_cast<BasePlayer*>(settings::closestPlayer);

	bool hit = true;

	if (projectile->integrity() <= 0.f)
	{
		hit = false; //projectile_integrity
	}
	float timeSinceLastTick = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime());
	float last_tick_time = Mathf::Max(0.f, Mathf::Min(timeSinceLastTick, 1.f));
	float magnitude = target_ply->GetParentVelocity().magnitude();
	float num2 = 1.f + 0.5f;
	float num9 = 2.f / 60.f;
	float num10 = 2.f * Mathx::Max(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());
	float num12 = (last_tick_time + num9 + num10) * num2;
	float num14 = projectile->currentPosition().distance(HitPositionWorld) + 0.01;
	float num19 = target_ply->BoundsPadding() + num12 * magnitude + 0.1f;
	float num20 = target_ply->Distance(HitPositionWorld);

	bool flag7 = target_ply->playerModel()->isNpc();
	bool flag2 = target_ply->HasPlayerFlag(PlayerFlags::Sleeping);
	bool flag3 = target_ply->HasPlayerFlag(PlayerFlags::Wounded);
	bool flag4 = target_ply->mounted();

	float num16 = target_ply->MaxVelocity() + target_ply->GetParentVelocity().magnitude();
	float num17 = target_ply->BoundsPadding() + num12 * num16;
	float num18 = target_ply->Distance(HitPositionWorld);

	float num21 = target_ply->MaxVelocity() + target_ply->GetParentVelocity().magnitude();
	float num22 = num12 * num21;
	float num24 = projectile->traveledDistance() + 1.f + projectile->currentPosition().magnitude() + num22;
	if (num14 > num24)
	{
		hit = false; // projectile_distance
	}
	return hit;
}

// Связка с Manipulator: m_manipulate — текущее серверное смещение глаза (inline-определение в cheat/other.h).
extern Vector3 m_manipulate;

bool bullet_tp(Projectile* projectile) {
	auto* target_player = reinterpret_cast<BasePlayer*>(settings::closestPlayer);

	if (settings::weapons::bullet_tp) {
		Transform* target_transform = target_player->transform_(head);
		PlayerProjectileUpdate* ppu = (PlayerProjectileUpdate*)methods::object_new(il2cpp::_init_class(("PlayerProjectileUpdate"), ("ProtoBuf")));
		HitTest* ht = projectile->hitTest();

		// Манипулированный «глаз» как точка отсчёта траектории (как в STW):
		// сервер считает, что наш глаз смещён на m_manipulate, поэтому и перенаправление
		// пули строим от этой же точки — попадание легализуется трассировкой от серверной позиции глаза.
		Vector3 tp_origin = projectile->currentPosition();
		static bool bt_use_manipulator = true;
		if (bt_use_manipulator && settings::combat::manipulator &&
			GetAsyncKeyState(settings::misc::manipulator_key) && !m_manipulate.empty()) {
			tp_origin = tp_origin + m_manipulate;
		}

		Vector3 next_bullet_position = tp_origin + (projectile->currentVelocity() * 0.01f);
		Line line = Line(tp_origin, next_bullet_position);
		Vector3 HitPosition = target_player->transform_(head)->position();
		Vector3 closest_point = line.ClosestPoint(target_transform->position());

		Vector3 newBulletPos = Vector3::move_towards(closest_point, target_transform->position(), 0.97f); // 0.97f
		Vector3 movpos = Vector3::move_towards(newBulletPos, target_transform->position(), 0.97f); // 0.97f

		float RealRadius = 2.65f;

		float travel = max((projectile->traveledTime() + projectile->traveledTime()) - projectile->closeFlybyDistance(), 0);
		Vector3 gr = Physics::get_gravity();
		Vector3 a; Vector3 b;

		if (settings::combat::bones_target == 0)
		{
			target_transform = target_player->transform_(head);
		}
		else if (settings::combat::bones_target == 1)
		{
			target_transform = target_player->transform_(spine4);
		}
		else if (settings::combat::bones_target == 2)
		{
			int yeet1 = rand() % 100;
			if (yeet1 > 50) {
				target_transform = target_player->transform_(head);
			}
			else {
				target_transform = target_player->transform_(spine1);
			}
		}
		else if (settings::combat::bones_target == 3)
		{
			int num = rand() % 100;
			if (num > 90)
			{
				target_transform = target_player->transform_(head);
			}
			else if (num < 90 && num > 80)
			{
				target_transform = target_player->transform_(neck);
			}
			else if (num < 80 && num > 70)
			{
				target_transform = target_player->transform_(r_hip);
			}
			else if (num < 70 && num > 60)
			{
				target_transform = target_player->transform_(pelvis);
			}
			else if (num < 60 && num > 50)
			{
				target_transform = target_player->transform_(l_clavicle);
			}
			else if (num < 50 && num > 40)
			{
				target_transform = target_player->transform_(l_upperarm);
			}
			else if (num < 40 && num > 30)
			{
				target_transform = target_player->transform_(l_foot);
			}
			else if (num < 30 && num > 20)
			{
				target_transform = target_player->transform_(r_foot);
			}
			else if (num < 20 && num > 10)
			{
				target_transform = target_player->transform_(l_hand);
			}
			else if (num < 10)
			{
				target_transform = target_player->transform_(r_hand);
			}
			else
			{
				target_transform = target_player->transform_(spine1);
			}
		}

		if (!utils::LineOfSight(closest_point, movpos))
			return false;

		SimulateProjectile(closest_point, projectile->currentVelocity(), projectile->tumbleSpeed(), travel, gr * projectile->gravityModifier(), projectile->drag(), a, b);

		if (Math::Distance_3D(projectile->currentPosition(), target_transform->position()) <= RealRadius && projectile->isAuthoritative() && projectile->isAlive())
		{
			if (ppu && ht && target_transform && target_player)
			{
				if (projectile->projectileID() != NULL)
				{
					ppu->projectileID() = projectile->projectileID();
					ppu->travelTime() = projectile->traveledTime();
					ppu->curVelocity() = projectile->currentVelocity();
					ppu->curPosition() = closest_point;
					LocalPlayer::Entity()->SPU(ppu);
					RPC_Counter.Increment();
					ppu->curPosition() = newBulletPos; // trajectory_start / trajectory_update_total
					LocalPlayer::Entity()->SPU(ppu);
					RPC_Counter.Increment();

					target_transform->set_position(movpos);
					RPC_Counter.Increment();

					ht->AttackRay() = Ray(closest_point, movpos);
					ht->HitTransform() = target_transform;
					ht->HitEntity() = reinterpret_cast<BasePlayer*>(settings::closestPlayer);
					ht->HitPoint() = target_transform->InverseTransformPoint(movpos);
					ht->HitNormal() = target_transform->InverseTransformDirection(movpos);
					ht->HitDistance() = Math::Distance_3D(closest_point, HitPosition);
					ht->damageProperties() = projectile->damageProperties();
					ht->MaxDistance() = 1000.0f;
					ht->DidHit() = true;

					if (projectile->projectileID() != 0 && ppu->projectileID() != 0 && check_hit(movpos, projectile))
					{
						projectile->DoHit(ht, movpos, Vector3());

						DDraw::Capsule(closest_point, Quaternion(), 0.3f, 2 * 0.3f, Color(1, 1, 1, 1), 5.f, false);
						RPC_Counter.Increment();
					}
				}
			}
		}
	}

	return true;
}