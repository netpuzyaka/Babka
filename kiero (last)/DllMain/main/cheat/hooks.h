#include "../utils/defs.h"
#include "combat/hitscan.h"
#include "combat/bullet_tp.h"
#include "combat/stw.h"
#include "combat/hammerspam.h"
#include "other.h"

float last_shoot_time = 0.f;

void __fastcall SetFlying(ModelState* a1, bool a2) { }
Projectile* projv;
bool proj = false;
void DoMovement(Projectile* projectile, float deltaTime) {
	auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
	BaseProjectile* _held = held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
	auto currentVelocity = projectile->currentVelocity() * deltaTime;
	auto intmag = currentVelocity.Magnitude();
	auto intnum = 1.f / intmag;
	auto speed = currentVelocity * intnum;
	auto lineposition = projectile->currentPosition() + speed * currentVelocity.Magnitude();

	if (projectile->isAuthoritative() && settings::misc::bullet_tracers) {

		DDraw::Line(projectile->currentPosition(), lineposition, Color(255, 255, 255, 255), 0.9f, false, true);
	}
	if (projectile->owner()->userID() == LocalPlayer::Entity()->userID() && settings::misc::followprojectile)
	{
		proj = true;
		projv = projectile;
	}

	// STW (Shoot Throw Wall) — «проброс» снаряда сквозь препятствие к ближайшей точке цели.
	// Вызывается до оригинального DoMovement, пока позиция снаряда ещё актуальна для этого тика.
	if (settings::weapons::stw && projectile->isAuthoritative()) {
		stw(projectile, deltaTime);
		RPC_Counter.Reset();
	}

	return original_domovement(projectile, deltaTime);
}
void DoHitNotify(BaseCombatEntity* entity, HitInfo* info, Projectile* prj) {
	if (entity->IsPlayer()) {
		if (settings::misc::custom_hitsound) {
			if (settings::misc::hitsound_style == 0) {
				PlaySoundA((LPCSTR)roblox, NULL, SND_MEMORY | SND_ASYNC);
			}
			if (settings::misc::hitsound_style == 1) {
				PlaySoundA((LPCSTR)minecraft, NULL, SND_MEMORY | SND_ASYNC);
			}
			if (settings::misc::hitsound_style == 2) {
				PlaySoundA((LPCSTR)crystal, NULL, SND_MEMORY | SND_ASYNC);
			}
			return;
		}
	}
	return original_dohitnotify(entity, info, prj);
}
bool get_isHeadshot(HitInfo* hitinfo) {
	if (settings::misc::custom_hitsound) {
		return false;
	}
	return original_getisheadshot(hitinfo);
}
void ProjectileUpdate_hk(Projectile* pr)
{
	ak47fix(pr);

	auto* target_player = reinterpret_cast<BasePlayer*>(settings::closestPlayer);
	Vector3 vector2 = pr->currentVelocity() * 0.03125;
	float magnitude = vector2.Magnitude();
	float num2 = 1.f / magnitude;
	Vector3 vector3 = vector2 * num2;
	Vector3 vector4 = pr->currentPosition() + vector3 * magnitude;
	Line line = Line(pr->currentPosition(), vector4);
	Vector3 FirstNearest = line.ClosestPoint(target_player->GetBoneByID(head));
	float DistanceToPoint1 = FirstNearest.Distance(target_player->GetBoneByID(head));

	if (DistanceToPoint1 < 2.60f) // 2.560f
	{
		bool didTp = false;

		for (Projectile* i = pr; pr->isAlive(); pr->UpdateVelocity(0.00025))
		{
			if (settings::weapons::bullet_tp) {
				if (bullet_tp(pr))
					didTp = true;
			}

			if (i->launchTime() <= 0) {
				break;
			}
			float time = Time::time();
			if (time - i->launchTime() < i->traveledTime() + 0.03125f) {
				break;
			}
		}
	}

	return original_Update(pr);
}

static bool HasGotOrig = false;
static float Orig_ClothingMoveSpeedReduction = 0.f;
float speedhackPauseTime;
Vector3 pre_last_pos;

void WalkClientInput(PlayerWalkMovement* move, InputState* input, ModelState* state) {
	original_walkclientinput(move, input, state);

	auto localplayer = LocalPlayer::Entity();
	if (localplayer->userID() == LocalPlayer::Entity()->userID()) {
		if (settings::misc::fly_auto_stop && !GetAsyncKeyState(settings::misc::debugging)) {
			if (!localplayer->has_modelstate_flag(ModelStateFlag::Mounted))
			{
				Vector3 current = localplayer->transform()->position();
				Vector3 old = localplayer->lastSentTick()->__position();
				Vector3 vector4 = (localplayer->transform()->position() - localplayer->lastSentTick()->__position());
				Vector3 overrided = Vector3(current.x, current.y, current.z);
				if (settings::misc::fly_auto_stop && VFlyhack >= (VMaxFlyhack - 0.4f))
				{
					overrided = Vector3(overrided.x, current.y < old.y ? (current.y) : old.y, overrided.z);
				}
				if (settings::misc::fly_auto_stop && HFlyhack >= (HMaxFlyhack - 2.5f))
				{
					overrided = Vector3(old.x, overrided.y, old.z);
				}
				if (!WaterLevel::Test(overrided - Vector3(0.0f, 2.f, 0.0f), true, false, LocalPlayer::Entity()))
				{
					if (settings::misc::fly_auto_stop && HFlyhack >= (HMaxFlyhack - 2.5f) ||
						settings::misc::fly_auto_stop && VFlyhack >= (VMaxFlyhack - 0.4f))
					{
						if (overrided != current)
						{
							move->BaseTeleportTo(overrided);
						}
					}
				}
			}
		}
	}
}

void HandChams() {
	if (!LocalPlayer::Entity()->is_alive() || LocalPlayer::Entity()->has_modelstate_flag(ModelStateFlag::Sleeping)) return;
	if (!settings::visuals::chams::hand_chams) return;

	static float r = 1.00f, g = 0.00f, b = 1.00f;
	static int cases = 0;
	switch (cases) {
	case 0: { r -= 0.004f; if (r <= 0) cases += 1; break; }
	case 1: { g += 0.004f; b -= 0.004f; if (g >= 1) cases += 1; break; }
	case 2: { r += 0.004f; if (r >= 1) cases += 1; break; }
	case 3: { b += 0.004f; g -= 0.004f; if (b >= 1) cases = 0; break; }
	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	}

	BaseViewModel::ActiveModel()->useViewModelCamera() = false;

	auto renderers = BaseViewModel::ActiveModel()->GetComponentsInChildren(Type::Renderer());
	if (renderers) {
		for (int i = 0; i < renderers->size(); i++) {
			Renderer_* renderer = reinterpret_cast<Renderer_*>(renderers->get(i));
			if (!renderer || !renderer->material()) continue;

			Material_* material = renderer->material();
			if (!material) continue;

			switch (settings::visuals::chams::chams_render_mode) {
			case 0: {
				if (!material->get_name()->Contains(StringIl::New("fumes")) && !material->get_name()->Contains(StringIl::New("flash")) && !material->get_name()->Contains(StringIl::New("holosight"))) {
					if (settings::visuals::chams::hand_chams_type == 0) {
						renderer->set_material(Gold);
					}
					else if (settings::visuals::chams::hand_chams_type == 1) {
						renderer->set_material(Fade);
					}
					else if (settings::visuals::chams::hand_chams_type == 2) {
						renderer->set_material(Glitch);
					}
				}

				break;

			}
			case 1: {
				if (!material->get_name()->Contains(StringIl::New("fumes")) && !material->get_name()->Contains(StringIl::New("flash")) && !material->get_name()->Contains(StringIl::New("holosight"))) {
					if (material->get_name()->Contains(StringIl::New("Arm")) || material->get_name()->Contains(StringIl::New("hoodie")) || material->get_name()->Contains(StringIl::New("Glove"))
						|| material->get_name()->Contains(StringIl::New("Hand")) || material->get_name()->Contains(StringIl::New("Suit")) || material->get_name()->Contains(StringIl::New("tshirt"))
						|| material->get_name()->Contains(StringIl::New("hazmat")) || material->get_name()->Contains(StringIl::New("torso"))) {
						if (settings::visuals::chams::hand_chams_type == 0) {
							renderer->set_material(Gold);
						}
						else if (settings::visuals::chams::hand_chams_type == 1) {
							renderer->set_material(Fade);
						}
						else if (settings::visuals::chams::hand_chams_type == 2) {
							renderer->set_material(Glitch);
						}
					}
				}

				break;

			}
			case 2: {
				if (!material->get_name()->Contains(StringIl::New("fumes")) && !material->get_name()->Contains(StringIl::New("flash")) && !material->get_name()->Contains(StringIl::New("holosight"))) {
					if (!material->get_name()->Contains(StringIl::New("Arm")) && !material->get_name()->Contains(StringIl::New("hoodie")) && !material->get_name()->Contains(StringIl::New("Glove"))
						&& !material->get_name()->Contains(StringIl::New("Hand")) && !material->get_name()->Contains(StringIl::New("Suit")) && !material->get_name()->Contains(StringIl::New("tshirt"))
						&& !material->get_name()->Contains(StringIl::New("hazmat")) && !material->get_name()->Contains(StringIl::New("torso"))) {
						if (settings::visuals::chams::hand_chams_type == 0) {
							renderer->set_material(Gold);
						}
						else if (settings::visuals::chams::hand_chams_type == 1) {
							renderer->set_material(Fade);
						}
						else if (settings::visuals::chams::hand_chams_type == 2) {
							renderer->set_material(Glitch);
						}
					}
				}

				break;
			}
			}
		}
	}
}

