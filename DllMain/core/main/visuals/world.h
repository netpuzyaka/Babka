void world_esp(BaseEntity* entity,char* buff) {
	if (settings::world::ore) {
		if (entity->class_name_hash() == STATIC_CRC32("OreResourceEntity")) {
			if (entity->ShortPrefabName_hash() == STATIC_CRC32("stone-ore") ||
				entity->ShortPrefabName_hash() == STATIC_CRC32("sulfur-ore") ||
				entity->ShortPrefabName_hash() == STATIC_CRC32("metal-ore")) {
				Vector2 screen;
				ImColor col(settings::world::colors::ore_color[0], settings::world::colors::ore_color[1], settings::world::colors::ore_color[2], settings::world::colors::ore_color[3]);

				std::string string; char buf[256] = { 0 };
				sprintf_s(buf, ("%.0f m"), entity->transform()->position().distance(LocalPlayer::Entity()->GetBoneByID(spine4)));
				string += buf;

				if (utils::w2s(entity->transform()->position(), screen)) {
					switch (entity->ShortPrefabName_hash()) {
					case STATIC_CRC32("stone-ore"):
						if (settings::world::ore_type[0]) {
							DrawString(screen.x, screen.y, col, "Stone Ore");
							DrawString(screen.x, screen.y - settings::player::font_size + 1, col, string.c_str());
						}
						break;
					case STATIC_CRC32("sulfur-ore"):
						if (settings::world::ore_type[1]) {
							DrawString(screen.x, screen.y, col, "Sulfur Ore");
							DrawString(screen.x, screen.y - settings::player::font_size + 1, col, string.c_str());
						}
						break;
					case STATIC_CRC32("metal-ore"):
						if (settings::world::ore_type[2]) {
							DrawString(screen.x, screen.y, col, "Metal Ore");
							DrawString(screen.x, screen.y - settings::player::font_size + 1, col, string.c_str());
						}
						break;
					}
				}
			}
		}
	}
	if (settings::world::dropped_items) {
		if (entity->ShortPrefabName_hash() == STATIC_CRC32("generic_world"))
		{
			ImColor col(settings::world::colors::dropped_items_color[0], settings::world::colors::dropped_items_color[1], settings::world::colors::dropped_items_color[2], settings::world::colors::dropped_items_color[3]);

			Vector2 screen;
			if (utils::w2s(entity->transform()->position(), screen)) {
				std::string string;	char buf[256] = { 0 };
				sprintf_s(buf, ("%ls"), entity->item()->info()->displayName()->english());
				string += buf;

				std::string string1; char buf1[256] = { 0 };
				sprintf_s(buf1, ("%.0f m"), entity->transform()->position().distance(LocalPlayer::Entity()->GetBoneByID(spine4)));
				string1 += buf1;

				DrawString(screen.x, screen.y, col, string.c_str());
				DrawString(screen.x, screen.y - settings::player::font_size + 1, col, string1.c_str());

			}
		}
	}
}