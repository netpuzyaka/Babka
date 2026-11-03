#include <string>
#include <windows.h>

static float off_arrows_alpha = 0;
static bool off_arrows_animation = false;

// Wide string -> UTF-8 (CStringA не используется: требует atlstr.h/MFC и ломает переносимость заголовка)
static std::string wide_to_utf8(const wchar_t* w) {
	if (!w) return std::string();
	const int len = ::WideCharToMultiByte(CP_UTF8, 0, w, -1, nullptr, 0, nullptr, nullptr);
	if (len <= 1) return std::string();
	std::string out(static_cast<size_t>(len - 1), '\0');
	::WideCharToMultiByte(CP_UTF8, 0, w, -1, out.data(), len - 1, nullptr, nullptr);
	return out;
}

void player_esp(BasePlayer* Player) {
	if (settings::player::ignoring_flags_players[0] && Player->get_flag(PlayerFlags::Sleeping)) { return; }
	else if (settings::player::ignoring_flags_players[1] && Player->get_flag(PlayerFlags::Wounded)) { return; }
	else if (settings::player::ignoring_flags_players[2] && Player->get_flag(PlayerFlags::SafeZone)) { return; }
	else if (settings::player::ignoring_flags_players[3] && LocalPlayer::Entity()->is_teammate(Player)) { return; }

	Box2D box{};
	if (utils::compute_player_box_from_bones(Player, box)) {
		ImFont* font = fonts[fonts_::esp_font].get(settings::player::font_size);
		const float w = box.right - box.left;
		const float h = box.bottom - box.top;
		const float cx = box.left + w * 0.5f;
		int pos = settings::player::font_size - 4;
		int pos_ = settings::player::font_size - 4;
		if (settings::player::name) {
			ImColor col(settings::player::colors::name_color[0], settings::player::colors::name_color[1], settings::player::colors::name_color[2], settings::player::colors::name_color[3]);

			std::string _name(wide_to_utf8(Player->_displayName()));
			DrawString(cx, box.top - pos_, col, _name.c_str());
			pos_ += settings::player::font_size - 1;
		}
		if (settings::player::distance)
		{
			ImColor col(settings::player::colors::distance_color[0], settings::player::colors::distance_color[1], settings::player::colors::distance_color[2], settings::player::colors::distance_color[3]);
			std::string string; char buf[256] = { 0 };
			sprintf_s(buf, ("%.0f m"), Player->GetBoneByID(spine4).distance(LocalPlayer::Entity()->GetBoneByID(spine4)));
			string += buf;
			DrawString(cx, box.top - pos_, col, string.c_str());
			pos_ += settings::player::font_size - 1;
		}

		if (settings::player::box) {
			if (settings::player::fillbox) {
				ImColor col(settings::player::colors::fillbox_color[0], settings::player::colors::fillbox_color[1], settings::player::colors::fillbox_color[2], settings::player::colors::fillbox_color[3]);
				FilledRect(box.left, box.top, w, h, col);
			}
			ImColor col(settings::player::colors::box_color[0], settings::player::colors::box_color[1], settings::player::colors::box_color[2], settings::player::colors::box_color[3]);

			if (settings::player::box_type == 0) {
				DrawESPBox({ box.left, box.top }, { box.right, box.bottom }, col);
			}
			else {
				DrawCornerBox({ box.left, box.top }, { box.right, box.bottom }, col);
			}
		}
		if (settings::player::lookingdirection)
		{
			ImColor col(settings::player::colors::lookingdirection_color[0], settings::player::colors::lookingdirection_color[1], settings::player::colors::lookingdirection_color[2], settings::player::colors::lookingdirection_color[3]);

			Vector2 screen;
			Vector2 head_1;
			auto head_pos = Player->GetBoneByID(head);
			if (utils::w2s(Player->GetBoneByID(head) + Player->eyes()->BodyForward(), screen) && utils::w2s(head_pos, head_1))
			{
				DrawLine(head_1.x, head_1.y, screen.x, screen.y, col, 1.5f, true);
			}
		}
		if (settings::player::skeleton) {
			float dist = Player->GetBoneByID(head).distance(LocalPlayer::Entity()->GetBoneByID(head));
			if (dist < 250.f) {
				ImColor col(settings::player::colors::skeleton_color[0], settings::player::colors::skeleton_color[1], settings::player::colors::skeleton_color[2], settings::player::colors::skeleton_color[3]);
				auto head_b = Player->GetBoneByID(head);
				auto spine4_b = Player->GetBoneByID(spine4);
				auto spine1_b = Player->GetBoneByID(spine1);
				auto l_upperarm_b = Player->GetBoneByID(l_upperarm);
				auto l_forearm_b = Player->GetBoneByID(l_forearm);
				auto l_hand_b = Player->GetBoneByID(l_hand);
				auto r_upperarm_b = Player->GetBoneByID(r_upperarm);
				auto r_forearm_b = Player->GetBoneByID(r_forearm);
				auto r_hand_b = Player->GetBoneByID(r_hand);
				auto l_hip_b = Player->GetBoneByID(l_hip);
				auto l_knee_b = Player->GetBoneByID(l_knee);
				auto l_foot_b = Player->GetBoneByID(l_foot);
				auto r_hip_b = Player->GetBoneByID(r_hip);
				auto r_knee_b = Player->GetBoneByID(r_knee);
				auto r_foot_b = Player->GetBoneByID(r_foot);
				auto r_toe_b = Player->GetBoneByID(r_toe);
				auto l_toe_b = Player->GetBoneByID(l_toe);

				Vector2 head, spine, l_upperarm, l_forearm, l_hand, r_upperarm, r_forearm, r_hand, spine1, l_hip, l_knee, l_foot, r_hip, r_knee, r_foot, l_toe, r_toe;
				if (utils::w2s(head_b, head) &&
					utils::w2s(spine4_b, spine) &&
					utils::w2s(l_upperarm_b, l_upperarm) &&
					utils::w2s(l_forearm_b, l_forearm) &&
					utils::w2s(l_hand_b, l_hand) &&
					utils::w2s(r_upperarm_b, r_upperarm) &&
					utils::w2s(r_forearm_b, r_forearm) &&
					utils::w2s(spine1_b, spine1) &&
					utils::w2s(r_hand_b, r_hand) &&
					utils::w2s(l_hip_b, l_hip) &&
					utils::w2s(l_knee_b, l_knee) &&
					utils::w2s(l_foot_b, l_foot) &&
					utils::w2s(r_hip_b, r_hip) &&
					utils::w2s(r_knee_b, r_knee) &&
					utils::w2s(r_toe_b, r_toe) &&
					utils::w2s(l_toe_b, l_toe) &&
					utils::w2s(r_foot_b, r_foot)) {

					DrawLine({ head.x,head.y }, { spine.x,spine.y }, col, 1.2f);
					DrawLine({ spine.x,spine.y }, { l_upperarm.x,l_upperarm.y }, col, 1.2f);
					DrawLine({ l_upperarm.x,l_upperarm.y }, { l_forearm.x,l_forearm.y }, col, 1.2f);
					DrawLine({ l_forearm.x,l_forearm.y }, { l_hand.x,l_hand.y }, col, 1.2f);
					DrawLine({ spine.x,spine.y }, { r_upperarm.x,r_upperarm.y }, col, 1.2f);
					DrawLine({ r_upperarm.x,r_upperarm.y }, { r_forearm.x,r_forearm.y }, col, 1.2f);
					DrawLine({ r_forearm.x,r_forearm.y }, { r_hand.x,r_hand.y }, col, 1.2f);
					DrawLine({ spine.x,spine.y }, { spine1.x,spine1.y }, col, 1.2f);
					DrawLine({ spine1.x,spine1.y }, { l_hip.x,l_hip.y }, col, 1.2f);
					DrawLine({ l_hip.x,l_hip.y }, { l_knee.x,l_knee.y }, col, 1.2f);
					DrawLine({ l_knee.x,l_knee.y }, { l_foot.x,l_foot.y }, col, 1.2f);
					DrawLine({ spine1.x,spine1.y }, { r_hip.x,r_hip.y }, col, 1.2f);
					DrawLine({ r_hip.x,r_hip.y }, { r_knee.x,r_knee.y }, col, 1.2f);
					DrawLine({ r_knee.x,r_knee.y }, { r_foot.x,r_foot.y }, col, 1.2f);
					DrawLine({ r_foot.x,r_foot.y }, { r_toe.x,r_toe.y }, col, 1.2f);
					DrawLine({ l_foot.x,l_foot.y }, { l_toe.x,l_toe.y }, col, 1.2f);

				}
			}
		}
		if (settings::player::teamId && Player->currentTeam() != 0) {
			ImColor col = ImColor(settings::player::colors::teamId_color[0], settings::player::colors::teamId_color[1], settings::player::colors::teamId_color[2], settings::player::colors::teamId_color[3]);
			std::string string = std::to_string(Player->currentTeam());
			ImVec2 textSize = font->CalcTextSizeA(12.f, FLT_MAX, 0.0f, string.c_str());
			DrawString( box.right + 5 + textSize.x / 2, box.top + textSize.y / 2, col, string.c_str());
		}
		if (settings::player::healthbar)
		{
			const float cur = Player->health();
			const float maxh = max(100, Player->health());
			const float t = std::clamp(cur / maxh, 0.0f, 1.0f);

			int red = 0x50, green = 0xFF, blue = 0x50;
			if (cur >= 25.0f) {
				if (cur <= 50.0f) { red = 0xD7; green = 0xC8; blue = 0x50; }
			}
			else {
				red = 0xFF; green = 0x32; blue = 0x50;
			}

			ImColor barCol = settings::player::healthbar_custom_color ? ImColor(settings::player::colors::healthbar_color[0], settings::player::colors::healthbar_color[1], settings::player::colors::healthbar_color[2], settings::player::colors::healthbar_color[3]): ImColor(red, green, 0, 255);

			char hp_text[16]{};
			std::snprintf(hp_text, sizeof(hp_text), "%.0f", cur);

			Vector2 barPos = { box.left - 5.0f, box.top };
			Vector2 barSize = { 4.0f, h };
			Progbar(barPos, barSize, cur, maxh, barCol, 2.0f, true);

			if (settings::player::healthbar_text) {
				ImVec2 textSize = font->CalcTextSizeA(settings::player::font_size, FLT_MAX, 0.0f, hp_text);

				const float innerTop = barPos.y + 1.0f;
				const float innerBottom = barPos.y + barSize.y - 1.0f;
				const float innerH = max(0.0f, innerBottom - innerTop);

				float fillCenter = innerBottom - innerH * t;

				const float halfH = textSize.y;
				fillCenter = min(fillCenter, innerBottom - halfH);
				fillCenter = max(fillCenter, innerTop);

				const float text_x = barPos.x - textSize.x - 2;
				const float text_y = fillCenter;

				DrawString(text_x, text_y, ImColor(255, 255, 255), hp_text, true, false);

			}
		}

		if (settings::player::weapon)
		{
			ImColor col(settings::player::colors::weapon_color[0], settings::player::colors::weapon_color[1], settings::player::colors::weapon_color[2], settings::player::colors::weapon_color[3]);
			
			Item* ActWeapon = Player->GetHeldItem();
			if (ActWeapon) {
				std::string string;	char buf[256] = { 0 };
				sprintf_s(buf, ("%ls"), ActWeapon->get_name());
				string += buf;
				DrawString(cx, box.bottom + pos, col, string.c_str());
				pos += settings::player::font_size - 1;
			}
			else {
				DrawString(cx, box.bottom + pos, col, "Empty");
				pos += settings::player::font_size - 1;
			}
		}

		if (settings::player::flags_players[0] && Player->get_flag(PlayerFlags::Sleeping)) {
			DrawString(cx, box.bottom + pos, ImColor(255, 180, 0), "Sleeper");
			pos += settings::player::font_size - 1;
		}
		if (settings::player::flags_players[1] && Player->get_flag(PlayerFlags::Wounded)) {
			DrawString(cx, box.bottom + pos, ImColor(255, 0, 0), "Wounded");
			pos += settings::player::font_size - 1;
		}
		if (settings::player::flags_players[2] && Player->get_flag(PlayerFlags::SafeZone)) {
			DrawString(cx, box.bottom + pos, ImColor(0, 255, 79), "SafeZone");
			pos += settings::player::font_size - 1;
		}
		if (settings::player::flags_players[3] && LocalPlayer::Entity()->is_teammate(Player)) {
			DrawString(cx, box.bottom + pos, ImColor(40, 255, 0), "Teammate");
			pos += settings::player::font_size - 1;
		}
	}
	else if (settings::player::off_arrows)
	{
		constexpr float RAD2DEG = 57.2957795f;
	
		Vector3 localSpine = LocalPlayer::Entity()->GetBoneByID(spine4);
		Vector3 targetSpine = Player->GetBoneByID(spine4);
	
		float deltaX = localSpine.x - targetSpine.x;
		float deltaZ = localSpine.z - targetSpine.z;
	
		Vector3 localEyesEuler = Math::EulerAngles(MainCamera::Camera()->Get_Rotation());
		float yawDeltaDeg = std::atan2(deltaX, deltaZ) * RAD2DEG - 180.0f - localEyesEuler.y;
	
		int screenCenterX = static_cast<int>(settings::gui::screen_size.x / 2);
		int screenCenterY = static_cast<int>(settings::gui::screen_size.y / 2);
	
		Vector2 tipPoint = ComputeDirectionPoint(yawDeltaDeg, 5.0f, screenCenterX, screenCenterY, 150.0f);
		Vector2 leftPoint = ComputeDirectionPoint(yawDeltaDeg + 2.0f, 3.0f, screenCenterX, screenCenterY, 140.0f);
		Vector2 rightPoint = ComputeDirectionPoint(yawDeltaDeg - 2.0f, 3.0f, screenCenterX, screenCenterY, 140.0f);
	
		ImColor col( settings::player::colors::off_arrows_color[0], settings::player::colors::off_arrows_color[1], settings::player::colors::off_arrows_color[2], settings::player::off_arrows_animation ? off_arrows_alpha : settings::player::colors::off_arrows_color[3]);
	
		bool isTeammate = LocalPlayer::Entity()->is_teammate(Player);
		ImColor finalColor = isTeammate ? ImColor(0, 255, 0) : col;
	
		DrawTriangle(tipPoint.x, tipPoint.y, leftPoint.x, leftPoint.y, rightPoint.x, rightPoint.y, finalColor);
	}
}
