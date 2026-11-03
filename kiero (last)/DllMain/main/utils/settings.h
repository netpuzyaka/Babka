inline ImDrawList* DrawList;
Vector3 best_target = Vector3(0, 0, 0);

float bullet_tp_radius;

namespace settings
{
	char ConfigName[0x100] = "cfg";
	bool isreloading = false;
	bool just_shot = false;
	float fixed_time_last_shot = 0.0f;
	bool did_reload = false;
	float time_since_last_shot = 0.0f;
	uintptr_t closestPlayer = NULL;
	float hor_flyhack = 0.f;
	float flyhack = 0.f;
	float max_flyhack = 0.f;
	static std::string selected_cfg = "";
	float max_hor_flyhack = 0.f;
	MODULEENTRY32W gBase;
	ImVec2 screen_size = {0, 0};
	namespace combat
	{
		float bullet_counter = 1;
		bool visualize_fov = false;
		bool rapid_fire = false;
		bool manipulator = false;
		bool rapid_shoot = false;
		bool manipulate_angle = false;
		bool instantbullet  = false;
		bool draw_radius_on_player = false;
		bool hit_scan = false;
		int rapidshoot_key = 0;
		bool psilent = false;
		bool ladder_reflect = false;
		bool silentmelee = false;
		bool powershoot = false;
		bool hammerspam = false;
		bool autoreload = false;
		bool manipulator_indicator = false;
		bool projectile_skip = false;
		int autoshoot_key{ };
		int powershoot_key{ };
		int autoshoot_key_mode = 0;
		bool target_name = false;
		int fov = 100;
		bool autoshoot = false;
		static bool ignore_players_type[4] = { false, false, false, false };
		int bones_target = 0;
		static float fov_color[4] = { 255 , 255 , 255 , 255 };
	}
	namespace weapons
	{
		bool compound = false;
		bool fastbow = false;
		bool minicopter_aim = false;
		bool no_recoil = false;
		bool hamerdraw = false;
		int recoil_control = 100.f;
		float bulottp = 2.560f;
		int fast_bullet_value = 1;
		bool penetrate = false;
		bool fast_bullets = false;
		int no_spread_value = 100;
		int manipulator_mode = 1;
		bool show_radius = false;
		bool eokatap = false;
		bool automatic = false;
		bool no_sway = false;
		bool show_predict_trajectory = false;
		bool no_spread = false;
		bool bullet_tp = false;
		bool stw = false;
		bool sphere_on_self = false;
		bool aimhelper = false;
	}
	namespace visual
	{
		static float target_trasers_color[4] = { 255 , 255 , 255 , 255 };
		bool name = false;
		bool target_trasers = false;
		bool fillbox = false;
		bool box = false;
		bool ShowAlerts = false;
		int boxstyle = 0;
		bool belt = false;
		bool lookingdirection = false;
		int arrow_dist = 140;
		int arrow_size = 2;
		bool ignore_sleepers = false;
		static float wounded_color[4] = { 255 , 0 , 0 };
		static float sleeper_color[4] = { 255 , 180 , 0 };
		static float Lookingdirection_color[4] = { 255 , 255 , 255, 255 };
		static float box_color[4] = { 255 , 255 , 255 , 255 };
		static float chams_color[4] = { 255 , 255 , 255, 255 };
		static float name_color[4] = { 255 , 255 , 255, 255 };
		static float weapon_color[4] = { 255 , 255 , 255, 255 };
		int font_scale = 12.f;
		static float off_color[4] = { 255 , 255 , 255, 255 };
		static float distance_color[4] = { 255 , 255 , 255, 255 };
		static float skeleton_color[4] = { 255 , 255 , 255, 255 };
		bool skeleton = false;
		static bool ignore_players_type[2] = { false, false };
		static bool flags_players[4] = { false, false, false, false };
		bool weapon = false;
		bool distance = false;
		bool ignore_wounded = false;
		bool off_arrors = false;
		float box_corner_length = 3.5f;
	}
	namespace ores {
		bool closest_ore = false;
		bool show_collectables = false;
		bool stone = false;
		bool sulfur = false;
		bool metal = false;
		bool show_distance = false;
		float draw_distance = 300.f;
	}
	namespace visuals {
		namespace chams {
			bool hand_chams = false;

