static bool aiir = false;
static float color_a = 0;
#include "player_esp.h"
#include "world_esp.h"

void enity_loop() {
{
		color_a = ImLerp(color_a, aiir ? 1.f : 0.f, ImGui::GetIO().DeltaTime * 4.f);
		if (color_a <= 0.01f || color_a >= 0.99f) aiir = !aiir;
		float xs = settings::screen_size.x / 2, ys = settings::screen_size.y / 2;
		float FOV = settings::combat::fov, CurFOV;
		auto entityList = BaseNetworkable::clientEntities()->entityList();
		for (int i = 0; i < entityList->vals->size; i++) {
			uintptr_t Entity = *reinterpret_cast<uintptr_t*>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
			auto entity = *reinterpret_cast<BaseEntity**>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
			if (!Entity) continue;
			uintptr_t Object = *reinterpret_cast<uint64_t*>(Entity + 0x10);
			if (!Object) continue;
			uintptr_t ObjectClass = *reinterpret_cast<uint64_t*>(Object + 0x30);
			if (!ObjectClass) continue;
			pUncStr name = read(ObjectClass + 0x60, pUncStr); if (!name) continue;
			char* buff = name->stub;

			if (!reinterpret_cast<BaseEntity*>(Entity)->IsValid()) { continue; }
			if (!reinterpret_cast<Component*>(Entity)->gameObject()) { continue; }
			if (strstr(buff, ("Local"))) { continue; }

			if (reinterpret_cast<BaseCombatEntity*>(Entity)->IsPlayer()) {
				BasePlayer* Player = (BasePlayer*)Entity;
				
				if(Player->IsNpc() && !settings::npc::name && !settings::npc::distance && !settings::npc::weapon && !settings::npc::box && !settings::npc::skeleton && !settings::combat::ignore_players_type[2])  continue;
				if (!Player->IsNpc())
				{
					render_esp_player(Player);
				}
				else 
				{
					render_esp_npc(Player);
				}
				bool Playerwounded = Player->get_flag(64);
				if (settings::combat::ignore_players_type[0] && Player->get_flag(PlayerFlags::Sleeping)) continue;
				if (Playerwounded && settings::combat::ignore_players_type[1])	continue;
				if (Player->IsNpc() && settings::combat::ignore_players_type[2])	continue;
				if (LocalPlayer::Entity()->is_teammate(Player) && settings::combat::ignore_players_type[3]) continue;
				if (FOV > (CurFOV = GetFov(Player, BoneList(0.5))) && Player->is_alive()) {
					if (GetFov(Player, BoneList(0.5)) < GetFov(reinterpret_cast<BasePlayer*>(settings::closestPlayer), BoneList(0.5)) || settings::closestPlayer == NULL)
					{
						FOV = CurFOV;
						settings::closestPlayer = (uintptr_t)Player;
					}
				}
			}
			else
			{
				world_render(ObjectClass,Entity,buff);
			}
		}
		BasePlayer* TargetPlayer = reinterpret_cast<BasePlayer*>(settings::closestPlayer);
		if (reinterpret_cast<BasePlayer*>(settings::closestPlayer)) {
			if (settings::combat::fov < (CurFOV = GetFov(reinterpret_cast<BasePlayer*>(settings::closestPlayer), BoneList(0.5)))) {
				settings::closestPlayer = NULL;
			}
		}
		if (TargetPlayer) {
			if (!TargetPlayer->is_alive()) {
				settings::closestPlayer = NULL;
			}
			if (TargetPlayer->GetBoneByID(head).x == 0 || TargetPlayer->GetBoneByID(head).y == 0 || TargetPlayer->GetBoneByID(head).z == 0) {
				settings::closestPlayer = NULL;
			}
			if (TargetPlayer->IsNpc() && settings::combat::ignore_players_type[2]) {
				settings::closestPlayer = NULL;
			}
			if (TargetPlayer->get_flag(PlayerFlags::Sleeping) && settings::combat::ignore_players_type[0]) {
				settings::closestPlayer = NULL;
			}
			if (LocalPlayer::Entity()->is_teammate(TargetPlayer) && settings::combat::ignore_players_type[3]) {
				settings::closestPlayer = NULL;
			}
			Vector2 screen;
			Quaternion Quaternion2;

			if (settings::combat::target_name)
			{
				std::string string;
				std::string _name(CStringA(TargetPlayer->_displayName()));
				char buf[256] = { 0 }; sprintf_s(buf, (CStringA(TargetPlayer->_displayName())));
				string += buf;
				DrawString(xs, ys - 50, ImColor(255, 255, 255), string.c_str());
			}

			if (settings::weapons::bullet_tp && settings::weapons::show_radius) {
				auto transform = TargetPlayer->GetBoneByID(head);

				float radius_x = 2.60f;
				float radius_y = 2.60f - 0.2;

				Vector3 center = transform - Vector3(0, 0.1, 0);
				const int numSegments = 5;
				static float rotation = 0.00f;
				rotation += 0.03f;
				const float angleIncrement = ((2 * IM_PI) / numSegments);
				int pointCount = 0;

				for (int i = 0; i < numSegments; ++i)
				{
					const float angle = angleIncrement * i + rotation;
					const float cosVal = std::cos(angle);
					const float sinVal = std::sin(angle);

					if (pointCount > 0) break;
					float x = center.x + radius_x * cosVal;
					float y = center.y + radius_y * sinVal;
					float z = center.z + radius_x * sinVal;
					float y2 = center.y + radius_y * cosVal;
					DDraw::Sphere_invis(Vector3(x, y, center.z), 0.05f, Color(1, 1, 1, 1), 0.01f, false, false);
					DDraw::Sphere_invis(Vector3(x, center.y, z), 0.05f, Color(1, 1, 1, 1), 0.01f, false, false);
					DDraw::Sphere_invis(Vector3(center.x, y2, z), 0.05f, Color(1, 1, 1, 1), 0.01f, false, false);
				}
			}
		}

		if (settings::misc::flyhack_indicator) {
			if (VFlyhack / VMaxFlyhack != 0 || HFlyhack / HMaxFlyhack != 0)
			{
				Progbar({ xs - 150, ys - 490 }, { 300, 7 }, VFlyhack / VMaxFlyhack, 1.f);
				Progbar({ xs - 150, ys - 500 }, { 300, 7 }, HFlyhack / HMaxFlyhack, 1.f);
			}
		}

		if (settings::misc::reload_coldown) {
			auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();

			float size = 200;
			if (held && held->class_name_hash() == STATIC_CRC32("BaseProjectile") || held->class_name_hash() == STATIC_CRC32("BowWeapon") || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1965232394 || held->class_name_hash() == STATIC_CRC32("CompoundBowWeapon") || held->class_name_hash() == STATIC_CRC32("BaseLauncher")) {
				if (settings::did_reload == false && settings::time_since_last_shot <= (held->reloadTime() - (held->reloadTime() / 10)) && settings::time_since_last_shot > 0) {
					float SamReloadDuration = settings::time_since_last_shot;
					float SamReloadDurationTotal = (held->reloadTime() - (held->reloadTime() / 10));
					auto SamPercentage = (((SamReloadDuration / SamReloadDurationTotal) * 100.0f) + 1.f) / 100;
					float Num = 1 - SamPercentage;
					if (SamPercentage < 0.1)
						Num = 0;

					float size = 100;
					DrawString(xs, ys + 55.f - 10.f, ImColor(255, 255, 255), "Reloading");
					FilledRect(xs - (size / 2), ys + 55.f, size, 6.f, ImColor(14, 14, 14), 6, 0);
					if (Num != 0) {
						if (Num > 1.f)
							Num = 1.f;

						float x = (SamPercentage * size);
						if (x > (size) * 2)
							x = (size) * 2; //s

						if (x <= size)
						{
							FilledRect(xs - (size / 2), ys + 55.f, x - 2, 6.f, ImColor(0, 255, 0), 6, 0);
							Rect(xs - (size / 2), ys + 55.f, size, 6.f, ImColor(58, 58, 58), 6, 0);
						}
					}
				}
				else if (held->HasReloadCooldown()) {
					float SamReloadDuration = held->nextReloadTime() - GLOBAL_TIME;
					float SamReloadDurationTotal = held->CalculateCooldownTime(held->nextReloadTime(), held->reloadTime()) - GLOBAL_TIME;
					auto SamPercentage = (((SamReloadDuration / SamReloadDurationTotal) * 100.0f) + 1.f) / 100;
					float red, green, blue;
					float Num = SamPercentage;
					if (SamPercentage < 0.1)
						Num = 0;

					float size = 100;
					DrawString(xs, ys + 55.f - 10.f, ImColor(255, 255, 255), "Reloading");
					FilledRect(xs - (size / 2), ys + 55.f, size, 6.f, ImColor(14, 14, 14), 6, 0);
					if (Num != 0) {
						if (Num > 1.f)
							Num = 1.f;

						float x = (SamPercentage * size);
						if (x > (size) * 2)
							x = (size) * 2; //s

						if (x <= size)
						{
							FilledRect(xs - (size / 2), ys + 55.f, x - 2, 6.f, ImColor(0, 255, 0), 6, 0);
							Rect(xs - (size / 2), ys + 55.f, size, 6.f, ImColor(58, 58, 58), 6, 0);
						}


					}
				}
			}
		}
		if (settings::combat::visualize_fov) {
			DrawCircle(settings::screen_size.x / 2, settings::screen_size.y / 2, settings::combat::fov, 1.2f, ImColor(settings::combat::fov_color[0], settings::combat::fov_color[1], settings::combat::fov_color[2]));
		}
	}
}

void esp_render()
{
		DrawList = ImGui::GetBackgroundDrawList();
		enity_loop();
}