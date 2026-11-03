#include "defs.h"
int flick = 0;
int yaw = 100;
using namespace hk_defs;
Vector3 last_head_pos = Vector3::Zero();
Vector3 last_neck_pos = Vector3::Zero();
Vector3 last_spine4_pos = Vector3::Zero();
Vector3 last_spine3_pos = Vector3::Zero();
Vector3 last_spine2_pos = Vector3::Zero();
Vector3 last_spine1_pos = Vector3::Zero();
Vector3 last_l_upperarm_pos = Vector3::Zero();
Vector3 last_l_forearm_pos = Vector3::Zero();
Vector3 last_l_hand_pos = Vector3::Zero();
Vector3 last_r_upperarm_pos = Vector3::Zero();
Vector3 last_r_forearm_pos = Vector3::Zero();
Vector3 last_r_hand_pos = Vector3::Zero();
Vector3 last_pelvis_pos = Vector3::Zero();
Vector3 last_l_knee_pos = Vector3::Zero();
Vector3 last_l_foot_pos = Vector3::Zero();
Vector3 last_r_knee_pos = Vector3::Zero();
Vector3 last_r_foot_pos = Vector3::Zero();
Vector3 last_head = Vector3::Zero();
Vector3 last_neck = Vector3::Zero();
Vector3 last_spine4 = Vector3::Zero();
Vector3 last_spine3 = Vector3::Zero();
Vector3 last_spine2 = Vector3::Zero();
Vector3 last_spine1 = Vector3::Zero();
Vector3 last_l_upperarm = Vector3::Zero();
Vector3 last_l_forearm = Vector3::Zero();
Vector3 last_l_hand = Vector3::Zero();
Vector3 last_r_upperarm = Vector3::Zero();
Vector3 last_r_forearm = Vector3::Zero();
Vector3 last_r_hand = Vector3::Zero();
Vector3 last_pelvis = Vector3::Zero();
Vector3 last_l_knee = Vector3::Zero();
Vector3 last_l_foot = Vector3::Zero();
Vector3 last_r_knee = Vector3::Zero();
Vector3 last_r_foot = Vector3::Zero();
uintptr_t shader;
DWORD64 liluzivert = NULL;

#define minm( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#define maxx( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
float LastUpdate = 0.f;
namespace BulletTP {
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
			velocity -= velocity * (drag * num);
			travelTime -= num2;
		}
		int num3 = int(travelTime / num);
		for (int i = 0; i < num3; i++)
		{
			prevPosition = position;
			prevVelocity = velocity;
			position += velocity * num;
			velocity += gravity * num;
			velocity -= velocity * (drag * num);
		}
		partialTime = travelTime - num * (float)num3;
		if (partialTime > 0)
		{
			prevPosition = position;
			prevVelocity = velocity;
			position += velocity * partialTime;
		}
	}
	float CalculateBulletRadius(float distToTarget, float num10, float num11, float boundsPadding) {
		float num12 = boundsPadding + num10 * num11;
		return num12;
	}
	bool BulkaTP(Projectile* projectile, float deltaTime)
	{
		if (projectile->isAuthoritative())
		{
			auto playerProjectileUpdate = (PlayerProjectileUpdate*)methods::object_new(il2cpp::_init_class(("PlayerProjectileUpdate"), ("ProtoBuf")));
			if (vars::combat::bullet_tp) {

				if (auto transform = target_player->transform_(head)) {
					 
					HitTest* hitTest = reinterpret_cast<HitTest*>(projectile->hitTest());
					Vector3 aa, bb;

					bool flag18 = !(projectile->projectileID());
					if (!flag18)
					{
						bool flag22 = projectile->integrity() <= 0.f;
						if (!flag22)
						{
							auto targetPos = transform->position();
							auto projPos = projectile->transform()->position();
							auto distToTarget = targetPos.distance(projPos);
							float num = Mathf::Clamp(projectile->traveledTime(), 0.f, 8.f);
							float num2 = 1.f + 0.5f;
							float projectile_clientframes = 2.f;
							float projectile_serverframes = 2.f;
							float num3 = Mathx::Decrement(projectile->launchTime());
							float num4 = Mathf::Clamp(Mathx::Increment(Time::realtimeSinceStartup()) - num3, 0.f, 8.f);
							float num5 = num;
							float num7 = Mathf::Min(num4, num5);
							float num8 = projectile_clientframes / 60.f;
							float num9 = projectile_serverframes * Mathx::Max(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());

							float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;

							float num10 = (desyncTime + num7 + num8 + num9) * num2;
							float num11 = target_player->MaxVelocity() + target_player->GetParentVelocity().Magnitude();
							float num12 = target_player->BoundsPadding() + num10 * num11;
							float num13 = distToTarget;
							bool flag64 = num13 > num12;

							float bulletRadius = CalculateBulletRadius(distToTarget, num10, num11, target_player->BoundsPadding());

							auto transform1 = reinterpret_cast<BasePlayer*>(target_player)->get_bone_pos(head);
							Quaternion q;
							static float r = 1.00f, g = 0.00f, b = 1.00f;
							static int cases = 0;
							switch (cases) {
							case 0: { r -= 0.004f; if (r <= 0) cases += 1; break; }
							case 1: { g += 0.004f; b -= 0.004f; if (g >= 1) cases += 1; break; }
							case 2: { r += 0.004f; if (r >= 1) cases += 1; break; }
							case 3: { b += 0.004f; g -= 0.004f; if (b >= 1) cases = 0; break; }
							default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
							}
							if (vars::visuals::onan)
							{
								if (vars::visuals::ponan == 0)
								{
									DDraw::Sphere(transform1, bulletRadius, Color(1.f, 1.f, 1.f, 255.f), 0.01f, false);
								}
								if (vars::visuals::ponan == 1)
								{
									DDraw::SphereGizmoZV(transform1, bulletRadius, Color(vars::colors::colsphere[0], vars::colors::colsphere[1], vars::colors::colsphere[2], 255.f), 0.01f, false, true);
								}
								if (vars::visuals::ponan == 2)
								{
									DDraw::Box(transform1, bulletRadius, Color(1.f, 1.f, 1.f, 255.f), 0.01f, false);
								}
							}
							if (vars::combat::BulletTeleportGradient)
							{
								if (vars::visuals::ponan == 0)
								{
									DDraw::Sphere(transform1, bulletRadius, Color(r, g, b, g), 0.01f, false);
								}
								if (vars::visuals::ponan == 1)
								{
									DDraw::SphereGizmoZV(transform1, bulletRadius, Color(r, g, b ,g), 0.01f, false, true);
								}
								if (vars::visuals::ponan == 2)
								{
									DDraw::Box(transform1, bulletRadius, Color(r, g, b, g), 0.01f, false);
								}
							}
							HitTest* hTest = projectile->hitTest();


							if (distToTarget <= bulletRadius)
							{
								if (GamePhysics::LineOfSight_(target_player->get_bone_pos(spine2), projectile->currentPosition(), LayerMasks::ProjectileLineOfSightCheckTerrain, 0.f) &&
									GamePhysics::LineOfSight_(target_player->get_bone_pos(head), projectile->currentPosition(), LayerMasks::ProjectileLineOfSightCheckTerrain, 0.f))
								{
									auto newPos = Vector3::move_towards(projectile->transform()->position(), targetPos, 1.0f);
									Ray r(projectile->transform()->position(), newPos - projectile->currentPosition());
									hitTest->AttackRay() = r;
									hitTest->HitTransform() = transform;
									hitTest->HitEntity() = target_player;
									hitTest->HitPoint() = transform->InverseTransformPoint(newPos);
									hitTest->HitNormal() = transform->InverseTransformDirection(projectile->transform()->position());
									hitTest->DidHit() = true;
									hitTest->HitDistance() = distToTarget;
									hitTest->MaxDistance() = 999.f;
									projectile->DoHit(hitTest, newPos, hitTest->HitNormalWorld());
								}


							}
							return true;
						}
					}
				}
			}

		}

	}
	bool BulletTP(Projectile* instance, float deltaTime)
	{

	}

	bool STW(Projectile* instance, Vector3 NextCurrentPosition, Vector3 CurrentPosition, Vector3 CurrentVelocity, float deltaTime)
	{
		while (true) { // stw by vidodoggy / .banqai    for help dm
			Vector3 aa; Vector3 bb;

			BasePlayer* targetPlayer = target_player;
			auto playerProjectileUpdate = (PlayerProjectileUpdate*)methods::object_new(il2cpp::_init_class(("PlayerProjectileUpdate"), ("ProtoBuf")));

			if (instance->projectileID() == 0)
				return false;

			if (instance->integrity() <= 0.f)
				return false;

			if (!targetPlayer)
				return false;

			auto Line = NextCurrentPosition - CurrentPosition; // линия с глаз
			auto LineLength = Line.UnityMagnitude(); //
			Line.UnityNormalize(); //

			//auto CenterPosition = targetPlayer->PivotPoint(); //Vector3(0.9f, 0.9f, 0.f)
			auto CenterPosition = targetPlayer->PivotPoint(); //Vector3(0.9f, 0.9f, 0.f)
			auto v = CenterPosition - CurrentPosition;
			auto d = v.DotSero(Line);

			if (d < 0.0f)
			{
				d = 0.0f;
			}
			else if (d > LineLength)
			{
				d = LineLength;
			}

			auto OriginalClosestPointOnLine = CurrentPosition + Line * d;
			auto ClosestPointOnLine = OriginalClosestPointOnLine;
			//auto ClosestPoint = utils::ClosestPoint(targetPlayer, ClosestPointOnLine);
			auto ClosestPoint = utils::ClosestPoint(targetPlayer, ClosestPointOnLine);

			auto OriginalDistance = targetPlayer->Distance(ClosestPointOnLine); // дистанция
			auto Distance = OriginalDistance;

			Vector3 traveledThisUpdate = instance->currentVelocity() * deltaTime;

			Vector3 HitPointWorld = ClosestPoint; //новая позиция пули

			Vector3 Hitbox = targetPlayer->transform()->position() + Vector3(0, 1.49f, 0);
			Vector3 Dir_ = Hitbox - instance->currentPosition();

			RaycastHit hitInfo;
			if (!GamePhysics::Trace(Ray(instance->currentPosition(), instance->currentVelocity().Normalized()), 0.f, &hitInfo, traveledThisUpdate.Length() + 1.f, LayerMasks::Terrain | LayerMasks::Construction | LayerMasks::World))
			{
				break;
			}

			if (Distance > 1.2f)
			{
				auto endPositionTrajectoryUsage = Distance - 1.2f + 0.01f;
				auto amountNeeded = endPositionTrajectoryUsage / Distance;
				auto direction = HitPointWorld + ClosestPointOnLine;
				auto newPosition = ClosestPointOnLine + (direction * amountNeeded);

				if (ClosestPointOnLine.Distance(newPosition) > 1.f || !GamePhysics::LineOfSight(ClosestPointOnLine, newPosition, 10551296, 0.f))
					return false;

				ClosestPointOnLine = newPosition;
				Distance = targetPlayer->Distance(ClosestPointOnLine); // реги
			}

			if (Distance > 1.f)
			{
				auto playerDistanceUsage = minm(0.19f, Distance - 1.f);
				auto amountNeeded = 1.f - playerDistanceUsage / Distance;
				auto direction = HitPointWorld + ClosestPointOnLine;
				auto newPosition = ClosestPointOnLine + (direction * amountNeeded);// реги

				HitPointWorld = newPosition;
			}

			auto LPlayer = LocalPlayer::Entity();

			instance->previousPosition() = instance->currentPosition(); //сверка прожектайл
			instance->currentPosition() = OriginalClosestPointOnLine;
			instance->traveledDistance() += instance->previousPosition().Distance(instance->currentPosition());
			instance->traveledTime() += instance->previousPosition().Distance(instance->currentPosition()) / CurrentVelocity.Length();

			if (playerProjectileUpdate)
			{
				playerProjectileUpdate->projectileID() = instance->projectileID();
				playerProjectileUpdate->travelTime() = instance->traveledTime();
				playerProjectileUpdate->curVelocity() = instance->currentVelocity();
				playerProjectileUpdate->curPosition() = instance->currentPosition();

				Vector3 position2 = instance->currentPosition();
				Vector3 curPosition = playerProjectileUpdate->curPosition();
				Vector3 b2 = (curPosition - position2).UnityNormalize_Sero() * 0.01f;

				int num14 = 2162688;
				num14 |= 8388608;
				num14 |= 134217728;

				if (!GamePhysics::LineOfSight_(position2 - b2, curPosition + b2, num14, 0.f))
				{
					return false;
				}

				LocalPlayer::Entity()->SPU(playerProjectileUpdate); // короче реги
				RPC_Counter.Increment();

				((PlayerProjectileUpdate*)playerProjectileUpdate)->curPosition() = instance->currentPosition() + (Dir_.Normalized() * 0.97f);

				LocalPlayer::Entity()->SPU(playerProjectileUpdate); //
			}

			instance->previousPosition() = instance->currentPosition();
			instance->currentPosition() = ClosestPointOnLine;
			instance->traveledDistance() += instance->previousPosition().Distance(instance->currentPosition());
			instance->traveledTime() += instance->previousPosition().Distance(instance->currentPosition()) / CurrentVelocity.Length();

			if (playerProjectileUpdate)
			{
				playerProjectileUpdate->projectileID() = instance->projectileID();
				playerProjectileUpdate->travelTime() = instance->traveledTime();
				playerProjectileUpdate->curVelocity() = instance->currentVelocity();
				playerProjectileUpdate->curPosition() = instance->currentPosition();

				Vector3 position2 = instance->currentPosition();
				Vector3 curPosition = playerProjectileUpdate->curPosition();
				Vector3 b2 = (curPosition - position2).UnityNormalize_Sero() * 0.01f;

				int num14 = 2162688;
				num14 |= 8388608;
				num14 |= 134217728;

				if (!GamePhysics::LineOfSight_(position2 - b2, curPosition + b2, num14, 0.f))
				{
					return false;
				}

				LocalPlayer::Entity()->SPU(playerProjectileUpdate);
				RPC_Counter.Increment();

				((PlayerProjectileUpdate*)playerProjectileUpdate)->curPosition() = instance->currentPosition() + (Dir_.Normalized() * 0.97f);

				LocalPlayer::Entity()->SPU(playerProjectileUpdate);
			}

			HitTest* hTest = instance->hitTest();

			instance->transform()->set_position(HitPointWorld);

			Ray ray = Ray(instance->currentPosition(), (HitPointWorld - instance->currentPosition()).Normalized());

			SimulateProjectile(instance->currentPosition(), instance->currentVelocity(), instance->tumbleSpeed(), maxx(instance->traveledTime() - instance->closeFlybyDistance(), 0), Physics::get_gravity() * instance->gravityModifier(), instance->drag(), aa, bb);

			hTest->AttackRay().origin = hitInfo.point;
			hTest->AttackRay().dir = instance->currentVelocity().Normalized().Normalized();
			hTest->HitTransform() = targetPlayer->transform_(head);
			hTest->HitEntity() = targetPlayer;
			hTest->HitPoint() = hTest->HitTransform()->InverseTransformPoint(HitPointWorld);
			hTest->HitNormal() = hTest->HitTransform()->InverseTransformDirection(instance->transform()->position());
			hTest->BestHit() = true;
			hTest->MultiHit() = true;
			hTest->DidHit() = true;
			hTest->HitDistance() = Distance;
			hTest->MaxDistance() = 999.f;
			hTest->Forgiveness() = 1.f;
			instance->DoHit(hTest, hTest->HitPoint(), hTest->HitNormal());
			instance->Update();
		}

		return true;
	}

}