			int chams_render_mode = 0;
			int hand_chams_type = 0;
			int weapon_chams_type = 0;
		}

		namespace base {
			bool tc = false;
			bool sleeping_bag = false;
			bool bed = false;
			bool boxes = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace vehicles {
			bool minicopter = false;
			bool scrapheli = false;
			bool boat = false;
			bool rhib = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace turrets {
			bool auto_turret = false;
			bool flame_turret = false;
			bool shotgun_turret = false;
			bool landmine = false;
			bool sam_site = false;
			bool bear_trap = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace other {
			bool dropped_items = false;
			bool bodybag = false;
			bool corpse = false;
			bool stash = false;
			bool debyyg = false;
			bool hemp = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace crates {
			bool elite = false;
			bool military = false;
			bool supply = false;
			bool chinook = false;
			bool heli = false;
			bool bradley = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace animals {
			bool bear = false;
			bool pig = false;
			bool chicken = false;
			bool wolf = false;
			bool deer = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
	}
	namespace npc
	{
		bool name = false;
		bool box = false;
		int boxstyle = 0;
		static float box_color[3] = { 255, 196, 0 };
		static float name_color[3] = { 255, 196, 0 };
		static float weapon_color[3] = { 255, 196, 0 };
		static float off_color[3] = { 255, 196, 0 };
		static float distance_color[3] = { 255, 196, 0 };
		static float skeleton_color[3] = { 255, 196, 0 };
		bool skeleton = false;
		bool weapon = false;
		bool distance = false;
	}
	namespace misc
	{
		int spam_mode = 0;
		bool hammer_spam = false;
		bool chatspam = false;
		bool speedhackindicator = false;
		float speedhackspeed = 9.9f;
		int spam_key = 0;
		int predict_type = 0;
		bool mie_changer = false;
		int followprojectile_key{ };
		bool walk_to_marker = false;
		bool skycolor = false;
		bool no_rain = false;
		bool custom_hitsound = false;
		int hitsound_style = 0;
		bool auto_upgrade = false;
		float mie = 1.f;
		bool brightness_changer = false;
		float brightness = 1.f;
		bool rayleigh_changer = false;
		bool followprojectile = false;
		bool flyhack_indicator = false;
		float rayleigh = 1.f;
		bool speedhack = false;

		float speedhacksoso;
		float speedhack_cur;

		bool ModelState = false;
		bool stesh_finder = false;
		int debugging = 0;
		int modelstate = 0;
		int font = 0;
		int stesh_finder_key = 0;
		bool interactive_debug = false;
		bool auto_pickup = false;
		static float sky_color_col[3] = { 200 , 0 , 0 };
		bool mass_suicide = false;
		bool aspect_ratio = false;
		bool fly_auto_stop = false;
		int weapon_spam_key = 0;
		bool weapon_spam = false;
		int mass_suicide_key = 0;
		bool omnidirectional_sprinting = false;
		bool fakeadmin = false;
		bool walkonwater = false;
		bool movement_line = false;
		int walkonwaterkey = { };
		int speedhackbind = { };
		bool walker = false;
		bool inf_jump = false;
		bool spiderman = false;
		int zoom_key = 0;
		bool can_attack = false;
		int manipulator_key = 0;
		bool fov = false;
		int hitmaterial = 0;
		bool anti_aim = false;
		int fov_scale = 90;
		float aspect_ratio_value = 1.8f;
		bool bright_ambient = false;
		bool gizmo_sphere = false;
		bool reload_coldown = false;
		bool bullet_tracers = false;
		bool fast_loot = false;
	}
	namespace menu
	{
		bool watermark = true;
		bool show = true;
		bool panic = false;
		float alpha_menu = 1.f;
	}
}