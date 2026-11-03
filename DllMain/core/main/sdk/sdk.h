class GameObject {
public:
    const char* name() {
        if (!this) return "";
        static auto off = Offsets::GameObject::name;
        if (!off) return "";
        uintptr_t namePtr = read<uintptr_t>((uintptr_t)this + off);
        if (!namePtr) return "";
        return reinterpret_cast<const char*>(namePtr + 0x14);
    }

    int layer() {
        if (!this) return 0;
        static auto off = Offsets::GameObject::layer;
        if (!off) return 0;
        return read<int>((uintptr_t)this + off);
    }

    bool active() {
        if (!this) return false;
        static auto off = Offsets::GameObject::active;
        if (!off) return false;
        return read<bool>((uintptr_t)this + off);
    }
};

class Component {
public:
    const char* class_name() {
        if (!this) return "";
        auto oc = *reinterpret_cast<uint64_t*>(this);
        if (!oc) return "";
        return *reinterpret_cast<char**>(oc + 0x10);
    }
    uint32_t class_name_hash() {
        if (!this) return 0;
        auto oc = *reinterpret_cast<uint64_t*>(this);
        if (!oc) return 0;
        if (!*reinterpret_cast<char**>(oc + 0x10)) return 0;
        const char* name = *reinterpret_cast<char**>(oc + 0x10);
        if (!name) return 0;
        return RUNTIME_CRC32(name);

    }
    GameObject* gameObject() {
        if (!this) return nullptr;
        static auto off = Offsets::Methods::Component_get_gameObject;
        if (!off) return nullptr;
        return SafeExecution::Execute<GameObject*>(off, nullptr, this);
    }
};
template<typename T>
class Il2CppList {
public:
    explicit Il2CppList(uintptr_t list_addr) : addr(list_addr) {}

    bool valid() const { return addr != 0; }

    int size() const {
        if (!addr) return 0;
        return read<int>(addr + 0x18);
    }

    T* get(int index) const {
        if (!addr) return nullptr;
        int n = size();
        if (index < 0 || index >= n) return nullptr;
        uintptr_t items = read<uintptr_t>(addr + 0x10);
        if (!items) return nullptr;
        return read<T*>(items + 0x20 + static_cast<uintptr_t>(index) * sizeof(uintptr_t));
    }

    uintptr_t address() const { return addr; }

private:
    uintptr_t addr{};
};

class Transform : public Component {
public:
    Vector3 position() {
        if (!this) return Vector3::Zero();

        static uintptr_t off = Offsets::Methods::Transform_get_position;
        if (!off) return Vector3::Zero();
        return SafeExecution::Execute<Vector3>(off, Vector3::Zero(), this);
    }
    Vector3 localPosition() {
        if (!this) return Vector3::Zero();
        static auto off = Offsets::Transform::localPosition;
        return read<Vector3>((uintptr_t)this + off);
    }
};
class BaseNetworkable : public Component {
public:
    class EntityRealm {
    public:
        ListDictionary* entityList() {
            if (!this) return nullptr;
            static auto off = Offsets::EntityRealm::entityList;
            if (!off) return 0;
            return read<ListDictionary*>((uintptr_t)this + off);
        }
    };

    static EntityRealm* clientEntities() {
        static uintptr_t clazz = (uintptr_t)Offsets::Classes::BaseNetworkable;
        if (!clazz) return nullptr;

        uintptr_t staticFields = read<uintptr_t>(clazz + 0xB8);
        if (!staticFields) return nullptr;

        return read<EntityRealm*>(staticFields);
    }
    std::uint32_t ShortPrefabName_hashtry(static auto auto_ShortPrefabName_hash) {
        __try {
            if (!reinterpret_cast<il2cpp::String * (__fastcall*)(BaseNetworkable*)>(auto_ShortPrefabName_hash)(this)->buffer
                || !this
                || !auto_ShortPrefabName_hash) return 0;
            return RUNTIME_CRC32_W(reinterpret_cast<il2cpp::String * (__fastcall*)(BaseNetworkable*)>(auto_ShortPrefabName_hash)(this)->buffer);
        }
        __except (SafeExecution::fail(GetExceptionCode(), GetExceptionInformation())) { return 0; };
    }