float CalculateBulletRadius(float distToTarget, float num10, float num11, float boundsPadding) {
	float num12 = boundsPadding + num10 * num11;
	return num12;
}


namespace hk {
	namespace exploit {
		void ProjectileUpdate_hk(Projectile* projectile) {
			static float r = 1.00f, g = 0.00f, b = 1.00f;
			static int cases = 0;
			switch (cases) {
			case 0: { r -= 0.004f; if (r <= 0) cases += 1; break; }
			case 1: { g += 0.004f; b -= 0.004f; if (g >= 1) cases += 1; break; }
			case 2: { r += 0.004f; if (r >= 1) cases += 1; break; }
			case 3: { b += 0.004f; g -= 0.004f; if (b >= 1) cases = 0; break; }
			default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
			}
			if (vars::weapons::thick_bullet)
				projectile->thickness() = 0.7f;
			else
				projectile->thickness() = 0.1f;
			if (vars::weapons::scale) {
				projectile->transform()->set_scale({ vars::weapons::bullet_sizex, vars::weapons::bullet_sizey, vars::weapons::bullet_sizez });
			}
			if (vars::weapons::test && projectile->isAuthoritative()) {
				DDraw::SphereGizmoZV(projectile->currentPosition(), 0.19f, Color(r, g, b, g), 0.008f, false, false);
			}
			if (vars::weapons::test2 && !projectile->isAuthoritative()) {
				DDraw::SphereGizmoZV(projectile->currentPosition(), 0.19f, Color(r, g, b, g), 0.008f, false, false);
			}

			return original_Update(projectile);
		}
		void DoMovement(Projectile* projectile, float deltaTime) {
			BaseProjectile* held = held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
			auto currentVelocity = projectile->currentVelocity() * deltaTime;
			auto intmag = currentVelocity.Magnitude();
			auto intnum = 1.f / intmag;
			auto speed = currentVelocity * intnum;
			auto lineposition = projectile->currentPosition() + speed * currentVelocity.Magnitude();

			static float r = 1.00f, g = 0.00f, b = 1.00f;
			static int cases = 0;
			switch (cases) {
			case 0: { r -= 0.004f; if (r <= 0) cases += 1; break; }
			case 1: { g += 0.004f; b -= 0.004f; if (g >= 1) cases += 1; break; }
			case 2: { r += 0.004f; if (r >= 1) cases += 1; break; }
			case 3: { b += 0.004f; g -= 0.004f; if (b >= 1) cases = 0; break; }
			default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
			}

			if (projectile->isAuthoritative() && vars::debug::bullettracer) {
				if (vars::stuff::bttype == 0)
				{
					DDraw::Line(projectile->currentPosition(), lineposition, Color(0.9, 0, 0, 0), 0.9f, false, false);
				}
				if (vars::stuff::bttype == 1)
				{
					DDraw::Line(projectile->currentPosition(), lineposition, Color(r, g, b, g), 0.9f, false, false);
				}
				if (vars::stuff::bttype == 2)
				{
					float a = Random::Range(0.f, 255.f);
					float d = Random::Range(0.f, 255.f);
					float c = Random::Range(0.f, 255.f);
					DDraw::Line(projectile->currentPosition(), lineposition, Color(a, d, c, 0), 1.f, true, true);
				}
				if (vars::stuff::bttype == 3)
				{
					DDraw::Line(projectile->currentPosition(), lineposition, Color(vars::colors::mov_line.x, vars::colors::mov_line.y, vars::colors::mov_line.z, 255), 1.f, true, true);
				}
			}
			if (!projectile->isAuthoritative() &&  vars::debug::bullettartracer) {
				if (vars::stuff::bttype == 0)
				{
					DDraw::Line(projectile->currentPosition(), lineposition, Color(0.9, 0, 0, 0), 0.9f, false, false);
				}
				if (vars::stuff::bttype == 1)
				{
					DDraw::Line(projectile->currentPosition(), lineposition, Color(r, g, b, g), 0.9f, false, false);
				}
			}
			if (projectile->isAuthoritative( ) && vars::combat::always_heli_rotor) {
				if (InGame::stor::closestHeli != NULL) {
					Vector3 tar = reinterpret_cast<BaseEntity*>(InGame::stor::closestHeli)->transform( )->position( );
					if (utils::LineOfSight(tar, projectile->currentPosition( )) && Math::Distance_3D(projectile->currentPosition( ), tar) < 35.0f) {
						if (projectile->traveledDistance( ) > 35.0f) {
							Transform* transform = reinterpret_cast<BaseEntity*>(InGame::stor::closestHeli)->transform( );

							HitTest* hitTest = projectile->hitTest( );
							hitTest->DidHit( ) = true;
							hitTest->HitEntity() = (BaseEntity*)InGame::stor::closestHeli;
							hitTest->HitTransform( ) = transform;
							hitTest->HitPoint( ) = transform->InverseTransformPoint(projectile->currentPosition( ));
							hitTest->HitNormal( ) = transform->InverseTransformDirection(projectile->currentPosition( ));
							hitTest->AttackRay( ) = Ray(projectile->currentPosition( ), tar - projectile->currentPosition( ));
							projectile->DoHit(hitTest, hitTest->HitPointWorld( ), hitTest->HitNormalWorld( ));
							return;

						}
					}
				}
			}
			if (vars::combat::bullet_tp) {

				BulletTP::BulkaTP(projectile, deltaTime);
			}
			if (vars::combat::stw) {
				Vector3 a = projectile->currentVelocity() * deltaTime;
				float magnitude = a.Length();
				float num2 = 1 / magnitude;
				Vector3 vec2 = a * num2;
				Vector3 vec3 = projectile->currentPosition() + vec2 * magnitude;

				BulletTP::STW(projectile, vec3, projectile->currentPosition(), projectile->currentVelocity(), deltaTime);
				RPC_Counter.Reset();
			}

			return original_domovement(projectile, deltaTime);
		}
		bool Refract(Projectile* prj, uint32_t seed, Vector3 point, Vector3 normal, float resistancePower) {
			if (vars::combat::tree_reflect) {
				float gravity;
				if (target_player != nullptr && target_player->IsValid() && LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) {
					gravity = GetGravity(LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo());
					a::Prediction(prj->currentPosition(), target_player->GetBoneByID(spine1), target_player->newVelocity(), GetBulletSpeed(), gravity);
					prj->currVel(((target_player)->GetBoneByID(head) - prj->currentPosition()) * (GetBulletSpeed() / 150.f));
					prj->currPos(prj->currentPosition() + prj->currentVelocity().Normalized() * 0.001f);
				}
			}
			else {
				return original_refract(prj, seed, point, normal, resistancePower);
			}
		}
	}
	namespace misc {
		float LastUpdate = 0.f;

