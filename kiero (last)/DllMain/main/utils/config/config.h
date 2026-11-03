#include <string>
#include <vector>
#include <Windows.h>
template <typename T>
class VarType
{
public:
	VarType(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};
namespace config_manager {
	void read_directory(const std::string& name, std::vector<std::string>& v);
}
void  config_manager::read_directory(const std::string& name, std::vector<std::string>& v) {
	std::string pattern(name);
	pattern.append("\\*");

	WIN32_FIND_DATA data;
	HANDLE find;

	if ((find = FindFirstFileA(pattern.c_str(), (LPWIN32_FIND_DATAA)&data)) != INVALID_HANDLE_VALUE) {
		do {
			std::string filename((char*)data.cFileName);
			if (filename.substr(filename.find_last_of(".") + 1) == ("cfg"))
				v.push_back(filename);
		} while (FindNextFileA(find, (LPWIN32_FIND_DATAA)&data) != 0);
		FindClose(find);
	}
}

std::string szPath = "";
std::vector<VarType<int>*> ints;
std::vector<VarType<bool>*> bools;
std::vector<VarType<float>*> floats;
class CConfig
{
public:
	std::vector < std::string > GetConfigList()
	{
		std::vector < std::string > m_ConfigList;
		for (const auto& p : std::filesystem::recursive_directory_iterator(("C:\\kiero\\")))
		{
			if (!std::filesystem::is_directory(p) && p.path().extension().string() == (".cfg"))
			{
				auto file = p.path().filename().string();
				m_ConfigList.push_back(file.substr(0, file.size() - 4));
			}
		}

		return m_ConfigList;
	}
	CConfig()
	{
		ints = std::vector<VarType<int>*>();
		bools = std::vector<VarType<bool>*>();
		floats = std::vector<VarType<float>*>();
	}

	void Initialize()
	{
		szPath = "C:\\kiero\\";
		Setup();
	}

	void Save()
	{
		std::string file;
		file = szPath + settings::selected_cfg + ".cfg";

		CreateDirectoryA(szPath.c_str(), NULL);

		for (VarType<int>* pValue : ints)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<float>* pValue : floats)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<bool>* pValue : bools)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), *pValue->value ? "1" : "0", file.c_str());
	}
	void Create()
	{
		std::string file;
		file = szPath + settings::ConfigName + ".cfg";

		CreateDirectoryA(szPath.c_str(), NULL);

		for (VarType<int>* pValue : ints)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<float>* pValue : floats)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<bool>* pValue : bools)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), *pValue->value ? "1" : "0", file.c_str());
	}
	void Remove()
	{
		std::string file;
		file = szPath + settings::selected_cfg + ".cfg";
		std::remove(file.c_str());
	}

	void Load()
	{
		std::string file;
		file = szPath + settings::selected_cfg + ".cfg";
		CreateDirectoryA(szPath.c_str(), NULL);

		char value_l[32] = { '\0' };

		for (VarType<int>* pValue : ints)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = atoi(value_l);
		}

		for (VarType<float>* pValue : floats)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = (float)atof(value_l);
		}

		for (VarType<bool>* pValue : bools)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = !strcmp(value_l, "1");
		}
	}

