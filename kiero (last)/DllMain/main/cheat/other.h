#include <array>
#include <corecrt_math_defines.h>
#include <utility>

inline Vector3 m_manipulate = Vector3::Zero(); // inline — безопасно при включении из нескольких TU
float VFlyhack = 0.0f;
float HFlyhack = 0.0f;
float VMaxFlyhack = 0.0f;
float HMaxFlyhack = 0.0f;
float flyhackDistanceVertical = 0.f;
float flyhackDistanceHorizontal = 0.f;
float flyhackPauseTime;

namespace AntiHackProtection
{
	static float noclip_margin_dismount = 0.22f;
	static float noclip_backtracking = 0.01f;
	static bool reporting = false;
	static bool admincheat = true;
	static bool objectplacement = true;
	static bool modelstate = true;
	static bool forceposition = true;
	static int userlevel = 2;
	static int enforcementlevel = 1;
	static float maxdesync = 1.f;
	static float maxdeltatime = 1.f;
	static float tickhistorytime = 0.5f;
	static float tickhistoryforgiveness = 0.1f;
	static float relaxationrate = 0.1f;
	static float relaxationpause = 10.f;
	static float maxviolation = 100.f;
	static int terrain_protection = 1;
	static int terrain_timeslice = 64;
	static float terrain_padding = 0.3f;
	static float terrain_penalty = 100.f;
	static bool terrain_kill = true;
	static bool terrain_check_geometry = false;
	static int noclip_protection = 3;
	static bool noclip_reject = true;
	static float noclip_penalty = 0.f;
	static float noclip_margin = 0.09f;
	static float noclip_stepsize = 0.1f;
	static int noclip_maxsteps = 15;
	static int speedhack_protection = 2;
	static bool speedhack_reject = true;
	static float speedhack_penalty = 0.f;
	static float speedhack_forgiveness = 2.f;
	static float speedhack_forgiveness_inertia = 10.f;
	static float speedhack_slopespeed = 10.f;
	static int flyhack_protection = 3;
	static bool flyhack_reject = false;
	static float flyhack_penalty = 100.f;
	static float flyhack_forgiveness_vertical = 1.5f;
	static float flyhack_forgiveness_vertical_inertia = 10.f;
	static float flyhack_forgiveness_horizontal = 1.5f;
	static float flyhack_forgiveness_horizontal_inertia = 10.f;
	static float flyhack_extrusion = 2.f;
	static float flyhack_margin = 0.05f;
	static float flyhack_stepsize = 0.1f;
	static int flyhack_maxsteps = 15;
	static int projectile_protection = 6;
	static float projectile_penalty = 0.f;
	static float projectile_forgiveness = 0.5f;
	static float projectile_serverframes = 2.f;
	static float projectile_clientframes = 2.f;
	static float projectile_trajectory = 1.f;
	static float projectile_anglechange = 60.f;
	static float projectile_velocitychange = 1.1f;
	static float projectile_desync = 1.f;
	static float projectile_backtracking = 0.01f;
	static float projectile_losforgiveness = 0.2f;
	static int projectile_damagedepth = 2;
	static int projectile_impactspawndepth = 1;
	static bool projectile_terraincheck = true;
	static bool projectile_vehiclecheck = true;
	static bool projectile_positionoffset = true;
	static int melee_protection = 4;
	static float melee_penalty = 0.f;
	static float melee_forgiveness = 0.5f;
	static float melee_serverframes = 2.f;
	static float melee_clientframes = 2.f;
	static float melee_backtracking = 0.01f;
	static float melee_losforgiveness = 0.2f;
	static bool melee_terraincheck = true;
	static bool melee_vehiclecheck = true;
	static int eye_protection = 4;
	static float eye_penalty = 0.f;
	static float eye_forgiveness = 0.5f;
	static float eye_serverframes = 2.f;
	static float eye_clientframes = 2.f;
	static bool eye_terraincheck = true;
	static bool eye_vehiclecheck = true;
	static float eye_noclip_cutoff = 0.06f;
	static float eye_noclip_margin = 0.21f;
	static float eye_noclip_backtracking = 0.01f;
	static float eye_losradius = 0.18f;
	static float eye_history_penalty = 100.f;
	static float eye_history_forgiveness = 0.1f;
	static float build_losradius = 0.01f;
	static float build_losradius_sleepingbag = 0.3f;
	static bool build_terraincheck = true;
	static bool build_vehiclecheck = true;
	static int build_inside_check = 2;
	static int debuglevel = 1;
}