		void __fastcall SetFlying(ModelState* a1, bool a2) { }
		void SendClientTick(BasePlayer* baseplayer) {
			if (!baseplayer) return baseplayer->SendClientTick();
			if (baseplayer->userID() == LocalPlayer::Entity()->userID()) {
				Vector3 current = baseplayer->transform()->position();
				Vector3 old = baseplayer->lastSentTick()->position();
				Vector3 vector4 = (baseplayer->transform()->position() - baseplayer->lastSentTick()->position());
				Vector3 overrided = Vector3(current.x, current.y, current.z);
				if (vars::misc::fly_auto_stopper && VFlyhack >= (VMaxFlyhack - 1.5f))
				{
					overrided = Vector3(overrided.x, current.y < old.y ? (current.y - 0.3f) : old.y, overrided.z);
				}
				if (vars::misc::fly_auto_stopper && HFlyhack >= (HMaxFlyhack - 2.7f))
				{
					overrided = Vector3(old.x, overrided.y, old.z);
				}
				if (vars::misc::fly_auto_stopper && HFlyhack >= (HMaxFlyhack - 2.7f) ||
					vars::misc::fly_auto_stopper && VFlyhack >= (VMaxFlyhack - 1.5f))
				{
					if (overrided != current)
						baseplayer->movement()->TeleportTo(overrided);
				}



				if (vars::misc::bhop) {
					static float b = 5.0f;
					if (b >= 5.0f) {
						float radius = baseplayer->GetRadius();
						float height = baseplayer->GetHeight(false);
						Vector3 vector = (baseplayer->lastSentTick()->position() + baseplayer->transform()->position()) * 0.5f;
						float flyhack_extrusion = 0.25f;
						Vector3 vector2 = vector + Vector3(0.0f, radius - flyhack_extrusion, 0.0f);
						Vector3 vector3 = vector + Vector3(0.0f, height - radius, 0.0f);
						float radius2 = radius - 0.05f;
						bool isgrounded = GamePhysics::CheckCapsule(vector2, vector3, radius2, 1503731969, GamePhysics::QueryTriggerInteraction::Ignore);
						if (isgrounded) {
							baseplayer->movement()->Jump(baseplayer->modelState());
							b = 0.0f;
						}
					}
					b++;
				}
				if (vars::misc::local_bones)
				{
					last_head_pos = LocalPlayer::Entity()->GetBoneByID(head);// baseplayer->bones()->head->position;
					last_neck_pos = LocalPlayer::Entity()->GetBoneByID(neck);//baseplayer->bones()->neck->position;
					last_spine4_pos = LocalPlayer::Entity()->GetBoneByID(spine4);// baseplayer->bones()->spine4->position;
					last_spine1_pos = LocalPlayer::Entity()->GetBoneByID(spine1);//baseplayer->bones()->spine1->position;
					last_l_upperarm_pos = LocalPlayer::Entity()->GetBoneByID(l_upperarm); //baseplayer->bones()->l_upperarm->position;
					last_l_forearm_pos = LocalPlayer::Entity()->GetBoneByID(l_forearm);//baseplayer->bones()->l_forearm->position;
					last_l_hand_pos = LocalPlayer::Entity()->GetBoneByID(l_hand);//baseplayer->bones()->l_hand->position;
					last_r_upperarm_pos = LocalPlayer::Entity()->GetBoneByID(r_upperarm);//baseplayer->bones()->r_upperarm->position;
					last_r_forearm_pos = LocalPlayer::Entity()->GetBoneByID(r_forearm);//baseplayer->bones()->r_forearm->position;
					last_r_hand_pos = LocalPlayer::Entity()->GetBoneByID(r_hand);//baseplayer->bones()->r_hand->position;
					last_pelvis_pos = LocalPlayer::Entity()->GetBoneByID(pelvis);//baseplayer->bones()->pelvis->position;
					last_l_knee_pos = LocalPlayer::Entity()->GetBoneByID(l_knee); //baseplayer->bones()->l_knee->position;
					last_l_foot_pos = LocalPlayer::Entity()->GetBoneByID(l_foot);// baseplayer->bones()->l_foot->position;
					last_r_knee_pos = LocalPlayer::Entity()->GetBoneByID(r_knee);//baseplayer->bones()->r_knee->position;
					last_r_foot_pos = LocalPlayer::Entity()->GetBoneByID(r_foot);//baseplayer->bones()->r_foot->position;
				}
				if (vars::misc::TargetBones)
				{
					BasePlayer* target_player = reinterpret_cast<BasePlayer*>(target_player);
					last_head = target_player->GetBoneByID(head);// baseplayer->bones()->head->position;
					last_neck = target_player->GetBoneByID(neck);//baseplayer->bones()->neck->position;
					last_spine4 = target_player->GetBoneByID(spine4);// baseplayer->bones()->spine4->position;
					last_spine1 = target_player->GetBoneByID(spine1);//baseplayer->bones()->spine1->position;
					last_l_upperarm = target_player->GetBoneByID(l_upperarm); //baseplayer->bones()->l_upperarm->position;
					last_l_forearm = target_player->GetBoneByID(l_forearm);//baseplayer->bones()->l_forearm->position;
					last_l_hand_pos = target_player->GetBoneByID(l_hand);//baseplayer->bones()->l_hand->position;
					last_r_upperarm = target_player->GetBoneByID(r_upperarm);//baseplayer->bones()->r_upperarm->position;
					last_r_forearm = target_player->GetBoneByID(r_forearm);//baseplayer->bones()->r_forearm->position;
					last_r_hand = target_player->GetBoneByID(r_hand);//baseplayer->bones()->r_hand->position;
					last_pelvis = target_player->GetBoneByID(pelvis);//baseplayer->bones()->pelvis->position;
					last_l_knee = target_player->GetBoneByID(l_knee); //baseplayer->bones()->l_knee->position;
					last_l_foot = target_player->GetBoneByID(l_foot);// baseplayer->bones()->l_foot->position;
					last_r_knee = target_player->GetBoneByID(r_knee);//baseplayer->bones()->r_knee->position;
					last_r_foot = target_player->GetBoneByID(r_foot);//baseplayer->bones()->r_foot->position;
				}
			}
			return baseplayer->SendClientTick();
		}