float movementlinecol[] = { 1.f, 1.f,1.f,1.f };

void ClientInput(BasePlayer* baseplayah, ModelState* ModelState) {
	if (!baseplayah) return original_clientinput(baseplayah, ModelState);
	if (!baseplayah->IsValid()) return original_clientinput(baseplayah, ModelState);

	// CREDIT FOR HAND CHAMS / FACZAD SRC

	if (settings::visuals::chams::hand_chams_type == 0 || settings::visuals::chams::weapon_chams_type == 0
		|| settings::visuals::chams::hand_chams_type == 1 || settings::visuals::chams::weapon_chams_type == 1
		|| settings::visuals::chams::hand_chams_type == 2 || settings::visuals::chams::weapon_chams_type == 2) {
		static auto Facz = AssetBundle::LoadFromFile("C:\\kiero\\bundles\\Config.volume");

		if (settings::visuals::chams::hand_chams_type == 0 || settings::visuals::chams::weapon_chams_type == 0)
		{
			Gold = Facz->LoadAsset<Material_>("gold_faczad.mat", Type::Material());
		}
		if (settings::visuals::chams::hand_chams_type == 1 || settings::visuals::chams::weapon_chams_type == 1)
		{
			Fade = Facz->LoadAsset<Material_>("fade_faczad.mat", Type::Material());
		}
		if (settings::visuals::chams::hand_chams_type == 2 || settings::visuals::chams::weapon_chams_type == 2)
		{
			Glitch = Facz->LoadAsset<Material_>("glitch_faczad.mat", Type::Material());
		}
	}

	auto held = baseplayah->GetHeldEntity<BaseProjectile>();
	Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
	DWORD64 active = weapon->entity();
	DWORD64 Held = weapon->entity();

	BaseProjectile* _held = held = baseplayah->GetHeldEntity<BaseProjectile>();
	BaseMelee* melee = LocalPlayer::Entity()->GetHeldEntity<BaseMelee>();
	HandChams();
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(settings::closestPlayer);
	float lastShotTime = _held->lastShotTime() - GLOBAL_TIME;
	float reloadTime = _held->nextReloadTime() - GLOBAL_TIME;
	bool deployed = read(Held + Offsets::HeldEntity_isDeployed, bool);
	float curtime = LocalPlayer::Entity()->lastSentTickTime();

	if (settings::menu::panic)
		ConVar::Graphics::_fov() = 90.f;

	else if (settings::misc::fov)
	{
		float changeSpeed = 0.2f;
		float FOV = settings::misc::fov_scale;
		if (GetAsyncKeyState(settings::misc::zoom_key))
		{
			float oldFOV = ConVar::Graphics::_fov();
			float newFOV = oldFOV + (15.f - oldFOV) * changeSpeed;
			ConVar::Graphics::_fov() = newFOV;
		}
		else
		{
			float zoomfov = ConVar::Graphics::_fov();
			float newFOV = zoomfov + (FOV - zoomfov) * changeSpeed;
			ConVar::Graphics::_fov() = newFOV;
		}
	}
	else
		ConVar::Graphics::_fov() = 90.f;

	if (weapon->GetID() == -75944661) {
		weapon->EokaTap();
	}

	if (held->class_name_hash() != STATIC_CRC32("BaseMelee") && held->class_name_hash() != STATIC_CRC32("Hammer") && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
		weapon->NoSway();
	}

	if (weapon->GetID() == 1588298435 || weapon->GetID() == -778367295 || weapon->GetID() == -1367281941 || weapon->GetID() == -765183617 || weapon->GetID() == -41440462 || weapon->GetID() == 795371088 || weapon->GetID() == 649912614 || weapon->GetID() == 818877484 || weapon->GetID() == -852563019 || weapon->GetID() == 1373971859 || weapon->GetID() == 1914691295 || weapon->GetID() == 1953903201 || weapon->GetID() == -1123473824) {
		weapon->SetAutomatic();
	}

	if (settings::misc::rayleigh_changer) {
		Weather::set_rayleigh(settings::misc::rayleigh);
	}
	else {
		Weather::set_rayleigh(1.f);
	}

	if (settings::misc::mie_changer) {
		Weather::set_mie(settings::misc::mie);
	}
	else {
		Weather::set_mie(1.f);
	}

	if (settings::misc::no_rain) {
		Weather::set_rain(0.f);
	}

	if (settings::misc::brightness_changer) {
		Weather::set_brightness(settings::misc::brightness);
	}
	else {
		Weather::set_brightness(1.f);
	}

	if (settings::misc::auto_pickup)
	{
		BaseEntity* collectibleEntity = BaseNetworkable::clientEntities()->FindClosest<BaseEntity*>(STATIC_CRC32("CollectibleEntity"), LocalPlayer::Entity(), 1.5f);
		if (collectibleEntity && collectibleEntity != nullptr && collectibleEntity != 0x0)
			collectibleEntity->_ServerRPC("Pickup");
	}

	if (settings::combat::silentmelee)
	{
		if (_held->class_name_hash() == STATIC_CRC32("BaseMelee") || _held->class_name_hash() == STATIC_CRC32("Jackhammer"))
		{
			Vector3 pos = LocalPlayer::Entity()->transform()->position() + Vector3(0.f, 1.f, 0.f);
			other::draw_circle(pos, 3);
		}
	}

	if (settings::weapons::minicopter_aim)
		if (baseplayah->mounted())
			baseplayah->mounted()->canWieldItems() = true;

	if (_held && _held != nullptr && _held->class_name_hash() == STATIC_CRC32("BaseProjectile") ||
		_held && _held != nullptr && _held->class_name_hash() == STATIC_CRC32("BowWeapon") ||
		_held && _held != nullptr && LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1965232394) {
		if (settings::combat::autoreload && _held)
		{
			BaseProjectile* ent = baseplayah->GetHeldEntity<BaseProjectile>();

			if (!settings::did_reload)
				settings::time_since_last_shot = (Time::fixedTime() - settings::fixed_time_last_shot);

			if (settings::just_shot && (settings::time_since_last_shot > 0.2f))
			{
				ent->_ServerRPC(("StartReload"));
				ent->SendSignalBroadcast(BaseEntity::Signal::Reload);
				settings::just_shot = false;
			}
			if (settings::time_since_last_shot > (_held->reloadTime() - (_held->reloadTime() / 10))
				&& !settings::did_reload)
			{
				ent->_ServerRPC(("Reload"));
				settings::did_reload = true;
				settings::time_since_last_shot = 0;
			}
		}
	}
	else {
		settings::did_reload = false;
		settings::just_shot = true;
		settings::fixed_time_last_shot = Time::fixedTime();
	}

	if (settings::combat::rapid_fire && held->class_name_hash() == STATIC_CRC32("BaseProjectile")) {
		held->repeatDelay() = 0.07f;
	}
	else {
		held->repeatDelay() = 0.15f;
	}

	if (settings::weapons::fastbow && held->class_name_hash() == STATIC_CRC32("BowWeapon")) {
		held->arrowBack() = 1.f;
		held->attackReady() = true;
	}

	if (baseplayah->userID() == LocalPlayer::Entity()->userID()) {
		if (held && held->class_name_hash() == STATIC_CRC32("BaseProjectile") || _held->class_name_hash() == STATIC_CRC32("BowWeapon") || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1965232394 || _held->class_name_hash() == STATIC_CRC32("CompoundBowWeapon") || _held->class_name_hash() == STATIC_CRC32("BaseLauncher") && LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == 1055319033 || LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == -75944661) {
			if (!held->Empty())
			{
				if (!((_held->HasAttackCooldown() || _held->nextAttackTime() >= Time::time() || _held->timeSinceDeploy() < _held->deployDelay())))
				{
					if (reloadTime < 1.0f && lastShotTime < -0.1f)
					{
						if (reinterpret_cast<BasePlayer*>(settings::closestPlayer) != nullptr && (!LocalPlayer::Entity()->is_teammate(reinterpret_cast<BasePlayer*>(settings::closestPlayer)) || !settings::combat::ignore_players_type == 3) && reinterpret_cast<BasePlayer*>(settings::closestPlayer)->IsValid() && baseplayah->get_flag(PlayerFlags::Connected)) {
							if (settings::combat::powershoot)
							{
								if (_held->class_name_hash() == STATIC_CRC32("BowWeapon") || LocalPlayer::Entity()->GetActiveWeapon()->GetID() == 1965232394 || _held->class_name_hash() == STATIC_CRC32("CompoundBowWeapon") || LocalPlayer::Entity()->GetActiveWeapon()->LoadedAmmo() == -75944661)
								{
									if (GetAsyncKeyState(settings::combat::powershoot_key)) {
										autoshoot::OneShootWeapon();
									}
								}
								else
								{
									if (GetAsyncKeyState(settings::combat::powershoot_key)) {
										autoshoot::BulletsFiredPerShoot();
									}
								}
							}
						}
					}
				}
			}
		}

		if (settings::weapons::compound && held->class_name_hash() == STATIC_CRC32("CompoundBowWeapon")) {
			reinterpret_cast<CompoundBowWeapon*>(held)->currentHoldProgress() = 1.5f;
		}

		GLOBAL_TIME = Time::time();
	}

	if (TargetPlayer)
	{
		best_target = TargetPlayer->transform_(head)->position();
	}

	if (settings::weapons::bullet_tp && settings::combat::hit_scan && TargetPlayer != nullptr) {
		hitscan_void();
	}

	if (settings::misc::followprojectile && proj && !projv->isAlive())
	{
		proj = false;
	}

	if (settings::misc::aspect_ratio && !settings::menu::panic) {
		Camera::SetAspect(settings::misc::aspect_ratio_value);
	}
	else {
		Camera::SetAspect(1.8f);
	}

	if (settings::menu::panic)
	{
		baseplayah->UnloadFakeAdmin();
	}
	else if (settings::misc::fakeadmin)
	{
		baseplayah->FakeAdmin();
	}

	if (active && settings::misc::weapon_spam && GetAsyncKeyState(settings::misc::weapon_spam_key)) {
		reinterpret_cast<void(*)(uintptr_t, Signal, Str)>((void*)Offsets::SendSignalBroadcast)(active, Signal::Attack, Str((L"")));
	}

	if (settings::misc::stesh_finder && GetAsyncKeyState(settings::misc::stesh_finder_key))
	{
		BaseEntity* stash_object = BaseNetworkable::clientEntities()->FindClosest<BaseEntity*>(STATIC_CRC32("StashContainer"), LocalPlayer::Entity(), 3.0f);
		if (stash_object && stash_object != nullptr)
			stash_object->_ServerRPC("RPC_OpenLoot");
	}

	if (settings::misc::mass_suicide && GetAsyncKeyState(settings::misc::mass_suicide_key)) {
		LocalPlayer::Entity()->OnLand(-108.0001f);
	}

	if (settings::misc::movement_line)
	{
		static Vector3 previousPos;
		Vector3 localpos = LocalPlayer::Entity()->playerModel()->position();
		if (!previousPos.empty())
		{
			if (utils::LineOfSight(localpos, previousPos))
				DDraw::Line(Vector3(localpos.x, localpos.y + 0.3f, localpos.z), Vector3(previousPos.x, previousPos.y + 0.3f, previousPos.z), Color(movementlinecol[0], movementlinecol[1], movementlinecol[2], 1), 1.f, true, true);
		}
		previousPos = localpos;
	}

	if (settings::misc::spiderman) {

		uintptr_t Movement = read(LocalPlayer::Entity() + Offsets::BasePlayer_movement, uintptr_t);
		write(Movement + Offsets::PlayerWalkMovementt_groundAngles, 0.f, float);
		write(Movement + Offsets::PlayerWalkMovementt_groundAngleNew, 0.f, float);
	}

	if (settings::misc::fly_auto_stop || settings::misc::flyhack_indicator)
	{
		float flyhack_forgiveness_interia = 10.0f;
		float flyhack_forgiveness = 1.f;
		float flyhack_extrusion = 2.f;
		bool flag = false;
		bool isInAir = false;
		Vector3 vector = (LocalPlayer::Entity()->lastSentTick()->__position() + LocalPlayer::Entity()->transform()->position()) * 0.5f;
		flyhackPauseTime = max(0.f, flyhackPauseTime - Time::deltaTime());

		if (!LocalPlayer::Entity()->OnLadder() && !WaterLevel::Test(vector - Vector3(0.0f, flyhack_extrusion, 0.0f), true, false, LocalPlayer::Entity())) {
			float radius = LocalPlayer::Entity()->GetRadius();
			float height = LocalPlayer::Entity()->GetHeight(false);

			Vector3 vector2 = vector + Vector3(0.0f, radius - flyhack_extrusion, 0.0f);
			Vector3 vector3 = vector + Vector3(0.0f, height - radius, 0.0f);
			float radius2 = radius - 0.05f;
			isInAir = !GamePhysics::CheckCapsule(vector2, vector3, radius2, 1503731969, GamePhysics::QueryTriggerInteraction::Ignore);

			if (isInAir)
			{
				Vector3 vector4 = (LocalPlayer::Entity()->transform()->position() - LocalPlayer::Entity()->lastSentTick()->__position());
				float num2 = abs(vector4.y);
				float num3 = Misc::Magnitude2D(vector4);
				if (vector4.y >= 0.0f)
				{
					flyhackDistanceVertical += vector4.y;
					flag = true;
				}
				if (num2 < num3)
				{
					flyhackDistanceHorizontal += num3;
					flag = true;
				}
			}
			float num5 = max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
			float num6 = (LocalPlayer::Entity()->GetJumpHeight() + num5);

			float num7 = max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
			float num8 = (5.f + num7);
			VMaxFlyhack = num6;
			if (flyhackDistanceVertical <= (num6)) {
				VFlyhack = flyhackDistanceVertical;
			}
			if (VFlyhack >= VMaxFlyhack)
				VFlyhack = VMaxFlyhack;
			HMaxFlyhack = num8;
			if (flyhackDistanceHorizontal <= (num8)) {
				float num7 = max((flyhackPauseTime > 0.0f) ? flyhack_forgiveness_interia : flyhack_forgiveness, 0.0f);
				float num8 = ((4.f + num7) * 3);
				HFlyhack = flyhackDistanceHorizontal;
			}
			if (HFlyhack >= HMaxFlyhack)
				HFlyhack = HMaxFlyhack;

		}
		else {
			HFlyhack = 0;
			VFlyhack = 0;
			flyhackDistanceHorizontal = 0.f;
			flyhackDistanceVertical = 0.f;
		}
		if (!isInAir)
		{
			HFlyhack = 0;
			VFlyhack = 0;
			flyhackDistanceHorizontal = 0;
			flyhackDistanceVertical = 0.f;
		}
		if (WaterLevel::Test(vector - Vector3(0.0f, flyhack_extrusion, 0.f), true, false, LocalPlayer::Entity()))
		{
			HFlyhack = 0;
			VFlyhack = 0;
			flyhackDistanceHorizontal = 0.f;
			flyhackDistanceVertical = 0.f;
		}
	}

	if (GetAsyncKeyState(settings::misc::spam_key)) {
		hammerspam();
	}

	original_clientinput(baseplayah, ModelState);

	if (settings::misc::ModelState)
	{
		if (settings::misc::modelstate == 0) {
			LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::OnLadder);
		}
		else if (settings::misc::modelstate == 1) {
			LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::OnGround);
		}
		else if (settings::misc::modelstate == 2) {
			LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Ducked);
		}
		else if (settings::misc::modelstate == 3) {
			LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Sleeping);
		}
		else if (settings::misc::modelstate == 4)
		{
			LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Sprinting);
		}
		else if (settings::misc::modelstate == 5)
		{
			LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Flying);
		}
		else if (settings::misc::modelstate == 6)
		{
			LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Aiming);
		}
		else if (settings::misc::modelstate == 7)
		{
			LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Prone);
		}
		else if (settings::misc::modelstate == 8)
		{
			LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Mounted);
		}
		else if (settings::misc::modelstate == 9)
		{
			LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Relaxed);
		}
		else if (settings::misc::modelstate == 10)
		{
			LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::OnPhone);
		}
	}

	if (settings::misc::omnidirectional_sprinting && !LocalPlayer::Entity()->get_flag(64)) {
		LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Sprinting);
	}

	if (settings::misc::interactive_debug && GetAsyncKeyState(settings::misc::debugging)) {
		BaseProjectile* ent = baseplayah->GetHeldEntity<BaseProjectile>();
		LocalPlayer::Entity()->add_modelstate_flag(ModelStateFlag::Mounted);
		ent->_ServerRPC(("RPC_LootPlayer"));
	}
}