namespace autoshoot {
	float lastshottime;

	void BulletsFiredPerShoot() {
		auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
		BaseProjectile* _held = held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
		float desyncTime = (Time::realtimeSinceStartup() - 0.75f) - 0.03125 * 3;
		Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
		DWORD64 active = weapon->entity();

		auto target = reinterpret_cast<BasePlayer*>(settings::closestPlayer)->GetBoneByID(head);

		if (settings::weapons::bullet_tp && settings::combat::hit_scan) {
			target = best_target;
		}
		else {
			target = reinterpret_cast<BasePlayer*>(settings::closestPlayer)->GetBoneByID(head);
		}

		if (utils::LineOfSight(target, LocalPlayer::Entity()->eyes()->position())) {
			for (int i = 0; i < settings::combat::bullet_counter; i++)
			{
				_held->LaunchProjectile();
				reinterpret_cast<void(*)(uintptr_t, Signal, Str)>((void*)Offsets::SendSignalBroadcast)(active, Signal::Attack, Str((L"")));
				_held->primaryMagazine()->contents()--;
				_held->UpdateAmmoDisplay();
				_held->ShotFired();
				_held->DidAttackClientside();
				_held->BeginCycle();
			}
		}
	}

	void OneShootWeapon() {
		auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
		BaseProjectile* _held = held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
		float desyncTime = (Time::realtimeSinceStartup() - 0.75f) - 0.03125 * 3;
		Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
		DWORD64 active = weapon->entity();

		auto target = reinterpret_cast<BasePlayer*>(settings::closestPlayer)->GetBoneByID(head);

		if (settings::weapons::bullet_tp && settings::combat::hit_scan) {
			target = best_target;
		}
		else {
			target = reinterpret_cast<BasePlayer*>(settings::closestPlayer)->GetBoneByID(head);
		}

		if (utils::LineOfSight(target, LocalPlayer::Entity()->eyes()->position())) {
			_held->LaunchProjectile();
			_held->primaryMagazine()->contents()--;
			_held->UpdateAmmoDisplay();
			_held->ShotFired();
			_held->DidAttackClientside();
			_held->BeginCycle();
		}
	}

	void DefaultAutoShoot() {
		auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
		BaseProjectile* _held = held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
		float desyncTime = (Time::realtimeSinceStartup() - 0.75f) - 0.03125 * 3;
		Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
		DWORD64 active = weapon->entity();

		if (settings::weapons::bullet_tp && settings::combat::hit_scan)
		{
			if (utils::LineOfSight(best_target, LocalPlayer::Entity()->eyes()->position())) {
				_held->LaunchProjectile();
				_held->primaryMagazine()->contents()--;
				_held->UpdateAmmoDisplay();
				_held->ShotFired();
				_held->DidAttackClientside();
				_held->BeginCycle();
			}
		}
		else
		{
			if (utils::LineOfSight(reinterpret_cast<BasePlayer*>(settings::closestPlayer)->GetBoneByID(head), LocalPlayer::Entity()->eyes()->position())) {
				_held->LaunchProjectile();
				_held->primaryMagazine()->contents()--;
				_held->UpdateAmmoDisplay();
				_held->ShotFired();
				_held->DidAttackClientside();
				_held->BeginCycle();
			}
		}
	}
}

