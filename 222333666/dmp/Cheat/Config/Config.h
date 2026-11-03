#include <string>
#include <vector>
#include <Windows.h>
#include <filesystem>
#include "Base63.h"
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

class CConfig
{
public:
	CConfig()
	{
		ints = std::vector<VarType<int>*>();
		bools = std::vector<VarType<bool>*>();
		floats = std::vector<VarType<float>*>();
	}

	void Initialize()
	{
		szPath = "Sky.one\\";
		Setup();
	}
	void Create()
	{
		std::string file;
		file = szPath + vars::stuff::selected_cfg + ".cfg";

		CreateDirectoryA(szPath.c_str(), NULL);

		for (VarType<int>* pValue : ints)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<float>* pValue : floats)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<bool>* pValue : bools)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), *pValue->value ? "1" : "0", file.c_str());
	}
	std::vector < std::string > GetConfigList()
	{
		std::filesystem::create_directory("Sky.one\\");

		std::vector < std::string > m_ConfigList;
		for (const auto& p : std::filesystem::recursive_directory_iterator(("Sky.one\\")))
		{
			if (!std::filesystem::is_directory(p) && p.path().extension().string() == (".cfg"))
			{
				auto file = p.path().filename().string();
				m_ConfigList.push_back(file.substr(0, file.size() - 4));
			}
		}

		return m_ConfigList;
	}
	void Save(const char* szConfigName)
	{
		std::string file;
		file = szPath + szConfigName + ".cfg";

		CreateDirectoryA(szPath.c_str(), NULL);

		for (VarType<int>* pValue : ints)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<float>* pValue : floats)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<bool>* pValue : bools)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), *pValue->value ? "1" : "0", file.c_str());
	}

	void Remove(const char* szConfigName)
	{
		std::string file;
		file = szPath + szConfigName + ".cfg";
		std::remove(file.c_str());
	}

	void Load(const char* szConfigName)
	{
		std::string file;
		file = szPath + szConfigName + ".cfg";
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
		SetupValue(vars::stuff::font, 0, ("Visuals"), ("Font text"));

		// --Keys
		SetupValue(vars::keys::debugging, 0, ("keys"), ("debugging"));
		SetupValue(vars::keys::zoom, 0, ("keys"), ("zoom"));
		SetupValue(vars::keys::low_velocity_key, 0, ("keys"), ("low_velocity_key"));
		SetupValue(vars::keys::suicide, 0, ("keys"), ("suicide"));
		SetupValue(vars::keys::manipulated_key, 0, ("keys"), ("manipulated_key"));
		SetupValue(vars::keys::ignore_stopper, 0, ("keys"), ("ignore_stopper"));
		SetupValue(vars::keys::bhop, 0, ("keys"), ("bhop"));
		SetupValue(vars::keys::stashopen, 0, ("keys"), ("stashopen"));
		SetupValue(vars::keys::TeleportTopPlayer, 0, ("keys"), ("TeleportTopPlayer key"));

		SetupValue(vars::keys::speedkey, 0, ("keys"), ("speedkey"));
		SetupValue(vars::keys::instakill, 0, ("keys"), ("instakill"));

		// --Combat
		SetupValue(vars::combat::ExtentForMoutend, false, ("Combat"), ("ExtentForMoutend"));
		SetupValue(vars::combat::ManipulatorRadios, false, ("Combat"), ("ManipulatorRadios"));
		SetupValue(vars::combat::BulletTeleportGradient, false, ("Combat"), ("BulletTeleportGradient"));
		SetupValue(vars::combat::pierce, false, ("Combat"), ("pierce"));
		SetupValue(vars::combat::doubletap, false, ("Combat"), ("doubletap"));
		SetupValue(vars::combat::doubletaptype, 0, ("Combat"), ("doubletaptype"));

		SetupValue(vars::combat::bullet_tp, false, ("Combat"), ("bullet_tp"));
		SetupValue(vars::visuals::ponan, false, ("Combat"), ("BTP Style"));
		SetupValue(vars::visuals::onan, false, ("Combat"), ("Show BTP"));
		SetupValue(vars::combat::autoreload, false, ("Combat"), ("autoreload"));
		SetupValue(vars::combat::instakill, false, ("Combat"), ("instakill"));
		SetupValue(vars::combat::autoshoot, false, ("Combat"), ("autoshoot"));
		SetupValue(vars::combat::always_heli_rotor, false, ("Combat"), ("always_heli_rotor"));
		SetupValue(vars::combat::Manipulator_shot_atBt, false, 
			
			
			
			
			
			
			("Combat"), ("Manipulator_shot_atBt"));
		SetupValue(vars::combat::silent_melee, false, ("Combat"), ("silent_melee"));
		SetupValue(vars::combat::psilent, false, ("Combat"), ("psilent"));
		SetupValue(vars::combat::psilentheli, false, ("Combat"), ("psilentheli"));
		SetupValue(vars::combat::visualize_fov, false, ("Combat"), ("visualize_fov"));
		SetupValue(vars::combat::manipulator, false, ("Combat"), ("manipulator"));
		SetupValue(vars::combat::ignore_sleepers, false, ("Combat"), ("ignore_sleepers"));
		SetupValue(vars::combat::ignore_team, false, ("Combat"), ("ignore_team"));
		SetupValue(vars::combat::ignore_npc, false, ("Combat"), ("ignore_npc"));
		SetupValue(vars::combat::hitbox, 0, ("Combat"), ("HitBox_ov"));
		SetupValue(vars::combat::desync_autoshoot_type, 0, ("Combat"), ("Desync Type"));
		SetupValue(vars::combat::fov, 100.f, ("Combat"), ("Aimbot Fove"));
		SetupValue(vars::combat::DesynctTime, 0.95f, ("Combat"), ("DesyncTime"));
		// -- Weapon
		SetupValue(vars::weapons::rapidfire, false, ("Weapon"), ("rapidfire"));

		SetupValue(vars::weapons::no_recoil, false, ("Weapon"), ("no_recoil"));
		SetupValue(vars::weapons::test, false, ("Weapon"), ("Test"));
		SetupValue(vars::weapons::test2, false, ("Weapon"), ("Test2"));
		SetupValue(vars::weapons::recoil_control, 100.f, ("Weapon"), ("recoil_control"));
		SetupValue(vars::weapons::fast_bullets, false, ("Weapon"), ("fast_bullets"));
		SetupValue(vars::weapons::low_velocity, false, ("Weapon"), ("low_velocity"));
		SetupValue(vars::weapons::penetrate, false, ("Weapon"), ("penetrate"));
		SetupValue(vars::weapons::minicopter_aim, false, ("Weapon"), ("minicopter_aim"));
		SetupValue(vars::weapons::remove_attack_anim, false, ("Weapon"), ("remove_attack_anim"));
		SetupValue(vars::weapons::no_spread, false, ("Weapon"), ("no_spread"));
		SetupValue(vars::weapons::automatic, false, ("Weapon"), ("automatic"));
		SetupValue(vars::weapons::thick_bullet, false, ("Weapon"), ("thick_bullet"));
		SetupValue(vars::weapons::no_sway, false, ("Weapon"), ("no_sway"));
		SetupValue(vars::weapons::eokatap, false, ("Weapon"), ("eokatap"));
		SetupValue(vars::weapons::compound, false, ("Weapon"), ("compound"));

		// -- players
		SetupValue(vars::players::box_::outline, true, ("Visuals"), ("outline box"));
		SetupValue(vars::players::box_::colorcheck, true, ("Visuals"), ("colorcheck"));
		SetupValue(vars::players::skeleton_::outline, true, ("Visuals"), ("Skeleton Outline"));
		SetupValue(vars::players::skeleton_::colorcheck, true, ("Visuals"), ("Skeletom Color Check"));
		SetupValue(vars::players::name_::outline, true, ("Visuals"), ("Name Outline"));
		SetupValue(vars::players::name_::font, 1, ("Visuals"), ("Name Font"));

		SetupValue(vars::players::name_::colorcheck, true, ("Visuals"), ("Name Color check"));
		SetupValue(vars::players::distance_::outline, true, ("Visuals"), ("Distance Outline"));
		SetupValue(vars::players::distance_::colorcheck, true, ("Visuals"), ("Distance Color Check"));
		SetupValue(vars::players::weapon_::outline, true, ("Visuals"), ("Weapon Outline"));
		SetupValue(vars::players::weapon_::font, 1, ("Visuals"), ("Weapon Font"));
		SetupValue(vars::players::weapon_::colorcheck, true, ("Visuals"), ("Weapon Color Check"));
		SetupValue(vars::players::healthbar_::font, 1, ("Visuals"), ("HealthBar Font"));
		SetupValue(vars::players::healthbarstyle, 0, ("Visuals"), ("HealthBar Style"));

		SetupValue(vars::players::TargetBelt, false, ("Visuals"), ("TargetBelt"));

		SetupValue(vars::players::target_tracers, false, ("Visuals"), ("target_tracers"));
		SetupValue(vars::players::oof_arrows, false, ("Visuals"), ("oof_arrows"));
		SetupValue(vars::players::distance, false, ("Visuals"), ("distance"));
		SetupValue(vars::players::box, false, ("Visuals"), ("box"));
		SetupValue(vars::players::boxstyle, 0, ("Visuals"), ("boxstyle"));
		SetupValue(vars::players::skeleton, false, ("Visuals"), ("skeleton"));
		SetupValue(vars::players::name, false, ("Visuals"), ("name"));
		SetupValue(vars::players::healthbar, false, ("Visuals"), ("healthbar"));
		SetupValue(vars::players::weapon, false, ("Visuals"), ("weapon"));
		SetupValue(vars::players::WeaponIcon, false, ("Visuals"), ("WeaponIcon"));
		SetupValue(vars::players::DisableWeaponName, false, ("Visuals"), ("DisableWeaponName"));
		SetupValue(vars::players::sleeperignore, false, ("Visuals"), ("sleeperignore"));
		SetupValue(vars::players::targetline, false, ("Visuals"), ("targetline"));
		// -- Npc
		SetupValue(vars::npc::oof_arrows, false, ("Visuals npc"), ("oof_arrows"));
		SetupValue(vars::npc::distance, false, ("Visuals npc"), ("distance"));
		SetupValue(vars::npc::box, false, ("Visuals npc"), ("box"));
		SetupValue(vars::npc::skeleton, false, ("Visuals npc"), ("skeleton"));
		SetupValue(vars::npc::name, false, ("Visuals npc"), ("name"));
		SetupValue(vars::npc::healthbar, false, ("Visuals npc"), ("healthbar"));
		SetupValue(vars::npc::weapon, false, ("Visuals npc"), ("weapon"));
		SetupValue(vars::npc::WeaponIcon, false, ("Visuals npc"), ("WeaponIcon"));
		SetupValue(vars::npc::DisableWeaponName, false, ("Visuals npc"), ("DisableWeaponName"));
		// -- Other
		SetupValue(vars::visuals::xueta, 5.f, ("Other"), ("Radial Radius"));
		SetupValue(vars::visuals::skycolor, false, ("Other"), ("skycolor"));
		SetupValue(vars::visuals::show_distance_bulletTp, false, ("Other"), ("show_distance_bulletTp"));
		SetupValue(vars::visuals::No_bobing, false, ("Other"), ("No_bobing"));
		SetupValue(vars::visuals::bradley_apc, false, ("Other"), ("bradley_apc"));
		SetupValue(vars::visuals::patrol_heli, false, ("Other"), ("patrol_heli"));
		SetupValue(vars::visuals::base::tc, false, ("Other"), ("Tc"));
		SetupValue(vars::visuals::base::sleeping_bag, false, ("Other"), ("sleeping_bag"));
		SetupValue(vars::visuals::base::bed, false, ("Other"), ("bed"));
		SetupValue(vars::visuals::base::boxes, false, ("Other"), ("boxes"));
		SetupValue(vars::visuals::base::show_distance, false, ("Other"), ("show_distance"));
		SetupValue(vars::visuals::base::draw_distance, 300.f, ("Other"), ("draw_distance base"));
		SetupValue(vars::visuals::vehicles::minicopter, false, ("Other"), ("minicopter"));
		SetupValue(vars::visuals::vehicles::scrapheli, false, ("Other"), ("scrapheli"));
		SetupValue(vars::visuals::vehicles::boat, false, ("Other"), ("boat"));
		SetupValue(vars::visuals::vehicles::rhib, false, ("Other"), ("rhib"));
		SetupValue(vars::visuals::vehicles::show_distance, false, ("Other"), ("show_distance"));
		SetupValue(vars::visuals::vehicles::draw_distance, 300.f, ("Other"), ("draw_distance vehicle"));
		SetupValue(vars::visuals::turrets::auto_turret, false, ("Other"), ("auto_turret"));
		SetupValue(vars::visuals::turrets::flame_turret, false, ("Other"), ("flame_turret"));
		SetupValue(vars::visuals::turrets::shotgun_turret, false, ("Other"), ("shotgun_turret"));
		SetupValue(vars::visuals::turrets::landmine, false, ("Other"), ("landmine"));
		SetupValue(vars::visuals::turrets::sam_site, false, ("Other"), ("sam_site"));
		SetupValue(vars::visuals::turrets::bear_trap, false, ("Other"), ("bear_trap"));
		SetupValue(vars::visuals::turrets::show_distance, false, ("Other"), ("show_distance"));
		SetupValue(vars::visuals::turrets::draw_distance, 300.f, ("Other"), ("draw_distance turret"));
		SetupValue(vars::visuals::other::dropped_items, false, ("Other"), ("dropped_items"));
		SetupValue(vars::visuals::other::bodybag, false, ("Other"), ("bodybag"));
		SetupValue(vars::visuals::other::corpse, false, ("Other"), ("corpse"));
		SetupValue(vars::visuals::other::stash, false, ("Other"), ("stash"));
		SetupValue(vars::visuals::other::hemp, false, ("Other"), ("hemp"));
		SetupValue(vars::visuals::other::show_distance, false, ("Other"), ("show_distance"));
		SetupValue(vars::visuals::other::draw_distance, 300.f, ("Other"), ("draw_distance other"));
		SetupValue(vars::visuals::crates::elite, false, ("Other"), ("elite"));
		SetupValue(vars::visuals::crates::military, false, ("Other"), ("military"));
		SetupValue(vars::visuals::crates::supply, false, ("Other"), ("supply"));
		SetupValue(vars::visuals::crates::chinook, false, ("Other"), ("chinook"));
		SetupValue(vars::visuals::crates::heli, false, ("Other"), ("heli"));
		SetupValue(vars::visuals::crates::bradley, false, ("Other"), ("bradley"));
		SetupValue(vars::visuals::crates::show_distance, false, ("Other"), ("show_distance"));
		SetupValue(vars::visuals::crates::draw_distance, 300.f, ("Other"), ("draw_distance crates"));
		SetupValue(vars::visuals::animals::bear, false, ("Other"), ("bear"));
		SetupValue(vars::visuals::animals::pig, false, ("Other"), ("pig"));
		SetupValue(vars::visuals::animals::chicken, false, ("Other"), ("chicken"));
		SetupValue(vars::visuals::animals::wolf, false, ("Other"), ("wolf"));
		SetupValue(vars::visuals::animals::deer, false, ("Other"), ("deer"));
		SetupValue(vars::visuals::animals::show_distance, false, ("Other"), ("show_distance"));
		SetupValue(vars::visuals::animals::draw_distance, 300.f, ("Other"), ("draw_distance animals"));


		// -- MiscTargetInfo
		SetupValue(vars::misc::TargetInfo, false, ("Misc"), ("TargetInfo"));
		//vars::debug::bullettracer
		SetupValue(vars::debug::bullettracer, false, ("Misc"), ("Bullet Tracer"));
		SetupValue(vars::stuff::bttype, false, ("Misc"), ("Bullet Tracer Type"));
		SetupValue(vars::debug::bullettartracer, false, ("Misc"), ("Bullet Tracer"));
		SetupValue(vars::stuff::bttype, false, ("Misc"), ("Bullet Tracer Type"));

		SetupValue(vars::misc::interactive_debug, false, ("Misc"), ("Ineractive Debug"));
		
		SetupValue(vars::misc::fakelag, 0, ("Misc"), ("fakelag"));
		SetupValue(vars::misc::TeloportTopPlayer, false, ("Misc"), ("TeloportTopPlayer"));

		SetupValue(vars::misc::modelstate, 0, ("Misc"), ("modelstate"));
		SetupValue(vars::misc::crosshair, false, ("Misc"), ("crosshair"));
		SetupValue(vars::misc::sphere, false, ("Misc"), ("Colision Sphera"));
		SetupValue(vars::misc::Sphera, 0, ("Misc"), ("Sphera Style"));
		SetupValue(vars::misc::zoom, false, ("Misc"), ("zoom"));
		SetupValue(vars::misc::jesus, false, ("Misc"), ("jesus"));
		SetupValue(vars::misc::fotsize, 12.f, ("Misc"), ("fotsize"));
		SetupValue(vars::misc::bhop, false, ("Misc"), ("bhop"));
		SetupValue(vars::misc::fly_auto_stopper, false, ("Misc"), ("fly_auto_stopper"));
		SetupValue(vars::misc::weapon_spam, false, ("Misc"), ("weapon_spam"));
		SetupValue(vars::misc::fast_loot, false, ("Misc"), ("fast_loot"));
		SetupValue(vars::misc::AspectRatio, false, ("Misc"), ("AspectRatio"));
		SetupValue(vars::misc::night_stars, false, ("Misc"), ("Stars"));
		SetupValue(vars::misc::stars, 0, ("Misc"), ("Intens"));
		SetupValue(vars::misc::flyhack_indicator, false, ("Misc"), ("flyhack_indicator"));
		SetupValue(vars::misc::reload_indicator, false, ("Misc"), ("reload_indicator"));
		SetupValue(vars::misc::manipulator_indicator, false, ("Misc"), ("manipulator_indicator"));
		SetupValue(vars::misc::spiderman, false, ("Misc"), ("spiderman"));
		SetupValue(vars::misc::better_jump, false, ("Misc"), ("better_jump"));
		SetupValue(vars::misc::no_fall, false, ("Misc"), ("no_fall"));
		SetupValue(vars::misc::hitmaterial, 0, ("Misc"), ("Hit Material"));
		SetupValue(vars::misc::gesture, 0, ("Misc"), ("Gesture Spam"));

		SetupValue(vars::misc::auto_pickup, false, ("Misc"), ("Auto Pickp Up"));
		SetupValue(vars::misc::auto_farm, false, ("Misc"), ("auto_farm"));
		SetupValue(vars::misc::auto_farm_ore, false, ("Misc"), ("auto_farm_ore"));
		SetupValue(vars::misc::auto_farm_tree, false, ("Misc"), ("auto_farm_tree"));
		SetupValue(vars::misc::can_attack, false, ("Misc"), ("can_attack"));
		SetupValue(vars::misc::faster_healing, false, ("Misc"), ("faster_healing"));
		SetupValue(vars::misc::suicide, false, ("Misc"), ("suicide"));
		SetupValue(vars::misc::annoyer, false, ("Misc"), ("annoyer"));
		SetupValue(vars::misc::bright_ambient, false, ("Misc"), ("bright_ambient"));
		SetupValue(vars::misc::Sphera, false, ("Misc"), ("Sphera"));
		SetupValue(vars::misc::fov, 90.f, ("Misc"), ("Custom Foving Player"));
		SetupValue(vars::misc::ratio, 1.4f, ("Misc"), ("ratio"));
		SetupValue(vars::misc::omnidirectional_sprinting, false, ("Misc"), ("omnidirectional_sprinting"));
		SetupValue(vars::misc::fakeadmin, false, ("Misc"), ("fakeadmin"));
		SetupValue(vars::misc::damagemarker, false, ("Misc"), ("Damage Marker"));
		SetupValue(vars::misc::hitmarker, false, ("Misc"), ("Hit Marker"));

		SetupValue(vars::misc::custom_time, false, ("Misc"), ("custom_time"));
		SetupValue(vars::misc::time, 12.f, ("Misc"), ("time"));
		//vars::stuff::font
		SetupValue(vars::stuff::font, 0, ("Misc"), ("Global Render Font"));

		SetupValue(vars::colors::ambient_color.x, 0.8f, ("colors"), ("ambient_color x"));
		SetupValue(vars::colors::ambient_color.y, 0.8f, ("colors"), ("ambient_color y"));
		SetupValue(vars::colors::ambient_color.z, 0.8f, ("colors"), ("ambient_color z"));
		SetupValue(vars::colors::ambient_color.w, 0.8f, ("colors"), ("ambient_color w"));

		SetupValue(vars::colors::sky_color.x, 0.8f, ("colors"), ("sky_color x"));
		SetupValue(vars::colors::sky_color.y, 0.8f, ("colors"), ("sky_color y"));
		SetupValue(vars::colors::sky_color.z, 0.8f, ("colors"), ("sky_color z"));
		SetupValue(vars::colors::sky_color.w, 0.8f, ("colors"), ("sky_color w"));

		SetupValue(vars::colors::one_color.x, 0.8f, ("colors"), ("Radial Color x"));
		SetupValue(vars::colors::one_color.y, 0.8f, ("colors"), ("Radial Color y"));
		SetupValue(vars::colors::one_color.z, 0.8f, ("colors"), ("Radial Color z"));
		SetupValue(vars::colors::one_color.w, 0.8f, ("colors"), ("Radial Color w"));

		SetupValue(vars::colors::damagemarker.x, 0.8f, ("colors"), ("damagemarker Color x"));
		SetupValue(vars::colors::damagemarker.y, 0.8f, ("colors"), ("damagemarker Color y"));
		SetupValue(vars::colors::damagemarker.z, 0.8f, ("colors"), ("damagemarker Color z"));
		SetupValue(vars::colors::damagemarker.w, 0.8f, ("colors"), ("damagemarker Color w"));

		SetupValue(vars::colors::hitmarker.x, 0.8f, ("colors"), ("hitmarker Color x"));
		SetupValue(vars::colors::hitmarker.y, 0.8f, ("colors"), ("hitmarker Color y"));
		SetupValue(vars::colors::hitmarker.z, 0.8f, ("colors"), ("hitmarker Color z"));
		SetupValue(vars::colors::hitmarker.w, 0.8f, ("colors"), ("hitmarker Color w"));

		SetupValue(vars::colors::colsphere[0], 0.8f, ("colors"), ("colsphere x"));
		SetupValue(vars::colors::colsphere[1], 0.8f, ("colors"), ("colsphere y"));
		SetupValue(vars::colors::colsphere[2], 0.8f, ("colors"), ("colsphere z"));
		SetupValue(vars::colors::colsphere[3], 0.8f, ("colors"), ("colsphere w"));

		SetupValue(vars::visible::box_color[0], 0.8f, ("colors"), ("player_color x"));
		SetupValue(vars::visible::box_color[1], 0.8f, ("colors"), ("player_color y"));
		SetupValue(vars::visible::box_color[2], 0.8f, ("colors"), ("player_color z"));
		SetupValue(vars::visible::box_color[3], 0.8f, ("colors"), ("player_color w"));

		SetupValue(vars::colors::npc_box_color[0], 0.8f, ("colors"), ("npc_color x"));
		SetupValue(vars::colors::npc_box_color[1], 0.8f, ("colors"), ("npc_color y"));
		SetupValue(vars::colors::npc_box_color[2], 0.8f, ("colors"), ("npc_color z"));
		SetupValue(vars::colors::npc_box_color[3], 0.8f, ("colors"), ("npc_color w"));

		SetupValue(vars::colors::target_color[0], 0.8f, ("colors"), ("target_color x"));
		SetupValue(vars::colors::target_color[1], 0.8f, ("colors"), ("target_color y"));
		SetupValue(vars::colors::target_color[2], 0.8f, ("colors"), ("target_color z"));
		SetupValue(vars::colors::target_color[3], 0.8f, ("colors"), ("target_color w"));
	}

	std::string szPath = "";

protected:
	std::vector<VarType<int>*> ints;
	std::vector<VarType<bool>*> bools;
	std::vector<VarType<float>*> floats;
};

CConfig config;