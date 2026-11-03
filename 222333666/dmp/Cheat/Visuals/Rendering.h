#include "menu/imgui/imgui_tricks.hpp"

ImColor percent_color(float percent) {
	float red, green, blue;
	if (percent < 0.5) {
		red = percent * 2.f * 255.f;
		green = 255.f;
		blue = 0.f;
	}
	else {
		red = 255.f;
		green = (2.f - 2.f * percent) * 255.f;
		blue = 0.f;
	}

	if (percent > 1.f)
		percent = 1.f;
	return ImColor(red,green,blue,255.f);
}
void pre_draw() {

	float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
	auto desynctime = Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime();
	auto desyncpercentage = (((desynctime / 0.85f) * 100.0f) + 1.f) / 100;
	float desynctime2 = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;
	if (vars::combat::draw_manip_radius)
	{
		if (vars::combat::vismp) {
			float ManipulatorCircleAnimation = ImTricks::Animations::FastFloatLerp(
				
				
				
				
				
				
				
				("ManipulatorCircle animation"), vars::combat::ManipulatorRadios && vars::misc::manipulator_indicator && GetAsyncKeyState(vars::keys::manipulated_key) && desyncpercentage > 0.1, 0.f, 1.f, 0.05f);
			float ManipulatorCircleAnimationFill = ImTricks::Animations::FastFloatLerp(("ManipulatorCircleFill animation"), vars::combat::ManipulatorRadios && vars::misc::manipulator_indicator && GetAsyncKeyState(vars::keys::manipulated_key) && desyncpercentage > 0.1, 0.f, 0.4f, 0.05f);
			if (ManipulatorCircleAnimation > 0.005f) {
				g_Render->DrawRing3D(LocalPlayer::Entity()->transform()->position(), desyncpercentage * 10, 190, ImColor(1.f, 0.f, 0.f, ManipulatorCircleAnimation), ImColor(1.f, 0.f, 0.f, ManipulatorCircleAnimationFill), 2.f, 0.f, true);
			}
		}
	}
	ent_loop();

	if (vars::players::targetline) {
		if (target_player != NULL && target_player->IsValid()) {
			static Vector2 startPos = Vector2(vars::stuff::ScreenWidth / 2.f, vars::stuff::ScreenHeight / 2.f);
			Vector2 ScreenPos;
			if (!(target_player->get_bone_pos(spine1).x == 0 && target_player->get_bone_pos(spine1).y == 0 && target_player->get_bone_pos(spine1).z == 0)) {
				if (utils::w2s(target_player->get_bone_pos(head), ScreenPos)) {
					g_Render->DrawLine(startPos.x, startPos.y, ScreenPos.x, ScreenPos.y, ImColor(vars::colors::target_color[0], vars::colors::target_color[1], vars::colors::target_color[2]), 1.2f, true);
				}
			}
		}
	}
	float ManipulatorAnimation = ImTricks::Animations::FastFloatLerp(("ManipulatorInd animation"), vars::misc::manipulator_indicator , 0.f, 1.f, 0.05f);
	if (ManipulatorAnimation>0.001f) {
		float size = 150;
		g_Render->FilledRect(xs - (size / 2), ys - 30, size, 6.f, ImColor(0.f, 0.f, 0.f, ManipulatorAnimation), 0, 0);
		if (vars::misc::manipulator_indicator && GetAsyncKeyState(vars::keys::manipulated_key)) {
			float ManipulatorAnimationac = ImTricks::Animations::FastFloatLerp(("ManipulatorInd Active animation"), vars::misc::manipulator_indicator && desyncpercentage > 0.001 , 0.f, 1.f, 0.05f);

			if (ManipulatorAnimationac > 0.005) {
				float size = 150;
				float x = (desynctime * size);
				if (x > (size) * 2) x = (size) * 2;

				g_Render->FilledRect(xs - (size / 2)+1, ys - 30+1, x-2, 6.f-2, g_Render->PercentColor(desyncpercentage, ManipulatorAnimationac), 0, 0);
			}
		}
		Vector2 screen;
		if (vars::combat::BulletTeleportGradient && vars::stuff::best_target != Vector3(0, 0, 0))
			if (utils::w2s(vars::stuff::best_target, screen))
				g_Render->AddRadialGradient(ImVec2(screen.x, screen.y), vars::visuals::xueta, ImColor(vars::colors::one_color.x, vars::colors::one_color.y, vars::colors::one_color.z, 25.f), ImColor(vars::colors::one_color.x, vars::colors::one_color.y, vars::colors::one_color.z, 0.f));
	}
	float FlyhackAnimation = ImTricks::Animations::FastFloatLerp(("Flyhack animation"), vars::misc::flyhack_indicator , 0.f, 1.f, 0.05f);

	if (FlyhackAnimation > 0.001f) {
		float barv = 5.0f;
		g_Render->FilledRect(screen_center.x - 125, barv, 250, 10, ImColor(0.f, 0.f, 0.f, FlyhackAnimation));
		g_Render->FilledRect(screen_center.x - 125, barv + 11, 250, 10, ImColor(0.f, 0.f, 0.f, FlyhackAnimation));
		float v, h;
		v = VFlyhack / (VMaxFlyhack - 1.0f);
		h = HFlyhack / (HMaxFlyhack - 1.0f);
		g_Render->FilledRect(screen_center.x - 124, barv + 1, 248 * (v >= 1.0f ? 1.0f : v), 8, g_Render->PercentColor(v, FlyhackAnimation));
		g_Render->FilledRect(screen_center.x - 124, barv + 12, 248 * (h >= 1.0f ? 1.0f : h), 8, g_Render->PercentColor(h, FlyhackAnimation));
	}
	int reload_anim = ImTricks::Animations::FastIntLerp(("ReloadInd animation"), vars::misc::reload_indicator , 0, 255, 15);
	if (reload_anim>1) {
		auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
		float size = 150;
		if (held) {
			if (held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {


				if (did_reload == false && time_since_last_shot <= (held->reloadTime() - (held->reloadTime() / 10)) && time_since_last_shot > 0) {
					g_Render->FilledRect(xs - (size / 2), ys - 37, size, 6.f, ImColor(0, 0, 0, reload_anim), 0, 0);
					float reloadDurationTotal = (held->reloadTime() - (held->reloadTime() / 10));
					float reloadDuration = time_since_last_shot;
					auto percentage = (((reloadDuration / reloadDurationTotal) * 100.0f) + 1.f) / 100;
					int reload_anim_active = ImTricks::Animations::FastIntLerp("ReloadInd1 animation", vars::misc::reload_indicator && percentage != 1, 0, 255, 15);

					if (reload_anim_active > 1) {
						ImVec2 center(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2);
						float size = 150;
						float x = (percentage * size);

						if (x > (size) * 2)
							x = (size) * 2; //s
						g_Render->FilledRect(xs - (size / 2) + 1, ys - 37 + 1, x - 2, 6.f - 2, ImColor(0, 200, 0, reload_anim_active), 0, 0);
					}
				}
				else {
					if (held->HasReloadCooldown()) {
						g_Render->FilledRect(xs - (size / 2), ys - 37, size, 6.f, ImColor(0, 0, 0, reload_anim), 0, 0);
						float SamReloadDuration = held->nextReloadTime() - GLOBAL_TIME;
						float SamReloadDurationTotal = held->CalculateCooldownTime(held->nextReloadTime(), held->reloadTime()) - GLOBAL_TIME;
						auto SamPercentage = (((SamReloadDuration / SamReloadDurationTotal) * 100.0f) + 1.f) / 100;
						int reload_anim_active = ImTricks::Animations::FastIntLerp(("ReloadInd2 animation"), vars::misc::reload_indicator && SamPercentage != 1, 0, 255, 15);

						if (reload_anim_active > 1) {
							ImVec2 center(vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2);
							float size = 150;
							float x = (SamPercentage * size);
							if (x > (size) * 2)
								x = (size) * 2; //s
							g_Render->FilledRect(xs - (size / 2)+1, ys - 37+1, x-2, 6.f-2, ImColor(0, 200, 0, reload_anim_active), 0, 0);

						}
					}
				}
			}
		}
	}
	float crosshair_anim = ImTricks::Animations::FastFloatLerp(("Crosshair animation"), vars::misc::crosshair, 0.f, 1.f, 0.05f);
	if (crosshair_anim > 0.01f) {
		//	"~manipulated~"
		g_Render->DrawFilledCircle(xs, ys, 2.5, ImColor(1.f, 1.f, 1.f, crosshair_anim));
	}
	float fov_anim = ImTricks::Animations::FastFloatLerp(("fov animation"), vars::combat::visualize_fov, 0.f, 1.f, 0.05f);
	if (fov_anim > 0.01f) {

		g_Render->DrawCircle(xs, ys, vars::combat::fov, 1.0f, ImColor(1.f, 1.f, 1.f, fov_anim));
	}

	int pos = 0;
	if (target_player)
	{
		if (vars::misc::TargetInfo && target_player != NULL && target_player->IsValid() && !show)
		{

			std::string _name(CStringA(target_player->_displayName()));
			g_Render->DrawString(xs, ys + 20 + pos, get_color(target_player), render2::outline | render2::centered_x, 2, 10, _name.c_str());
			pos += 11;
		}
	}
	if (vars::combat::manipulator && !m_manipulate.empty() && target_player != NULL) {
		g_Render->DrawString(xs, ys + 20+ pos, ImColor(255, 0, 0), render2::outline | render2::centered_x, 2, 10, ("~manipulated~"));
		pos += 11;
	}
	if (vars::misc::TeloportTopPlayer && GetAsyncKeyState(vars::keys::TeleportTopPlayer) && Math::Distance_3D(LocalPlayer::Entity()->get_bone_pos(head), target_player->get_bone_pos(head)) < 2.0f)
	{
		g_Render->DrawString(xs, ys + 20 + pos, ImColor(255, 0, 0), render2::outline | render2::centered_x, 2, 10, ("~teleport~"));
		pos += 11;
	}

	int w = 200, h = 102;


	if (vars::players::TargetBelt && show)
	{
		belt::belt_tab_mov(Vector2(w, h + 20.0f));
		g_Render->FilledRect(belt::pos.x, belt::pos.y, w, 20, ImColor(25, 25, 25), 3.f, ImDrawFlags_RoundCornersTop);
		g_Render->FilledRect(belt::pos.x, belt::pos.y + 20.0f, w, h, ImColor(30, 30, 30, 170), 3.f, ImDrawFlags_RoundCornersBottom);
		g_Render->FilledRect(belt::pos.x, belt::pos.y + h+23, w, 5, ImColor(0,0,0));
		g_Render->FilledRect(belt::pos.x + 1, belt::pos.y + h + 24, w/2.f, 3, ImColor(0, 230, 0));
		g_Render->DrawString(belt::pos.x + 1 + w/2, belt::pos.y + h + 18, ImColor(255, 255, 255), render2::centered_x | render2::outline, 2, 10, "50");


	}
}
void ImGuiRendering::BeginScene()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::Begin("##Backbuffer", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

	ImGui::SetWindowPos(ImVec2(0, 0), 0);
	ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), 0);
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	pre_draw();
	hitmarker::get().draw_hits(window->DrawList);
	g_Render->DrawString(10,10, ImColor(255, 255, 255), render2::outline, 3, 10, ("methadone || beta"));

}

void ImGuiRendering::EndScene()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->PushClipRectFullScreen();

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);
}
