int jitter = 1;
int jitter_speed = 10;
int spin_speed = 70;
int spin = 0; 

float VFlyhack = 0.0f;
float HFlyhack = 0.0f;
float VMaxFlyhack = 0.0f;
float HMaxFlyhack = 0.0f;
namespace entities {
	bool TargetVisible = false;
}
float flyhackDistanceVertical = 0.f;
float flyhackDistanceHorizontal = 0.f;
float flyhackPauseTime;
bool just_shot = false;
float fixed_time_last_shot = 0.0f;
bool did_reload = false;
float time_since_last_shot = 0.0f;
bool init, show = false;
#define null NULL
bool should_interactive = false;
Vector2 screen_center = {0, 0};
namespace variables {
	namespace manipulator {
		bool manipulated = false;
		Vector3 m_manipulate = Vector3::Zero();
		float m_last_manipulate_time = 0.0f;
		float desync = 0.0f;
	}
}

Vector3 fat_target = Vector3::Zero();

namespace InGame{
	namespace stor {
		Vector3 eye_pos = Vector3(0, 0, 0);
		uintptr_t uBase = NULL;
		uintptr_t closestPlayer = NULL;
		uintptr_t gBase = NULL;
	//	uintptr_t closestPlayer = NULL;

		uintptr_t closestHeli = NULL;
	}
}
bool matrixupdate = false;
namespace vars {
	namespace debug {
		bool debug = false;
		bool bullettartracer = false;
		bool bullettracer = false;
		bool espdebug = false;
		bool targetcolor = false;



	}
	namespace keys {
		int stashopen = 0;
		int TeleportTopPlayer = 0;
		int low_velocity_key = 0;
		int debugging = 0;
		int zoom = 0;
		int suicide = 0;
		int manipulated_key = 0;
		int ignore_stopper = 0;
		int bhop = 0;
		int speedkey = 0;
		int instakill = 0;

		int W{ 0x57 };
		int S{ 0x53 };
		int D{ 0x44 };
		int A{ 0x41 };
		int space{ 0x20 };
	}
	namespace stuff {
		int bttype = false;
		int font = 0;
		float size_font = 12.f;
		float testFloat = 0.f;

		Vector3 eyemani = Vector3(0,0,0);
		char ConfigName[0x100] = "";
		std::string selected_cfg = "";
		Vector3 best_target = Vector3(0, 0, 0);
		float anim_speed = 1.f;
		bool gongetflyhack = false;
		float flyhack = 0.f;
		float hor_flyhack = 0.f;
		float max_flyhack = 0.f;
		float max_hor_flyhack = 0.f;
		bool Panic = false;
		int ScreenHeight = 0;
		int ScreenWidth = 0;
	}
	namespace combat {
		int onal = 0;
		int autoshoot_type = 0;
		int bullet_counter = 0;
		bool tree_reflect = false;
		bool vismp = false;
		bool mpvis = false;
		bool manipulate_angle = false;
		bool m_check_bullet_tp = false;
		bool draw_manip_radius = false;
		bool hitscan = false;
		bool stw = false;
		bool ExtentForMoutend = false;
		bool hammerspam = false;
		bool ManipulatorRadios = false;
		bool BulletTeleportGradient = false;
		int hitbox = 0;
		bool pierce = false;
		bool bullet_tp = false;
		bool autoreload = false;
		bool instakill = false;
		bool autoshoot = false;
		int desync_autoshoot_type = 0;
		bool always_heli_rotor = false;
		bool Manipulator_shot_atBt = false;
		bool doubletap = false;
		int doubletaptype = 0;
		bool silent_melee = false;
		bool psilent = false;
		bool psilentheli = false;

		float fov = 100.f;
		float DesynctTime = 0.99f;

		bool visualize_fov = false;
		bool manipulator = false;
		bool ignore_sleepers = false;
		bool ignore_team = true;
		bool ignore_npc = false;
	}
	namespace weapons {
		bool test = false;
		bool test2 = false;
		float bullet_sizey = 0.19f;
		float bullet_sizex = 0.19f;
		float bullet_sizez = 0.19f;
		bool scale = false;
		bool huiznaet = false;
		int bullet_tp_type = 0;
		float bulletspeed = 1.00f;
		bool rapidfire = false;
		float fast_bullets_D = 1.0f;
		bool low_velocity = false;
		bool no_recoil = false;
		float recoil_control = 100.f;
		bool fast_bullets = false;
		bool penetrate = false;
		bool minicopter_aim = false;
		bool remove_attack_anim = false;
		bool no_spread = false;
		bool automatic = false;
		bool thick_bullet = false;
		bool no_sway = false;
		bool rapid_fire = false;
		bool eokatap = false;
		bool compound = false;
	}
	namespace players {
		int healthbarstyle = 0;
		float uptime = 2.f;
		bool chams = false;
		bool TargetBelt = false;
		bool DisableWeaponName = false;
		namespace healthbar_ {
			int font = 1;

		}
		namespace box_ {
			bool outline = false;
			bool colorcheck = true;

		}
		namespace skeleton_ {
			int font = 1;
			bool outline = false;
			bool colorcheck = true;
			ImColor color = ImColor(255, 255, 255);
		}
		namespace name_ {
			int font = 1;

