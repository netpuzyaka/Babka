#pragma once
namespace settings {
	namespace player {
		inline bool name = false;
		inline bool box = false;
		inline bool weapon = false;
		inline bool teamId = false;
		inline bool fillbox = false;
		inline bool lookingdirection = false;
		inline bool healthbar = false;
		inline bool healthbar_text = false;
		inline bool healthbar_custom_color = false;
		inline bool off_arrows_animation = false;
		inline bool skeleton = false;
		inline bool distance = false;
		inline bool off_arrows = false;
		inline bool flags_players[4];
		inline bool ignoring_flags_players[4];
		inline int box_type = 0;
		inline int font_size = 13;
		namespace colors {
			inline float name_color[4] = { 1.f,1.f, 1.f,1.f };
			inline float healthbar_color[4] = {1.f, 1.f, 1.f,1.f};
			inline float skeleton_color[4] = { 1.f,1.f, 1.f,1.f };
			inline float teamId_color[4] = { 0.f, 1.f, 0.f,1.f };
			inline float distance_color[4] = { 1.f, 1.f, 1.f,1.f };
			inline float fillbox_color[4] = { 0.f,0.f, 0.f,0.3f };
			inline float lookingdirection_color[4] = { 1.f,1.f, 1.f,1.f };
			inline float weapon_color[4] = { 1.f,1.f, 1.f,1.f };
			inline float off_arrows_color[4] = { 1.f,1.f, 1.f,1.f };
			inline float box_color[4] = { 1.f,1.f, 1.f,1.f };
		}
	}
	namespace world {
		inline bool dropped_items = false;
		inline bool ore = false;
		inline bool ore_type[3];
		namespace colors {
			inline float dropped_items_color[4] = { 1.f,1.f, 1.f,1.f };
			inline float ore_color[4] = { 1.f,1.f, 1.f,1.f };
		}
	}

	namespace gui {
		inline int key = VK_HOME;
		inline bool menu = true;
		inline bool off_screen_bypass = false;
		inline ImVec2 screen_size;
	}
}