void OnLand_hk(BasePlayer* ply, float vel) {
	if (!LocalPlayer::Entity()->get_flag(PlayerFlags::Connected)) return ply->OnLand(vel);
}

void UpdateVelocity_hk(PlayerWalkMovement* self) {
	if (!self->flying()) {
		Vector3 vel = self->TargetMovement();
		if (settings::misc::omnidirectional_sprinting && !LocalPlayer::Entity()->get_flag(64)) {
			float max_speed = (self->swimming() || self->Ducking() > 0.5) ? 1.7f : 5.5f;
			if (vel.length() > 0.f) {
				Vector3 target_vel = Vector3(vel.x / vel.length() * max_speed, vel.y, vel.z / vel.length() * max_speed);
				self->TargetMovement() = target_vel;
			}
		}
	}
	Vector3 vector = (LocalPlayer::Entity()->lastSentTick()->__position() + LocalPlayer::Entity()->transform()->position()) * 0.5f;
	if (settings::misc::walkonwater && WaterLevel::Test(vector - Vector3(0, 0.3, 0), true, false, LocalPlayer::Entity())) {
		self->flying() = true;
	}
	return original_updatevelos(self);
}

void HandleJumping_hk(PlayerWalkMovement* a1, ModelState* state, bool wantsJump, bool jumpInDirection = false) {
	if (settings::misc::fly_auto_stop && !GetAsyncKeyState(settings::misc::debugging))
	{
		auto localplayer = LocalPlayer::Entity();
		Vector3 current = localplayer->lastSentTick()->__position();
		if (!WaterLevel::Test(current - Vector3(0.0f, 2.f, 0.0f), true, false, LocalPlayer::Entity()))
		{
			if (HFlyhack >= (HMaxFlyhack - 2.5f)
				|| VFlyhack >= (VMaxFlyhack - 0.4f))
				return original_jumpup(a1, state, false, jumpInDirection);
		}
	}

	if (settings::misc::inf_jump) {
		a1->landTime() = 0.f;
		a1->jumpTime() = 0.f;
		a1->groundTime() = 999999999.f;
	}

	return original_jumpup(a1, state, wantsJump, jumpInDirection);
}