    std::uint32_t ShortPrefabName_hash() {
        static auto auto_ShortPrefabName_hash = Offsets::BaseNetworkable::get_ShortPrefabName;
        return ShortPrefabName_hashtry(auto_ShortPrefabName_hash);
    }

};
class Phrase {
public:
    const wchar_t* english() {
        try {
            static auto off = Offsets::Phrase::english;
            if (!this) return L"";

            if (!(*reinterpret_cast<il2cpp::String**>(this + off))
                || !(*reinterpret_cast<il2cpp::String**>(this + off))->buffer
                ) return L"";
            return (*reinterpret_cast<il2cpp::String**>(this + off))->buffer;
        }
        catch (...) {};
    }
};
class ItemDefinition : public Component {
public:
    Phrase* displayName() const {
        if (!this) return 0;
        return read<Phrase*>((uintptr_t)this + Offsets::ItemDefinition::displayName);
    }
};
class Item {
public:
    uint64_t uid() const {
        if (!this) return 0;
        return read<uint64_t>((uintptr_t)this + Offsets::Item::uid);
    }
    ItemDefinition* info() const {
        if (!this) return 0;
        return read<ItemDefinition*>((uintptr_t)this + Offsets::Item::info);
    }
    wchar_t* get_name() {
        if (!this) return nullptr;
        uintptr_t info = read<uintptr_t>((uintptr_t)this + Offsets::Item::info);
        if (!info) return nullptr;
        uintptr_t disp = read<uintptr_t>(info + Offsets::ItemDefinition::displayName);
        if (!disp) return nullptr;
        auto str_hdr = read<uintptr_t>(disp + 0x18);
        if (!str_hdr) return nullptr;
        pUncStr Str = reinterpret_cast<pUncStr>(str_hdr);
        return Str ? Str->str : nullptr;
    }

};
class BaseEntity : public BaseNetworkable {
public:
    bool IsDestroyed() {
        if (!this) return true;
        static auto off = Offsets::BaseEntity::IsDestroyed;
        if (!off) return true;
        return read<bool>((uintptr_t)this + off);
    }

    bool IsValid() {
        if (!this) return false;
        return !this->IsDestroyed();
    }

    Transform* transform() {
        if (!this) return nullptr;
        static auto off = Offsets::BaseEntity::transform;
        return SafeExecution::Execute<Transform*>(off, nullptr, this);

       // return read<Transform*>((uintptr_t)this + off);
    }
    Item* item() {
        if (!this) return nullptr;
        static auto off = Offsets::WorldItem::item;
        return read<Item*>((uintptr_t)this + off);

        //return SafeExecution::Execute<Item*>(off, nullptr, this);
    }
    Vector3 position() {
        Transform* t = transform();
        if (!t) return Vector3::Zero();
        return t->position();
    }
};

class BaseCombatEntity : public BaseEntity {
public:
    enum class LifeState {
        Alive = 0,
        Dead = 1
    };
    const char* ClassName() {
        if (!this) return "";
        auto oc = read<uint64_t>((uintptr_t)this);
        if (!oc) return "";
        return read<char*>(oc + 0x10);
    }

    bool IsPlayer() {
        if (!this) return false;
        const char* className = this->ClassName();
        return !strcmp(className, "BasePlayer") ||
            !strcmp(className, "NPCPlayerApex") ||
            !strcmp(className, "NPCMurderer") ||
            !strcmp(className, "NPCPlayer") ||
            !strcmp(className, "HumanNPC") ||
            !strcmp(className, "Scientist") ||
            !strcmp(className, "TunnelDweller") ||
            !strcmp(className, "HTNPlayer") ||
            !strcmp(className, "HumanNPCNew") ||
            !strcmp(className, "ScientistNPCNew") ||
            !strcmp(className, "BanditGuard") ||
            !strcmp(className, "ScientistNPC") ||
            !strcmp(className, "NPCMissionProvider") ||
            !strcmp(className, "NPCShopkeeper");
    }

    float health() {
        if (!this) return 0.0f;
        static auto off = Offsets::BaseCombatEntity::health;
        return read<float>((uintptr_t)this + off);
    }

    float maxHealth() {
        if (!this) return 0.0f;
        static auto off = Offsets::BaseCombatEntity::maxHealth;
        return read<float>((uintptr_t)this + off);
    }
    float startHealth() {
        if (!this) return 0.0f;
        static auto off = Offsets::BaseCombatEntity::startHealth;
        return read<float>((uintptr_t)this + off);
    }
    LifeState lifestate() const {
        if (!this) return static_cast<LifeState>(-1);
        static uintptr_t off = Offsets::BaseCombatEntity::lifestate;
        if (!off) return static_cast<LifeState>(-1);
        return read<LifeState>((uintptr_t)this + off);
    }
    bool is_alive() {
        if (!this) return false;
        return this->lifestate() == LifeState::Alive;
    }
};