			bool outline = true;
			bool colorcheck = true;
			ImColor color = ImColor(255, 255, 255);
		}
		namespace distance_ {
			int font = 1;

			bool outline = true;
			bool colorcheck = true;
			ImColor color = ImColor(255, 255, 255);
		}
		namespace weapon_ {
			int font = 1;

			bool outline = true;
			bool colorcheck = true;
			ImColor color = ImColor(255, 255, 255);
		}

		bool target_tracers = false;
		bool oof_arrows = false;
		bool sphere = false;
		bool distance = false;
		bool box = false;
		int boxstyle = 0;
		bool skeleton = false;
		bool name = false;
		bool healthbar = false;

		bool weapon = false;
		bool WeaponIcon = false;

		bool sleeperignore = false;
		bool targetline = false;
	}
	namespace npc {
		bool DisableWeaponName = false;
		bool distance = false;
		bool oof_arrows = false;
		bool box = false;
		bool skeleton = false;
		bool name = false;
		bool healthbar = false;
		bool weapon = false;
		bool WeaponIcon = false;
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
		int Allkillefect = 0;
		bool visded = false;
		bool onan = false;
		float xueta = 5.f;
		int ponan = 0;
		bool skycolor = false;
		bool show_distance_bulletTp = false;
		bool No_bobing = false;
		bool bradley_apc = false;
		bool patrol_heli = false;
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
	namespace misc {
		bool night_stars = false;
		float stars = 0.f;
		float hitmarker_duration = 1.f;
		bool sphere = false;
		bool local_bones = false;
		bool TargetBones = false;
		bool TargetInfo = false;
		bool interactive_debug = false;
		int gesture = 0;
		bool farmbot = false;
		float intensivity = 1;
		bool farmbot_trees = false;
		bool farmbot_ore = false;
		bool farmbot_barrels = false;

		int hitmaterial = 0;
		bool auto_pickup = false;
		bool auto_farm = false;

		bool TeloportTopPlayer = false;

		bool hitmarker = false;
		bool damagemarker = false;
		int fakelag = 0;

		int modelstate = 0;
		bool crosshair = false;
		bool zoom = false;
		bool jesus = false;

		float fotsize = 12.f;
		bool bhop = false;
		bool fly_auto_stopper = false;
		bool weapon_spam = false;
		bool fast_loot = false;
		bool AspectRatio = false;

		bool flyhack_indicator = false;
		bool reload_indicator = false;
		bool manipulator_indicator = false;

		bool spiderman = false;
		bool better_jump = false;
		bool no_fall = false;
		bool auto_farm_ore = false;
		bool auto_farm_tree = false;
		bool can_attack = false;

		bool faster_healing = false;
		bool suicide = false;

		bool annoyer = false;
		bool bright_ambient = false;
		int Sphera = 0;
		float fov = 90.f;
		float ratio = 1.4f;

		bool omnidirectional_sprinting = false;
		bool fakeadmin = false;
		bool custom_time = false;
		float time = 10.0f;
	}
	namespace colors {
		float sleep_color[] = { 1.f, 1.f, 0.f };
		float team_color[] = { 0.f, 255.f, 0.f };
		ImVec4 marker = { 255.f, 255.f, 0.f, 255.f };
		float oof_color[] = { 255.f, 255.f, 255.f };
		float npc_name_color[] = { 255.f, 255.f, 255.f };
		float npc_healthdist_color[] = { 255.f, 255.f, 255.f };
		float npc_weapons_color[] = { 255.f, 255.f, 255.f };
		float target_color[] = { 255.f, 255.f, 255.f };

		float npc_skeleton_color[] = { 255.f, 255.f, 255.f };
		float npc_box_color[] = { 255.f, 255.f, 255.f };

		ImVec4 ambient_color = { 0.8f, 0.8f, 0.8f, 0.8f };
		ImVec4 sky_color = { 0.8f, 0.8f, 0.8f, 0.8f };
		ImVec4 one_color = { 1.f, 0.0f, 0.0f, 1.f };
		ImVec4 damagemarker = { 1.f, 0.0f, 0.0f, 1.f };
		ImVec4 hitmarker = { 1.f, 0.0f, 0.0f, 1.f };

		ImVec4 two_color = { 1.f, 0.0f, 0.0f, 0.0f };
		ImVec4 angle = { 1.f, 0.f, 0.f, 1.0f };
		ImVec4 mov_line = { 255.f, 0.f, 255.f, 255.f };

		float colsphere[] = { 1.f, 1.f,1.f };

		float BulletTp_color[] = { 1.f, 1.f,1.f ,1.f };
	}
	namespace visible {
		float skeleton_color[] = { 255.f, 255.f, 255.f };
		float box_color[] = { 255.f, 255.f, 255.f };
	}
	namespace invisible {
		float skeleton_color[] = { 255.f, 255.f, 255.f };
		float box_color[] = { 0.f, 255.f, 255.f };
	}
}