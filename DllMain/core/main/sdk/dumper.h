namespace Offsets
{
    namespace BasePlayer
    {
        uintptr_t playerInput;
        uintptr_t inventory;
        uintptr_t clActiveItem;
        uintptr_t belt;
        uintptr_t modelState;
        uintptr_t movement;
        uintptr_t eyes;
        uintptr_t clientTeam;
        uintptr_t lifestate;
        uintptr_t playerModel;
        uintptr_t playerFlags;
        uintptr_t health;
        uintptr_t maxHealth;
        uintptr_t displayName;
        uintptr_t userid;
        uintptr_t currentTeam;
    }

    namespace MainCamera
    {

        uintptr_t get_position;
        uintptr_t set_position;
        uintptr_t set_up;
        uintptr_t set_forward;
        uintptr_t get_rotation;

    }
    namespace Phrase
    {
        uintptr_t english;
    }
    namespace WorldItem
    {
        uintptr_t item;
    }
    namespace BaseEntity
    {
        uintptr_t IsDestroyed;
        uintptr_t transform;
        uintptr_t bounds;
        uintptr_t position;
        uintptr_t rotation;
        uintptr_t prefabID;
        uintptr_t skinID;
        uintptr_t gameObjectLayer;
        uintptr_t flags;
        uintptr_t model;
    }

    namespace BaseNetworkable
    {
        uintptr_t net;
        uintptr_t clientEntities;
        uintptr_t get_ShortPrefabName;
        uintptr_t serverEntities;
        uintptr_t entityList;
        uintptr_t entityRealm;
        uintptr_t staticFields;
    }

    namespace Transform
    {
        uintptr_t position;
        uintptr_t rotation;
        uintptr_t localPosition;
        uintptr_t localRotation;
        uintptr_t localScale;
        uintptr_t parent;
        uintptr_t childCount;
    }

    namespace Component
    {
        uintptr_t gameObject;
        uintptr_t transform;
        uintptr_t tag;
        uintptr_t name;
    }

    namespace GameObject
    {
        uintptr_t transform;
        uintptr_t layer;
        uintptr_t tag;
        uintptr_t name;
        uintptr_t active;
        uintptr_t componentList;
    }

    namespace BaseCombatEntity
    {
        uintptr_t health;
        uintptr_t maxHealth;
        uintptr_t lifestate;
        uintptr_t faction;
        uintptr_t startHealth;
        uintptr_t repair;
        uintptr_t pickup;
    }

    namespace PlayerModel
    {
        uintptr_t boneTransforms;
        uintptr_t boneNames;
        uintptr_t bindPoses;
        uintptr_t rootBone;
        uintptr_t isLocalPlayer;
        uintptr_t visible;
        uintptr_t shadow;
        uintptr_t newVelocity;
        uintptr_t position;
        uintptr_t IsNpc;
    }

    namespace PlayerInput
    {
        uintptr_t state;
        uintptr_t bodyAngles;
        uintptr_t headAngles;
        uintptr_t movement;
        uintptr_t buttons;
    }

    namespace PlayerInventory
    {
        uintptr_t containerBelt;
        uintptr_t containerWear;
    }

    namespace ItemContainer
    {
        uintptr_t itemList;
    }

    namespace Item
    {
        uintptr_t info;
        uintptr_t heldEntity;
        uintptr_t uid;
    }

    namespace ItemDefinition
    {
        uintptr_t displayName;
        uintptr_t itemid;
        uintptr_t iconSprite;
    }

    namespace Model
    {
        uintptr_t boneTransforms;
    }

    namespace HeldEntity
    {
        uintptr_t isDeployed;
    }

    namespace AttackEntity
    {
        uintptr_t nextAttackTime;
        uintptr_t timeSinceDeploy;
        uintptr_t deployDelay;
        uintptr_t repeatDelay;
    }

    namespace BaseProjectile
    {
        uintptr_t primaryMagazine;
        uintptr_t automatic;
        uintptr_t aimSway;
        uintptr_t aimSwaySpeed;
    }

    namespace HitTest
    {
        uintptr_t MaxDistance;
        uintptr_t HitTransform;
        uintptr_t AttackRay;
        uintptr_t DidHit;
        uintptr_t HitEntity;
        uintptr_t HitPoint;
        uintptr_t HitNormal;
        uintptr_t damageProperties;
    }

    namespace BaseMelee
    {
        uintptr_t maxDistance;
        uintptr_t damageProperties;
    }

    namespace BowWeapon
    {
        uintptr_t wasAiming;
        uintptr_t attackready;
        uintptr_t arrowBack;
    }

    namespace FlintStrikeWeapon
    {
        uintptr_t successFraction;
        uintptr_t didSparkThisFrame;
    }

    namespace PlayerWalkMovement
    {
        uintptr_t gravityMultiplier;
        uintptr_t groundAngles;
        uintptr_t groundAngleNew;
    }

    namespace PlayerEyes
    {
        uintptr_t viewOffset;
        uintptr_t BodyForward;
        uintptr_t get_rotation;
    }

    namespace ModelState
    {
        uintptr_t flags;
    }

    namespace Projectile
    {
        uintptr_t currentVelocity;
    }

    namespace EntityRealm
    {
        uintptr_t entityList;
        uintptr_t children;
        uintptr_t parent;
        uintptr_t root;
    }


    namespace ConVar
    {
        uintptr_t admin;
        uintptr_t graphics;
    }

    namespace Methods
    {
        uintptr_t Component_get_gameObject;
        uintptr_t Transform_get_position;
        uintptr_t Transform_get_rotation;
        uintptr_t GameObject_get_transform;
        uintptr_t GameObject_get_layer;
        uintptr_t BaseEntity_get_IsDestroyed;
        uintptr_t SendSignalBroadcast;
    }

    namespace Classes
    {
        il2cpp::methods::Il2CppClass* MainCamera;
        il2cpp::methods::Il2CppClass* LocalPlayer; 
        il2cpp::methods::Il2CppClass* BaseNetworkable;
        il2cpp::methods::Il2CppClass* BaseEntity;
        il2cpp::methods::Il2CppClass* BasePlayer;
        il2cpp::methods::Il2CppClass* Transform;
        il2cpp::methods::Il2CppClass* Component;
        il2cpp::methods::Il2CppClass* GameObject;
        il2cpp::methods::Il2CppClass* BaseCombatEntity;
        il2cpp::methods::Il2CppClass* PlayerModel;
        il2cpp::methods::Il2CppClass* EntityRealm;
        il2cpp::methods::Il2CppClass* ListDictionary;
        il2cpp::methods::Il2CppClass* TOD_Sky;
    }

    namespace Static
    {
        HMODULE GameAssemblyBase;
        HMODULE UnityPlayerBase;
    }

    void Dump() {
        std::cout << "[DUMPER] Starting offset dump..." << std::endl;

        Static::GameAssemblyBase = GetModuleHandleA("GameAssembly.dll");
        Static::UnityPlayerBase = GetModuleHandleA("UnityPlayer.dll");

        if (!Static::GameAssemblyBase) {
            std::cout << "[DUMPER] ERROR: GameAssembly.dll not found!" << std::endl;
            return;
        }

        std::cout << "[DUMPER] GameAssembly.dll: 0x" << std::hex << Static::GameAssemblyBase << std::endl;

        Classes::TOD_Sky = CLASS("Assembly-CSharp-firstpass::TOD_Sky");
        Classes::BaseNetworkable = CLASS("Assembly-CSharp::BaseNetworkable");
        Classes::LocalPlayer = CLASS("Assembly-CSharp::LocalPlayer"); 

        Classes::BaseEntity = CLASS("Assembly-CSharp::BaseEntity");
        Classes::MainCamera = CLASS("Assembly-CSharp::MainCamera");
        Classes::BasePlayer = CLASS("Assembly-CSharp::BasePlayer");
        Classes::Transform = CLASS("UnityEngine.CoreModule::UnityEngine::Transform");
        Classes::Component = CLASS("UnityEngine.CoreModule::UnityEngine::Component");
        Classes::GameObject = CLASS("UnityEngine.CoreModule::UnityEngine::GameObject");
        Classes::BaseCombatEntity = CLASS("Assembly-CSharp::BaseCombatEntity");
        Classes::PlayerModel = CLASS("Assembly-CSharp::PlayerModel");
        Classes::EntityRealm = CLASS("Assembly-CSharp::EntityRealm");
        Classes::ListDictionary = CLASS("Assembly-CSharp::ListHashSet");

        BaseEntity::IsDestroyed = OFFSET("Assembly-CSharp::BaseNetworkable::<IsDestroyed>k__BackingField");
        BaseEntity::transform = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_transform(): Transform");
        BaseEntity::bounds = OFFSET("Assembly-CSharp::BaseEntity::bounds");
        BaseEntity::position = OFFSET("Assembly-CSharp::BaseEntity::position");
        BaseEntity::rotation = OFFSET("Assembly-CSharp::BaseEntity::rotation");
        BaseEntity::prefabID = OFFSET("Assembly-CSharp::BaseEntity::prefabID");
        BaseEntity::skinID = OFFSET("Assembly-CSharp::BaseEntity::skinID");
        BaseEntity::flags = OFFSET("Assembly-CSharp::BaseEntity::flags");
        BaseEntity::model = il2cpp::value("BaseEntity", "model");

        BasePlayer::playerInput = il2cpp::value("BasePlayer", "input");
        BasePlayer::inventory = OFFSET("Assembly-CSharp::BasePlayer::inventory");
        BasePlayer::clActiveItem = OFFSET("Assembly-CSharp::BasePlayer::clActiveItem");
        BasePlayer::modelState = il2cpp::value("BasePlayer", "modelState");
        BasePlayer::movement = il2cpp::value("BasePlayer", "movement");
        BasePlayer::eyes = OFFSET("Assembly-CSharp::BasePlayer::eyes");
        BasePlayer::currentTeam = il2cpp::value("BasePlayer", "currentTeam");
        BasePlayer::lifestate = OFFSET("Assembly-CSharp::BasePlayer::lifestate");
        BasePlayer::playerFlags = il2cpp::value("BasePlayer", "playerFlags");
        BasePlayer::health = OFFSET("Assembly-CSharp::BasePlayer::_health");
        BasePlayer::maxHealth = OFFSET("Assembly-CSharp::BasePlayer::_maxHealth");
        BasePlayer::displayName = OFFSET("Assembly-CSharp::BasePlayer::_displayName");
        BasePlayer::playerModel = il2cpp::value(("BasePlayer"), ("playerModel"));

        Offsets::MainCamera::get_position = METHOD("Assembly-CSharp::MainCamera::get_position(): Vector3");
        Offsets::MainCamera::set_position = METHOD("Assembly-CSharp::MainCamera::set_position(): Vector3");
        Offsets::MainCamera::set_up = METHOD("Assembly-CSharp::MainCamera::set_up(): Vector3");
        Offsets::MainCamera::set_forward = METHOD("Assembly-CSharp::MainCamera::set_forward(): Vector3");
        Offsets::MainCamera::get_rotation = METHOD("Assembly-CSharp::MainCamera::get_rotation(): Quaternion");
        
        BasePlayer::userid = il2cpp::value("BasePlayer", "userID");

        BaseNetworkable::net = OFFSET("Assembly-CSharp::BaseNetworkable::net");
        BaseNetworkable::entityList = OFFSET("Assembly-CSharp::BaseNetworkable::entityList");
        BaseNetworkable::staticFields = OFFSET("Assembly-CSharp::BaseNetworkable::<static_fields>");
        BaseNetworkable::get_ShortPrefabName = METHOD("Assembly-CSharp::BaseNetworkable::get_ShortPrefabName(): String");

        Transform::position = OFFSET("UnityEngine.CoreModule::UnityEngine::Transform::position");
        Transform::rotation = OFFSET("UnityEngine.CoreModule::UnityEngine::Transform::rotation");
        Transform::localPosition = OFFSET("UnityEngine.CoreModule::UnityEngine::Transform::localPosition");
        Transform::localRotation = OFFSET("UnityEngine.CoreModule::UnityEngine::Transform::localRotation");
        Transform::localScale = OFFSET("UnityEngine.CoreModule::UnityEngine::Transform::localScale");
        Transform::parent = OFFSET("UnityEngine.CoreModule::UnityEngine::Transform::parent");

        Component::gameObject = OFFSET("UnityEngine.CoreModule::UnityEngine::Component::gameObject");
        Component::transform = OFFSET("UnityEngine.CoreModule::UnityEngine::Component::transform");
        Component::tag = OFFSET("UnityEngine.CoreModule::UnityEngine::Component::tag");

        GameObject::transform = OFFSET("UnityEngine.CoreModule::UnityEngine::GameObject::transform");
        GameObject::layer = OFFSET("UnityEngine.CoreModule::UnityEngine::GameObject::layer");
        GameObject::tag = OFFSET("UnityEngine.CoreModule::UnityEngine::GameObject::tag");
        GameObject::name = OFFSET("UnityEngine.CoreModule::UnityEngine::GameObject::name");
        GameObject::active = OFFSET("UnityEngine.CoreModule::UnityEngine::GameObject::activeSelf");

        BaseCombatEntity::health = il2cpp::value("BaseCombatEntity", "_health");
        BaseCombatEntity::maxHealth = il2cpp::value("BaseCombatEntity", "_maxHealth");
        BaseCombatEntity::lifestate = OFFSET("Assembly-CSharp::BaseCombatEntity::lifestate");
        BaseCombatEntity::startHealth = il2cpp::value("BaseCombatEntity", "startHealth");

        PlayerModel::boneTransforms = il2cpp::value("Model", "boneTransforms");
        PlayerModel::boneNames = il2cpp::value("Model", "boneNames");
        PlayerModel::rootBone = il2cpp::value("Model", "rootBone");
        PlayerModel::isLocalPlayer = il2cpp::value("PlayerModel", "isLocalPlayer");
        PlayerModel::visible = il2cpp::value("PlayerModel", "visible");
        PlayerModel::newVelocity = il2cpp::value("PlayerModel", "newVelocity");
        PlayerModel::position = il2cpp::value("PlayerModel", "position");
        PlayerModel::IsNpc = OFFSET("Assembly-CSharp::PlayerModel::<IsNpc>k__BackingField");

        PlayerInventory::containerBelt = il2cpp::value("PlayerInventory", "containerBelt");
        PlayerInventory::containerWear = il2cpp::value("PlayerInventory", "containerWear");

        ItemContainer::itemList = il2cpp::value("ItemContainer", "itemList");

        Item::heldEntity = il2cpp::value("Item", "heldEntity");
        Item::uid = il2cpp::value("Item", "uid");
        Item::info = OFFSET("Assembly-CSharp::Item::info");

        ItemDefinition::displayName = OFFSET("Assembly-CSharp::ItemDefinition::displayName");
        ItemDefinition::itemid = il2cpp::value("ItemDefinition", "itemid");
        ItemDefinition::iconSprite = il2cpp::value("ItemDefinition", "iconSprite");

        Model::boneTransforms = il2cpp::value("Model", "boneTransforms");

        HeldEntity::isDeployed = il2cpp::value("HeldEntity", "isDeployed");

        AttackEntity::nextAttackTime = il2cpp::value("AttackEntity", "nextAttackTime");
        AttackEntity::timeSinceDeploy = il2cpp::value("AttackEntity", "timeSinceDeploy");
        AttackEntity::deployDelay = il2cpp::value("AttackEntity", "deployDelay");
        AttackEntity::repeatDelay = il2cpp::value("AttackEntity", "repeatDelay");

        BaseProjectile::primaryMagazine = il2cpp::value("BaseProjectile", "primaryMagazine");
        BaseProjectile::automatic = il2cpp::value("BaseProjectile", "automatic");
        BaseProjectile::aimSway = il2cpp::value("BaseProjectile", "aimSway");
        BaseProjectile::aimSwaySpeed = il2cpp::value("BaseProjectile", "aimSwaySpeed");

        HitTest::MaxDistance = il2cpp::value("HitTest", "MaxDistance");
        HitTest::HitTransform = il2cpp::value("HitTest", "HitTransform");
        HitTest::AttackRay = il2cpp::value("HitTest", "AttackRay");
        HitTest::DidHit = il2cpp::value("HitTest", "DidHit");
        HitTest::HitEntity = il2cpp::value("HitTest", "HitEntity");
        HitTest::HitPoint = il2cpp::value("HitTest", "HitPoint");
        HitTest::HitNormal = il2cpp::value("HitTest", "HitNormal");
        HitTest::damageProperties = il2cpp::value("HitTest", "damageProperties");

        BaseMelee::maxDistance = il2cpp::value("BaseMelee", "maxDistance");
        BaseMelee::damageProperties = il2cpp::value("BaseMelee", "damageProperties");

        BowWeapon::wasAiming = il2cpp::value("BowWeapon", "wasAiming");
        BowWeapon::attackready = il2cpp::value("BowWeapon", "attackready");
        BowWeapon::arrowBack = il2cpp::value("BowWeapon", "arrowBack");

        FlintStrikeWeapon::successFraction = il2cpp::value("FlintStrikeWeapon", "successFraction");
        FlintStrikeWeapon::didSparkThisFrame = il2cpp::value("FlintStrikeWeapon", "_didSparkThisFrame");

        PlayerWalkMovement::gravityMultiplier = il2cpp::value("PlayerWalkMovement", "gravityMultiplier");
        PlayerWalkMovement::groundAngles = il2cpp::value("PlayerWalkMovement", "groundAngle");
        PlayerWalkMovement::groundAngleNew = il2cpp::value("PlayerWalkMovement", "groundAngleNew");

        PlayerEyes::viewOffset = il2cpp::value("PlayerEyes", "viewOffset");
        PlayerEyes::BodyForward = METHOD("Assembly-CSharp::PlayerEyes::BodyForward(): Vector3");
        PlayerEyes::get_rotation = METHOD("Assembly-CSharp::PlayerEyes::get_rotation(): Quaternion");

        Phrase::english = OFFSET("Rust.Localization::Phrase::english");

        PlayerInput::bodyAngles = il2cpp::value("PlayerInput", "bodyAngles");

        ModelState::flags = il2cpp::value("ModelState", "flags");

        Projectile::currentVelocity = il2cpp::value("Projectile", "currentVelocity");

        EntityRealm::entityList = OFFSET("Assembly-CSharp::EntityRealm::entityList");

        ConVar::admin = il2cpp::init_class("Admin", "ConVar");
        ConVar::graphics = il2cpp::init_class("Graphics", "ConVar");

        WorldItem::item = OFFSET("Assembly-CSharp::WorldItem::item");

        Methods::Component_get_gameObject = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_gameObject(): GameObject");
        Methods::Transform_get_position = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_position(): Vector3");
        Methods::Transform_get_rotation = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_rotation(): Quaternion");
        Methods::GameObject_get_transform = METHOD("UnityEngine.CoreModule::UnityEngine::GameObject::get_transform(): Transform");
        Methods::GameObject_get_layer = METHOD("UnityEngine.CoreModule::UnityEngine::GameObject::get_layer(): int");
        Methods::SendSignalBroadcast = METHOD("Assembly-CSharp::BaseEntity::SendSignalBroadcast(Signal,String): Void");

        std::cout << "[DUMPER] Offset dump completed successfully!" << std::endl;
    }
}