namespace other {
	void draw_circle(Vector3 center, float radius)
	{
		Color color = Color(1, 1, 1, 1);
		const int numSegments = 20;
		const float angleIncrement = 2.0f * static_cast<float>(M_PI) / static_cast<float>(numSegments);

		for (int i = 0; i < numSegments; ++i)
		{
			float angle = angleIncrement * static_cast<float>(i);
			float x = center.x + radius * Mathf::Cos(angle);
			float z = center.z + radius * Mathf::Sin(angle);

			angle += angleIncrement;
			float x1 = center.x + radius * Mathf::Cos(angle);
			float z1 = center.z + radius * Mathf::Sin(angle);

			DDraw::Line(Vector3(x, center.y, z), Vector3(x1, center.y, z1), color, 0.01f, false, true);
		}
	}

	inline void DynamicManipAngles(std::vector<Vector3>& re, float max = 1.5f, float maxy = 1.5f, int numPoints = 100)
	{
		float radius = max; // Radius of the sphere

		for (int i = 0; i < numPoints; ++i) {
			float theta = static_cast<float>((rand)()) / static_cast<float>(RAND_MAX) * 2 * M_PI; // Random angle
			float phi = static_cast<float>((rand)()) / static_cast<float>(RAND_MAX) * M_PI;     // Random inclination angle

			float x = radius * sinf(phi) * cosf(theta);
			float y = maxy * sinf(phi) * sinf(theta);
			float z = radius * cosf(phi);

			re.emplace_back(x, y, z);
			re.emplace_back(-x, -y, -z);
			re.emplace_back(x, 0.f, z);

			re.emplace_back(0.f, y, 0.f);
			re.emplace_back(0.f, -y, 0.f);

			re.emplace_back(-x, 0.f, 0.f);
			re.emplace_back(x, 0.f, 0.f);

			re.emplace_back(0.f, 0.f, z);
			re.emplace_back(0.f, 0.f, -z);
		}
	}

	bool TestNoClipping(Vector3 oldPos, Vector3 newPos, float radius, float backtracking, bool sphereCast, Collider*& collider, bool vehicleLayer = false, BaseEntity* ignoreEntity = NULL)
	{
		int num = 1503731969;
		if (!vehicleLayer)
		{
			num &= -8193;
		}
		Vector3 normalized = (newPos - oldPos).normalized();
		Vector3 vector = oldPos - normalized * backtracking;
		float magnitude = (newPos - vector).magnitude();
		Ray ray = Ray(vector, normalized);
		RaycastHit hitInfo;
		bool flag = (ignoreEntity == NULL) ? Physics::Raycast_(ray, hitInfo, magnitude + radius, num, QueryTriggerInteraction::Ignore) : GamePhysics::Trace(ray, 0.f, hitInfo, magnitude + radius, num, GamePhysics::QueryTriggerInteraction::Ignore, ignoreEntity);
		if (!flag && sphereCast)
		{
			flag = ((ignoreEntity == NULL) ? Physics::SphereCast_(ray, radius, hitInfo, magnitude, num, QueryTriggerInteraction::Ignore) : GamePhysics::Trace(ray, radius, hitInfo, magnitude, num, GamePhysics::QueryTriggerInteraction::Ignore, ignoreEntity));
		}
		collider = (Collider*)hitInfo.m_Collider;
		return flag && GamePhysics::Verify(hitInfo, NULL);
	}

	//bool ValidateEyePos(Vector3 eyePos, Vector3 realEye)
	//{
	//	auto* target_player = reinterpret_cast<BasePlayer*>(settings::closestPlayer);

	//	auto player = LocalPlayer::Entity();
	//	bool flag = true;

	//	if (eyePos == Vector3::Zero())
	//	{
	//		flag = false;
	//	}

	//	static float eye_losradius = 0.18f;
	//	static float eye_noclip_cutoff = 0.06f;
	//	static float eye_noclip_margin = 0.21f;
	//	static float eye_noclip_backtracking = 0.01f;
	//	static int noclip_protection = 3;

	//	Collider* collider;

