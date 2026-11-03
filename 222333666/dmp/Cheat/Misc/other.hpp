#include <array>
#include <corecrt_math_defines.h>
#include <utility>

inline void hitscan_angles(std::vector<Vector3>& re, float radius, unsigned int sectors, unsigned int rings)
{
	float const R = 1.0f / (float)(rings - 1);
	float const S = 1.0f / (float)(sectors - 1);
	int r, s;

	double desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;
	float mm_max_eye = (0.1f + ((desyncTime + 2.0f / 60.0f + 0.125f) * 1.5) * LocalPlayer::Entity()->MaxVelocity()) - 0.05f;
	for (r = 0; r < rings * 2; r++)
		for (s = 0; s < sectors * 2; s++)
		{
			float y = sin(-(M_PI / 2) + M_PI * r * R);
			float x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
			float z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

			x *= radius;
			y *= radius;
			z *= radius;

			if (!target_player->has_modelstate_flag(ModelStateFlag::Mounted)) {
				if (r == 4)
				{
					y = 1.40f + mm_max_eye * 0.1f;
				}
				else if (r == 3)
				{
					y = 0.55f + mm_max_eye * 0.1f;
				}
			}

			re.push_back(Vector3(x, y, z));
		}
}


inline void vischeck_manipulation(std::vector<Vector3>& re, float radius, unsigned int sectors)
{
	float const S = 1.0f / static_cast<float>(sectors - 1);
	int s;

	for (s = 0; s < sectors; s++)
	{
		float angle = 2.0f * M_PI * s * S;
		float x = cos(angle) * radius;
		float z = sin(angle) * radius;
		float y = 1.5f;

		re.push_back(Vector3(x, y, z));
	}
}


#define M_PI 3.14159265358979323846f

// VALIDATE EYE SHIT 

bool TestNoClipping(BasePlayer* ply, Vector3 oldPos, Vector3 newPos, float radius, float backtrack) {
	int num = 429990145;
	Vector3 normalized = (newPos - oldPos).normalized();
	Vector3 vector = oldPos - normalized * backtrack;
	float magnitude = (newPos - vector).Length();
	Ray z = Ray(vector, normalized);
	bool flag = Physics::Raycast1(z, magnitude + radius, 429990145);
	if (!flag) {
		flag = Physics::SphereCast(z, radius, magnitude, 429990145);
	}
	return flag;
}
bool ValidateEyePos2(Vector3 eyePos)
{
	float deltatime = Time::deltaTime();

	bool flag = true;
	float num = 1.5f;
	float num2 = 2.f / 60.f;
	float num3 = 2.f * deltatime;
	float num4 = (1.f + num2 + num3) * num;
	float num8 = fabs(LocalPlayer::Entity()->GetParentVelocity().y);
	float num9 = LocalPlayer::Entity()->BoundsPadding() + num4 + num8 + LocalPlayer::Entity()->GetJumpHeight();
	float num10 = fabs(LocalPlayer::Entity()->eyes()->get_position().y - eyePos.y);

	auto transform = LocalPlayer::Entity()->transform();
	Vector3 position = transform->position();
	Vector3 position2 = LocalPlayer::Entity()->eyes()->get_position();

	if (num10 > num9)
	{
		flag = false;
	}
	if (position.distance(position2) > 0.06f && TestNoClipping(LocalPlayer::Entity(), LocalPlayer::Entity()->lastSentTick()->__position(), position, 0.01f, 0.01f))
	{
		flag = true;
	}
	if (position.distance(position2) > 0.01f && TestNoClipping(LocalPlayer::Entity(), position2, eyePos, 0.01f, 0.01f))
	{
		flag = false;
	}
	return flag;
}

// MANIPULATOR 

Vector3 m_manipulate = Vector3::Zero();
Vector3 m_hitscan_manipulator = Vector3::Zero();
Vector3 m_manipulate_check = Vector3::Zero();

Vector3 getTargetPos(BasePlayer* target) {
	if (target->get_flag(PlayerFlags::Wounded))
		return target->get_bone_pos(head);
	else
		return target->transform()->position() + Vector3(0, 1.49f, 0);
}

bool isLOS(Vector3 point1, Vector3 point2) {
	return utils::LineOfSight(point1, point2);
}

bool processFatDefault(Vector3 point, Vector3 targetPos, std::vector<Vector3> fatDefault, Vector3 fatChoice, bool isFatAvailable) {
	Vector3 re_t = target_player->transform()->position() + target_player->transform()->up() * (target_player->eyes()->EyeOffset().y + target_player->eyes()->viewOffset().y);
	for (auto& offset : fatDefault) {
		Vector3 offsetPos = targetPos + offset;
		if (utils::LineOfSight(point, offsetPos)) {
			fatChoice = offset;
			m_hitscan_manipulator = offsetPos;
			isFatAvailable = true;
			if (utils::LineOfSight(re_t, m_hitscan_manipulator)) return true;
		}
		m_hitscan_manipulator = Vector3::Zero();
	}

	if (vars::combat::m_check_bullet_tp && vars::combat::bullet_tp)
		return isFatAvailable;

	return false;
}