		void ClientInput(BasePlayer* plly, ModelState* ModelState) { 

			if (!plly) return original_clientinput(plly, ModelState);
			if (!plly->IsValid()) return original_clientinput(plly, ModelState);

			if (vars::misc::spiderman)
			{
				LocalPlayer::Entity()->movement()->groundAngle() = 0.f;
				LocalPlayer::Entity()->movement()->groundAngleNew() = 0.f;
			}

			if (plly->userID() == LocalPlayer::Entity()->userID()) {

				auto held = plly->GetHeldEntity<BaseProjectile>();
				if (vars::misc::TeloportTopPlayer && GetAsyncKeyState(vars::keys::TeleportTopPlayer) && Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), target_player->get_bone_pos(head)) < 2.5f)
				{
					Vector3 curVel = LocalPlayer::Entity()->movement()->body()->velocity();
					Vector3 curVel2 = target_player->transform_(head)->position();

					plly->movement()->TeleportTo(curVel2);
				}
				if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key))
					plly->clientTickInterval() = vars::combat::DesynctTime;
				else {
					vars::stuff::best_target = Vector3(0, 0, 0);
					switch (vars::misc::fakelag)
					{
					case 0:
						plly->clientTickInterval() = 0.05f;

						break;
					case 1: //basic
						plly->clientTickInterval() = 0.4f;
						break;
					case 2: //doubletap

						float v = 0.5f;
						if (held)
							if (held->repeatDelay() > 0.01f)
								v = (held->repeatDelay() * 2.0f);
						if (plly->clientTickInterval() == 0.2f)
							plly->clientTickInterval() = v;
						else
							plly->clientTickInterval() = 0.2f;
						break;
					}
				}
				BaseMelee* melee = LocalPlayer::Entity()->GetHeldEntity<BaseMelee>();
				DWORD64 Mozgi = 0;

				//auto LoadAsset = reinterpret_cast<DWORD64(*)(DWORD64, Str, DWORD64)>(0);
				//auto Instantiate = reinterpret_cast<GameObject * (*)(DWORD64, Vector3, Quaternion)>(0);
				//LoadAsset = reinterpret_cast<DWORD64(*)(DWORD64, Str, DWORD64)>(*reinterpret_cast<DWORD64*>(il2cpp::method((uintptr_t)(("AssetBundle"), ("LoadAsset_Internal"), 2, ("name"), ("UnityEngine"), 1))));
				//Instantiate = reinterpret_cast<GameObject * (*)(DWORD64, Vector3, Quaternion)>(*reinterpret_cast<DWORD64*>(il2cpp::method((uintptr_t)(("Object"), ("Instantiate"), 3, (""), ("UnityEngine")))));
				//if (vars::visuals::visded)
				//{
				//	if (vars::visuals::Allkillefect == 0)
				//	{

				//		if (target_player)
				//		{
				//			if (!target_player->IsDead())
				//			{
				//				DWORD64 LogoPng = 0;
				//				Vector3 playerPos = target_player->get_bone_pos(head);
				//				//liluzivert = LoadAsset(Mozgi, (L"BrainPizdec"), il2cpp::TypeGetObject(("UnityEngine"), ("GameObject")));
				//				//Instantiate(liluzivert, playerPos, target_player->eyes()->get_rotation());
				//				//reinterpret_cast<void(*)(Str, DWORD64)>(InGame::stor::gBase + 0x69F260)(Str(L"assets/bundledassets/pressf/brain/source/brain/brainpizdec.prefab"), liluzivert);
				//				liluzivert = LoadAsset(LogoPng, (L"Skull"), il2cpp::TypeGetObject(("UnityEngine"), ("GameObject")));
				//				Instantiate(liluzivert, playerPos, target_player->eyes()->get_rotation());
				//				reinterpret_cast<void(*)(Str, DWORD64)>(InGame::stor::gBase + 0x69F260)(Str(L"assets/skull.prefab"), liluzivert);
				//			}
				//		}
				//	}
				//}
				if (held) {
					BaseProjectile* _held = _held = plly->GetHeldEntity<BaseProjectile>();

					if (vars::weapons::huiznaet)
					{
						int cout = _held->primaryMagazine()->contents();
						std::cout << "Puji: " << cout << std::endl;
					}


					if (vars::weapons::no_sway && held->class_name_hash() != STATIC_CRC32("BaseMelee")) {
						held->aimSway() = 0.f;
						held->aimSwaySpeed() = 0.f;
					}
					if (vars::weapons::automatic)
						held->automatic() = true;
					int reapetdelaycache = 0;
					if (vars::weapons::rapidfire) {
						if (reapetdelaycache == 0)
							reapetdelaycache = held->repeatDelay();
						held->repeatDelay() = 0.07f;
					}
					Vector3 target;
					if (vars::misc::sphere) {
						if (vars::misc::Sphera == 0)
						{

							RaycastHit hitInfo;
							Quaternion q;
							bool valid = Physics::Raycast(LocalPlayer::Entity()->eyes()->position(), LocalPlayer::Entity()->eyes()->BodyForward(), &hitInfo, 400.f, 256 | 2048 | 65536 | 1073741824 | 8388608 | 2097152 | 4194304 | 67108864 | 134217728 | 33554432 | 32768 | 8192 | 512 | 1, QueryTriggerInteraction::Ignore);
							if (valid) {
								DDraw::Sphere(hitInfo.point, 0.3f, Color(vars::colors::colsphere[0], vars::colors::colsphere[1], vars::colors::colsphere[2], 255.f), 0.01f, false);
							}

						}
						if (vars::misc::Sphera == 1)
						{
							RaycastHit hitInfo;
							Quaternion q;
							bool valid = Physics::Raycast(LocalPlayer::Entity()->eyes()->position(), LocalPlayer::Entity()->eyes()->BodyForward(), &hitInfo, 400.f, 256 | 2048 | 65536 | 1073741824 | 8388608 | 2097152 | 4194304 | 67108864 | 134217728 | 33554432 | 32768 | 8192 | 512 | 1, QueryTriggerInteraction::Ignore);
							if (valid) {
								DDraw::SphereGizmoZV(hitInfo.point, 0.3f, Color(vars::colors::colsphere[0], vars::colors::colsphere[1], vars::colors::colsphere[2], 255.f), 0.01f, false, true);
							}
						}
						if (vars::misc::Sphera == 2)
						{
							RaycastHit hitInfo;
							Quaternion q;
							bool valid = Physics::Raycast(LocalPlayer::Entity()->eyes()->position(), LocalPlayer::Entity()->eyes()->BodyForward(), &hitInfo, 400.f, 256 | 2048 | 65536 | 1073741824 | 8388608 | 2097152 | 4194304 | 67108864 | 134217728 | 33554432 | 32768 | 8192 | 512 | 1, QueryTriggerInteraction::Ignore);
							if (valid) {
								DDraw::Box(hitInfo.point, 0.4f, Color(vars::colors::colsphere[0], vars::colors::colsphere[1], vars::colors::colsphere[2], 255.f), 0.01f, false);
							}
						}
					}
					float lastShotTime = _held->lastShotTime() - GLOBAL_TIME;
					float reloadTime = _held->nextReloadTime() - GLOBAL_TIME;
					float desyncTime = (Time::realtimeSinceStartup() - plly->lastSentTickTime()) - 0.03125 * 3;
					if (w_last_syringe == 0.f) {
						w_last_syringe = LocalPlayer::Entity()->lastSentTickTime();
					}
					Item* weapon = LocalPlayer::Entity()->GetHeldItem();
					if (vars::misc::faster_healing && (weapon->info()->itemid() == 1079279582 || weapon->info()->itemid() == -2072273936) && LocalPlayer::Entity()->health() < 99) {
						BaseProjectile* ent = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
						if (LocalPlayer::Entity()->lastSentTickTime() > w_last_syringe + 0.7f) {
							ent->_ServerRPC(("UseSelf"));
							w_last_syringe = LocalPlayer::Entity()->lastSentTickTime();
						}
					}
					if (held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
						if (vars::combat::autoreload)
						{
							BaseProjectile* ent = plly->GetHeldEntity<BaseProjectile>();

							if (!did_reload)
								time_since_last_shot = (Time::fixedTime() - fixed_time_last_shot);

							if (just_shot && (time_since_last_shot > 0.2f))
							{
								ent->_ServerRPC(("StartReload"));
								ent->SendSignalBroadcast(BaseEntity::Signal::Reload);
								just_shot = false;
							}
							if (time_since_last_shot > (_held->reloadTime() - (_held->reloadTime() / 10))
								&& !did_reload)
							{
								ent->_ServerRPC(("Reload"));
								did_reload = true;
								time_since_last_shot = 0;
							}
						}
					}
					Projectile* projectile;

					if (target_player != nullptr && vars::combat::bullet_tp && vars::combat::Manipulator_shot_atBt) {
						Vector3 z = reinterpret_cast<BasePlayer*>(target_player)->get_bone_pos(head);
						Vector3 eye = vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key) ? vars::stuff::eyemani : LocalPlayer::Entity()->eyes()->position();

						if (!utils::LineOfSight(z, eye)) {
							auto transform = target_player->transform_(head);
							auto targetPos = transform->position();
							auto projPos = projectile->transform()->position();
							auto distToTarget = targetPos.distance(projPos);
							float num = Mathf::Clamp(projectile->traveledTime(), 0.f, 8.f);
							float num2 = 1.f + 0.5f;
							float projectile_clientframes = 2.f;
							float projectile_serverframes = 2.f;
							float num3 = Mathx::Decrement(projectile->launchTime());
							float num4 = Mathf::Clamp(Mathx::Increment(Time::realtimeSinceStartup()) - num3, 0.f, 8.f);
							float num5 = num;
							float num7 = Mathf::Min(num4, num5);
							float num8 = projectile_clientframes / 60.f;
							float num9 = projectile_serverframes * Mathx::Max(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());

							float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;

							float num10 = (desyncTime + num7 + num8 + num9) * num2;
							float num11 = target_player->MaxVelocity() + target_player->GetParentVelocity().Magnitude();
							float num12 = target_player->BoundsPadding() + num10 * num11;
							float num13 = distToTarget;
							bool flag64 = num13 > num12;
							float bulletRadius = CalculateBulletRadius(distToTarget, num10, num11, target_player->BoundsPadding());

							if (utils::LineOfSight(eye, z + Vector3(0, bulletRadius, 0)))
								vars::stuff::best_target = z + Vector3(0, bulletRadius, 0);
							if (!utils::LineOfSight(eye, z + Vector3(0, bulletRadius, 0)) && utils::LineOfSight(eye, z + Vector3(bulletRadius, 0, 0)))
								vars::stuff::best_target = z + Vector3(bulletRadius, 0, 0);
							if (!utils::LineOfSight(eye, z + Vector3(bulletRadius, 0, 0)) && utils::LineOfSight(eye, z + Vector3(-bulletRadius, 0, 0)))
								vars::stuff::best_target = z + Vector3(-bulletRadius, 0, 0);
							if (!utils::LineOfSight(eye, z + Vector3(-bulletRadius, 0, 0)) && utils::LineOfSight(eye, z + Vector3(0, 0, bulletRadius)))
								vars::stuff::best_target = z + Vector3(0, 0, bulletRadius);
							if (!utils::LineOfSight(eye, z + Vector3(0, 0, bulletRadius)) && utils::LineOfSight(eye, z + Vector3(0, 0, -bulletRadius)))
								vars::stuff::best_target = z + Vector3(0, 0, -bulletRadius);
						}
						else
							vars::stuff::best_target = Vector3(2, 0, 0);
					}
					else
						vars::stuff::best_target = Vector3(0, 0, 0);

					if (vars::combat::Manipulator_shot_atBt) {
						if (vars::stuff::best_target != Vector3(0, 0, 0))
						{
							target = vars::stuff::best_target;
						}
						else
						{
							target = reinterpret_cast<BasePlayer*>(target_player)->get_bone_pos(head);
						}
					}

					if (target_player) {
						if (vars::combat::hitscan) {
							if (vars::stuff::best_target != Vector3(0, 0, 0))
							{
								target = vars::stuff::best_target;
							}
							else
							{
								target = vars::combat::onal == 0 ? target_player->get_bone_pos(head) : target_player->get_bone_pos(spine1);
							}
						}
						else

							target = vars::combat::onal == 0 ? target_player->get_bone_pos(head) : target_player->get_bone_pos(spine1);
					}
					else
						target = reinterpret_cast<BasePlayer*>(target_player)->get_bone_pos(head);
					bool autoshoot_cheack = vars::combat::autoshoot_type == 1 ? vars::combat::autoshoot && vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key) : vars::combat::autoshoot;
					//if (autoshoot_cheack) {
					//	if (held && _held->class_name_hash() == STATIC_CRC32("BaseProjectile") || _held->class_name_hash() == STATIC_CRC32("BowWeapon"))
					//	{
					//		if (_held->HasAttackCooldown() || _held->nextAttackTime() >= Time::time() || _held->timeSinceDeploy() < _held->deployDelay()) {
					//		}
					//		else
					//		{
					//			if (!held->Empty()) {
					//				if (reloadTime < 1.0f && lastShotTime < -0.1f) {
					//					if (reinterpret_cast<BasePlayer*>(target_player) != nullptr && !LocalPlayer::Entity()->is_teammate((uintptr_t)reinterpret_cast<BasePlayer*>(target_player)) && reinterpret_cast<BasePlayer*>(target_player)->IsValid() && plly->HasPlayerFlag(PlayerFlags::Connected)/* && !did_reload*/) {
					//						if (utils::LineOfSight(target, plly->eyes()->position())) {
					//							Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
					//							DWORD64 active = weapon->entity(); 
					//							LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Attack, ("")); 
					//							_held->LaunchProjectile();
					//							_held->primaryMagazine()->contents()--;
					//							_held->UpdateAmmoDisplay();
					//							_held->ShotFired();
					//							_held->DidAttackClientside();
					//							_held->BeginCycle();
					//						}
					//					}
					//				}
					//			}
					//		}

					//	}
					//	if (melee && melee != nullptr && _held->class_name_hash() != STATIC_CRC32("BaseProjectile") || _held->class_name_hash() != STATIC_CRC32("BowWeapon") || _held->class_name_hash() != STATIC_CRC32("CrossBowWeapon") || held->class_name_hash() == STATIC_CRC32("BaseMelee")) {
					//		if (melee->canThrowAsProjectile()) {
					//			if (reinterpret_cast<BasePlayer*>(target_player) != nullptr && !LocalPlayer::Entity()->is_teammate((uintptr_t)reinterpret_cast<BasePlayer*>(target_player)) && reinterpret_cast<BasePlayer*>(target_player)->IsValid() && plly->HasPlayerFlag(PlayerFlags::Connected)/* && !did_reload*/) {
					//				if (melee->HasAttackCooldown() || melee->nextAttackTime() >= Time::time() || melee->timeSinceDeploy() < melee->deployDelay()) {
					//				}
					//				else
					//				{
					//					if (utils::LineOfSight(target, plly->eyes()->position())) {
					//						melee->DoThrow();
					//					}
					//				}
					//			}
					//		}
					//	}
					//}

					if (plly->userID() == LocalPlayer::Entity()->userID()) {
						if (vars::combat::autoshoot && GetAsyncKeyState(vars::keys::manipulated_key) || vars::combat::autoshoot && GetAsyncKeyState(vars::keys::manipulated_key) && vars::combat::hitscan || vars::combat::autoshoot && GetAsyncKeyState(vars::keys::manipulated_key)) {
							if (vars::combat::autoshoot_type == 0) {
								if (!held->Empty()) {
									if (_held && reloadTime < 1.f) {
										if (lastShotTime < -0.1f) {
											if (reinterpret_cast<BasePlayer*>(target_player) && !LocalPlayer::Entity()->is_teammate((uintptr_t)reinterpret_cast<BasePlayer*>(target_player)) && plly->get_flag(PlayerFlags::Connected)) {
												if (utils::LineOfSight(target, plly->eyes()->position())) {
													Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
													DWORD64 active = weapon->entity();
													LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Attack, (""));
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
								}
							}
						}

						if (vars::combat::instakill && vars::keys::manipulated_key && GetAsyncKeyState(vars::keys::instakill)) {
							if (!held->Empty()) {
								if (reinterpret_cast<BasePlayer*>(target_player) != nullptr && !LocalPlayer::Entity()->is_teammate((uintptr_t)reinterpret_cast<BasePlayer*>(target_player)) && reinterpret_cast<BasePlayer*>(target_player)->IsValid() && plly->get_flag(PlayerFlags::Connected)/* && !did_reload*/) {
									if (utils::LineOfSight(target, plly->eyes()->position())) {
										plly->clientTickInterval() = 0.99f;
										if (desyncTime > 0.75f) {
											Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
											DWORD64 active = weapon->entity();
											LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Attack, (""));
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
						}


						static bool alreadystartedReload = false;

						static bool alreadyReset = false;

						if (vars::weapons::compound && held->class_name_hash() == STATIC_CRC32("CompoundBowWeapon")) {
							reinterpret_cast<CompoundBowWeapon*>(held)->currentHoldProgress() = 1.5f;
						}

						GLOBAL_TIME = Time::time();
					}
				
			
			
					if (melee && melee != nullptr && _held->class_name_hash() != STATIC_CRC32("BaseProjectile") || _held->class_name_hash() != STATIC_CRC32("BowWeapon") || _held->class_name_hash() != STATIC_CRC32("CrossBowWeapon") || (weapon->info()->itemid() != 1079279582 || weapon->info()->itemid() != -2072273936))
					{
						auto melee_attack = [&](Vector3 pos, BaseEntity* p, BaseMelee* melee, bool is_player = false)
						{
							if (!p->IsValid() || !melee) return;
							if (melee->nextAttackTime() >= Time::fixedTime()) return;
							if (melee->deployDelay() > melee->timeSinceDeploy()) return;
							auto trans = is_player ? reinterpret_cast<BasePlayer*>(p)->transform_(head) : p->transform();
							if (!trans) return;
							Ray r = Ray(plly->eyes()->get_position(), (pos - LocalPlayer::Entity()->eyes()->get_position()).normalized());
							Vector3 origin = LocalPlayer::Entity()->eyes()->position();
							HitTest* hit = HitTest::New();
							hit->HitEntity() = p;
							hit->DidHit() = true;
							hit->MaxDistance() = melee->maxDistance();
							hit->HitTransform() = trans;
							hit->AttackRay() = r;
							hit->HitNormal() = trans->InverseTransformPoint(pos);
							hit->HitPoint() = trans->InverseTransformPoint(pos);
							melee->DoAttack(hit);
							melee->StartAttackCooldown(melee->repeatDelay());
						};
						if (vars::combat::silent_melee && reinterpret_cast<BasePlayer*>(target_player)->get_bone_pos(head).distance(LocalPlayer::Entity()->eyes()->position()) <= melee->maxDistance() + 2.0f)
						{
							melee_attack(reinterpret_cast<BasePlayer*>(target_player)->get_bone_pos(head), target_player, melee, true);
						}
						if (vars::misc::auto_farm) {
							BaseMelee* melee = LocalPlayer::Entity()->GetHeldEntity<BaseMelee>();
							auto jackhammerorchainsaw = LocalPlayer::Entity()->GetHeldEntity();
							if (melee && melee != nullptr && melee->class_name_hash() == STATIC_CRC32("BaseMelee") ||
								jackhammerorchainsaw && jackhammerorchainsaw != nullptr && melee->class_name_hash() == STATIC_CRC32("Jackhammer"))
							{
								if (vars::misc::auto_farm_ore)
								{
									BaseNetworkable* marker = BaseNetworkable::clientEntities()->FindClosest(STATIC_CRC32("OreHotSpot"), LocalPlayer::Entity(), melee->maxDistance() + 1.8f);
									if (marker && marker != nullptr && marker->transform()->position().distance(LocalPlayer::Entity()->eyes()->position()) <= melee->maxDistance() + 1.8f)
									{
										if (!(melee->nextAttackTime() >= Time::fixedTime())) {
											if (!(melee->deployDelay() > melee->timeSinceDeploy())) {
												Vector3 origin = LocalPlayer::Entity()->eyes()->position();
												Vector3 playerPos = marker->transform()->position();
												HitTest* hit = HitTest::New();
												hit->_HitEntity() = marker;
												hit->DidHit() = true;
												hit->MaxDistance() = melee->maxDistance();
												hit->HitTransform() = marker->transform();
												hit->AttackRay() = Ray(origin, origin + (playerPos - origin));
												hit->HitNormal() = marker->transform()->InverseTransformPoint(marker->transform()->position());
												hit->HitPoint() = marker->transform()->InverseTransformPoint(marker->transform()->position());
												melee->DoAttack(hit);
												melee->StartAttackCooldown(melee->repeatDelay());
											}
										}

									}
								}
								if (vars::misc::auto_farm_tree)
								{
									BaseNetworkable* TreeEntity = BaseNetworkable::clientEntities()->FindClosest(STATIC_CRC32("TreeEntity"), LocalPlayer::Entity(), melee->maxDistance() + 1.8f);
									if (TreeEntity && TreeEntity->transform()->position().distance(LocalPlayer::Entity()->eyes()->position()) <= melee->maxDistance() + 1.8f)
									{
										BaseNetworkable* tree = BaseNetworkable::clientEntities()->FindClosest(STATIC_CRC32("TreeMarker"), TreeEntity, melee->maxDistance() + 1.8f);
										if (tree && tree->transform()->position().distance(LocalPlayer::Entity()->eyes()->position()) <= melee->maxDistance() + 1.8f)
										{
											if (!(melee->nextAttackTime() >= Time::fixedTime())) {
												if (!(melee->deployDelay() > melee->timeSinceDeploy())) {
													Vector3 origin = LocalPlayer::Entity()->eyes()->position();
													Vector3 treepos = TreeEntity->transform()->position();
													treepos.y = origin.y;
													HitTest* hit = HitTest::New();
													hit->_HitEntity() = TreeEntity;
													hit->DidHit() = true;
													hit->HitMaterial_() = il2cpp::String::New(("Wood"));
													hit->MaxDistance() = melee->maxDistance();
													hit->HitTransform() = TreeEntity->transform();
													hit->AttackRay() = Ray(origin, treepos - origin);
													hit->HitNormal() = TreeEntity->transform()->InverseTransformPoint(treepos);
													hit->HitPoint() = TreeEntity->transform()->InverseTransformPoint(treepos);

													melee->DoAttack(hit);
													melee->StartAttackCooldown(melee->repeatDelay());
												}
											}

										}
									}

								}
							}
						}
					}
					if (vars::visuals::No_bobing)
					{
						if (auto ActiveModel = BaseViewModel::ActiveModel())
						{
							auto bob = ActiveModel->bob();

							auto lower = ActiveModel->lower();

							auto sway = ActiveModel->sway();

							bob->bobAmountRun() = 0.f;
							bob->bobAmountWalk() = 0.f;
							bob->bobSpeedRun() = 0.f;
							bob->bobSpeedWalk() = 0.f;
							lower->shouldLower() = false;
						}
					}

					if (vars::weapons::compound && held->class_name_hash() == STATIC_CRC32("CompoundBowWeapon")) {
						reinterpret_cast<CompoundBowWeapon*>(held)->currentHoldProgress() = 1.5f;
					}

				}
				else {
					did_reload = false;
					just_shot = true;
					fixed_time_last_shot = Time::fixedTime();
				}
				if (vars::misc::auto_pickup)
				{
					BaseEntity* collectibleEntity = BaseNetworkable::clientEntities()->FindClosest<BaseEntity*>(STATIC_CRC32("CollectibleEntity"), LocalPlayer::Entity(), 3.0f);
					if (collectibleEntity && collectibleEntity != nullptr && collectibleEntity != 0x0)
						collectibleEntity->_ServerRPC("Pickup");
				}
				float changeSpeed = 0.3f;
				float FOV = vars::misc::fov;
				if (GetAsyncKeyState(vars::keys::zoom))
				{

					if (GetAsyncKeyState(vars::keys::zoom))
					{
						float oldFOV = ConVar::Graphics::_fov();
						float newFOV = (oldFOV - 30.f) * changeSpeed;
						ConVar::Graphics::_fov() = newFOV;
					}
				}
				else
				{
					float zoomfov = ConVar::Graphics::_fov();
					float newFOV = zoomfov + (FOV - zoomfov) * changeSpeed;
					ConVar::Graphics::_fov() = newFOV;
				}
				if (vars::misc::zoom && GetAsyncKeyState(vars::keys::zoom))
				{
					float oldFOV = ConVar::Graphics::_fov();
					float newFOV = oldFOV + (15.f - oldFOV) * changeSpeed;
					ConVar::Graphics::_fov() = newFOV;
				}
				else
				{
					float zoomfov = ConVar::Graphics::_fov();
					float newFOV = zoomfov + (FOV - zoomfov) * changeSpeed;
					ConVar::Graphics::_fov() = newFOV;
				}
				if (vars::misc::custom_time)
					BasePlayer::Admintime() = vars::misc::time;
				if (vars::misc::AspectRatio)
					Camera::SetAspect(vars::misc::ratio);
				if (vars::misc::fakeadmin)
					plly->playerFlags() |= PlayerFlags::IsAdmin;
				float nextActionTime = 0, period = 1.4721, last_gesture_rpc = 0.f;;
				if (vars::misc::gesture > 0
					&& Time::fixedTime() > last_gesture_rpc + 0.35f)
				{
					switch (vars::misc::gesture) {
					case 0:
						break;
					case 1:
						LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("clap"));
						break;
					case 2:
						LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("friendly"));
						break;
					case 3:
						LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("thumbsdown"));
						break;
					case 4:
						LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("thumbsup"));
						break;
					case 5:
						LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("ok"));
						break;
					case 6:
						LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("point"));
						break;
					case 7:
						LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("shrug"));
						break;
					case 8:
						LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("victory"));
						break;
					case 9:
						LocalPlayer::Entity()->SendSignalBroadcast(BaseEntity::Signal::Gesture, ("wave"));
						break;
					}
					last_gesture_rpc = Time::fixedTime();
				}
				auto err = plly->GetHeldEntity<BaseProjectile>();
				auto ishak = plly->GetHeldEntity<BaseMelee>();
				auto playerPos = target_player->transform_(head)->position();
				auto distance = (int)Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), target_player->get_bone_pos(head));

				if (vars::misc::suicide && GetAsyncKeyState(vars::keys::suicide)) {
					LocalPlayer::Entity()->OnLand(-108.0001f);
				}
				GLOBAL_TIME = Time::time();
				if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key))
					plly->clientTickInterval() = 0.99f;
				else {
					plly->clientTickInterval() = 0.05f;
				}
				if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
					if (target_player)
					{
						other::find_manipulate_angle();
					}
				}
				else if (!m_manipulate.empty()) {
					m_manipulate = Vector3::Zero();
				}
				if (vars::weapons::minicopter_aim)
					if (plly->mounted())
						plly->mounted()->canWieldItems() = true;
				Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::Water, !vars::misc::jesus);
				Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::Tree, vars::misc::jesus);
				Physics::IgnoreLayerCollision((int)Layer::PlayerMovement, (int)Layer::AI, vars::misc::jesus);
				if (vars::visuals::skycolor)
				{
					UINT64 klass = read(InGame::stor::gBase + 43639072, UINT64);//TOD_Sky_c
					UINT64 static_fields = read(klass + 0xB8, UINT64);
					UINT64 instances = read(static_fields, UINT64);
					UINT64 List1 = read(instances + 0x10, UINT64);
					UINT64 TOD_Sky_ = read(List1 + 0x20, UINT64);

					auto days = *reinterpret_cast<DWORD64*>(TOD_Sky_ + 0x50);
					auto dsky_color = *reinterpret_cast<DWORD64*>(days + 0x28);
					auto clr = Color(vars::colors::sky_color.x, vars::colors::sky_color.y, vars::colors::sky_color.z, vars::misc::intensivity);
					auto dsky_gradient = *reinterpret_cast<DWORD64*>(dsky_color + 0x10);
					*reinterpret_cast<Color*>(dsky_gradient) = clr;

					auto nights = *reinterpret_cast<DWORD64*>(TOD_Sky_ + 0x58);
					auto nsky_color = *reinterpret_cast<DWORD64*>(nights + 0x28);
					auto nsky_gradient = *reinterpret_cast<DWORD64*>(nsky_color + 0x10);
					*reinterpret_cast<Color*>(nsky_gradient) = clr;

				}
			}
			float flyhack_forgiveness_interia = 10.0f;
			float flyhack_forgiveness = 1.0f;
			float flyhack_extrusion = 2.0f;
			bool flag = false;
			bool isInAir = false;
			Vector3 vector = (plly->lastSentTick()->position() + plly->transform()->position()) * 0.5f;
			flyhackPauseTime = Mathf::Max(0.f, flyhackPauseTime - Time::deltaTime());

			if (!plly->OnLadder() && !WaterLevel::Test(vector - Vector3(0.0f, flyhack_extrusion, 0.0f), true, plly)) {
				float radius = plly->GetRadius();
				float height = plly->GetHeight(false);

				Vector3 vector2 = vector + Vector3(0.0f, radius - flyhack_extrusion, 0.0f);
				Vector3 vector3 = vector + Vector3(0.0f, height - radius, 0.0f);
				float radius2 = radius - 0.05f;

				isInAir = !GamePhysics::CheckCapsule(vector2, vector3, radius2, 1503731969, GamePhysics::QueryTriggerInteraction::Ignore);

				if (isInAir)
				{
					Vector3 vector4 = (plly->transform()->position() - plly->lastSentTick()->position());
					float num2 = Mathf::Abs(vector4.y);
					float num3 = Misc::Magnitude2D(vector4);
					if (vector4.y >= 0.0f)
					{
						flyhackDistanceVertical += vector4.y;
						flag = true;
					}
					if (num2 < num3)
					{
						flyhackDistanceHorizontal += num3;
						flag = true;
					}
					if (flag)
					{
						float num5 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
						float num6 = (plly->GetJumpHeight() + num5);

						float num7 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
						float num8 = (5.f + num7);

					}

				}
				else {
					flyhackDistanceHorizontal = 0.f;
					flyhackDistanceVertical = 0.f;
				}
				float num5 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
				float num6 = ((plly->GetJumpHeight() + num5) * 3);
				VMaxFlyhack = num6;
				if (flyhackDistanceVertical <= (num6)) {
					VFlyhack = flyhackDistanceVertical;
				}
				if (VFlyhack >= VMaxFlyhack)
					VFlyhack = VMaxFlyhack;
				float num7 = Mathf::Max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
				float num8 = ((4.f + num7) * 3);
				HMaxFlyhack = num8;
				if (flyhackDistanceHorizontal <= (num8)) {
					HFlyhack = flyhackDistanceHorizontal;
				}
				if (HFlyhack >= HMaxFlyhack)
					HFlyhack = HMaxFlyhack;

			}
			else {
				flyhackDistanceHorizontal = 0.f;
				flyhackDistanceVertical = 0.f;
			}
			if (!isInAir)
			{
				flyhackDistanceHorizontal = 0.f;
				flyhackDistanceVertical = 0.f;
			}
			if (WaterLevel::Test(vector - Vector3(0.0f, flyhack_extrusion, 0.0f), true, plly))
			{
				flyhackDistanceHorizontal = 0.f;
				flyhackDistanceVertical = 0.f;
			}
			original_clientinput(plly, ModelState);

			switch (vars::misc::modelstate)
			{
			case 1:
				LocalPlayer::Entity()->modelState()->flags() |= (int)ModelStateFlag::OnLadder;

				break;
			case 2:
				LocalPlayer::Entity()->modelState()->flags() |= (int)ModelStateFlag::OnGround;
				break;
			case 3:
				LocalPlayer::Entity()->modelState()->flags() |= (int)ModelStateFlag::Ducked;
				break;
			case 4:
				LocalPlayer::Entity()->modelState()->flags() |= (int)ModelStateFlag::Sleeping;
				break;

			}
			if (vars::misc::omnidirectional_sprinting) {
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Sprinting);
			}
			if (vars::misc::interactive_debug && GetAsyncKeyState(vars::keys::debugging)) {
				BaseProjectile* ent = plly->GetHeldEntity<BaseProjectile>();
				LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Mounted);
				ent->_ServerRPC(("RPC_LootPlayer"));
			}
		}
		//spisok ganov
			//berreta:-852563019
			//ak:1545779598
			//lrka:-1812555177
			//bow:1443579727
			//peshka:818877484
			//mp5:1318558775
			//berdanka:-904863145
			//pulik:-2069578888
		void UpdateAmbient(TOD_Sky* TOD_Sky) {
			if (!vars::misc::bright_ambient) {
				return original_updateambient(TOD_Sky);
			}
			if (vars::misc::night_stars) {
				uintptr_t stars = read(TOD_Sky + 0x70, uintptr_t);
				*(float*)(stars + 0x14) = vars::misc::stars;
			}
			RenderSettings::set_ambientMode(RenderSettings::AmbientMode::Flat);
			RenderSettings::set_ambientIntensity(7.f);
			RenderSettings::set_ambientLight(Color({vars::colors::ambient_color.x, vars::colors::ambient_color.y, vars::colors::ambient_color.z, 1}));
		}
		pUncStr Run(ConsoleOptions* options, pUncStr strCommand, DWORD64 args) {
			if (options->IsFromServer( )) {
				std::wstring cmd = std::wstring(strCommand->str);
				if (cmd.find((L"noclip")) != std::wstring::npos || cmd.find((L"debugcamera")) != std::wstring::npos || cmd.find((L"camlerp")) != std::wstring::npos || cmd.find((L"camspeed")) != std::wstring::npos || cmd.find((L"admintime")) != std::wstring::npos) {
					strCommand = nullptr;
				}
			}
			return original_consolerun(options, strCommand, args);
		}
	}
	namespace combat {
		inline void DoAttack_hk(FlintStrikeWeapon* weapon) noexcept {
			if (!weapon) return;
			if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return weapon->DoAttack();
			if (vars::weapons::eokatap) weapon->_didSparkThisFrame() = true;
			return weapon->DoAttack();
		}
		float GetRandomVelocity(ItemModProjectile* mod) {
			Vector3 target_pos = target_player->transform()->position();
			float distance = Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), target_pos);

			if (vars::weapons::fast_bullets) {
				if (vars::weapons::low_velocity && GetAsyncKeyState(vars::keys::low_velocity_key)) {
					return original_getrandomvelocity(mod) * 0.600;
				}
				else
				{
					if (distance < 60.f && !(LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1953903201 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1443579727 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1367281941 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1540934679 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1602646136))
					{
						return original_getrandomvelocity(mod) * 0.550;
					}
					else
					{
						return original_getrandomvelocity(mod) * vars::weapons::bulletspeed;
					}
				}
			}

			return original_getrandomvelocity(mod);
		}
		void AddPunch(HeldEntity* a1, Vector3 a2, float duration) {
			if (vars::weapons::no_recoil) {
				a2 *= vars::weapons::recoil_control / 100.f;
			}
			return original_addpunch(a1, a2, duration);
		}
		inline Vector3 MoveTowards_hk(Vector3 current, Vector3 target, float maxDelta) {
			if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return Vector3_::MoveTowards(current, target, maxDelta);
			static auto ptr = METHOD("Assembly-CSharp::BaseProjectile::SimulateAimcone(): Void");
			if (!ptr) return Vector3_::MoveTowards(current, target, maxDelta);
			if (CALLED_BY(ptr, 0x800)) {
				target *= vars::weapons::recoil_control / 100.f;
				maxDelta *= vars::weapons::recoil_control / 100.f;
			}
			return Vector3_::MoveTowards(current, target, maxDelta);
		}
		bool DoHit(Projectile* prj, HitTest* test, Vector3 point, Vector3 normal) {
			auto localPlayer = LocalPlayer::Entity();
			auto held = localPlayer->GetHeldEntity<BaseProjectile>();
			if (prj->isAuthoritative( )) {

				if (vars::combat::ignore_team) {
					if (test->HitEntity( ) != null) {
						if (test->HitEntity( )->IsValid( )) {
							if (LocalPlayer::Entity( )->is_teammate((uintptr_t)reinterpret_cast<BasePlayer*>(test->HitEntity( )))) {
								if (reinterpret_cast<BaseCombatEntity*>(test->HitEntity( ))->IsPlayer( )) {
									return false;
								}
							}
						}
					}
				}
				if (vars::misc::hitmarker) {
					if (test->HitEntity() != nullptr) {
						if (test->HitEntity()->IsValid()) {
							if (reinterpret_cast<BasePlayer*>(test->HitEntity())->IsPlayer()) {
								DDraw::Sphere(prj->previousPosition(), 0.35f, Color(vars::colors::marker.x, vars::colors::marker.y, vars::colors::marker.z, 0), vars::misc::hitmarker_duration, false);
							}
						}
					}
				}
				if (vars::misc::hitmaterial == 0) {
				}
				if (vars::misc::hitmaterial == 1) {
					test->HitMaterial_() = il2cpp::String::New(("glass"));
				}
				if (vars::misc::hitmaterial == 2) {
					test->HitMaterial_() = il2cpp::String::New(("water"));
				}
				if (vars::misc::hitmaterial == 3) {
					test->HitMaterial_() = il2cpp::String::New(("wood"));
				}
				if (vars::misc::hitmaterial == 4) {
					test->HitMaterial_() = il2cpp::String::New(("metal"));
				}
				if (vars::misc::hitmaterial == 5) {
					test->HitMaterial_() = il2cpp::String::New(("sand"));
				}
				if (vars::misc::hitmaterial == 6) {
					test->HitMaterial_() = il2cpp::String::New(("grass"));
				}
				if (vars::misc::hitmaterial == 7) {
					test->HitMaterial_() = il2cpp::String::New(("rock"));
				}
				if (vars::misc::hitmaterial == 8) {
					test->HitMaterial_() = il2cpp::String::New(("concrete"));
				}
				if (vars::misc::hitmaterial == 9) {
					test->HitMaterial_() = il2cpp::String::New(("forest"));
				}
				if (vars::misc::hitmaterial == 10) {
					test->HitMaterial_() = il2cpp::String::New(("cloth"));
				}
				if (vars::misc::hitmaterial == 11) {
					test->HitMaterial_() = il2cpp::String::New(("explosions"));
				}

	
				if (vars::weapons::penetrate) {
					if (test->HitEntity( ) != null) {
						if (test->HitEntity( )->IsValid( )) {
							BaseCombatEntity* lol = reinterpret_cast<BaseCombatEntity*>(test->HitEntity( ));

							if (lol->ClassNameHash( ) == STATIC_CRC32("CargoShip") || lol->ClassNameHash( ) == STATIC_CRC32("BaseOven")
								|| lol->ClassNameHash( ) == STATIC_CRC32("TreeEntity") || lol->ClassNameHash( ) == STATIC_CRC32("OreResourceEntity")
								|| lol->ClassNameHash( ) == STATIC_CRC32("CH47HelicopterAIController") || lol->ClassNameHash( ) == STATIC_CRC32("MiniCopter")
								|| lol->ClassNameHash( ) == STATIC_CRC32("BoxStorage") || lol->ClassNameHash( ) == STATIC_CRC32("Workbench")
								|| lol->ClassNameHash( ) == STATIC_CRC32("VendingMachine") || lol->ClassNameHash( ) == STATIC_CRC32("Barricade")
								|| lol->ClassNameHash( ) == STATIC_CRC32("BuildingPrivlidge") || lol->ClassNameHash( ) == STATIC_CRC32("LootContainer")
								|| lol->ClassNameHash( ) == STATIC_CRC32("HackableLockedCrate") || lol->ClassNameHash( ) == STATIC_CRC32("ResourceEntity")
								|| lol->ClassNameHash( ) == STATIC_CRC32("RidableHorse") || lol->ClassNameHash( ) == STATIC_CRC32("MotorRowboat")
								|| lol->ClassNameHash( ) == STATIC_CRC32("ScrapTransportHelicopter") || lol->ClassNameHash( ) == STATIC_CRC32("JunkPile")
								|| lol->ClassNameHash( ) == STATIC_CRC32("MiningQuarry") || lol->ClassNameHash( ) == STATIC_CRC32("WaterCatcher")) {
								return false;
							}
						}
					}
				}
			}
			return original_dohit(prj, test, point, normal);
		}

		bool CanAttack(BasePlayer* a1) {
			if (vars::misc::can_attack)
				return true;
			return original_canattack(a1);
		}
		Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = true) {
			Vector3 target;
			if (target_player) {
				if (vars::combat::hitscan) {
					target = m_hitscan_manipulator;
				}
				else
					if (vars::combat::onal == 0) {
						target = target_player->get_bone_pos(head);
					}
					else {
						target = target_player->get_bone_pos(spine1);
					}
			}
			if (vars::combat::psilent) {
				if (target_player) {
					auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
					BaseProjectile* _held = held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
					auto mag = held->primaryMagazine();
					if (!mag) return original_aimconedirection(aimCone, inputVec, anywhereInside);
					auto ammo = mag->ammoType();
					if (!ammo) return original_aimconedirection(aimCone, inputVec, anywhereInside);
					auto mod = ammo->GetComponent<ItemModProjectile>(Type::ItemModProjectile());
					if (!mod) return original_aimconedirection(aimCone, inputVec, anywhereInside);
					auto projectile = mod->projectileObject()->Get()->GetComponent<Projectile>(Type::Projectile());
					if (!projectile) return original_aimconedirection(aimCone, inputVec, anywhereInside);

					if (projectile)
					{
						auto projectileVelocity = mod->projectileVelocity();

						auto projectileVelocityScale = _held->projectileVelocityScale();

						if (vars::weapons::fast_bullets) {
							if (vars::weapons::low_velocity && GetAsyncKeyState(vars::keys::low_velocity_key)) {
								projectileVelocityScale = 0.600 * _held->projectileVelocityScale();
							}
							else
							{
								if (Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), target_player->transform()->position()) < 60.f && !(LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1953903201 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1443579727 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == -1367281941 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1540934679 || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1602646136))
								{
									projectileVelocityScale = 0.550 * _held->projectileVelocityScale();
								}
								else
								{
									projectileVelocityScale = vars::weapons::bulletspeed * _held->projectileVelocityScale();
								}
							}
						}
						else
						{
							projectileVelocityScale = 1.f * _held->projectileVelocityScale();
						}

						float drag = projectile->drag();
						float gravityModifier = projectile->gravityModifier();
						float initialDistance = projectile->initialDistance();
						auto gravity = Physics::get_gravity();
						auto deltaTime = Time::fixedDeltaTime();
						auto timescale = Time::timeScale();

						float DeltaForLoop = deltaTime * timescale;

						Vector3 localPos = LocalPlayer::Entity()->eyes()->get_position();

						Vector3 actualTargetPos = target_player->get_bone_pos(head);
						if (vars::combat::bullet_tp && vars::combat::hitscan
							&& m_hitscan_manipulator != Vector3::Zero()
							&& !utils::LineOfSight(localPos, actualTargetPos)) {
							actualTargetPos = m_hitscan_manipulator;
						}
						else
						{
							actualTargetPos = target_player->get_bone_pos(head);
						}
						if (vars::combat::bullet_tp && vars::combat::hitscan && m_hitscan_manipulator != Vector3::Zero()) {
							auto transform = target_player->transform_(head);
							auto targetPos = transform->position();
							auto projPos = projectile->transform()->position();
							auto distToTarget = targetPos.distance(projPos);
							float num = Mathf::Clamp(projectile->traveledTime(), 0.f, 8.f);
							float num2 = 1.f + 0.5f;
							float projectile_clientframes = 2.f;
							float projectile_serverframes = 2.f;
							float num3 = Mathx::Decrement(projectile->launchTime());
							float num4 = Mathf::Clamp(Mathx::Increment(Time::realtimeSinceStartup()) - num3, 0.f, 8.f);
							float num5 = num;
							float num7 = Mathf::Min(num4, num5);
							float num8 = projectile_clientframes / 60.f;
							float num9 = projectile_serverframes * Mathx::Max(Time::deltaTime(), Time::smoothDeltaTime(), Time::fixedDeltaTime());

							float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;

							float num10 = (desyncTime + num7 + num8 + num9) * num2;
							float num11 = target_player->MaxVelocity() + target_player->GetParentVelocity().Magnitude();
							float num12 = target_player->BoundsPadding() + num10 * num11;

							float bulletRadius = CalculateBulletRadius(distToTarget, num10, num11, target_player->BoundsPadding());

							if ((actualTargetPos - localPos).magnitude() <= bulletRadius && !utils::LineOfSight(localPos, actualTargetPos)) {
								actualTargetPos = m_hitscan_manipulator;
							}

						}
						else {
							actualTargetPos = target_player->get_bone_pos(head);
						}

						float bulletTime = std::sqrt((actualTargetPos.x) * (actualTargetPos.x) + (actualTargetPos.z) * (actualTargetPos.z));

						Vector3 targetvel = target_player->GetWorldVelocity();
						Vector3 targetPosition = actualTargetPos;

						auto _aimDir = original_aimconedirection(0.f, targetPosition - localPos, false);

						auto position = localPos;
						float num = 0.03125f;
						int num3 = (8.f / DeltaForLoop);

						int simulations = 0;

						while (simulations < 30)
						{
							simulations++;
							bool hitPlayer = false;

							_aimDir = original_aimconedirection(0.f, targetPosition - localPos, false);
							Vector3 velocity = _aimDir * projectileVelocity * projectileVelocityScale;

							auto currentPosition = localPos;
							auto previousPosition = currentPosition;


							Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
							Vector3 offset = Vector3().Zero();

							for (int i = -1; i < num3; i++)
							{
								previousPosition = currentPosition;
								currentPosition += velocity * deltaTime;
								velocity += gravity * gravityModifier * deltaTime;
								velocity -= velocity * drag * deltaTime;

								auto line = (currentPosition - previousPosition);
								auto len = line.UnityMagnitude();
								line.UnityNormalize();
								auto v = actualTargetPos - previousPosition;
								auto d = Vector3().UnityDot(v, line);

								if (d < 0.f)
								{
									d = 0.f;
								}
								else if (d > len)
								{
									d = len;
								}

								Vector3 nearestPoint = previousPosition + line * d;

								if (nearestPoint.distance(actualTargetPos) < 0.1f)
								{
									bulletTime = i * num;
									hitPlayer = true;
								}
								else if (nearestPoint.distance(actualTargetPos) < closestPoint.distance(actualTargetPos))
								{
									closestPoint = nearestPoint;
									offset = actualTargetPos - nearestPoint;
								}
							}
							if (hitPlayer) break;
							targetPosition += offset;
						}


						if (bulletTime != 1337.f)
						{
							Vector3 finalVelocity = Vector3(target_player->GetWorldVelocity().x, 0, target_player->GetWorldVelocity().z) * 0.75f * bulletTime;

							actualTargetPos += finalVelocity;

							Vector3 targetPosition = actualTargetPos;


							auto _aimDir = original_aimconedirection(0.f, targetPosition - localPos, false);
							float bulletTime = 1337.f;
							int sims = 0;
							while (sims < 30)
							{

								sims++;
								bool hitPlayer = false;

								_aimDir = original_aimconedirection(0.f, targetPosition - localPos, false);
								Vector3 velocity = _aimDir * projectileVelocity * projectileVelocityScale;

								auto currentPosition = localPos;
								auto previousPosition = currentPosition;

								Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
								Vector3 offset = Vector3().Zero();

								for (int i = -1; i < num3; i++)
								{
									previousPosition = currentPosition;
									currentPosition += velocity * num;
									velocity += gravity * gravityModifier * num;
									velocity -= velocity * drag * num;

									auto line = (currentPosition - previousPosition);
									auto len = line.UnityMagnitude();
									line.UnityNormalize();
									auto v = actualTargetPos - previousPosition;
									auto d = Vector3().UnityDot(v, line);

									if (d < 0.f)
									{
										d = 0.f;
									}
									else if (d > len)
									{
										d = len;
									}

									Vector3 nearestPoint = previousPosition + line * d;

									if (nearestPoint.distance(actualTargetPos) < 0.1f)
									{
										bulletTime = i * num;
										hitPlayer = true;
									}
									else if (nearestPoint.distance(actualTargetPos) < closestPoint.distance(actualTargetPos))
									{
										closestPoint = nearestPoint;
										offset = actualTargetPos - nearestPoint;
									}
								}

								if (hitPlayer) break;
								targetPosition += offset;
							}

							did_reload = false;
							just_shot = true;
							fixed_time_last_shot = Time::fixedTime();

							return _aimDir;
						}
					}
				}
				else {

				}
			}
			if (vars::weapons::no_spread) aimCone = 0.f;
			did_reload = false;
			just_shot = true;
			fixed_time_last_shot = Time::fixedTime();
			return original_aimconedirection(aimCone, inputVec, anywhereInside);
		}
		Vector3 hk_BodyLeanOffset(PlayerEyes* a1) {
			if (vars::combat::manipulator && !m_manipulate.empty()) {
				return m_manipulate;
			}
			return Original_BodyLeanOffset(a1);
		}
		Vector3 hk_EyePositionForPlayer(BaseMountable* arg1, BasePlayer* arg2, Quaternion* arg3) {
			BasePlayer* player = arg2;
			if (player->userID()) {
				if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
					return Original_EyePositionForPlayer(arg1, arg2, arg3) + m_manipulate;
				}
			}
			return Original_EyePositionForPlayer(arg1, arg2, arg3);
		}
		inline Attack* BuildAttackMessage_hk(HitTest* self, BaseEntity* a2) noexcept {
			if (!self) return self->BuildAttackMessage();
			auto ret = self->BuildAttackMessage();
			auto entity = BaseNetworkable::clientEntities()->Find<BasePlayer*>(ret->hitID());

			if (!entity->IsPlayer() || vars::combat::always_heli_rotor)
			{
				if (entity->class_name_hash() == STATIC_CRC32("BaseHelicopter"))
				{
					if (entity->health() <= 5000.0f)
						ret->hitBone() = utils::StringPool::Get(("tail_rotor_col"));
					else
						ret->hitBone() = utils::StringPool::Get(("engine_col"));
				}
			}

			auto localPlayer = LocalPlayer::Entity();
			if (localPlayer) {

				if (reinterpret_cast<BasePlayer*>(self->ignoreEntity())->userID() == localPlayer->userID()) {
					if (entity) {
						if (entity->IsPlayer()) {
							if (vars::weapons::thick_bullet) {
								auto bone = entity->model()->find_bone(ret->hitPositionWorld());
								if (bone.second) {
									ret->hitPositionWorld() = bone.first->position();
								}
							}
							if (vars::combat::hitbox != 0) {
								if (vars::combat::hitbox == 1)
									ret->hitBone() = utils::StringPool::Get(("spine4"));
								else if (vars::combat::hitbox == 2)
									ret->hitBone() = utils::StringPool::Get(("head"));
								else if (vars::combat::hitbox == 3) {
									// yandere dev in this bitch
									int num = rand() % 100;

									if (num > 90)
										ret->hitBone() = utils::StringPool::Get(("head"));
									else if (num < 90 && num > 80)
										ret->hitBone() = utils::StringPool::Get(("neck"));
									else if (num < 80 && num > 70)
										ret->hitBone() = utils::StringPool::Get(("l_clavicle"));
									else if (num < 70 && num > 60)
										ret->hitBone() = utils::StringPool::Get(("pelvis"));
									else if (num < 60 && num > 50)
										ret->hitBone() = utils::StringPool::Get(("r_hip"));
									else if (num < 50 && num > 40)
										ret->hitBone() = utils::StringPool::Get(("r_foot"));
									else if (num < 40 && num > 30)
										ret->hitBone() = utils::StringPool::Get(("spine1"));
									else if (num < 30 && num > 20)
										ret->hitBone() = utils::StringPool::Get(("l_hand"));
									else if (num < 20 && num > 10)
										ret->hitBone() = utils::StringPool::Get(("r_upperarm"));
									else if (num < 10)
										ret->hitBone() = utils::StringPool::Get(("l_knee"));
									else
										ret->hitBone() = utils::StringPool::Get(("spine4"));
								}
								else if (vars::combat::hitbox == 4) {
									int yeet = rand() % 100;
									if (yeet > 50)
										ret->hitBone() = utils::StringPool::Get(("head"));
									else
										ret->hitBone() = utils::StringPool::Get(("spine4"));
								}
							}

						}
					}
				}
			}
			return ret;
			
		}
		void LaunchProjectile_hk(BaseProjectile* self)
		{
			Vector3 o = LocalPlayer::Entity()->transform()->position();

			int sb = vars::combat::doubletaptype;
			float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;
			if (self->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
				int ammo = self->primaryMagazine()->contents();
				if (ammo <= 0) return self->LaunchProjectile();
				if (vars::weapons::rapidfire && !LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1443579727) sb = 0;
				switch (sb)
				{
				case 0:
					break;
				case 1: //basic

					if (desyncTime > 0.001f)
					{
						self->LaunchProjectile();
						if (self->primaryMagazine()->contents() > 0)
						{
							self->LaunchProjectile();
							self->primaryMagazine()->contents()--;
							self->UpdateAmmoDisplay();
							self->ShotFired();
							self->DidAttackClientside();
						}
						LocalPlayer::Entity()->SendClientTick();
						return;
					}

					break;
				case 2: //smart
					float f = desyncTime / (self->repeatDelay() * 0.9f);
					int z = (int)f;


					for (size_t i = 0; i < (z > 9 ? 9 : (z < 0 ? 0 : z)); i++)
						if (self->primaryMagazine()->contents() > 0)
						{
							self->LaunchProjectile();
							self->primaryMagazine()->contents()--;
							self->UpdateAmmoDisplay();
							self->ShotFired();
							self->DidAttackClientside();
						}

					if (z <= 0)
						self->LaunchProjectile();

					LocalPlayer::Entity()->SendClientTick();
					return;
				}

			}
			return self->LaunchProjectile();
		}

		void hk_DoFirstPersonCamera(PlayerEyes* a1, Component* cam) {
			if (!a1 || !cam) return;
			Original_DoFirstPersonCamera_hk(a1, cam);
			if (vars::combat::manipulator) {
				Vector3 re_p = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);
				cam->transform()->set_position(re_p);
			}
		}
	}
	void Hk_TryToMove(ItemIcon* a1) {
		Original_TryToMove_hk(a1);
		if (vars::misc::fast_loot) {
			if (a1->queuedForLooting())
			{
				a1->RunTimedAction();
			}
		}
	}
}

