void corpse(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
	if (settings::visuals::other::corpse) {
		if (strstr(buff, ("player_corpse.prefab"))) {

			BaseEntity* corpse = (BaseEntity*)Object;
			if (corpse) {
				Vector3 pos = corpse->transform()->position();
				float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
				Vector2 screen;
				std::string string2 = "Corpse";
				if (utils::w2s(pos, screen) && distance <= settings::visuals::other::draw_distance) {
					if (settings::visuals::other::show_distance) {

						char buf2[256] = { 0 }; sprintf_s(buf2, "[ %.1fm ]", distance);
						string2 += buf2;
					}
					DrawString(screen.x, screen.y, ImColor(255, 0, 0, 255), string2.c_str());

				}
			}
		}
	}
}
void tc(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
	if (settings::visuals::base::tc) {
		if (strstr(buff, ("cupboard.tool.deployed.prefab"))) {

			BaseEntity* cupboard = (BaseEntity*)Object;
			if (cupboard) {
				Vector3 pos = cupboard->transform()->position();
				float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= settings::visuals::base::draw_distance) {
					int upkeep = safe_read(cupboard + 0x728, float); // private float cachedProtectedMinutes;
					std::string string;
					char buf[256] = { 0 }; sprintf_s(buf, "Tool Cupboard | %d hours", upkeep / 60);
					string = buf;
					if (settings::visuals::base::show_distance) {
						std::string string2;
						char buf2[256] = { 0 }; sprintf_s(buf2, "[ %.1fm ]", distance);
						string += buf2;
					}

					DrawString(screen.x, screen.y, ImColor(0, 255, 0, 255), string.c_str());
				}
			}
		}
	}
}
void sleepingbag(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
	if (settings::visuals::base::sleeping_bag) {
		if (strstr(buff, ("sleepingbag_leather_deployed.prefab"))) {

			BaseEntity* bag = (BaseEntity*)Object;
			if (bag) {
				Vector3 pos = bag->transform()->position();
				float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
				Vector2 screen;
				std::string string2 = "Sleeping Bag";
				if (utils::w2s(pos, screen) && distance <= settings::visuals::base::draw_distance) {
					if (settings::visuals::base::show_distance) {

						char buf2[256] = { 0 }; sprintf_s(buf2, "[ %.1fm ]", distance);
						string2 += buf2;
					}
					DrawString(screen.x, screen.y, ImColor(128, 128, 0), string2.c_str());

				}
			}
		}
	}
}
void bed(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
	if (settings::visuals::base::bed) {
		if (strstr(buff, ("bed_deployed.prefab"))) {

			BaseEntity* bag = (BaseEntity*)Object;
			if (bag) {
				Vector3 pos = bag->transform()->position();
				float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
				Vector2 screen;
				std::string string2 = "Bed";
				if (utils::w2s(pos, screen) && distance <= settings::visuals::base::draw_distance) {
					if (settings::visuals::base::show_distance) {
						char buf2[256] = { 0 }; sprintf_s(buf2, "[ %.1fm ]", distance);
						string2 += buf2;
					}
					DrawString(screen.x, screen.y, ImColor(107, 142, 35), string2.c_str());

				}
			}
		}
	}
}
void stash(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
	typedef bool(__stdcall* IsHidden)(BaseEntity*);
	if (settings::visuals::other::stash) {
		if (strstr(buff, ("small_stash_deployed.prefab"))) {

			BaseEntity* stash = (BaseEntity*)Object;
			if (stash) {
				Vector3 pos = stash->transform()->position();
				float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= settings::visuals::other::draw_distance) {

					std::string string = "Stash";
					if (settings::visuals::other::show_distance) {

						char buf[256] = { 0 }; sprintf_s(buf, "[ %.1fm ]", distance);
						string += buf;
					}
					DrawString(screen.x, screen.y, ImColor(255, 255, 0), string.c_str());


				}
			}
		}
	}
}