pUncStr Run(ConsoleOptions* options, pUncStr strCommand, DWORD64 args) {
	if (options->IsFromServer()) {
		std::wstring cmd = std::wstring(strCommand->str);
		if (cmd.find((L"noclip")) != std::wstring::npos || cmd.find((L"debugcamera")) != std::wstring::npos || cmd.find((L"camspeed")) != std::wstring::npos || cmd.find((L"admintime")) != std::wstring::npos) {
			strCommand = nullptr;
		}

	}
	return original_consolerun(options, strCommand, args);
}

void hk_DoFirstPersonCamera(PlayerEyes* a1, Component* cam) {
	if (!a1 || !cam) return;
	Original_DoFirstPersonCamera_hk(a1, cam);
	if (settings::misc::followprojectile && GetAsyncKeyState(settings::misc::followprojectile_key) && proj && projv->isAuthoritative())
	{
		Vector3 p = projv->currentPosition();
		cam->transform()->set_position(Vector3(p.x, p.y + 0.1f, p.z));
	}
}

// ===== Manipulator: хуки (порт из 222333666, адаптация под SDK проекта) =====
// Отдаём серверу манипулированное смещение глаза вместо реального BodyLeanOffset.
Vector3 hk_BodyLeanOffset(PlayerEyes* eyes) {
	if (settings::combat::manipulator && GetAsyncKeyState(settings::misc::manipulator_key) && !m_manipulate.empty())
		return m_manipulate;
	return Original_BodyLeanOffset(eyes);
}

// Смещаем позицию глаз на величину манипуляции — снаряды стартуют из «серверного» глаза,
// поэтому пули легально летят из той же точки, куда смотрит сервер.
Vector3 hk_EyePositionForPlayer(BaseMountable* mount, BasePlayer* player, Quaternion* rot) {
	auto orig = Original_EyePositionForPlayer(mount, player, rot);
	if (settings::combat::manipulator && GetAsyncKeyState(settings::misc::manipulator_key) && !m_manipulate.empty())
		return orig + m_manipulate;
	return orig;
}