	//	int num11 = 2162688 | 8388608 | 134217728;
	//	Vector3 center = player->eyes()->center();
	//	Vector3 position = player->eyes()->position();
	//	if (!LineOfSightRadius(center, position, num11, eye_losradius) || !LineOfSightRadius(position, eyePos, num11, eye_losradius))
	//	{
	//		flag = false;
	//	}
	//	Vector3 position2 = player->eyes()->position();
	//	float num15 = position2.distance(eyePos);
	//	if (num15 > eye_noclip_cutoff)
	//	{
	//		if (TestNoClipping(realEye, eyePos, 0.5f - 0.21f, 0.01f, true, collider, false, nullptr))
	//		{
	//			flag = false;
	//		}
	//	}
	//	else if (num15 > 0.01f && TestNoClipping(realEye, eyePos, 0.01f, 0.01f, true, collider, false, nullptr))
	//	{
	//		flag = false;
	//	}

	//	return flag;
	//}

	bool check_eye(Vector3 eyePos, Vector3 realEye)
	{
		float timeSinceLastTick = (Time::realtimeSinceStartup() - 0.75f);
		float last_tick_time = Mathf::Max(0.f, Mathf::Min(timeSinceLastTick, 1.f));
		bool hit = true;
		float num = 1.f + AntiHackProtection::eye_forgiveness;
		float eye_clientframes = AntiHackProtection::eye_clientframes;
		float eye_serverframes = AntiHackProtection::eye_serverframes;
		float num2 = eye_clientframes / 60.f;
		float num3 = eye_serverframes * Mathx::Max(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());
		float num4 = (last_tick_time + num2 + num3) * num;
		float num5 = LocalPlayer::Entity()->MaxVelocity() + LocalPlayer::Entity()->GetParentVelocity().magnitude();
		float num6 = LocalPlayer::Entity()->BoundsPadding() + num4 * num5;
		float num7 = LocalPlayer::Entity()->eyes()->position().distance(eyePos) + 0.01;
		float num8 = Mathf::Abs(LocalPlayer::Entity()->GetMountVelocity().y + LocalPlayer::Entity()->GetParentVelocity().y);
		float num9 = LocalPlayer::Entity()->BoundsPadding() + num4 * num8 + LocalPlayer::Entity()->GetJumpHeight();
		float num10 = Mathf::Abs(LocalPlayer::Entity()->eyes()->position().y - eyePos.y) + 0.01;

		auto* target_player = reinterpret_cast<BasePlayer*>(settings::closestPlayer);

		Vector3 center = target_player->eyes()->center();
		Vector3 position = target_player->eyes()->position();

		static float eye_losradius = 0.18f;
		static float eye_noclip_cutoff = 0.06f;
		static float eye_noclip_margin = 0.21f;
		static float eye_noclip_backtracking = 0.01f;
		static int noclip_protection = 3;

		Collider* collider;

		int num12 = 2162688;
		num12 |= 8388608;
		num12 |= 134217728;

		if (eyePos == Vector3::Zero())
		{
			hit = false;
		}

		if (num7 > num6)
		{
			hit = false; // eye_distance
		}

		if (num10 > num9)
		{
			hit = false; // eye_altitude
		}

		if (!GamePhysics::LineOfSightRadius(center, position, num12, AntiHack::eye_losradius, NULL) || !GamePhysics::LineOfSightRadius(position, eyePos, num12, AntiHack::eye_losradius, NULL))
		{
			hit = false; // eye_los
		}

		int num11 = 2162688 | 8388608 | 134217728;

		if (!LineOfSightRadius(center, position, num11, eye_losradius) || !LineOfSightRadius(position, eyePos, num11, eye_losradius))
		{
			hit = false;
		}

		float num15 = position.distance(eyePos);
		if (num15 > eye_noclip_cutoff)
		{
			if (TestNoClipping(realEye, eyePos, 0.5f - 0.21f, 0.01f, true, collider, false, nullptr))
			{
				hit = false;
			}
		}
		else if (num15 > 0.01f && TestNoClipping(realEye, eyePos, 0.01f, 0.01f, true, collider, false, nullptr))
		{
			hit = false;
		}

		return hit;
	}