void hackablecrate(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
	typedef bool(__stdcall* IsBeingHacked)(BaseEntity*);
	typedef bool(__stdcall* IsFullyHacked)(BaseEntity*);
	if (settings::visuals::crates::chinook) {
		if (strstr(buff, ("codelockedhackablecrate.prefab"))) {

			BaseEntity* crate = (BaseEntity*)Object;
			if (crate) {
				Vector3 pos = crate->transform()->position();
				float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen)) {
					uintptr_t timerText = safe_read(crate + 0x530, uintptr_t); // public Text timerText; || public class HackableLockedCrate
					auto* m_Text = reinterpret_cast<pUncStr>(safe_read(timerText + 0xD0, DWORD64));
					ImColor color;

					std::string _name((LPCSTR)CStringA(m_Text->str));

					color = ImColor(255, 69, 0);


					std::string string = "Chinook Crate";
					char buf[256] = { 0 }; sprintf_s(buf, "[ %.1fm ]", distance);
					string = buf;
					DrawString(screen.x, screen.y, ImColor(255, 255, 255), string.c_str());
				}
			}
		}
	}
}
void world(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
	typedef uintptr_t(__stdcall* GetItem)(uintptr_t);
	if (settings::visuals::other::dropped_items) {
		if (strstr(buff, ("world"))) {

			BaseEntity* item = (BaseEntity*)Object;
			if (item) {
				Vector3 pos = item->transform()->position();
				float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), pos);
				Vector2 screen;
				if (utils::w2s(pos, screen) && distance <= settings::visuals::other::draw_distance) {
					uintptr_t Item = safe_read(item + 0x188, uintptr_t); // public Item item; || public class WorldItem : BaseEntity
					uintptr_t itemDefinition = safe_read(Item + 0x18, uintptr_t);
					uintptr_t displayName = safe_read(itemDefinition + 0x30, uintptr_t);
					auto* english = reinterpret_cast<pUncStr>(safe_read(displayName + 0x10, DWORD64)); // public static readonly DisplayNameAttribute Default; || private string _displayName;
					int amount = safe_read(Item + 0x28, int);

					std::wstring eng = std::wstring(english->str);
					if (!(eng.find((L"Arrow")) != std::wstring::npos) && !(eng.find((L"Nails")) != std::wstring::npos)) {
						std::string string;
						char buf[256] = { 0 }; sprintf_s(buf, "%ls", english->str);
						string = buf;
						if (settings::visuals::other::show_distance) {
							char buf[256] = { 0 }; sprintf_s(buf, "[ %.1fm ]", distance);
							string += buf;

						}
						DrawString(screen.x, screen.y, ImColor(255, 255, 255, 255), string.c_str());

					}
				}
			}
		}
	}
}
void world_render(DWORD64 ObjectClass, DWORD64 Entity, char* buff)
{

	corpse(ObjectClass, Entity, buff);
	tc(ObjectClass, Entity, buff);
	sleepingbag(ObjectClass, Entity, buff);
	bed(ObjectClass, Entity, buff);
	stash(ObjectClass, Entity, buff);
	hackablecrate(ObjectClass, Entity, buff);
	world(ObjectClass, Entity, buff);
	if (settings::ores::show_collectables) {
		miscvis(Entity, buff, settings::ores::stone, settings::ores::show_distance, settings::ores::draw_distance, ("stone-collectable.prefab"), (L"Stone Collectable"), ImColor(255, 255, 255));
		miscvis(Entity, buff, settings::ores::sulfur, settings::ores::show_distance, settings::ores::draw_distance, ("sulfur-collectable.prefab"), (L"Sulfur Collectable"), ImColor(255, 215, 0));
		miscvis(Entity, buff, settings::ores::metal, settings::ores::show_distance, settings::ores::draw_distance, ("metal-collectable.prefab"), (L"Metal Collectable"), ImColor(139, 69, 19));
	}
	miscvis(Entity, buff, settings::ores::stone, settings::ores::show_distance, 20, ("stone-collectable.prefab"), (L"Stone Collectable"), ImColor(255, 255, 255));
	miscvis(Entity, buff, settings::ores::stone, settings::ores::show_distance, settings::ores::draw_distance, ("stone-ore.prefab"), (L"Stone Ore"), ImColor(255, 255, 255));
	miscvis(Entity, buff, settings::ores::sulfur, settings::ores::show_distance, settings::ores::draw_distance, ("sulfur-ore.prefab"), (L"Sulfur Ore"), ImColor(255, 215, 0));
	miscvis(Entity, buff, settings::ores::metal, settings::ores::show_distance, settings::ores::draw_distance, ("metal-ore.prefab"), (L"Metal Ore"), ImColor(139, 69, 19));
	miscvis(Entity, buff, settings::visuals::crates::elite, settings::visuals::crates::show_distance, settings::visuals::crates::draw_distance, ("crate_elite.prefab"), (L"Elite Crate"), ImColor(46, 139, 87));
	miscvis(Entity, buff, settings::visuals::crates::military, settings::visuals::crates::show_distance, settings::visuals::crates::draw_distance, ("crate_normal.prefab"), (L"Military Crate"), ImColor(1, 68, 33));
	miscvis(Entity, buff, settings::visuals::crates::supply, settings::visuals::crates::show_distance, settings::visuals::crates::draw_distance, ("supply_drop.prefab"), (L"Airdrop"), ImColor(0, 139, 139));
	miscvis(Entity, buff, settings::visuals::crates::heli, settings::visuals::crates::show_distance, settings::visuals::crates::draw_distance, ("heli_crate.prefab"), (L"Heli Crate"), ImColor(1, 50, 32));
	miscvis(Entity, buff, settings::visuals::crates::bradley, settings::visuals::crates::show_distance, settings::visuals::crates::draw_distance, ("bradley_crate.prefab"), (L"Bradley Crate"), ImColor(173, 255, 47));
	miscvis(Entity, buff, settings::visuals::vehicles::minicopter, settings::visuals::vehicles::show_distance, settings::visuals::vehicles::draw_distance, ("minicopter.entity.prefab"), (L"Minicopter"), ImColor(0, 0, 255));
	miscvis(Entity, buff, settings::visuals::vehicles::scrapheli, settings::visuals::vehicles::show_distance, settings::visuals::vehicles::draw_distance, ("scraptransporthelicopter.prefab"), (L"Scrap Heli"), ImColor(0, 0, 139));
	miscvis(Entity, buff, settings::visuals::vehicles::boat, settings::visuals::vehicles::show_distance, settings::visuals::vehicles::draw_distance, ("rowboat.prefab"), (L"Boat"), ImColor(173, 216, 230));
	miscvis(Entity, buff, settings::visuals::vehicles::rhib, settings::visuals::vehicles::show_distance, settings::visuals::vehicles::draw_distance, ("rhib.prefab"), (L"RHIB"), ImColor(224, 255, 255));
	miscvis(Entity, buff, settings::visuals::turrets::auto_turret, settings::visuals::turrets::show_distance, settings::visuals::turrets::draw_distance, ("autoturret_deployed.prefab"), (L"Auto Turret"), ImColor(255, 255, 255));
	miscvis(Entity, buff, settings::visuals::turrets::flame_turret, settings::visuals::turrets::show_distance, settings::visuals::turrets::draw_distance, ("flameturret.deployed.prefab"), (L"Flame Turret"), ImColor(255, 140, 0));
	miscvis(Entity, buff, settings::visuals::turrets::shotgun_turret, settings::visuals::turrets::show_distance, settings::visuals::turrets::draw_distance, ("guntrap.deployed.prefab"), (L"Shotgun Trap"), ImColor(105, 105, 105));
	miscvis(Entity, buff, settings::visuals::turrets::landmine, settings::visuals::turrets::show_distance, settings::visuals::turrets::draw_distance, ("landmine.prefab"), (L"Landmine"), ImColor(138, 43, 226));
	miscvis(Entity, buff, settings::visuals::turrets::sam_site, settings::visuals::turrets::show_distance, settings::visuals::turrets::draw_distance, ("sam_site_turret_deployed.prefab"), (L"SAM Site"), ImColor(176, 224, 230));
	miscvis(Entity, buff, settings::visuals::turrets::bear_trap, settings::visuals::turrets::show_distance, settings::visuals::turrets::draw_distance, ("beartrap.prefab"), (L"Beartrap"), ImColor(255, 248, 220));
	miscvis(Entity, buff, settings::visuals::other::hemp, settings::visuals::other::show_distance, settings::visuals::other::draw_distance, ("hemp-collectable.prefab"), (L"Hemp"), ImColor(50, 205, 50));
	miscvis(Entity, buff, settings::visuals::base::boxes, settings::visuals::base::show_distance, settings::visuals::base::draw_distance, ("box.wooden.large.prefab"), (L"Box"), ImColor(188, 143, 143));
	miscvis(Entity, buff, settings::visuals::other::bodybag, settings::visuals::other::show_distance, settings::visuals::other::draw_distance, ("item_drop_backpack.prefab"), (L"Bodybag"), ImColor(139, 0, 139));
	miscvis(Entity, buff, settings::visuals::animals::bear, settings::visuals::animals::show_distance, settings::visuals::animals::draw_distance, ("bear.prefab"), (L"Bear"), ImColor(139, 69, 19));
	miscvis(Entity, buff, settings::visuals::animals::wolf, settings::visuals::animals::show_distance, settings::visuals::animals::draw_distance, ("wolf.prefab"), (L"Wolf"), ImColor(119, 136, 153));
	miscvis(Entity, buff, settings::visuals::animals::pig, settings::visuals::animals::show_distance, settings::visuals::animals::draw_distance, ("boar.prefab"), (L"Pig"), ImColor(255, 136, 77));
	miscvis(Entity, buff, settings::visuals::animals::chicken, settings::visuals::animals::show_distance, settings::visuals::animals::draw_distance, ("chicken.prefab"), (L"Chicken"), ImColor(173, 255, 47));
	miscvis(Entity, buff, settings::visuals::animals::deer, settings::visuals::animals::show_distance, settings::visuals::animals::draw_distance, ("horse.prefab"), (L"Horse"), ImColor(244, 164, 96));
}