bool isValidPoint(Vector3 point, Vector3 targetPos, BasePlayer* target, std::vector<Vector3> fatDefault, Vector3 fatChoice, bool isFatAvailable) {
	if (utils::LineOfSight(target->get_bone_pos(head), point)) return ValidateEyePos2(point);

	if (vars::combat::bullet_tp && vars::combat::hitscan) {
		if (!processFatDefault(point, targetPos, fatDefault, fatChoice, isFatAvailable)) return false;
	}
	else return false;

	return ValidateEyePos2(point);
}

namespace other {
	bool manipulating_to_fat = false;

	void find_manipulate_angle() {
		m_manipulate = Vector3::Zero();
		auto loco = LocalPlayer::Entity();
		Vector3 re_p = loco->transform()->position() + loco->transform()->up() * (loco->eyes()->EyeOffset().y + loco->eyes()->viewOffset().y);

		Vector3 rep = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);
		Vector3 re_t = target_player->transform()->position() + target_player->transform()->up() * (target_player->eyes()->EyeOffset().y + target_player->eyes()->viewOffset().y);
		Vector3 choice = Vector3::Zero();
		auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
		BaseProjectile* _held = held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();

		if (utils::LineOfSight(re_p, target_player->get_bone_pos(head))) {
			m_manipulate = Vector3::Zero();
			return;
		}

		float mm_max_eye;
		double desyncTime = (Time::realtimeSinceStartup() - loco->lastSentTickTime()) - 0.03125 * 3;
		auto desync = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.5) * LocalPlayer::Entity()->MaxVelocity()) - 0.05f;

		mm_max_eye = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.50f) * loco->MaxVelocity()) - 0.05f;

		Vector3 actual_target_pos = target_player->playerModel()->position() + Vector3(0.f, 0.2f, 0.f);
		float step = (M_PI * 2.0f) / 940;

		float radius = 2.0f;

		std::vector<Vector3> angle = {};

		vischeck_manipulation(angle, mm_max_eye, 16);

		float extended_distance = 0.f;
		float clawling_distance = 0.f;
		float normal_distance = 0.f;
		float smaller_distance = 0.f;
		float NPC_distance = 0.f;

		if (vars::weapons::bullet_tp_type == 0)
		{
			extended_distance = 4.f;
			clawling_distance = 2.f;
			normal_distance = 1.2f;
			smaller_distance = 1.2f;
			NPC_distance = 1.65f;
		}
		else if (vars::weapons::bullet_tp_type == 1)
		{
			extended_distance = 7.f;
			clawling_distance = 3.f;
			normal_distance = 1.6f;
			smaller_distance = 1.6f;
			NPC_distance = 2.5f;
		}
		else if (vars::weapons::bullet_tp_type == 2)
		{
			extended_distance = 11.f;
			clawling_distance = 5.f;
			normal_distance = 2.0f;
			smaller_distance = 2.0f;
			NPC_distance = 3.5f;
		}
		else if (vars::weapons::bullet_tp_type == 3)
		{
			extended_distance = 15.f;
			clawling_distance = 7.5f;
			normal_distance = 2.3f;
			smaller_distance = 2.2f;
			NPC_distance = 6.5f;
		}

		float distance = 0.f;
		bool isNPC = target_player->IsNpc();
		bool isMounted = !target_player->has_modelstate_flag(ModelStateFlag::Mounted);
		distance = isNPC ? NPC_distance :
			isMounted ? (
				(held->class_name_hash() == STATIC_CRC32("BowWeapon")
					|| held->class_name_hash() == STATIC_CRC32("CrossBowWeapon")
					|| held->class_name_hash() == STATIC_CRC32("BaseMelee") ? smaller_distance : normal_distance))
			: clawling_distance;

		std::vector<Vector3> fat_default = {};
		hitscan_angles(fat_default, distance, 10, 5); \
			bool fat_available = false;
		Vector3 fat_choice = Vector3::Zero();
		Vector3 target_pos;

		Vector3 pasta1 = target_player->playerModel()->position() + target_player->get_bone_pos(head);

		if (vars::combat::draw_manip_radius)
		{
			Vector3 actual_manipulator_pos = LocalPlayer::Entity()->transform()->position() + Vector3(0.f, 0.2f, 0.f);
			float step = (M_PI * 2.0f) / 72;
			for (float a = 0; a < (M_PI * 2.0f); a += step)
			{
				Vector3 start(mm_max_eye * cos(a) + actual_manipulator_pos.x, actual_manipulator_pos.y, mm_max_eye * sin(a) + actual_manipulator_pos.z);
				Vector3 end(mm_max_eye * cos(a + step) + actual_manipulator_pos.x, actual_manipulator_pos.y, mm_max_eye * sin(a + step) + actual_manipulator_pos.z);

				DDraw::Line(start, end, Color(100, 10, 100, 1), 0.f, false, true);
				//DDraw::Arrow(LocalPlayer::Entity()->eyes()->position(), end, 0.3f, Color(vars::colors::angle_arrow.x, vars::colors::angle_arrow.y, vars::colors::angle_arrow.z, 1.f), 0.01f);
			}
		}
		if (vars::combat::draw_manip_radius) {
			if (vars::combat::mpvis)
			{
				Vector3 actual_manipulator_pos = LocalPlayer::Entity()->transform()->position() + Vector3(0.f, 0.2f, 0.f);
				float step = (M_PI * 2.0f) / 72;
				for (float a = 0; a < (M_PI * 2.0f); a += step)
				{
					Vector3 max_manip_start(8.f * cos(a) + actual_manipulator_pos.x, actual_manipulator_pos.y, 8.f * sin(a) + actual_manipulator_pos.z);
					Vector3 max_manip_end(8.f * cos(a + step) + actual_manipulator_pos.x, actual_manipulator_pos.y, 8.f * sin(a + step) + actual_manipulator_pos.z);

					DDraw::Line(max_manip_start, max_manip_end, Color(100, 0, 0, 1), 0.f, false, true);
				}
			}
		}

		if (target_player->get_flag(PlayerFlags::Wounded))
		{
			target_pos = target_player->get_bone_pos(head);
		}
		else
		{
			target_pos = target_player->playerModel()->position() + Vector3(0, 1.49f, 0);
		}

		for (auto& angleDirection : angle) {
			Vector3 point = re_p + angleDirection;

			if (!isLOS(point, re_p) || !isValidPoint(point, target_pos, target_player, fat_default, fat_choice, fat_available)) continue;

			m_manipulate = angleDirection;

			return;
		}

		m_manipulate = fat_available ? fat_choice : Vector3::Zero();
		other::manipulating_to_fat = fat_available;
	}
}

