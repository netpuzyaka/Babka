
void render_esp_player(BasePlayer* BP)
{
	if (!BP->is_alive()) return;
	if (settings::visual::ignore_players_type[0] && BP->get_flag(PlayerFlags::Sleeping)) return;
	if (BP->get_flag(64) && settings::visual::ignore_players_type[1])	return;
	box_bounds ret = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };
	BoneList Bones[15] = {
		l_foot, l_knee, l_hip,
		r_foot, r_knee, r_hip,
		spine1, neck, head,
		l_upperarm, l_forearm, l_hand,
		r_upperarm, r_forearm, r_hand
	};
	CornerBox cornerBox;
	for (int j = 0; j < 15; j++)
	{
		auto currentBoneV3 = BP->GetBoneByID(BoneList(Bones[j])); Vector2 bone_screen;
		if (Bones[j] == BoneList(head))
		{
			currentBoneV3.y += 0.2f;
		}
		else if (Bones[j] == BoneList(r_foot) || Bones[j] == BoneList(l_foot))
		{
			currentBoneV3.y -= 0.2f;
		}
		utils::w2s(currentBoneV3, bone_screen);
		if (bone_screen.x < ret.left)
		{
			ret.left = bone_screen.x;
			cornerBox.left = currentBoneV3;
		}
		if (bone_screen.x > ret.right)
		{
			ret.right = bone_screen.x;
			cornerBox.right = currentBoneV3;
		}
		if (bone_screen.y < ret.top)
		{
			ret.top = bone_screen.y;
			cornerBox.top = currentBoneV3;
		}
		if (bone_screen.y > ret.bottom)
		{
			ret.bottom = bone_screen.y;
			cornerBox.bottom = currentBoneV3;
		}
	}
	if (ret.empty()) cornerBox.Valid = false;
	Vector2 left;
	auto leftw2s = utils::w2s(cornerBox.left, left);
	Vector2 right;
	auto rightw2s = utils::w2s(cornerBox.right, right);
	Vector2 top;
	auto topw2s = utils::w2s(cornerBox.top, top);
	Vector2 bottom;
	auto bottomw2s = utils::w2s(cornerBox.bottom, bottom);
	float Entity_x = left.x;
	float Entity_y = top.x;
	float Entity_h = left.x - right.x;
	float Entity_w = Entity_h / 2;
	int pos = 8;
	if (cornerBox.Valid && leftw2s || rightw2s || topw2s || bottomw2s)
	{
		if (settings::visual::name)
		{
			std::string _name(WideToAnsi(BP->_displayName()));
			DrawString(left.x - Entity_w, top.y - 8.f, ImColor(settings::visual::name_color[0], settings::visual::name_color[1], settings::visual::name_color[2]), _name.c_str());
			pos += settings::visual::font_scale - 1;
		}
		if (settings::visual::distance)
		{
			std::string string; char buf[256] = { 0 };
			sprintf_s(buf, ("%.1fm"), Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(spine4), BP->GetBoneByID(spine4)));
			string += buf;
			DrawString(left.x - Entity_w, top.y - pos, ImColor(settings::visual::distance_color[0], settings::visual::distance_color[1], settings::visual::distance_color[2]), string.c_str());
			pos += settings::visual::font_scale - 1;
		}

		if (settings::visual::fillbox) {
			DrawList->AddImageRounded(
				preview_slow,
				ImVec2(left.x, top.y),
				ImVec2(right.x, bottom.y),
				ImVec2(0, 0), ImVec2(1, 1),
				ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1)),
				6.f);
		}

		float box_width = ret.right - ret.left;
		float box_height = ret.bottom - ret.top;

		if (settings::visual::box)
		{
		    if (settings::visual::boxstyle == 0)
		    {
				//DrawList->AddImageRounded(
				//	kakrazz,
				//	ImVec2(box_width, box_height),
				//	ImVec2(ret.left, ret.top),
				//	ImVec2(0, 0), ImVec2(1, 1),
				//	ImGui::GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1)),
				//	6.f);

				// render kakrazz

				DrawEspBox({ left.x, top.y }, { right.x , bottom.y }, ImColor(settings::visual::box_color[0], settings::visual::box_color[1], settings::visual::box_color[2]), 0.5f);
		    }
			else if (settings::visual::boxstyle == 1)
			{
				DrawCornerBox({ left.x, top.y }, { right.x, bottom.y }, ImColor(settings::visual::box_color[0], settings::visual::box_color[1], settings::visual::box_color[2]));// corner
			}
			
		}
		if (settings::visual::lookingdirection)
		{
			Vector2 forwardd;
			auto head_pos = BP->GetBoneByID(head);
			Vector2 head_1;
			if (utils::w2s(BP->GetBoneByID(head) + (BP->eyes()->BodyForward() * 2), forwardd) && utils::w2s(head_pos, head_1))
			{
				DrawLine(head_1.x, head_1.y, forwardd.x, forwardd.y, ImColor(settings::visual::Lookingdirection_color[0], settings::visual::Lookingdirection_color[1], settings::visual::Lookingdirection_color[2]), 1.5f, true);
			}
		}
		if (settings::visual::target_trasers)
		{
			auto* TargetPlayer = reinterpret_cast<BasePlayer*>(settings::closestPlayer);
			Vector2 head_;
			if (utils::w2s(TargetPlayer->GetBoneByID(head), head_))
			{
				DrawLine(settings::screen_size.x / 2, settings::screen_size.y / 2, head_.x, head_.y, ImColor(settings::visual::target_trasers_color[0], settings::visual::target_trasers_color[1], settings::visual::target_trasers_color[2]), 1.5f, true);
			}
		}
		if (settings::visual::weapon)
		{
			Item* ActWeapon = BP->GetActiveWeapon();
			auto haveImage = get_icon_name(BP).texture.texture;
			if (!haveImage && settings::visual::weapon && BP->GetHeldItem()) {
				std::string string;	char buf[256] = { 0 };
				sprintf_s(buf, ("%ls"), ActWeapon->get_name());
				string += buf;
				DrawString(left.x - Entity_w, bottom.y + 8.f, ImColor(settings::visual::weapon_color[0], settings::visual::weapon_color[1], settings::visual::weapon_color[2]), string.c_str());
			}
			else if (!haveImage && settings::visual::weapon && !BP->GetHeldItem()) {
				DrawString(left.x - Entity_w, bottom.y  + 8.f, ImColor(settings::visual::weapon_color[0], settings::visual::weapon_color[1], settings::visual::weapon_color[2]), "Empty");
			}
			else if (settings::visual::weapon)
			{
				if (get_icon_name(BP).texture.texture && get_icon_name(BP).name != "")
				{
					DrawTexture(ImVec2(left.x - Entity_w, bottom.y ), get_icon_name(BP).size, ImColor(255, 255, 255), reinterpret_cast<void*>(get_icon_name(BP).texture.texture));
				}
			}
		}
		if (settings::visual::flags_players[0] && BP->get_flag(PlayerFlags::Sleeping)) {
			DrawString(left.x - Entity_w, top.y - pos , ImColor(255, 180, 0), "Sleeper");
			pos += settings::visual::font_scale - 1;
		}
		if (settings::visual::flags_players[1] && BP->get_flag(PlayerFlags::Wounded)) {
			DrawString(left.x - Entity_w, top.y - pos , ImColor(255, 0, 0), "Wounded");
			pos += settings::visual::font_scale - 1;
		}
		if (settings::visual::flags_players[2] && BP->get_flag(PlayerFlags::SafeZone)) {
			DrawString(left.x - Entity_w, top.y - pos , ImColor(0, 255, 79), "SafeZone");
			pos += settings::visual::font_scale - 1;
		}
		if (settings::visual::flags_players[3] && LocalPlayer::Entity()->is_teammate(BP)) {
			DrawString(left.x - Entity_w, top.y - pos , ImColor(40, 255, 0), "Teammate");
			pos += settings::visual::font_scale - 1;
		}
	
	
	}
	else if (settings::visual::off_arrors && !leftw2s && !rightw2s && !topw2s && !bottomw2s) {
		Vector3 local = LocalPlayer::Entity()->GetBoneByID(spine4);
		Vector3 cordi = BP->GetBoneByID(spine4);
		float y = local.x - cordi.x;
		float x = local.z - cordi.z;
		Vector3 eulerAngles = Math::EulerAngles(LocalPlayer::Entity()->eyes()->rotation());
		float angleYawRad = atan2(y, x) * 57.29578f - 180.f - eulerAngles.y;

		static float off_color_custom[3] = { 255 , 255 , 255 };
		auto playerpos = BP->GetBoneByID(head);
		auto localpos = LocalPlayer::Entity()->GetBoneByID(head);
		auto distance = playerpos.Distance(localpos);
		auto fwd = playerpos + (BP->eyes()->BodyForward() * distance);
		auto dist = fwd.Distance(localpos);
		auto r = (distance / 50.f); r = (r < 1.f ? 1.f : r);
		if (dist < r)
		{
			off_color_custom[0] = 255;
			off_color_custom[1] = 0;
			off_color_custom[2] = 0;
		}
		else
		{
			off_color_custom[0] = settings::visual::off_color[0];
			off_color_custom[1] = settings::visual::off_color[1];
			off_color_custom[2] = settings::visual::off_color[2];
		}
		Vector2 tp0 = CosTanSinLineH(angleYawRad, 5.f, settings::screen_size.x / 2, settings::screen_size.y / 2, 150.f);
		Vector2 tp1 = CosTanSinLineH(angleYawRad + 2.f, 3.f, settings::screen_size.x / 2, settings::screen_size.y / 2, 140.f);
		Vector2 tp2 = CosTanSinLineH(angleYawRad - 2.f, 3.f, settings::screen_size.x / 2, settings::screen_size.y / 2, 140.f);

		TriangleFilled(tp0.x, tp0.y, tp1.x, tp1.y, tp2.x, tp2.y, ImColor(off_color_custom[0], off_color_custom[1], off_color_custom[2], color_a));
	}
	
}
void render_esp_npc(BasePlayer* BP)
{
	box_bounds ret = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };
	BoneList Bones[15] = {
		l_foot, l_knee, l_hip,
		r_foot, r_knee, r_hip,
		spine1, neck, head,
		l_upperarm, l_forearm, l_hand,
		r_upperarm, r_forearm, r_hand
	};
	CornerBox cornerBox;
	for (int j = 0; j < 15; j++)
	{
		auto currentBoneV3 = BP->GetBoneByID(BoneList(Bones[j])); Vector2 bone_screen;
		if (Bones[j] == BoneList(head))
		{
			currentBoneV3.y += 0.2f;
		}
		else if (Bones[j] == BoneList(r_foot) || Bones[j] == BoneList(l_foot))
		{
			currentBoneV3.y -= 0.2f;
		}
		utils::w2s(currentBoneV3, bone_screen);
		if (bone_screen.x < ret.left)
		{
			ret.left = bone_screen.x;
			cornerBox.left = currentBoneV3;
		}
		if (bone_screen.x > ret.right)
		{
			ret.right = bone_screen.x;
			cornerBox.right = currentBoneV3;
		}
		if (bone_screen.y < ret.top)
		{
			ret.top = bone_screen.y;
			cornerBox.top = currentBoneV3;
		}
		if (bone_screen.y > ret.bottom)
		{
			ret.bottom = bone_screen.y;
			cornerBox.bottom = currentBoneV3;
		}
	}
	if (ret.empty()) cornerBox.Valid = false;
	Vector2 left;
	auto leftw2s = utils::w2s(cornerBox.left, left);
	Vector2 right;
	auto rightw2s = utils::w2s(cornerBox.right, right);
	Vector2 top;
	auto topw2s = utils::w2s(cornerBox.top, top);
	Vector2 bottom;
	auto bottomw2s = utils::w2s(cornerBox.bottom, bottom);
	float Entity_x = left.x;
	float Entity_y = top.x;
	float Entity_h = left.x - right.x;
	float Entity_w = Entity_h / 2;
	int pos = 8;
	if (cornerBox.Valid && leftw2s || rightw2s || topw2s || bottomw2s)
	{
		if (settings::npc::name)
		{

			std::string _name(WideToAnsi(BP->_displayName()));
			DrawString(left.x - Entity_w, top.y - 8.f, ImColor(255, 196, 0), _name.c_str());
			pos += settings::visual::font_scale - 1;
		}
		if (settings::npc::distance)
		{
			std::string string; char buf[256] = { 0 };
			sprintf_s(buf, ("%.1fm"), Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(spine4), BP->GetBoneByID(spine4)));
			string += buf;

			DrawString(left.x - Entity_w, top.y - pos, ImColor(255, 196, 0), string.c_str());
			pos += settings::visual::font_scale - 1;
		}
		if (settings::npc::box)
		{
			if (settings::npc::boxstyle == 0)
			{
				DrawEspBox(Vector2(left.x, top.y), Vector2(right.x, bottom.y), ImColor(255, 196, 0), 1.f);
			}
			else if (settings::npc::boxstyle == 1)
			{
				DrawCornerBox({ left.x, top.y }, { right.x, bottom.y }, ImColor(255, 196, 0));// corner
			}
		//	DrawCornerBox({ left.x, top.y }, { right.x, bottom.y }, ImColor(255, 196, 0));// corner
		}

		Item* ActWeapon = BP->GetActiveWeapon();
		if (settings::npc::weapon && !BP->HasPlayerFlag(PlayerFlags::Sleeping))
		{
			auto haveImage = get_icon_name(BP).texture.texture;
			if (!haveImage && settings::npc::weapon && BP->GetHeldItem()) {
				std::string string;	char buf[256] = { 0 };
				sprintf_s(buf, ("%ls"), ActWeapon->get_name());
				string += buf;
				DrawString(left.x - Entity_w, bottom.y + 8.f, ImColor(255, 196, 0), string.c_str());
			}
			else if (!haveImage && settings::npc::weapon && !BP->GetHeldItem()) {
				DrawString(left.x - Entity_w, bottom.y + 8.f, ImColor(255, 196, 0), "Empty");
			}
			else if (settings::npc::weapon)
			{
				if (get_icon_name(BP).texture.texture && get_icon_name(BP).name != "")
				{
					DrawTexture(ImVec2(left.x - Entity_w, bottom.y), get_icon_name(BP).size, ImColor(255, 255, 255), reinterpret_cast<void*>(get_icon_name(BP).texture.texture));
				}
			}
		}
	}
}