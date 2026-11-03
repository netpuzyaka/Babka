bool hitscaning = false;
void hitscan_void() { // CREDIT FOR HELP / CMETANA
	BasePlayer* targetPlayer = reinterpret_cast<BasePlayer*>(settings::closestPlayer);

	if (utils::LineOfSight(targetPlayer->GetBoneByID(head), best_target))
		best_target = targetPlayer->GetBoneByID(head);
	auto loco = LocalPlayer::Entity();
	Vector3 re_p = targetPlayer->GetBoneByID(head);
	std::vector<Vector3> angle_static = {};
	auto _right = targetPlayer->eyes()->MovementRight();
	auto forward = targetPlayer->eyes()->MovementForward();
	float radius_ = 2.56f;
	Vector3 targetheadpos = targetPlayer->GetBoneByID(head);
	for (int i = 0; i < 30; i += 1)
	{
		float theta = static_cast<float>(Math::rand()) / static_cast<float>(0x7fff) * 2 * M_PI;
		float phi = static_cast<float>(Math::rand()) / static_cast<float>(0x7fff) * M_PI;

		float x = radius_ * Mathf::Sin(phi) * Mathf::Cos(theta);
		float y = radius_ * Mathf::Sin(phi) * Mathf::Sin(theta);
		float z = radius_ * Mathf::Cos(phi);

		Vector3 point = Vector3(x, y, z);
		angle_static.push_back(point);
	};


	if (!utils::LineOfSight(LocalPlayer::Entity()->eyes()->position(), targetPlayer->transform_(head)->position()))
	{
		for (auto s : angle_static) {
			Vector3 point = re_p + s;

			if (!utils::LineOfSight(targetPlayer->GetBoneByID(head), point)) continue;
			if (!utils::LineOfSight(LocalPlayer::Entity()->eyes()->position(), point) && !GetAsyncKeyState(settings::misc::manipulator_key)) continue;
			if (utils::LineOfSight(LocalPlayer::Entity()->eyes()->position(), targetPlayer->GetBoneByID(head)))
			{
				best_target = targetPlayer->GetBoneByID(head);
				hitscaning = false;
			}
			else
			{
				best_target = point;
			}
			break;
		}
	}
}