void SendClientTick(BasePlayer* baseplayer) {
	if (!baseplayer) return original_sendclienttick(baseplayer);

	// Манипулятор: расширяем desync-окно и пересчитываем выгодную точку смещения глаза.
	if (settings::combat::manipulator && GetAsyncKeyState(settings::misc::manipulator_key)) {
		baseplayer->clientTickInterval() = 0.99f;
		if (settings::closestPlayer != NULL)
			other::find_manipulate_angle();
	}
	else if (!m_manipulate.empty()) {
		baseplayer->clientTickInterval() = 0.05f;
		m_manipulate = Vector3::Zero();
	}

	if (settings::misc::anti_aim) {

		auto input = safe_read(baseplayer + Offsets::BasePlayer_input, uintptr_t);
		auto state = safe_read(input + 0x28, uintptr_t);
		auto current = safe_read(state + 0x10, uintptr_t);
		if (!current)
			return original_sendclienttick(baseplayer);
		Vector3 real_angles = safe_read(current + 0x14, Vector3);
		Vector3 spin_angles = Vector3::Zero();

		spin_angles = Vector3(100, (rand() % 999 + -999), 100);
		Quaternion q;

		if (spin_angles != Vector3::Zero())
			safe_write(current + 0x14, spin_angles, Vector3);
	}

	return original_sendclienttick(baseplayer);
}

void CursorManagerUpdate_hk(CursorManager* _this)
{
	if (!settings::menu::show) return _this->Update();

	CursorManager::set_visible(true);
	CursorManager::set_lockstate(0);
}

float GetRandomVelocity(ItemModProjectile* mod) {
	static float speed = 1.f;

	if (settings::weapons::fast_bullets) {
		speed = 1.45f; // 1.499 unreg
	}
	else {
		speed = 1.f;
	}

	return original_getrandomvelocity(mod) * speed;
}

Vector3 MoveTowards(Vector3 a1, Vector3 a2, float maxDelta) {
	static auto ptr = METHOD("Assembly-CSharp::BaseProjectile::SimulateAimcone(): Void");
	if (CALLED_BY(ptr, 0x800)) {
		if (settings::weapons::no_recoil) {
			a2 *= settings::weapons::recoil_control / 100.f;
			maxDelta *= settings::weapons::recoil_control / 100.f;
		}
	}
	return original_movetowards(a1, a2, maxDelta);
}

void AddPunch(HeldEntity* a1, Vector3 a2, float duration) {
	if (settings::weapons::no_recoil) {
		a2 *= settings::weapons::recoil_control / 100.f;
	}
	return original_addpunch(a1, a2, duration);
}

void UpdateAmbient(TOD_Sky* TOD_Sky) {
	uintptr_t cycle = read(TOD_Sky + 0x38, uintptr_t);
	uintptr_t ambient = read(TOD_Sky + 0x90, uintptr_t);

	if (!settings::misc::bright_ambient) {
		return original_updateambient(TOD_Sky);
	}
	RenderSettings::set_ambientMode(RenderSettings::AmbientMode::Flat);
	RenderSettings::set_ambientIntensity(6.f);
	RenderSettings::set_ambientLight(Color({ 1, 1, 1, 1 }));
}

