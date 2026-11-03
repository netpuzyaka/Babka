typedef void(__fastcall* rerf)(Projectile*, float);
inline rerf original_domovement{ };

typedef void(__fastcall* hk_TryToMove)(ItemIcon*);
inline hk_TryToMove Original_TryToMove_hk{ };

typedef void(__fastcall* clientinput_fn)(BasePlayer*, ModelState*);
inline clientinput_fn original_clientinput{ };

typedef Vector3(__fastcall* modifiedaimconedirection)(float, Vector3, bool);
inline modifiedaimconedirection original_aimconedirection{ };

typedef float(__fastcall* getrandvel)(ItemModProjectile*);
inline getrandvel original_getrandomvelocity{ };

typedef void(__fastcall* sendclienttick)(BasePlayer*);
inline sendclienttick original_sendclienttick{ };

typedef void(__fastcall* launch)(Projectile*);
inline launch original_launch{ };

typedef Projectile* (__fastcall* create_projectile_fn)(BaseProjectile*, void*, Vector3, Vector3, Vector3);
inline create_projectile_fn original_create_projectile{ };

typedef void(__fastcall* addpunch)(HeldEntity*, Vector3, float);
inline addpunch original_addpunch{ };

typedef void(__fastcall* dohitnotify)(BaseCombatEntity*, HitInfo*, Projectile*);
inline dohitnotify original_dohitnotify{ };

typedef bool(__fastcall* isheadshot)(HitInfo*);
inline isheadshot original_getisheadshot{ };

typedef void(__fastcall* exploit)(Projectile*);
inline exploit original_Update{ };

typedef void(__fastcall* wqdqwdqwd)(PlayerWalkMovement*, InputState*, ModelState*);
inline wqdqwdqwd original_walkclientinput{ };

typedef bool(__fastcall* refr)(Projectile*, uint32_t, Vector3, Vector3, float);
inline refr original_refract{ };

typedef void(__fastcall* velos)(PlayerWalkMovement*);
inline velos original_updatevelos{ };

typedef bool(__fastcall* down)(InputState*, Button_o);
inline down original_isdown{ };

typedef void(__fastcall* upjumping)(PlayerWalkMovement*, ModelState*, bool, bool);
inline upjumping original_jumpup{ };

typedef pUncStr(__fastcall* consoleRun)(ConsoleOptions*, pUncStr, DWORD64);
inline consoleRun original_consolerun{ };

typedef Vector3(__fastcall* hk_BodyLeanOffset_main)(PlayerEyes*);
inline hk_BodyLeanOffset_main Original_BodyLeanOffset{ };

typedef Vector3(__fastcall* hk_EyePositionForPlayer_main)(BaseMountable*, BasePlayer*, Quaternion*);
inline hk_EyePositionForPlayer_main Original_EyePositionForPlayer{ };

typedef void(__fastcall* hk_DoFirstPersonCamera_main)(PlayerEyes*, Component*);
inline hk_DoFirstPersonCamera_main Original_DoFirstPersonCamera_hk{ };

typedef void(__fastcall* SetFlying_fn)(ModelState*, bool);
inline SetFlying_fn original_setflying{ };

typedef bool(__fastcall* dhit)(Projectile*, HitTest*, Vector3, Vector3);
inline dhit original_dohit{ };

typedef void(__fastcall* lateupd)(TOD_Sky*);
inline lateupd original_updateambient{ };

typedef Vector3(__fastcall* movetowards)(Vector3, Vector3, float);
inline movetowards original_movetowards{ };

typedef bool(__fastcall* can_attack_fn)(BasePlayer*);
inline can_attack_fn original_canattack{ };