private:
	void SetupValue(int& value, int def, std::string category, std::string name)
	{
		value = def;
		ints.push_back(new VarType<int>(category, name, &value));
	}

	void SetupValue(bool& value, bool def, std::string category, std::string name)
	{
		value = def;
		bools.push_back(new VarType<bool>(category, name, &value));
	}

	void SetupValue(float& value, float def, std::string category, std::string name)
	{
		value = def;
		floats.push_back(new VarType<float>(category, name, &value));
	}


	void Setup()
	{
		SetupValue(settings::combat::psilent, false, ("Combat"), ("Psilent"));
		SetupValue(settings::misc::predict_type, 0, ("Combat"), ("predict_type"));
		SetupValue(settings::combat::visualize_fov, false , ("Combat"), ("Draw fov"));
		SetupValue(settings::combat::fov, 100, ("Combat"), ("Fov"));
		SetupValue(settings::combat::bones_target, 0, ("Combat"), ("bone target"));
		SetupValue(settings::weapons::manipulator_mode, 0, ("Combat"), ("manipulator_mode"));
		SetupValue(settings::misc::manipulator_key, 0, ("Combat"), ("manipulator_key"));

		SetupValue(settings::weapons::bullet_tp, false, ("Combat"), ("Bullet tp"));
		SetupValue(settings::weapons::stw, false, ("Combat"), ("STW"));
		SetupValue(settings::combat::manipulator, false, ("Combat"), ("Manipulator"));
		SetupValue(settings::combat::hit_scan, false, ("Combat"), ("Hit scan"));
		SetupValue(settings::combat::autoreload, false, ("Combat"), ("Auto reload"));
		SetupValue(settings::combat::ignore_players_type[0], false, ("Combat"), ("ignore_players_type 0"));
		SetupValue(settings::combat::ignore_players_type[1], false, ("Combat"), ("ignore_players_type 1"));
		SetupValue(settings::combat::ignore_players_type[2], false, ("Combat"), ("ignore_players_type 2"));
		SetupValue(settings::combat::ignore_players_type[3], false, ("Combat"), ("ignore_players_type 3"));
		SetupValue(settings::combat::target_name, false, ("Combat"), ("Target name"));
		SetupValue(settings::combat::powershoot, false, ("Combat"), ("Powershoot"));
		SetupValue(settings::combat::powershoot_key, 0, ("Combat"), ("Powershoot key"));
		SetupValue(settings::combat::bullet_counter, 1, ("Combat"), ("Bullet counter"));
		SetupValue(settings::combat::silentmelee, false, ("Combat"), ("silentmelee"));
		SetupValue(settings::combat::projectile_skip, false, ("Other"), ("projectile_skip"));
		SetupValue(settings::weapons::fastbow, false, ("Weapons"), ("fastbow"));
		SetupValue(settings::combat::draw_radius_on_player, false, ("Combat"), ("draw_radius_on_player"));
		SetupValue(settings::weapons::show_radius, false, ("Combat"), ("show_radius"));
		SetupValue(settings::weapons::fastbow, false, ("Combat"), ("fastbow"));

		//weapon
		SetupValue(settings::weapons::compound, false, ("Weapons"), ("compound"));
		SetupValue(settings::weapons::minicopter_aim, false, ("Weapons"), ("minicopter_aim"));
		SetupValue(settings::weapons::no_recoil, false, ("Weapons"), ("no_recoil"));
		SetupValue(settings::weapons::recoil_control, 100, ("Weapons"), ("recoil_control"));
		SetupValue(settings::weapons::penetrate, false, ("Weapons"), ("penetrate"));
		SetupValue(settings::weapons::fast_bullets, false, ("Weapons"), ("fast_bullets"));
		SetupValue(settings::weapons::no_spread_value, 100, ("Weapons"), ("no_spread_value"));
		SetupValue(settings::weapons::eokatap, false, ("Weapons"), ("eokatap"));
		SetupValue(settings::weapons::automatic, false, ("Weapons"), ("automatic"));
		SetupValue(settings::combat::instantbullet, false, ("Weapons"), ("instantbullet"));
		SetupValue(settings::misc::can_attack, false, ("Weapons"), ("can_attack"));
		SetupValue(settings::weapons::no_sway, false, ("Weapons"), ("no_sway"));
		SetupValue(settings::weapons::no_spread, false, ("Weapons"), ("no_spread"));
		//visuals
		SetupValue(settings::visual::name, false, ("Visual"), ("name"));
		SetupValue(settings::visual::box, false, ("Visual"), ("box"));
		SetupValue(settings::visual::boxstyle, 0, ("Visual"), ("boxstyle"));
		SetupValue(settings::visual::belt, false, ("Visual"), ("belt"));
		SetupValue(settings::visual::lookingdirection, false, ("Visual"), ("lookingdirection"));
		SetupValue(settings::visual::ignore_sleepers, false, ("Visual"), ("ignore_sleepers"));
		SetupValue(settings::visual::Lookingdirection_color[0], 255, ("Visual"), ("Lookingdirection_color[0]"));
		SetupValue(settings::visual::Lookingdirection_color[1], 255, ("Visual"), ("Lookingdirection_color[1]"));
		SetupValue(settings::visual::Lookingdirection_color[2], 255, ("Visual"), ("Lookingdirection_color[2]"));

		SetupValue(settings::visual::box_color[0], 255, ("Visual"), ("box_color[0]"));
		SetupValue(settings::visual::box_color[1], 255, ("Visual"), ("box_color[1]"));
		SetupValue(settings::visual::box_color[2], 255, ("Visual"), ("box_color[2]"));


		SetupValue(settings::visual::name_color[0], 255, ("Visual"), ("name_color[0]"));
		SetupValue(settings::visual::name_color[1], 255, ("Visual"), ("name_color[1]"));
		SetupValue(settings::visual::name_color[2], 255, ("Visual"), ("name_color[2]"));
		SetupValue(settings::visual::fillbox, false, ("Visual"), ("fillbox"));
		SetupValue(settings::visual::weapon_color[0], 255, ("Visual"), ("weapon_color[0]"));
		SetupValue(settings::visual::weapon_color[1], 255, ("Visual"), ("weapon_color[1]"));
		SetupValue(settings::visual::weapon_color[2], 255, ("Visual"), ("weapon_color[2]"));

		SetupValue(settings::visual::off_color[0], 255, ("Visual"), ("off_color[0]"));
		SetupValue(settings::visual::off_color[1], 255, ("Visual"), ("off_color[1]"));
		SetupValue(settings::visual::off_color[2], 255, ("Visual"), ("off_color[2]"));

		SetupValue(settings::visual::distance_color[0], 255, ("Visual"), ("distance_color[0]"));
		SetupValue(settings::visual::distance_color[1], 255, ("Visual"), ("distance_color[1]"));
		SetupValue(settings::visual::distance_color[2], 255, ("Visual"), ("distance_color[2]"));

		SetupValue(settings::visual::skeleton_color[0], 255, ("Visual"), ("skeleton_color[0]"));
		SetupValue(settings::visual::skeleton_color[1], 255, ("Visual"), ("skeleton_color[1]"));
		SetupValue(settings::visual::skeleton_color[2], 255, ("Visual"), ("skeleton_color[2]"));

		SetupValue(settings::visual::target_trasers_color[0],255, ("Other"), ("target_trasers[0]"));
		SetupValue(settings::visual::target_trasers_color[1],255, ("Other"), ("target_trasers[1]"));
		SetupValue(settings::visual::target_trasers_color[2],255, ("Other"), ("target_trasers[2]"));

		SetupValue(settings::combat::fov_color[0], 255, ("Other"), ("fov_color[0]"));
		SetupValue(settings::combat::fov_color[1], 255, ("Other"), ("fov_color[1]"));
		SetupValue(settings::combat::fov_color[2], 255, ("Other"), ("fov_color[2]"));


		SetupValue(settings::visual::ignore_players_type[0], false, ("Visual"), ("ignore_players_type[0]"));
		SetupValue(settings::visual::ignore_players_type[1], false, ("Visual"), ("ignore_players_type[1]"));

		SetupValue(settings::visual::flags_players[0], false, ("Visual"), ("flags_players[0]"));
		SetupValue(settings::visual::flags_players[1], false, ("Visual"), ("flags_players[1]"));
		SetupValue(settings::visual::flags_players[2], false, ("Visual"), ("flags_players[0]"));
		SetupValue(settings::visual::flags_players[3], false, ("Visual"), ("flags_players[1]"));
		SetupValue(settings::visual::target_trasers, false, ("Visual"), ("target_trasers"));
		SetupValue(settings::visual::weapon, false, ("Visual"), ("weapon"));
		SetupValue(settings::visual::off_arrors, false, ("Visual"), ("off_arrors"));
		SetupValue(settings::visual::distance, false, ("Visual"), ("distance"));
		//npc

		SetupValue(settings::npc::name, false, ("npc"), ("name npc"));
		SetupValue(settings::npc::box, false, ("npc"), ("box npc"));
		SetupValue(settings::npc::boxstyle, 0, ("npc"), ("boxstyle npc"));
		SetupValue(settings::npc::weapon, false, ("npc"), ("weapon npc"));
		SetupValue(settings::npc::distance, false, ("npc"), ("distance npc"));
		//other
		SetupValue(settings::misc::custom_hitsound, false, ("Other"), ("custom_hitsound"));
		SetupValue(settings::misc::hitsound_style, 0, ("Other"), ("hitsound_style"));
		SetupValue(settings::misc::fov, false, ("Other"), ("custom fov"));
		SetupValue(settings::misc::fov_scale, 90.f, ("Other"), ("fov scale"));
		SetupValue(settings::misc::zoom_key, 0, ("Other"), ("zom key"));
		SetupValue(settings::misc::aspect_ratio, false, ("Other"), ("Aspect Ratio"));
		SetupValue(settings::misc::aspect_ratio_value, 1.8f, ("Other"), ("Aspect Ratio scale"));
		SetupValue(settings::misc::gizmo_sphere, false, ("Other"), ("Eye Sphere"));
		SetupValue(settings::misc::hitmaterial, 0, ("Other"), ("Hit Effect"));
		SetupValue(settings::misc::movement_line, false, ("Other"), ("Movement Line"));
		SetupValue(settings::misc::bullet_tracers, false, ("Other"), ("Bullet tracers"));
		SetupValue(settings::misc::skycolor, false, ("Other"), ("Sky color changer"));
		SetupValue(settings::misc::sky_color_col[0], false, ("Other"), ("sky_color_col[0]"));
		SetupValue(settings::misc::sky_color_col[1], false, ("Other"), ("sky_color_col[1]"));
		SetupValue(settings::misc::sky_color_col[2], false, ("Other"), ("sky_color_col[2]"));
		SetupValue(settings::misc::bright_ambient, false, ("Other"), ("Ambient"));

		SetupValue(settings::misc::flyhack_indicator, false, ("Other"), ("Fly indicator"));
		SetupValue(settings::misc::reload_coldown, false, ("Other"), ("Reload indicator"));
		SetupValue(settings::combat::target_name, false, ("Other"), ("Target name"));
		SetupValue(settings::misc::followprojectile, false, ("Other"), ("Follow Projectile"));
		SetupValue(settings::misc::followprojectile_key, 0, ("Other"), ("Follow Projectile key"));
		SetupValue(settings::misc::weapon_spam, false, ("Other"), ("Weapon spam"));
		SetupValue(settings::misc::weapon_spam_key, 0, ("Other"), ("Weapon spam key"));
		SetupValue(settings::misc::mie_changer, false, ("Other"), ("Mie Changer"));
		SetupValue(settings::misc::mie, 1.f, ("Other"), ("Mie Amount"));
		SetupValue(settings::misc::rayleigh_changer, false, ("Other"), ("Rayleigh Changer"));
		SetupValue(settings::visuals::chams::hand_chams, false, ("Other"), ("hand_chams"));
		SetupValue(settings::visuals::chams::hand_chams_type, 0, ("Other"), ("hand_chams_type"));
		SetupValue(settings::visuals::chams::chams_render_mode, 0, ("Other"), ("chams_render_mode"));
		SetupValue(settings::misc::rayleigh, 1.f, ("Other"), ("Rayleigh Amount"));
		SetupValue(settings::misc::brightness_changer, false, ("Other"), ("Brightness Changer"));
		SetupValue(settings::misc::brightness, 1.f, ("Other"), ("Brightness Amount"));
		SetupValue(settings::misc::no_rain, false, ("Other"), ("No rain & snowfall"));
		//world
		SetupValue(settings::visuals::other::dropped_items, false, ("world"), ("Dropped Items"));
		SetupValue(settings::visuals::other::hemp, false, ("world"), ("Hemp"));
		SetupValue(settings::visuals::other::corpse, false, ("world"), ("Corpses"));
		SetupValue(settings::visuals::other::bodybag, false, ("world"), ("Bodybags"));
		SetupValue(settings::visuals::other::stash, false, ("world"), ("Stashes"));
		SetupValue(settings::visuals::other::draw_distance, 300.f, ("world"), ("Important ESP Distance"));
		SetupValue(settings::visuals::other::show_distance, false, ("world"), ("Important ESP Show Distance"));

		SetupValue(settings::ores::stone, false, ("world"), ("Stone"));
		SetupValue(settings::ores::sulfur, false, ("world"), ("Sulfur"));
		SetupValue(settings::ores::metal, false, ("world"), ("Metal"));
		SetupValue(settings::ores::draw_distance, 300.f, ("world"), ("Ores ESP Distance"));
		SetupValue(settings::ores::show_collectables, false, ("world"), ("Show Collectables"));
		SetupValue(settings::ores::show_distance, false, ("world"), ("Ores ESP Distance Show Distance"));

		SetupValue(settings::visuals::crates::chinook, false, ("world"), ("Chinook Crates"));
		SetupValue(settings::visuals::crates::supply, false, ("world"), ("Airdrops"));
		SetupValue(settings::visuals::crates::heli, false, ("world"), ("Heli Box"));
		SetupValue(settings::visuals::crates::bradley, false, ("world"), ("Bradley Box"));
		SetupValue(settings::visuals::crates::military, false, ("world"), ("Military Box"));
		SetupValue(settings::visuals::crates::elite, false, ("world"), ("Elite Box"));
		SetupValue(settings::visuals::crates::draw_distance, 300.f, ("world"), ("Crates ESP Distance"));
		SetupValue(settings::visuals::crates::show_distance, false, ("world"), ("Crates ESP Show Distance"));

		SetupValue(settings::visuals::animals::bear, false, ("world"), ("Bears"));
		SetupValue(settings::visuals::animals::pig, false, ("world"), ("Boars"));
		SetupValue(settings::visuals::animals::wolf, false, ("world"), ("Wolfs"));
		SetupValue(settings::visuals::animals::deer, false, ("world"), ("Horses"));
		SetupValue(settings::visuals::animals::chicken, false, ("world"), ("Chicken"));
		SetupValue(settings::visuals::animals::draw_distance, 300.f, ("world"), ("Animals ESP Distance"));
		SetupValue(settings::visuals::animals::show_distance, false, ("world"), ("Animals ESP Show Distance"));

		SetupValue(settings::visuals::base::tc, false, ("world"), ("Tool Cupboards"));
		SetupValue(settings::visuals::base::sleeping_bag, false, ("world"), ("Sleeping Bags"));
		SetupValue(settings::visuals::base::bed, false, ("world"), ("Beds"));
		SetupValue(settings::visuals::base::boxes, false, ("world"), ("Boxes"));
		SetupValue(settings::visuals::base::draw_distance, 300.f, ("world"), ("Base ESP Distance"));
		SetupValue(settings::visuals::base::show_distance, false, ("world"), ("Base ESP Show Distance"));

		SetupValue(settings::visuals::turrets::auto_turret, false, ("world"), ("Auto Turrets"));
		SetupValue(settings::visuals::turrets::flame_turret, false, ("world"), ("Flame Turrets"));
		SetupValue(settings::visuals::turrets::shotgun_turret, false, ("world"), ("Shotgun Traps"));
		SetupValue(settings::visuals::turrets::sam_site, false, ("world"), ("SAM Sites"));
		SetupValue(settings::visuals::turrets::landmine, false, ("world"), ("Landmines"));
		SetupValue(settings::visuals::turrets::bear_trap, false, ("world"), ("Beartraps"));
		SetupValue(settings::visuals::turrets::draw_distance, 300.f, ("world"), ("Traps ESP Distance"));
		SetupValue(settings::visuals::turrets::show_distance, false, ("world"), ("Traps ESP Show Distance"));


		SetupValue(settings::misc::hammer_spam, false, ("misc"), ("hammer_spam"));
		SetupValue(settings::misc::spam_mode, 0, ("misc"), ("spam_mode"));
		SetupValue(settings::misc::spam_key, 0, ("misc"), ("spam_key"));
		SetupValue(settings::misc::fakeadmin, false, ("misc"), ("Fake admin"));
		SetupValue(settings::misc::fast_loot, false, ("misc"), ("Fast loot"));
		SetupValue(settings::misc::mass_suicide, false, ("misc"), ("Suicide"));
		SetupValue(settings::misc::mass_suicide_key, 0, ("misc"), ("Suicide key"));
		SetupValue(settings::misc::stesh_finder, false, ("misc"), ("Silent loot stash"));
		SetupValue(settings::misc::stesh_finder_key, 0, ("misc"), ("Silent loot stash key"));
		SetupValue(settings::misc::ModelState, false, ("misc"), ("Custom modelstate"));
		SetupValue(settings::misc::modelstate, 0, ("misc"), ("Modelstate"));
		SetupValue(settings::misc::font, 0, ("misc"), ("espfont"));
		SetupValue(settings::misc::spiderman, false, ("misc"), ("Spiderman"));
		SetupValue(settings::misc::omnidirectional_sprinting, false, ("misc"), ("Omni-Sprint"));
		SetupValue(settings::misc::walkonwater, false, ("misc"), ("Walk on water"));
		SetupValue(settings::misc::walkonwaterkey, 0, ("misc"), ("Walk on water key"));
		SetupValue(settings::misc::fly_auto_stop, false, ("misc"), ("Fly Stopper"));
		SetupValue(settings::misc::interactive_debug, false, ("misc"), ("Interactive Debug"));
		SetupValue(settings::misc::debugging, 0, ("misc"), ("Interactive Debug Key"));
		SetupValue(settings::misc::inf_jump, false, ("misc"), ("Infinity Jump"));
		SetupValue(settings::misc::walker, false, ("misc"), ("No Collision"));
		SetupValue(settings::misc::speedhack, false, ("misc"), ("SpeedHack"));
		SetupValue(settings::misc::speedhackbind, 0, ("misc"), ("SpeedHack key"));
		SetupValue(settings::misc::auto_pickup, false, ("misc"), ("Auto pick up"));
		SetupValue(settings::misc::anti_aim, false, ("misc"), ("Anti-aim"));

		SetupValue(settings::menu::watermark, true, ("menu"), ("Watermark"));
		/*SetupValue(color[0], 255, ("Other"), ("accent[0]"));
		SetupValue(color[1], 103, ("Other"), ("accent[1]"));
		SetupValue(color[2], 215, ("Other"), ("accent[2]"));*/
	}
};

CConfig config;