	void find_manipulate_angle() {
		Vector3 re_p = LocalPlayer::Entity()->GetNetworkEyePosition();

		Vector3 choice = Vector3::Zero();

		auto* target = reinterpret_cast<BasePlayer*>(settings::closestPlayer);

		auto right = LocalPlayer::Entity()->eyes()->MovementRight();
		auto forward = LocalPlayer::Entity()->eyes()->MovementForward();

		Vector3 vel = LocalPlayer::Entity()->get_movement()->TargetMovement();
		float len = vel.Length();

		float desyncTime = (Time::realtimeSinceStartup() - 0.75f) - 0.03125 * 3;
		float mm_max_eye = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.5f) * len) - 0.05f;
		float max_v_multicplier = 5.f;
		float v_mm_max_eye = mm_max_eye / max_v_multicplier;

		float num = 1.f + 0.5f;
		float eye_clientframes = 2.f;
		float eye_serverframes = 2.f;
		float num2 = eye_clientframes / 60.f;
		float num3 = eye_serverframes * Mathx::Max(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());
		float num4 = (desyncTime + num2 + num3) * num;
		float num5 = 5.5 + LocalPlayer::Entity()->GetParentVelocity().Magnitude();
		float num7 = LocalPlayer::Entity()->BoundsPadding() + num4 * num5 + 0.f; // eye_distance

		std::vector<Vector3> generatedPoints;

		if (settings::combat::draw_radius_on_player)
		{
			if (target) {
				Vector3 actual_target_pos = target->playerModel()->position() + Vector3(0.f, 0.2f, 0.f);
				float step = (M_PI * 2.0f) / 72;
				float radius = 1.0f;
				for (float a = 0; a < (M_PI * 2.0f); a += step)
				{
					// down position
					static float currentpos = 1.5;
					static bool Tick_current = false;
					static float Speed_current = 0.0004f;
					// head position
					static float headpos = 0;
					static bool Tick_head = false;
					static float Speed_head = 0.0004f;
					// -------------------------- //
					if (Tick_head || headpos >= 1.5)
					{
						Tick_head = true;
						if (!(headpos <= 0))
							headpos -= Speed_head;
						else if (headpos <= 0)
							Tick_head ^= 1;
					}

					else if (!Tick_head || headpos != 1.5)
					{
						Tick_head = false;
						if (!(headpos >= 1.5))
							headpos += Speed_head;
						else if (headpos >= 1.5)
							Tick_head ^= 1;
					}
					// -------------------------- //
					if (Tick_current || currentpos >= 1.5)
					{
						Tick_current = true;
						if (!(currentpos <= 0))
							currentpos -= Speed_current;
						else if (currentpos <= 0)
							Tick_current ^= 1;
					}

					else if (!Tick_current || currentpos != 1.5)
					{
						Tick_current = false;
						if (!(currentpos >= 1.5))
							currentpos += Speed_current;
						else if (currentpos >= 1.5)
							Tick_current ^= 1;
					}
					// -------------------------- //

					Vector3 upper_shmiga_start(radius * cos(a) + actual_target_pos.x, actual_target_pos.y + (float)currentpos, radius * sin(a) + actual_target_pos.z);
					Vector3 upper_shmiga_end(radius * cos(a + step) + actual_target_pos.x, actual_target_pos.y + (float)currentpos, radius * sin(a + step) + actual_target_pos.z);
					Vector3 down_shmiga_start(radius * cos(a) + actual_target_pos.x, actual_target_pos.y + (float)headpos, radius * sin(a) + actual_target_pos.z);
					Vector3 down_shmiga_end(radius * cos(a + step) + actual_target_pos.x, actual_target_pos.y + (float)headpos, radius * sin(a + step) + actual_target_pos.z);

					DDraw::Line(upper_shmiga_start, upper_shmiga_end, Color(100, 0, 0, 1), 0.f, false, false);
					DDraw::Line(down_shmiga_start, down_shmiga_end, Color(100, 0, 0, 1), 0.f, false, false);
				}
			}
		}

		DynamicManipAngles(generatedPoints, mm_max_eye, 1.5, 16);

		draw_circle(LocalPlayer::Entity()->GetBoneByID(penis), num7);

		Vector3 targetheadpos = target->GetBoneByID(head);

		if (settings::weapons::bullet_tp && settings::combat::hit_scan) {
			targetheadpos = best_target;
		}
		else {
			targetheadpos = target->GetBoneByID(head);
		}

		for (auto s : generatedPoints) {
			Vector3 point = re_p + s;
			 
			if (!utils::LineOfSight(point, re_p)) continue;
			
			if (!check_eye(point, re_p)) continue;

			if (!utils::LineOfSight(targetheadpos, point)) continue;

			choice = s;

			break;
		}

		auto fixed_time = Time::fixedTime();
		if (choice.empty()) {

			m_manipulate = Vector3::Zero();
			return;
		}

		m_manipulate = choice;
	}
}