// CHECK MANIPULATION ON POINTS

namespace manipulator_check_visible {
	void m_check_visibility() {
		Vector3 re_p = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);
		Vector3 choice = Vector3::Zero();
		auto loco = LocalPlayer::Entity();
		double mm_max_eye;

		int mask = vars::weapons::penetrate ? 10551296 : 1503731969;
		Vector3 target_pos = target_player->transform()->position();
		float distance = Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), target_pos);

		if (vars::combat::bullet_tp && vars::combat::hitscan)
		{
			if (m_hitscan_manipulator.empty()) {
				if (utils::LineOfSight(re_p, target_player->get_bone_pos(head))) {
					m_manipulate = Vector3::Zero();
					return;
				}
			}
			else
			{
				if (utils::LineOfSight(re_p, m_hitscan_manipulator)) {
					m_manipulate = Vector3::Zero();
					return;
				}
			}
		}
		else
		{
			if (utils::LineOfSight(re_p, target_player->get_bone_pos(head))) {
				m_manipulate = Vector3::Zero();
				return;
			}
		}

		std::vector<Vector3> arr = {};
		auto _right = loco->eyes()->MovementRight();
		auto forward = loco->eyes()->MovementForward();
		for (int i = 0; i < 5; i += ((mm_max_eye < 5.f) ? 2 : 1))
		{
			float a = (float)(i / 2.f);
			Vector3 up = Vector3(0.f, 1.5f, 0.f);
			Vector3 down = Vector3(0.f, -1.6f, 0.f);
			Vector3 left = Vector3(-(_right.x * 8.5), 0.f, -(_right.z * 8.5));
			Vector3 right = Vector3(_right.x * 8.5, 0.f, _right.z * 8.5);

			Vector3 fwd = Vector3(forward.x * 8.5, 0.f, forward.z * 8.5);
			Vector3 bwd = Vector3(-forward.x * 8.5, 0.f, -forward.z * 8.5); 

			arr.push_back(Vector3::Lerp(Vector3::Zero(), up, a));
			arr.push_back(Vector3::Lerp(Vector3::Zero(), left, 8.5));
			arr.push_back(Vector3::Lerp(Vector3::Zero(), right, 8.5));
			arr.push_back(Vector3::Lerp(Vector3::Zero(), fwd, 8.5));
			arr.push_back(Vector3::Lerp(Vector3::Zero(), bwd, 8.5));
		};

		for (auto s : arr) {
			Vector3 point = re_p + s;

			if (!utils::LineOfSight(point, re_p))
				continue;

			if (vars::combat::bullet_tp && vars::combat::hitscan)
			{
				if (m_hitscan_manipulator.empty()) {
					if (!utils::LineOfSight(target_player->get_bone_pos(head), point)) continue;
				}
				else
				{
					if (!utils::LineOfSight(m_hitscan_manipulator, point)) continue;
				}
			}
			else
			{
				if (!utils::LineOfSight(target_player->get_bone_pos(head), point)) continue;
			}

			choice = s;
			break;
		}
		if (choice.empty()) {
			m_manipulate_check = Vector3::Zero();
			return;
		}

		m_manipulate_check = choice;
	}
}