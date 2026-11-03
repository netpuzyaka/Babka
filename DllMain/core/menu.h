#include "main/settings.h"
void init_begins() {
	ChildManager& cm = ChildManager::get();
	auto& widgets = WidgetsManager::get();

	//static bool bools[100];
	//static int ints[100];
	//static float floats[100];
	//static bool multicombo_values[5];
	//static float col[100][4] = { 255,255,255,255 };
	//static char buf[16];
	//widgets.Checkbox("Silent", &bools[5], 0, 0, 0, true);
	//widgets.SliderInt("Field of view", &ints[0], 0, 180, u8"%d°");
	//widgets.MultiCombo("Bones", multicombo_values, { "Head", "Neck", "Body", "Legs", "Arms" });
	//widgets.TextField("##Text Field", buf, 16, { 0, 0 }, "Type the text...", i_type_01);

	TabsManager::get().add_page(1, [&]() {
		BeginGroup();
		{
			cm.beginchild("Player");
			{
				widgets.Checkbox("Name", &settings::player::name, 0, settings::player::colors::name_color);
				widgets.Checkbox("Distance", &settings::player::distance, 0, settings::player::colors::distance_color);
				widgets.Checkbox("Team id", &settings::player::teamId, 0, settings::player::colors::teamId_color);
				widgets.Checkbox("Box", &settings::player::box, 0, settings::player::colors::box_color,[&]() {
					widgets.Combo("Box type", &settings::player::box_type, { "Default", "Corner" }); 
					widgets.Checkbox("Fill", &settings::player::fillbox, 0, settings::player::colors::fillbox_color);
				});
				widgets.Checkbox("Skeleton", &settings::player::skeleton, 0, settings::player::colors::skeleton_color);
				widgets.Checkbox("Healthbar", &settings::player::healthbar, 0, 0, [&]() {
					widgets.Checkbox("Custom color", &settings::player::healthbar_custom_color, 0, settings::player::colors::healthbar_color);
					widgets.Checkbox("Healthbar text", &settings::player::healthbar_text);
				});
				widgets.Checkbox("Looking direction", &settings::player::lookingdirection, 0, settings::player::colors::lookingdirection_color);
				widgets.Checkbox("Weapon", &settings::player::weapon, 0, settings::player::colors::weapon_color);
				widgets.Checkbox("Off arrows", &settings::player::off_arrows, 0, settings::player::colors::off_arrows_color,[&]() {
					widgets.Checkbox("Animation", &settings::player::off_arrows_animation);
				});
				widgets.MultiCombo("Show flags", settings::player::flags_players, { "Sleeper", "Wounded", "SafeZone", "Teammate"});
				widgets.MultiCombo("Ignoring", settings::player::ignoring_flags_players, { "Sleeper", "Wounded", "SafeZone", "Teammate" });
			}
			cm.endchild();

			cm.beginchild("Other");
			{
				widgets.SliderInt("Font size", &settings::player::font_size, 12, 15, "%dpx");
			}
			cm.endchild();
		}
		EndGroup();

		SameLine();

		BeginGroup();
		{
			cm.beginchild("World");
			{
				widgets.Checkbox("Ore", &settings::world::ore, 0, settings::world::colors::ore_color, [&]() {
					widgets.MultiCombo("Ore type", settings::world::ore_type, { "Stone ore", "Sulfur ore", "Metal ore" });
					});
				widgets.Checkbox("Dropped items", &settings::world::dropped_items, 0, settings::world::colors::dropped_items_color);

			}
			cm.endchild();
		}
		EndGroup();
		});

	TabsManager::get().add_page(4, [&]() {

		BeginGroup();
		{
			cm.beginchild("Settings");
			{
				widgets.Binder("Menu key", &settings::gui::key);
				widgets.Checkbox("Off screen bypass", &settings::gui::off_screen_bypass, 0, 0, 0, true);
			}
			cm.endchild();
		}
		EndGroup();
		});
}