void TestFlying() {
	flyhackPauseTime = Mathf::Max(0.f, flyhackPauseTime - Time::deltaTime());
	bool inAir = false;
	float radius = LocalPlayer::Entity()->GetRadius();
	float height = LocalPlayer::Entity()->GetHeight(false);
	Vector3 vector = (LocalPlayer::Entity()->lastSentTick()->__position() + LocalPlayer::Entity()->transform()->position()) * 0.5f;
	Vector3 vector2 = vector + Vector3(0.f, radius - 1.85f, 0.f);
	Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
	float radius2 = radius - 0.05f;
	bool a = Physics::CheckCapsule(vector2, vector3, radius2, 1503731969, QueryTriggerInteraction::Ignore);
	inAir = !a;

	if (inAir) {
		bool flag = false;

		Vector3 vector4 = (LocalPlayer::Entity()->transform()->position() - LocalPlayer::Entity()->lastSentTick()->__position());
		float num3 = Mathf::Abs(vector4.y);
		float num4 = Misc::Magnitude2D(vector4);

		if (vector4.y >= 0.f) {
			flyhackDistanceVertical += vector4.y;
			flag = true;
		}
		if (num3 < num4) {
			flyhackDistanceHorizontal += num4;
			flag = true;
		}
		float flyhack_forgiveness_interia = 10.0f;
		float flyhack_forgiveness = 1.5f;
		float flyhack_extrusion = 1.85f;
		float num5 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
		float num6 = ((LocalPlayer::Entity()->GetJumpHeight() + num5) * 3);

		VMaxFlyhack = num6;
		if (flyhackDistanceVertical <= (num6)) {
			VFlyhack = flyhackDistanceVertical;
		}
		if (VFlyhack >= VMaxFlyhack)
			VFlyhack = VMaxFlyhack;
		float num7 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
		float num8 = ((5.f + num7) * 3);

		HMaxFlyhack = num8;
		if (flyhackDistanceHorizontal <= (num8)) {
			HFlyhack = flyhackDistanceHorizontal;
		}
		if (HFlyhack >= HMaxFlyhack)
			HFlyhack = HMaxFlyhack;
		if (flag) {
			float num5 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
			float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
			if (flyhackDistanceVertical > num6) {
			}
			float num7 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
			float num8 = 5.f + num7;
			if (flyhackDistanceHorizontal > num8) {
			}
		}
	}
	else {
		flyhackDistanceHorizontal = 0.f;
		flyhackDistanceVertical = 0.f;
	}
}

void CheckFlyhack() {
	TestFlying();

	float num5 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
	settings::max_flyhack = num6;
	if (flyhackDistanceVertical <= num6) {
		settings::flyhack = flyhackDistanceVertical;
	}

	float num7 = Mathf::Max((flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num8 = 5.f + num7;
	settings::max_hor_flyhack = num8;
	if (flyhackDistanceHorizontal <= num8) {
		settings::hor_flyhack = flyhackDistanceHorizontal;
	}
}