Attack* BuildAttackMessage_hk(HitTest* self, BaseEntity* a2) {
	if (!self) return self->BuildAttackMessage(a2);
	auto ret = self->BuildAttackMessage(a2);
	auto entity = BaseNetworkable::clientEntities()->Find<BasePlayer*>(ret->hitID());

	auto localPlayer = LocalPlayer::Entity();
	if (localPlayer) {
		if (reinterpret_cast<BasePlayer*>(self->ignoreEntity())->userID() == localPlayer->userID()) {
			if (entity) {
				if (entity->IsPlayer()) {
					if (settings::combat::bones_target == 0)
						ret->hitBone() = utils::StringPool::Get(("head"));
					else if (settings::combat::bones_target == 1)
						ret->hitBone() = utils::StringPool::Get(("spine4"));
					else if (settings::combat::bones_target == 2) {
						// yandere dev in this bitch
						int num = rand() % 100;

						if (num > 90)
							ret->hitBone() = utils::StringPool::Get(("head"));
						else if (num < 90 && num > 80)
							ret->hitBone() = utils::StringPool::Get(("neck"));
						else if (num < 80 && num > 70)
							ret->hitBone() = utils::StringPool::Get(("l_clavicle"));
						else if (num < 70 && num > 60)
							ret->hitBone() = utils::StringPool::Get(("pelvis"));
						else if (num < 60 && num > 50)
							ret->hitBone() = utils::StringPool::Get(("r_hip"));
						else if (num < 50 && num > 40)
							ret->hitBone() = utils::StringPool::Get(("r_foot"));
						else if (num < 40 && num > 30)
							ret->hitBone() = utils::StringPool::Get(("spine1"));
						else if (num < 30 && num > 20)
							ret->hitBone() = utils::StringPool::Get(("l_hand"));
						else if (num < 20 && num > 10)
							ret->hitBone() = utils::StringPool::Get(("r_upperarm"));
						else if (num < 10)
							ret->hitBone() = utils::StringPool::Get(("l_knee"));
						else
							ret->hitBone() = utils::StringPool::Get(("spine4"));
					}
					else if (settings::combat::bones_target == 3) {
						int yeet = rand() % 100;
						if (yeet > 50)
							ret->hitBone() = utils::StringPool::Get(("head"));
						else
							ret->hitBone() = utils::StringPool::Get(("spine4"));
					}
				}
			}
		}
	}
	return ret;
}

Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = true) {
	BasePlayer* target_player = reinterpret_cast<BasePlayer*>(settings::closestPlayer);
	Vector3 target;
	auto held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
	BaseProjectile* _held = held = LocalPlayer::Entity()->GetHeldEntity<BaseProjectile>();
	if (settings::combat::psilent && _held->class_name_hash() != STATIC_CRC32("BaseMelee")) {
		if (target_player) {
			if (settings::combat::hit_scan) {
				target = best_target;
			}
			else {
				if (settings::combat::bones_target == 0)
				{
					target = target_player->GetBoneByID(head);
				}
				else if (settings::combat::bones_target == 1)
				{
					target = target_player->GetBoneByID(spine4);
				}
				else if (settings::combat::bones_target == 2)
				{
					int yeet1 = rand() % 100;
					if (yeet1 > 50) {
						target = target_player->GetBoneByID(head);
					}
					else {
						target = target_player->GetBoneByID(spine1);
					}
				}
				else if (settings::combat::bones_target == 3)
				{
					int num = rand() % 100;
					if (num > 90)
					{
						target = target_player->GetBoneByID(head);
					}
					else if (num < 90 && num > 80)
					{
						target = target_player->GetBoneByID(neck);
					}
					else if (num < 80 && num > 70)
					{
						target = target_player->GetBoneByID(r_hip);
					}
					else if (num < 70 && num > 60)
					{
						target = target_player->GetBoneByID(pelvis);
					}
					else if (num < 60 && num > 50)
					{
						target = target_player->GetBoneByID(l_clavicle);
					}
					else if (num < 50 && num > 40)
					{
						target = target_player->GetBoneByID(l_upperarm);
					}
					else if (num < 40 && num > 30)
					{
						target = target_player->GetBoneByID(l_foot);
					}
					else if (num < 30 && num > 20)
					{
						target = target_player->GetBoneByID(r_foot);
					}
					else if (num < 20 && num > 10)
					{
						target = target_player->GetBoneByID(l_hand);
					}
					else if (num < 10)
					{
						target = target_player->GetBoneByID(r_hand);
					}
					else
					{
						target = target_player->GetBoneByID(spine1);
					}
				}
			}

			auto mag = held->primaryMagazine();
			if (!mag) return original_aimconedirection(aimCone, inputVec, anywhereInside);
			auto ammo = mag->ammoType();
			if (!ammo) return original_aimconedirection(aimCone, inputVec, anywhereInside);
			auto mod = ammo->GetComponent<ItemModProjectile>(Type::ItemModProjectile());
			if (!mod) return original_aimconedirection(aimCone, inputVec, anywhereInside);
			auto projectile = mod->projectileObject()->Get()->GetComponent<Projectile>(Type::Projectile());
			if (!projectile) return original_aimconedirection(aimCone, inputVec, anywhereInside);

			float distance = Math::Distance_3D(LocalPlayer::Entity()->GetBoneByID(head), target_player->GetBoneByID(head));

			if (projectile)
			{
				auto projectileVelocity = mod->projectileVelocity();

				auto projectileVelocityScale = _held->projectileVelocityScale();

				if (settings::weapons::fast_bullets) {
					projectileVelocityScale = 1.45f * _held->projectileVelocityScale();
				}
				else {
					projectileVelocityScale = 1.f * _held->projectileVelocityScale();
				}

				float drag = projectile->drag();
				float gravityModifier = projectile->gravityModifier();
				float initialDistance = projectile->initialDistance();
				auto gravity = Physics::get_gravity();
				auto deltaTime = Time::fixedDeltaTime();
				auto timescale = Time::timeScale();

				float DeltaForLoop = deltaTime * timescale;

				Vector3 localPos = LocalPlayer::Entity()->eyes()->get_position();

				Vector3 actualTargetPos;

				actualTargetPos = target;

				float bulletTime = std::sqrt((actualTargetPos.x) * (actualTargetPos.x) + (actualTargetPos.z) * (actualTargetPos.z));

				Vector3 targetvel = target_player->GetWorldVelocity();
				Vector3 targetPosition = actualTargetPos;

				auto _aimDir = original_aimconedirection(0.f, targetPosition - localPos, false);

				Vector3 playerVelocity = Vector3(target_player->GetWorldVelocity().x, 0, target_player->GetWorldVelocity().z);

				auto position = localPos;
				float num = 0.03125f;
				int num3 = (8.f / DeltaForLoop);

				int simulations = 0;

				float offset = 0.1;

				if (settings::misc::predict_type == 0) {
					while (simulations < 30)
					{
						simulations++;
						bool hitPlayer = false;

						_aimDir = original_aimconedirection(0.f, targetPosition - localPos, false);
						Vector3 velocity = _aimDir * projectileVelocity * projectileVelocityScale;

						auto currentPosition = localPos;
						auto previousPosition = currentPosition;

						Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
						Vector3 offset = Vector3().Zero();

						for (int i = -1; i < num3; i++)
						{
							previousPosition = currentPosition;
							currentPosition += velocity * deltaTime;
							velocity += gravity * gravityModifier * deltaTime;
							velocity -= velocity * drag * deltaTime;

							auto line = (currentPosition - previousPosition);
							auto len = line.UnityMagnitude();
							line.UnityNormalize();
							auto v = actualTargetPos - previousPosition;
							auto d = Vector3().UnityDot(v, line);

							if (d < 0.f)
							{
								d = 0.f;
							}
							else if (d > len)
							{
								d = len;
							}

							Vector3 nearestPoint = previousPosition + line * d;

							if (nearestPoint.distance(actualTargetPos) < 0.1f)
							{
								bulletTime = i * num;
								hitPlayer = true;
							}
							else if (nearestPoint.distance(actualTargetPos) < closestPoint.distance(actualTargetPos))
							{
								closestPoint = nearestPoint;
								offset = actualTargetPos - nearestPoint;
							}
						}
						if (hitPlayer) break;
						targetPosition += offset;
					}

					if (bulletTime != 1337.f)
					{
						Vector3 finalVelocity = playerVelocity * bulletTime;

						actualTargetPos += finalVelocity;

						Vector3 targetPosition = actualTargetPos;

						auto _aimDir = original_aimconedirection(0.f, targetPosition - localPos, false);
						float bulletTime = 1337.f;
						int sims = 0;
						while (sims < 30)
						{

							sims++;
							bool hitPlayer = false;

							_aimDir = original_aimconedirection(0.f, targetPosition - localPos, false);
							Vector3 velocity = _aimDir * projectileVelocity * projectileVelocityScale;

							auto currentPosition = localPos;
							auto previousPosition = currentPosition;

							Vector3 closestPoint(FLT_MAX, FLT_MAX, FLT_MAX);
							Vector3 offset = Vector3().Zero();

							for (int i = -1; i < num3; i++)
							{
								previousPosition = currentPosition;
								currentPosition += velocity * num;
								velocity += gravity * gravityModifier * num;
								velocity -= velocity * drag * num;

								auto line = (currentPosition - previousPosition);
								auto len = line.UnityMagnitude();
								line.UnityNormalize();
								auto v = actualTargetPos - previousPosition;
								auto d = Vector3().UnityDot(v, line);

								if (d < 0.f)
								{
									d = 0.f;
								}
								else if (d > len)
								{
									d = len;
								}

								Vector3 nearestPoint = previousPosition + line * d;

								if (nearestPoint.distance(actualTargetPos) < 0.1f)
								{
									bulletTime = i * num;
									hitPlayer = true;
								}
								else if (nearestPoint.distance(actualTargetPos) < closestPoint.distance(actualTargetPos))
								{
									closestPoint = nearestPoint;
									offset = actualTargetPos - nearestPoint;
								}
							}

							if (hitPlayer) break;
							targetPosition += offset;
						}
					}
				}
				else if (settings::misc::predict_type == 1) {
					while (simulations < 100)
					{
						auto position = localPos;
						auto origin = position;
						float num = deltaTime * timescale;
						float travelTime = 0.0f;
						int num3 = (int)(8.f / num);

						Vector3 targetPosition = actualTargetPos + Vector3(0, offset, 0);

						Vector3 vel = Vector3(targetvel.x, 0, targetvel.z);

						auto _aimDir = original_aimconedirection(0.f, targetPosition - localPos, false);
						Vector3 velocity = _aimDir * projectileVelocity * projectileVelocityScale;

						float x = 0.1f;
						if (localPos.distance(targetPosition) < 50.0f)
							x = 0.05f;
						x += localPos.distance(targetPosition) / 1000.0f;

						Vector3 t = SimulateProjectile_(position, velocity, x, travelTime, gravity, drag);

						if (travelTime > 8.f)
							travelTime = 0.0f;

						targetPosition = actualTargetPos + Vector3(0, offset, 0);
						_aimDir = original_aimconedirection(0.f, targetPosition - localPos, false);
						velocity = _aimDir * projectileVelocity * projectileVelocityScale;

						for (size_t i = 0; i < num3; i++)
						{
							origin = position;
							position += velocity * num;
							velocity += gravity * gravityModifier * num;
							velocity -= velocity * drag * num;

							if (LineCircleIntersection(actualTargetPos, 0.1f, origin, position, _aimDir, offset))
							{
								settings::did_reload = false;
								settings::just_shot = true;
								settings::fixed_time_last_shot = Time::fixedTime();

								return _aimDir;
							}
						}

						offset += 0.1f;
						simulations++;
					}
				}
				
				settings::did_reload = false;
				settings::just_shot = true;
				settings::fixed_time_last_shot = Time::fixedTime();

				return _aimDir;
			}
		}
	}

	if (settings::weapons::no_spread) {
		aimCone = settings::weapons::no_spread_value / 100.f;
	}
	settings::did_reload = false;
	settings::just_shot = true;
	settings::fixed_time_last_shot = Time::fixedTime();
	return original_aimconedirection(aimCone, inputVec, anywhereInside);
}

