namespace hk_defs {
	typedef Attack*(__fastcall* HitTest_fn)(HitTest*);
	inline HitTest_fn original_BuildAttackMessage{ };
	typedef void(__fastcall* SendProjectileAttack_fn)(BasePlayer*, PlayerProjectileAttack*);
	inline SendProjectileAttack_fn original_sendprojectileattack{ };

	typedef bool(__fastcall* dhit)(Projectile*, HitTest*, Vector3, Vector3);
	inline dhit original_dohit{ };

	typedef bool(__fastcall* can_attack_fn)(BasePlayer*);
	inline can_attack_fn original_canattack{ };

	typedef void(__fastcall* clientinput_fn)(BasePlayer*, ModelState*);
	inline clientinput_fn original_clientinput{ };

	typedef void(__fastcall* dohitnotify)(BaseCombatEntity*, HitInfo*, Projectile*);
	inline dohitnotify original_dohitnotify{ };

	typedef void(__fastcall* lateupd)(TOD_Sky*);
	inline lateupd original_updateambient{ };

	typedef void(__fastcall* rerf)(Projectile*, float);
	inline rerf original_domovement{ };

	typedef void(__fastcall* exploit)(Projectile*);
	inline exploit original_Update{ };

	typedef bool(__fastcall* refr)(Projectile*, uint32_t, Vector3, Vector3, float);
	inline refr original_refract{ };

	typedef float(__fastcall* getrandvel)(ItemModProjectile*);
	inline getrandvel original_getrandomvelocity{ };

	typedef void(__fastcall* sendclienttick)(BasePlayer*);
	inline sendclienttick original_sendclienttick{ };

	typedef Vector3(__fastcall* modifiedaimconedirection)(float, Vector3, bool);
	inline modifiedaimconedirection original_aimconedirection{ };

	typedef void(__fastcall* SetEffectScale_org)(float);
	inline SetEffectScale_org SetEffectSccale_hk_orig{ };

	typedef void(__fastcall* addpunch)(HeldEntity*, Vector3, float);
	inline addpunch original_addpunch{ };

	typedef void(__fastcall* serverrpc)(BaseEntity*, pUncStr);
	inline serverrpc original_serverrpc{ };

	typedef Vector3(__fastcall* movetowards)(Vector3, Vector3, float);
	inline movetowards original_movetowards{ };


	typedef Vector3(__fastcall* ModifyThirdPersonEyeOffset)(Vector3);
	inline ModifyThirdPersonEyeOffset original_ModifyThirdPersonEyeOffset{ };

	typedef void(__fastcall* SetFlying_fn)(ModelState*, bool);
	inline SetFlying_fn original_setflying{ };

	typedef Vector3(__fastcall* hk_BodyLeanOffset)(PlayerEyes*);
	inline hk_BodyLeanOffset Original_BodyLeanOffset{ };

	typedef Vector3(__fastcall* hk_EyePositionForPlayer)(BaseMountable*, BasePlayer*, Quaternion*);
	inline hk_EyePositionForPlayer Original_EyePositionForPlayer{ };

	typedef void(__fastcall* hk_DoFirstPersonCamera)(PlayerEyes*, Component*);
	inline hk_DoFirstPersonCamera Original_DoFirstPersonCamera_hk{ };
	typedef void(__fastcall* hk_TryToMove)(ItemIcon*);
	inline hk_TryToMove Original_TryToMove_hk{ };

	typedef pUncStr(__fastcall* consoleRun)(ConsoleOptions*, pUncStr, DWORD64);
	inline consoleRun original_consolerun{ };

	typedef void(__fastcall* handlejumping)(PlayerWalkMovement*, ModelState*, bool, bool);
	inline handlejumping original_handleJumping{ };

	typedef void(__fastcall* velos)(PlayerWalkMovement*);
	inline velos original_updatevelos{ };

	typedef bool(__fastcall* down)(InputState*, Button);
	inline down original_isdown{ };

	typedef void(__fastcall* upjumping)(PlayerWalkMovement*, ModelState*, bool, bool);
	inline upjumping original_jumpup{ };

	typedef void(__fastcall* dfixd)(PlayerWalkMovement*, ModelState*);
	inline dfixd original_dofixedupdate{ };

	typedef void(__fastcall* relaxed)(ModelState*, bool);
	inline relaxed original_isrelaxed{ };
}