class ItemContainer {
public:
    Il2CppList<Item>* itemList() {
        if (!this) return nullptr;
        uintptr_t list_addr = read<uintptr_t>((uintptr_t)this + Offsets::ItemContainer::itemList);
        if (!list_addr) return nullptr;
        return new Il2CppList<Item>(list_addr);
    }
};

class PlayerInventory {
public:
    ItemContainer* containerBelt() {
        if (!this) return nullptr;
        return read<ItemContainer*>((uintptr_t)this + Offsets::PlayerInventory::containerBelt);
    }

    ItemContainer* containerWear() {
        if (!this) return nullptr;
        return read<ItemContainer*>((uintptr_t)this + Offsets::PlayerInventory::containerWear);
    }
};
class PlayerEyes : public Component {
public:
    Vector3 BodyForward() {
        if (!this) return Vector3::Zero();
        static auto off = Offsets::PlayerEyes::BodyForward;
        return SafeExecution::Execute<Vector3>(off, Vector3::Zero(), this);
    }
    Quaternion rotation() {
        if (!this) return Quaternion{};
        static auto off = Offsets::PlayerEyes::get_rotation;
        return reinterpret_cast<Quaternion(__fastcall*)(PlayerEyes*)>(off)(this);
    }
};

class BasePlayer : public BaseCombatEntity {
public:
    PlayerInventory* inventory() {
        if (!this) return nullptr;
        return read<PlayerInventory*>((uintptr_t)this + Offsets::BasePlayer::inventory);
    }
    bool IsNpc() {
        if (!this) return false;
        uintptr_t player_model = read<uintptr_t>((uintptr_t)this + Offsets::BasePlayer::playerModel);
        if (!player_model) return false;
        return read<bool>(player_model + Offsets::PlayerModel::IsNpc); 
    }
    PlayerEyes* eyes() {
        if (!this) return nullptr;
        return read<PlayerEyes*>((uintptr_t)this + Offsets::BasePlayer::eyes);
    }
    uint64_t clActiveItem() {
        if (!this) return 0;
        return read<uint64_t>((uintptr_t)this + Offsets::BasePlayer::clActiveItem);
    }
    Vector3 GetBoneByID(int32_t bone) {
        uintptr_t player_model = read<uintptr_t>((uintptr_t)(this + Offsets::BaseEntity::model));
        if (!player_model) return Vector3::Zero();

        uintptr_t boneTransforms = read<uintptr_t>(player_model + Offsets::PlayerModel::boneTransforms);
        if (!boneTransforms) return Vector3::Zero();

        Transform* BoneValue = read<Transform*>(boneTransforms + 0x20 + bone * 0x8);
        if (!BoneValue) return Vector3::Zero();

        return BoneValue->position();
    }
    bool get_flag(int Flg) {
        return (read<int>(this + Offsets::BasePlayer::playerFlags)) & Flg;
    }
    int currentTeam() {
        auto TeamId = *(int*)(this + Offsets::BasePlayer::currentTeam);
        return TeamId;
    }

    bool is_teammate(BasePlayer* BasePlayer) {
        auto TeamId = *(int*)(BasePlayer + Offsets::BasePlayer::currentTeam);
        auto LocalTeamId = *(int*)(this + Offsets::BasePlayer::currentTeam);

        if (LocalTeamId == 0) return false;
        if (TeamId == LocalTeamId) return true;

        return false;
    }

    Item* GetHeldItem() {
        if (!this) return nullptr;

        auto inventory = this->inventory();
        if (!inventory) return nullptr;

        auto belt = inventory->containerBelt();
        if (!belt) return nullptr;

        auto item_list = belt->itemList();
        if (!item_list) return nullptr;

        for (int i = 0; i < item_list->size(); i++) {
            auto item = reinterpret_cast<Item*>(item_list->get(i));
            if (!item) continue;

            if (item->uid() == this->clActiveItem())
                return item;
        }

        return nullptr;
    }
    const wchar_t* _displayName() {
        if (!this) return L"";
        static auto off = Offsets::BasePlayer::displayName;
        return (*reinterpret_cast<il2cpp::String**>(this + off))->buffer;
    }
    uint64_t userID() {
        if (!this) return 0;
        static auto off = Offsets::BasePlayer::userid;
        if (!off) return 0;

        return read<uint64_t>((uintptr_t)this + off);
    }
};