void Launch(Projectile* pr) {
	while (pr->isAlive() && (pr->traveledDistance() < pr->initialDistance() || pr->traveledTime() < 0.1f))
	{
		auto* target_player = reinterpret_cast<BasePlayer*>(settings::closestPlayer);
		Vector3 vector2 = pr->currentVelocity() * 0.00025;
		float magnitude = vector2.Magnitude();
		float num2 = 1.f / magnitude;
		Vector3 vector3 = vector2 * num2;
		Vector3 vector4 = pr->currentPosition() + vector3 * magnitude;
		Line line = Line(pr->currentPosition(), vector4);
		Vector3 FirstNearest = line.ClosestPoint(target_player->GetBoneByID(head));
		float DistanceToPoint1 = FirstNearest.Distance(target_player->GetBoneByID(head));

		if (settings::weapons::bullet_tp) {
			if (DistanceToPoint1 < 20.f)
			{
				pr->UpdateVelocity(0.00025);
				bullet_tp(pr);
			}
			else
			{
				pr->UpdateVelocity(0.03125);
			}
		}
		else
		{
			pr->UpdateVelocity(0.03125);
		}
	}

	float time = Time::fixedTime();
	time -= pr->traveledTime();
	pr->launchTime() = time;

	return original_launch(pr);
}

bool CanAttack(BasePlayer* a1) {
	if (settings::misc::can_attack)
		return true;
	return original_canattack(a1);
}

bool DoHit(Projectile* prj, HitTest* test, Vector3 point, Vector3 normal) {
	auto localPlayer = LocalPlayer::Entity();
	auto held = localPlayer->GetHeldEntity<BaseProjectile>();

	if (prj->isAuthoritative()) {
		if (settings::misc::hitmaterial == 0) {
		}
		else if (settings::misc::hitmaterial == 1) {
			test->HitMaterial_() = il2cpp::String::New(("glass"));
		}
		else if (settings::misc::hitmaterial == 2) {
			test->HitMaterial_() = il2cpp::String::New(("water"));
		}
		else if (settings::misc::hitmaterial == 3) {
			test->HitMaterial_() = il2cpp::String::New(("wood"));
		}
		else if (settings::misc::hitmaterial == 4) {
			test->HitMaterial_() = il2cpp::String::New(("metal"));
		}
		else if (settings::misc::hitmaterial == 5) {
			test->HitMaterial_() = il2cpp::String::New(("sand"));
		}
		else if (settings::misc::hitmaterial == 6) {
			test->HitMaterial_() = il2cpp::String::New(("grass"));
		}
		else if (settings::misc::hitmaterial == 7) {
			test->HitMaterial_() = il2cpp::String::New(("rock"));
		}
		else if (settings::misc::hitmaterial == 8) {
			test->HitMaterial_() = il2cpp::String::New(("concrete"));
		}
		else if (settings::misc::hitmaterial == 9) {
			test->HitMaterial_() = il2cpp::String::New(("forest"));
		}
		else if (settings::misc::hitmaterial == 10) {
			test->HitMaterial_() = il2cpp::String::New(("cloth"));
		}
		else if (settings::misc::hitmaterial == 11) {
			test->HitMaterial_() = il2cpp::String::New(("explosions"));
		}

		if (settings::weapons::penetrate && !reinterpret_cast<BasePlayer*>(settings::closestPlayer)->IsNpc())
		{
			if (GetAsyncKeyState(settings::misc::manipulator_key)) {
				if (utils::LineOfSight(LocalPlayer::Entity()->eyes()->position(), reinterpret_cast<BasePlayer*>(settings::closestPlayer)->GetBoneByID(head)))
				{
					BaseCombatEntity* entity = reinterpret_cast<BaseCombatEntity*>(test->HitEntity());

					if (!entity->IsPlayer()) {
						return false;
					}

					if (entity->ClassNameHash() != STATIC_CRC32("BasePlayer")) {
						return false;
					}
				}
			}

			if (test->HitEntity() != NULL) {
				if (test->HitEntity()->IsValid()) {
					BaseCombatEntity* lol = reinterpret_cast<BaseCombatEntity*>(test->HitEntity());

					if (lol->ClassNameHash() == STATIC_CRC32("CargoShip") || lol->ClassNameHash() == STATIC_CRC32("BaseOven")
						|| lol->ClassNameHash() == STATIC_CRC32("TreeEntity") || lol->ClassNameHash() == STATIC_CRC32("OreResourceEntity")
						|| lol->ClassNameHash() == STATIC_CRC32("CH47HelicopterAIController") || lol->ClassNameHash() == STATIC_CRC32("MiniCopter")
						|| lol->ClassNameHash() == STATIC_CRC32("BoxStorage") || lol->ClassNameHash() == STATIC_CRC32("Workbench")
						|| lol->ClassNameHash() == STATIC_CRC32("VendingMachine") || lol->ClassNameHash() == STATIC_CRC32("Barricade")
						|| lol->ClassNameHash() == STATIC_CRC32("BuildingPrivlidge") || lol->ClassNameHash() == STATIC_CRC32("LootContainer")
						|| lol->ClassNameHash() == STATIC_CRC32("HackableLockedCrate") || lol->ClassNameHash() == STATIC_CRC32("ResourceEntity")
						|| lol->ClassNameHash() == STATIC_CRC32("RidableHorse") || lol->ClassNameHash() == STATIC_CRC32("MotorRowboat")
						|| lol->ClassNameHash() == STATIC_CRC32("ScrapTransportHelicopter") || lol->ClassNameHash() == STATIC_CRC32("JunkPile")
						|| lol->ClassNameHash() == STATIC_CRC32("MiningQuarry") || lol->ClassNameHash() == STATIC_CRC32("WaterCatcher")) {
						return false;
					}
				}
			}
		}
	}
	return original_dohit(prj, test, point, normal);
}

void Hk_TryToMove(ItemIcon* a1) {
	Original_TryToMove_hk(a1);
	if (settings::misc::fast_loot) {
		if (a1->queuedForLooting())
		{
			a1->RunTimedAction();
		}
	}
}

void hooking(void* Function, void** Original, void* Detour) {
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED) {
		return;
	}
	MH_CreateHook(Function, Detour, Original);
	MH_EnableHook(Function);
}

void unhooking(void* Function, void** Original, void* Detour) {
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED) {
		return;
	}
	MH_DisableHook(Function);
}

