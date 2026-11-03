#include <map>

//static auto getmodifiedaimcone = reinterpret_cast<Vector3(*)(float, Vector3, bool)>(*reinterpret_cast<uintptr_t*>(il2cpp::_method(("AimConeUtil"), ("GetModifiedAimConeDirection"), 0, (""), (""))));

namespace a {
	double CalcBulletDrop(double height, double DepthPlayerTarget, float velocity, float gravity) {
		double pitch = (Vector3::my_atan2(height, DepthPlayerTarget));
		double BulletVelocityXY = velocity * Vector3::my_cos(pitch);
		double Time = DepthPlayerTarget / BulletVelocityXY;
		double TotalVerticalDrop = (0.4905f * gravity * Time * Time);
		return TotalVerticalDrop * 10;
	}
	bool LineCircleIntersection(Vector3 center,
		float radius,
		Vector3 rayStart,
		Vector3 rayEnd,
		float& offset)
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

		float distance = P.distance_2d(Q);

		if (P.distance_2d(closestPoint) > distance || Q.distance_2d(closestPoint) > distance)
		{
			return false;
		}

		if (radius > closestPoint.distance_2d(Vector2(center.x, center.z)))
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
			if (radius > closestPoint.distance_2d(Vector2(center.x, center.y)))
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
	void Prediction(Vector3 local, Vector3& target, Vector3 targetvel, float bulletspeed, float gravity) {
		float Dist = Math::Distance_3D(target, local);
		float BulletTime = Dist / bulletspeed;
		Vector3 vel = Vector3(targetvel.x, 0, targetvel.z) * 0.75f;
		Vector3 predictVel = vel * BulletTime;
		target += predictVel;
		double height = target.y - local.y;
		Vector3 dir = target - local;
		float depthPlayerTarget = sqrt((dir.x * dir.x) + (dir.z * dir.z));
		float drop = CalcBulletDrop(height, depthPlayerTarget, bulletspeed, gravity);
		target.y += drop;
		Vector3 acc = Vector3(targetvel.x, -gravity, targetvel.z) * 0.75f;
		Vector3 deltaVel = acc * BulletTime;
		targetvel += deltaVel;
	}
	Vector3 get_aim_point(float speed, float gravity) {
		Vector3 ret = target_player->get_bone_pos(head);
		Prediction(LocalPlayer::Entity()->get_bone_pos(head), ret, target_player->newVelocity(), speed, gravity);
		return ret;
	}
}
float GetFov(BasePlayer* Entity, BoneList Bone) {
	Vector2 ScreenPos;
	if (!utils::w2s(Entity->get_bone_pos(Bone), ScreenPos)) return 1000.f;
	return Math::Distance_2D(Vector2(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2), ScreenPos);
}
float GetFovHeli(Vector3 pos) {
	Vector2 ScreenPos;
	if (!utils::w2s(pos, ScreenPos)) return 1000.f;
	return Math::Distance_2D(Vector2(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2), ScreenPos);
}
float GetGravity(int ammoid) {
	switch (ammoid) {
	case 14241751:
		return 1.10f;

	case -1234735557:
		return 0.75f;

	case 215754713:
		return 0.75f;

	case -1023065463:
		return 0.5f;

	case -2097376851:
		return 0.75f;

	case -1321651331:
		return 1.25f;

	case 785728077:
		return 1.0f;

	case 605467368:
		return 0.75f;

	case 1712070256:
		return 0.75f;

	default:
		return 1.5f;
	}
}
float GetBulletSpeed() {
	Item* active = LocalPlayer::Entity()->GetActiveWeapon();
	Weapon tar = active->Info();
	int ammo = active->LoadedAmmo();
	if (vars::weapons::fast_bullets)
	{
		if (vars::weapons::low_velocity && GetAsyncKeyState(vars::keys::low_velocity_key)) {
			if (LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1953903201 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1443579727 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1367281941)
			{
				if (ammo == 0) return vars::weapons::fast_bullets ? tar.ammo[0].speed * 0.8 + vars::stuff::testFloat : tar.ammo[0].speed + vars::stuff::testFloat;
				for (Ammo am : tar.ammo) {
					for (int id : am.id) {
						if (id == ammo) {
							return vars::weapons::fast_bullets ? am.speed * 0.8 + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
						}
					}
					if (am.id[0] == 0) return vars::weapons::fast_bullets ? am.speed * 0.8 + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
				}
				return vars::weapons::fast_bullets ? 250.f * 0.8 + vars::stuff::testFloat : 250.f + vars::stuff::testFloat;
			}
			else
			{
				if (ammo == 0) return vars::weapons::fast_bullets ? tar.ammo[0].speed * 0.510 + vars::stuff::testFloat : tar.ammo[0].speed + vars::stuff::testFloat;
				for (Ammo am : tar.ammo) {
					for (int id : am.id) {
						if (id == ammo) {
							return vars::weapons::fast_bullets ? am.speed * 0.510 + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
						}
					}
					if (am.id[0] == 0) return vars::weapons::fast_bullets ? am.speed * 0.510 + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
				}
				return vars::weapons::fast_bullets ? 250.f * 0.510 + vars::stuff::testFloat : 250.f + vars::stuff::testFloat;
			}
		}
		else
		{
			if (ammo == 0) return vars::weapons::fast_bullets ? tar.ammo[0].speed * vars::weapons::bulletspeed + vars::stuff::testFloat : tar.ammo[0].speed + vars::stuff::testFloat;
			for (Ammo am : tar.ammo) {
				for (int id : am.id) {
					if (id == ammo) {
						return vars::weapons::fast_bullets ? am.speed * vars::weapons::bulletspeed + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
					}
				}
				if (am.id[0] == 0) return vars::weapons::fast_bullets ? am.speed * vars::weapons::bulletspeed + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
			}
			return vars::weapons::fast_bullets ? 250.f * vars::weapons::bulletspeed + vars::stuff::testFloat : 250.f + vars::stuff::testFloat;
		}
	}
	else
	{
		if (ammo == 0) return vars::weapons::fast_bullets ? tar.ammo[0].speed * 1.00 + vars::stuff::testFloat : tar.ammo[0].speed + vars::stuff::testFloat;
		for (Ammo am : tar.ammo) {
			for (int id : am.id) {
				if (id == ammo) {
					return vars::weapons::fast_bullets ? am.speed * 1.00 + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
				}
			}
			if (am.id[0] == 0) return vars::weapons::fast_bullets ? am.speed * 1.00 + vars::stuff::testFloat : am.speed + vars::stuff::testFloat;
		}
		return vars::weapons::fast_bullets ? 250.f * 1.00 + vars::stuff::testFloat : 250.f + vars::stuff::testFloat;
	}
}