class MainCamera
{
public:
    static Vector3 Get_Position() {
        static auto off = Offsets::MainCamera::get_position;
        return reinterpret_cast<Vector3(*)()>(off)();
    }
    static Vector3 Set_Position() {
        static auto off = Offsets::MainCamera::set_position;
        return reinterpret_cast<Vector3(*)()>(off)();
    }
    static Vector3 Set_Up() {
        static auto off = Offsets::MainCamera::set_up;
        return reinterpret_cast<Vector3(*)()>(off)();
    }
    static Vector3 Set_Forward() {
        static auto off = Offsets::MainCamera::set_forward;
        return reinterpret_cast<Vector3(*)()>(off)();
    }
    static Quaternion Get_Rotation() {
        static auto off = Offsets::MainCamera::get_rotation;
        return reinterpret_cast<Quaternion(*)()>(off)();
    }
    static MainCamera* Camera() {
        static auto clazz = Offsets::Classes::MainCamera;
        return *reinterpret_cast<MainCamera**>(std::uint64_t(clazz->static_fields));
    }
};
class LocalPlayer {
public:
    static BasePlayer* Entity() {
        auto clazz = Offsets::Classes::LocalPlayer;
        if (!clazz) return nullptr;
        uintptr_t sf = reinterpret_cast<uintptr_t>(clazz->static_fields);
        if (!sf) return nullptr;
        return read<BasePlayer*>(sf);
    }
};


namespace utils {

	bool w2s(const Vector3& EntityPos, Vector2& ScreenPos)
	{
		if (EntityPos.x == 0 && EntityPos.y == 0 && EntityPos.z == 0)
			return false;

		auto matrix = il2cpp::find_matrix();
		if (!matrix)
			return false;

		Vector3 TransVec = Vector3(matrix->_14, matrix->_24, matrix->_34);
		Vector3 RightVec = Vector3(matrix->_11, matrix->_21, matrix->_31);
		Vector3 UpVec = Vector3(matrix->_12, matrix->_22, matrix->_32);
		float w = Math::Dot(TransVec, EntityPos) + matrix->_44;


		float y = Math::Dot(UpVec, EntityPos) + matrix->_42;
		float x = Math::Dot(RightVec, EntityPos) + matrix->_41;


		ScreenPos = Vector2((settings::gui::screen_size.x / 2) * (1.f + x / w), (settings::gui::screen_size.y / 2) * (1.f - y / w));

		if (w < 0.1f) return false;

		if (ScreenPos.x < 0 || ScreenPos.x > settings::gui::screen_size.x ||
			ScreenPos.y < 0 || ScreenPos.y > settings::gui::screen_size.y)
			return false;
		return true;
	}
    static inline bool compute_player_box_from_bones(BasePlayer* p, Box2D& out, float pad = 4.f) {
        static constexpr BoneList Bones[] = {
            l_foot, l_knee, l_hip,
            r_foot, r_knee, r_hip,
            spine1, neck, head,
            l_upperarm, l_forearm, l_hand,
            r_upperarm, r_forearm, r_hand
        };

        float minX = FLT_MAX, minY = FLT_MAX;
        float maxX = -FLT_MAX, maxY = -FLT_MAX;
        int visible = 0;

        for (BoneList id : Bones) {
            Vector3 w = p->GetBoneByID(id);

            if (id == head)    w.y += 0.20f;
            if (id == l_foot || id == r_foot) w.y -= 0.10f;

            Vector2 s;
            if (!w2s(w, s)) continue;

            visible++;
            if (s.x < minX) minX = s.x;
            if (s.x > maxX) maxX = s.x;
            if (s.y < minY) minY = s.y;
            if (s.y > maxY) maxY = s.y;
        }

        if (visible < 3) {
            out.valid = false;
            return false;
        }

        minX -= pad; maxX += pad;
        minY -= pad; maxY += pad;

        const float width = maxX - minX;
        const float height = maxY - minY;
        if (width <= 1.f || height <= 1.f) {
            out.valid = false;
            return false;
        }
        out.left = minX; out.top = minY;
        out.right = maxX; out.bottom = maxY;
        out.valid = true;
        return true;
    }

}