void hooks_load()
{
	hooking((void*)METHOD("Assembly-CSharp::BasePlayer::OnLand(Single): Void"), (void**)&BasePlayer::OnLand_, OnLand_hk);
	hooking((void*)METHOD("Assembly-CSharp::PlayerWalkMovement::UpdateVelocity(): Void"), (void**)&original_updatevelos, UpdateVelocity_hk);
	hooking((void*)METHOD("Assembly-CSharp::Projectile::Update(): Void"), (void**)&original_Update, ProjectileUpdate_hk);
	hooking((void*)METHOD("Assembly-CSharp::PlayerWalkMovement::HandleJumping(ModelState,Boolean,Boolean): Void"), (void**)&original_jumpup, HandleJumping_hk);
	hooking((void*)METHOD("Facepunch.Console::ConsoleSystem::Run(Option,String,Object[]): String"), (void**)&original_consolerun, Run);
	hooking((void*)METHOD("Assembly-CSharp::PlayerEyes::DoFirstPersonCamera(Camera): Void"), (void**)&Original_DoFirstPersonCamera_hk, hk_DoFirstPersonCamera);
	hooking((void*)METHOD("Assembly-CSharp::HeldEntity::AddPunch(Vector3,Single): Void"), (void**)&original_addpunch, AddPunch);
	hooking((void*)METHOD("Assembly-CSharp::Projectile::Launch(): Void"), (void**)&original_launch, Launch);
	hooking((void*)METHOD("Assembly-CSharp::BasePlayer::CanAttack(): Boolean"), (void**)&original_canattack, CanAttack);
	hooking((void*)METHOD("UnityEngine.CoreModule::UnityEngine::Vector3::MoveTowards(Vector3,Vector3,Single): Vector3"), (void**)&original_movetowards, MoveTowards);
	hooking((void*)METHOD("Assembly-CSharp-firstpass::TOD_Sky::UpdateAmbient(): Void"), (void**)&original_updateambient, UpdateAmbient);
	hooking((void*)METHOD("Rust.Data::ModelState::set_flying(Boolean): Void"), (void**)&original_setflying, SetFlying);
	hooking((void*)METHOD("Assembly-CSharp::HitTest::BuildAttackMessage(BaseEntity): Attack"), (void**)&HitTest::BuildAttackMessage_, BuildAttackMessage_hk);
	hooking((void*)METHOD("Assembly-CSharp::Projectile::DoHit(HitTest,Vector3,Vector3): Boolean"), (void**)&original_dohit, DoHit);
	hooking((void*)METHOD("Assembly-CSharp::BasePlayer::SendClientTick(): Void"), (void**)&original_sendclienttick, SendClientTick);
	hooking((void*)METHOD("Assembly-CSharp::ItemModProjectile::GetRandomVelocity(): Single"), (void**)&original_getrandomvelocity, GetRandomVelocity);
	hooking((void*)METHOD("Assembly-CSharp::AimConeUtil::GetModifiedAimConeDirection(Single,Vector3,Boolean): Vector3"), (void**)&original_aimconedirection, GetModifiedAimConeDirection);
	hooking((void*)METHOD("Assembly-CSharp::PlayerWalkMovement::ClientInput(InputState,ModelState): Void"), (void**)&original_walkclientinput, WalkClientInput);
	hooking((void*)METHOD("Assembly-CSharp::BasePlayer::ClientInput(InputState): Void"), (void**)&original_clientinput, ClientInput);
	hooking((void*)METHOD("Assembly-CSharp::ItemIcon::TryToMove(Boolean): Void"), (void**)&Original_TryToMove_hk, Hk_TryToMove);
	hooking((void*)METHOD("Assembly-CSharp::Projectile::DoMovement(Single): Void"), (void**)&original_domovement, DoMovement);
	hooking((void*)METHOD("Assembly-CSharp::BaseCombatEntity::DoHitNotify(HitInfo): Void"), (void**)&original_dohitnotify, DoHitNotify);
	hooking((void*)METHOD("Assembly-CSharp::CursorManager::Update(): Void"), (void**)&CursorManager::Update_, CursorManagerUpdate_hk);
	hooking((void*)METHOD("Assembly-CSharp::HitInfo::get_isHeadshot(): Boolean"), (void**)&original_getisheadshot, get_isHeadshot);
	hooking((void*)METHOD("Assembly-CSharp::PlayerEyes::get_BodyLeanOffset(): Vector3"), (void**)&Original_BodyLeanOffset, hk_BodyLeanOffset);
	hooking((void*)METHOD("Assembly-CSharp::BaseMountable::EyePositionForPlayer(BasePlayer,Quaternion): Vector3"), (void**)&Original_EyePositionForPlayer, hk_EyePositionForPlayer);
}

void hooks_unload()
{
	kiero::unbind(8);
	unhooking((void*)METHOD("Assembly-CSharp::BasePlayer::OnLand(Single): Void"), (void**)&BasePlayer::OnLand_, OnLand_hk);
	unhooking((void*)METHOD("Assembly-CSharp::PlayerWalkMovement::UpdateVelocity(): Void"), (void**)&original_updatevelos, UpdateVelocity_hk);
	unhooking((void*)METHOD("Assembly-CSharp::Projectile::Update(): Void"), (void**)&original_Update, ProjectileUpdate_hk);
	unhooking((void*)METHOD("Assembly-CSharp::PlayerWalkMovement::HandleJumping(ModelState,Boolean,Boolean): Void"), (void**)&original_jumpup, HandleJumping_hk);
	unhooking((void*)METHOD("Facepunch.Console::ConsoleSystem::Run(Option,String,Object[]): String"), (void**)&original_consolerun, Run);
	unhooking((void*)METHOD("Assembly-CSharp::PlayerEyes::DoFirstPersonCamera(Camera): Void"), (void**)&Original_DoFirstPersonCamera_hk, hk_DoFirstPersonCamera);
	unhooking((void*)METHOD("Assembly-CSharp::HeldEntity::AddPunch(Vector3,Single): Void"), (void**)&original_addpunch, AddPunch);
	unhooking((void*)METHOD("Assembly-CSharp::Projectile::Launch(): Void"), (void**)&original_launch, Launch);
	unhooking((void*)METHOD("Assembly-CSharp::BasePlayer::CanAttack(): Boolean"), (void**)&original_canattack, CanAttack);
	unhooking((void*)METHOD("UnityEngine.CoreModule::UnityEngine::Vector3::MoveTowards(Vector3,Vector3,Single): Vector3"), (void**)&original_movetowards, MoveTowards);
	unhooking((void*)METHOD("Assembly-CSharp-firstpass::TOD_Sky::UpdateAmbient(): Void"), (void**)&original_updateambient, UpdateAmbient);
	unhooking((void*)METHOD("Rust.Data::ModelState::set_flying(Boolean): Void"), (void**)&original_setflying, SetFlying);
	unhooking((void*)METHOD("Assembly-CSharp::HitTest::BuildAttackMessage(BaseEntity): Attack"), (void**)&HitTest::BuildAttackMessage_, BuildAttackMessage_hk);
	unhooking((void*)METHOD("Assembly-CSharp::Projectile::DoHit(HitTest,Vector3,Vector3): Boolean"), (void**)&original_dohit, DoHit);
	unhooking((void*)METHOD("Assembly-CSharp::BasePlayer::SendClientTick(): Void"), (void**)&original_sendclienttick, SendClientTick);
	unhooking((void*)METHOD("Assembly-CSharp::ItemModProjectile::GetRandomVelocity(): Single"), (void**)&original_getrandomvelocity, GetRandomVelocity);
	unhooking((void*)METHOD("Assembly-CSharp::AimConeUtil::GetModifiedAimConeDirection(Single,Vector3,Boolean): Vector3"), (void**)&original_aimconedirection, GetModifiedAimConeDirection);
	unhooking((void*)METHOD("Assembly-CSharp::PlayerWalkMovement::ClientInput(InputState,ModelState): Void"), (void**)&original_walkclientinput, WalkClientInput);
	unhooking((void*)METHOD("Assembly-CSharp::BasePlayer::ClientInput(InputState): Void"), (void**)&original_clientinput, ClientInput);
	unhooking((void*)METHOD("Assembly-CSharp::ItemIcon::TryToMove(Boolean): Void"), (void**)&Original_TryToMove_hk, Hk_TryToMove);
	unhooking((void*)METHOD("Assembly-CSharp::Projectile::DoMovement(Single): Void"), (void**)&original_domovement, DoMovement);
	unhooking((void*)METHOD("Assembly-CSharp::BaseCombatEntity::DoHitNotify(HitInfo): Void"), (void**)&original_dohitnotify, DoHitNotify);
	unhooking((void*)METHOD("Assembly-CSharp::CursorManager::Update(): Void"), (void**)&CursorManager::Update_, CursorManagerUpdate_hk);
	unhooking((void*)METHOD("Assembly-CSharp::HitInfo::get_isHeadshot(): Boolean"), (void**)&original_getisheadshot, get_isHeadshot);
	unhooking((void*)METHOD("Assembly-CSharp::PlayerEyes::get_BodyLeanOffset(): Vector3"), (void**)&Original_BodyLeanOffset, hk_BodyLeanOffset);
	unhooking((void*)METHOD("Assembly-CSharp::BaseMountable::EyePositionForPlayer(BasePlayer,Quaternion): Vector3"), (void**)&Original_EyePositionForPlayer, hk_EyePositionForPlayer);
}