void UpdateVelocity_hk(PlayerWalkMovement* self) {
	self->capsule()->set_radius(0.43);
	if (!self->flying()) {
		Vector3 vel = self->TargetMovement();
		if (vars::misc::omnidirectional_sprinting) {
			float max_speed = (self->swimming() || self->Ducking() > 0.5) ? 1.7f : 5.5f;
			if (vel.length() > 0.f) {
			//	if (GetAsyncKeyState(vars::keys::speedkey)) max_speed += 2;
				Vector3 target_vel = Vector3(vel.x / vel.length() * max_speed, vel.y, vel.z / vel.length() * max_speed);
				self->TargetMovement() = target_vel;
			}
		}
	}
	return original_updatevelos(self);
}

void HandleJumping_hk(PlayerWalkMovement* a1, ModelState* state, bool wantsJump, bool jumpInDirection = false) {
	if (vars::misc::fly_auto_stopper)
	{
		if (HFlyhack >= (HMaxFlyhack - 2.7f)
			|| VFlyhack >= (VMaxFlyhack - 1.7f))
			return original_jumpup(a1, state, false, jumpInDirection);
	}
	if (vars::misc::better_jump) {
		if (!wantsJump) return;
		a1->grounded() = (a1->climbing() = (a1->sliding() = false));
		state->set_ducked(false);
		a1->jumping() = true;
		state->set_jumped(true);
		a1->jumpTime() = Time::time();
		a1->ladder() = nullptr;
		Vector3 curVel = a1->body()->velocity();
		a1->body()->set_velocity({ curVel.x, 10, curVel.z });
		return;
	}
	return original_jumpup(a1, state, wantsJump, jumpInDirection);
}
void DoHitNotify(BaseCombatEntity* entity, HitInfo* info, Projectile* prj) {
	if (entity->IsPlayer()) {

		std::string _name(CStringA(reinterpret_cast<BasePlayer*>(entity)->_displayName()));
		std::string string;
		float damage = info->damageTypes()->Total();
		hitmarker::d_indicator_t DmgIndicator;
		DmgIndicator.damage = damage;
		DmgIndicator.player = reinterpret_cast<BasePlayer*>(entity);
		DmgIndicator.hit_box = head;
		DmgIndicator.erase_time = Time::time() + 3.2;
		DmgIndicator.initialized = false;
		hitmarker::get().d_indicators.push_back(DmgIndicator);
		hitmarker::get().add_hit(hitmarker_t(Time::time(), damage, head, reinterpret_cast<BasePlayer*>(entity)->get_bone_pos(head)));
	}
	return original_dohitnotify(entity, info, prj);

}
bool IsDown_hk(InputState* self, Button btn) {
	if (!LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) return original_isdown(self, btn);
	if (vars::combat::manipulator && GetAsyncKeyState(vars::keys::manipulated_key)) {
		if (btn == Button::FIRE_PRIMARY) {
			auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
			float lastShotTime = held->lastShotTime() - GLOBAL_TIME;
			float reloadTime = held->nextReloadTime() - GLOBAL_TIME;
			if ((held && !held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile"))) {
				if (target_player != nullptr) {
					if (vars::combat::hitscan) {
						if (utils::LineOfSight(target_player->get_bone_pos(head), LocalPlayer::Entity()->eyes()->position()) || utils::LineOfSight(m_hitscan_manipulator, LocalPlayer::Entity()->eyes()->position()))
							return true;
					}
					else {
						if (utils::LineOfSight(target_player->get_bone_pos(head), LocalPlayer::Entity()->eyes()->position()))
							return true;
					}
				}
			}
			if ((held && !held->Empty() && held->class_name_hash() == STATIC_CRC32("BaseProjectile"))) {
				if (target_player != nullptr) {
					if (vars::combat::Manipulator_shot_atBt) {
						if (utils::LineOfSight(target_player->get_bone_pos(head), LocalPlayer::Entity()->eyes()->position()) || utils::LineOfSight(m_hitscan_manipulator, LocalPlayer::Entity()->eyes()->position()))
							return true;
					}
					else {
						if (utils::LineOfSight(target_player->get_bone_pos(head), LocalPlayer::Entity()->eyes()->position()))
							return true;
					}
				}
			}
		}
	}
	float desyncpercentage;
	float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;
	desyncpercentage = ((desyncTime / 0.99f) * 100.0f) + 1.f;
	if (!LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) return original_isdown(self, btn);
	return original_isdown(self, btn);
}
void OnLand_hk(BasePlayer* ply, float vel) {
	if (!LocalPlayer::Entity()->HasPlayerFlag(PlayerFlags::Connected)) return ply->OnLand(vel);
	if (!vars::misc::no_fall)
		ply->OnLand(vel);
}

void hk_(void* Function, void** Original, void* Detour) {
	if (MH_Initialize( ) != MH_OK && MH_Initialize( ) != MH_ERROR_ALREADY_INITIALIZED) {
		return;
	}
	MH_CreateHook(Function, Detour, Original);
	MH_EnableHook(Function);
}
void hk__( ) {
	//iza manual mapa chto d debau
	hk_((void*)METHOD("Assembly-CSharp::BaseProjectile::LaunchProjectile(): Void"), (void**)&BaseProjectile::LaunchProjectile_, hk::combat::LaunchProjectile_hk);

	hk_((void*)METHOD("Rust.Data::ModelState::set_flying(Boolean): Void"), (void**)&original_setflying, hk::misc::SetFlying);
	hk_((void*)METHOD("Assembly-CSharp::ItemIcon::TryToMove(): Void"), (void**)&Original_TryToMove_hk, hk::Hk_TryToMove);
	hk_((void*)METHOD("Assembly-CSharp::HitTest::BuildAttackMessage(): Attack"), (void**)&HitTest::BuildAttackMessage_, hk::combat::BuildAttackMessage_hk);
	hk_((void*)METHOD("Assembly-CSharp::BaseCombatEntity::DoHitNotify(HitInfo): Void"), (void**)&original_dohitnotify, DoHitNotify);
	hk_((void*)METHOD("Assembly-CSharp::Projectile::Update(): Void"), (void**)&original_Update, hk::exploit::ProjectileUpdate_hk);
	hk_((void*)METHOD("Assembly-CSharp::FlintStrikeWeapon::DoAttack(): Void"), (void**)&FlintStrikeWeapon::DoAttack_, hk::combat::DoAttack_hk);
	hk_((void*)METHOD("Assembly-CSharp::BasePlayer::CanAttack(): Boolean"), (void**)&original_canattack, hk::combat::CanAttack);
	hk_((void*)METHOD("Assembly-CSharp::BasePlayer::SendClientTick(): Void"), (void**)&BasePlayer::SendClientTick_, hk::misc::SendClientTick);
	hk_((void*)METHOD("Assembly-CSharp::AimConeUtil::GetModifiedAimConeDirection(Single,Vector3,Boolean): Vector3"), (void**)&original_aimconedirection, hk::combat::GetModifiedAimConeDirection);
	hk_((void*)METHOD("Facepunch.Console::ConsoleSystem::Run(Option,String,Object[]): String"), (void**)&original_consolerun, hk::misc::Run);
	//hk_((void*)METHOD("Assembly-CSharp::ItemModProjectile::GetRandomVelocity(): Single"), (void**)&ItemModProjectile::GetRandomVelocity_, hk::combat::GetRandomVelocity);
	hk_((void*)METHOD("Assembly-CSharp::HeldEntity::AddPunch(Vector3,Single): Void"), (void**)&original_addpunch, hk::combat::AddPunch);
	hk_((void*)METHOD("UnityEngine.CoreModule::UnityEngine::Vector3::MoveTowards(Vector3,Vector3,Single): Vector3"), (void**)&Vector3_::MoveTowards_, hk::combat::MoveTowards_hk);
	hk_((void*)METHOD("Assembly-CSharp::Projectile::DoMovement(Single): Void"), (void**)&original_domovement, hk::exploit::DoMovement);
	hk_((void*)METHOD("Assembly-CSharp::Projectile::DoHit(HitTest,Vector3,Vector3): Boolean"), (void**)&original_dohit, hk::combat::DoHit);
	hk_((void*)METHOD("Assembly-CSharp-firstpass::TOD_Sky::UpdateAmbient(): Void"), (void**)&original_updateambient, hk::misc::UpdateAmbient);
	hk_((void*)METHOD("Assembly-CSharp::BasePlayer::ClientInput(InputState): Void"), (void**)&original_clientinput, hk::misc::ClientInput);
	hk_((void*)METHOD("Assembly-CSharp::PlayerWalkMovement::UpdateVelocity(): Void"), (void**)&original_updatevelos, UpdateVelocity_hk);
	hk_((void*)METHOD("Assembly-CSharp::PlayerWalkMovement::HandleJumping(ModelState,Boolean,Boolean): Void"), (void**)&original_jumpup, HandleJumping_hk);
	hk_((void*)METHOD("Assembly-CSharp::BasePlayer::OnLand(Single): Void"), (void**)&BasePlayer::OnLand_, OnLand_hk);
	//hk_((void*)(uintptr_t)(InGame::stor::gBase + CO::DoFixedUpdate), (void**)&original_dofixedupdate, hk::misc::DoFixedUpdate);
	hk_((void*)METHOD("Assembly-CSharp::ItemModProjectile::GetRandomVelocity(): Single"), (void**)&original_getrandomvelocity, hk::combat::GetRandomVelocity);
	hk_((void*)METHOD("Assembly-CSharp::PlayerEyes::get_BodyLeanOffset(): Vector3"), (void**)&Original_BodyLeanOffset, hk::combat::hk_BodyLeanOffset);
	hk_((void*)METHOD("Assembly-CSharp::BaseMountable::EyePositionForPlayer(BasePlayer,Quaternion): Vector3"), (void**)&Original_EyePositionForPlayer, hk::combat::hk_EyePositionForPlayer);
	hk_((void*)METHOD("Assembly-CSharp::PlayerEyes::DoFirstPersonCamera(Camera): Void"), (void**)&Original_DoFirstPersonCamera_hk, hk::combat::hk_DoFirstPersonCamera);
	hk_((void*)(uintptr_t)(InGame::stor::gBase + 0x2b1570), (void**)&original_refract, hk::exploit::Refract);
	//auto LoadAsset = reinterpret_cast<DWORD64(*)(DWORD64, Str, DWORD64)>(0);
	//auto Instantiate = reinterpret_cast<GameObject * (*)(DWORD64, Vector3, Quaternion)>(0);
	//LoadAsset = reinterpret_cast<DWORD64(*)(DWORD64, Str, DWORD64)>(*reinterpret_cast<DWORD64*>(il2cpp::method((uintptr_t)(("AssetBundle"), ("LoadAsset_Internal"), 2, ("name"), ("UnityEngine"), 1))));
	//Instantiate = reinterpret_cast<GameObject * (*)(DWORD64, Vector3, Quaternion)>(*reinterpret_cast<DWORD64*>(il2cpp::method((uintptr_t)(("Object"), ("Instantiate"), 3, (""), ("UnityEngine")))));
}