//void StepConstant(Vector2& angles) {
//	bool smooth = vars::combat::smooth;
//	Vector2 angles_step = angles - LocalPlayer::Entity()->viewangles();
//	Math::Normalize(angles_step.x, angles_step.y);
//
//	if (smooth) {
//		float factor_pitch = (vars::combat::smooth_factor / 10.f);
//		if (angles_step.x < 0.f) {
//			if (factor_pitch > std::abs(angles_step.x)) {
//				factor_pitch = std::abs(angles_step.x);
//			}
//			angles.x = LocalPlayer::Entity()->viewangles().x - factor_pitch;
//		}
//		else {
//			if (factor_pitch > angles_step.x) {
//				factor_pitch = angles_step.x;
//			}
//			angles.x = LocalPlayer::Entity()->viewangles().x + factor_pitch;
//		}
//	}
//	if (smooth) {
//		float factor_yaw = (vars::combat::smooth_factor / 10.f);
//		if (angles_step.y < 0.f) {
//			if (factor_yaw > std::abs(angles_step.y)) {
//				factor_yaw = std::abs(angles_step.y);
//			}
//			angles.y = LocalPlayer::Entity()->viewangles().y - factor_yaw;
//		}
//		else {
//			if (factor_yaw > angles_step.y) {
//				factor_yaw = angles_step.y;
//			}
//			angles.y = LocalPlayer::Entity()->viewangles().y + factor_yaw;
//		}
//	}
//}
