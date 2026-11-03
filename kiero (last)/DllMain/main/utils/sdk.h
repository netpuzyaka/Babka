#include <array>
#include <map>
#include "classes.h"
#define MAX_STRING_LEN 64

#define maxx( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#define minm( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )

class StringIl
{
public:
	char pad_0000[0x10];
	int len;
	wchar_t buffer[0];

	static StringIl* New(const char* str)
	{
		return il2cpp::call<StringIl*, const char*>(("il2cpp_string_new"), str);
	}
	bool Contains(StringIl* value) {
		static auto off = METHOD("mscorlib::System::String::Contains(String): Boolean");
		return reinterpret_cast<bool(__fastcall*)(StringIl*, StringIl*)>(off)(this, value);
	}
};

class Str {
	char zpad[0x10];
public:
	int size;
	wchar_t str[MAX_STRING_LEN + 1];
	Str(const wchar_t* st) {
		size = min(wcslen((wchar_t*)st), MAX_STRING_LEN);
		for (int i = 0; i < size; i++) {
			str[i] = st[i];
		}
		str[size] = 0;
	}
};
uintptr_t GetType(const char* space, const char* name) {
	return il2cpp::type_object(space, name);
}
using ptr_t = uint64_t;
enum UnmanagedCallingConvention {
	UnmanagedCdecl,
	UnmanagedStdcall,
	UnmanagedFastcall,
};
template<typename T = void*>
struct List_ {
public:
	char pad_0000[0x10];
	void* buffer;
	uint32_t size;

	T* get(uint32_t idx) {
		if (!this) return nullptr;

		if (idx > this->size) return nullptr;

		void* items = this->buffer;

		if (!items) return nullptr;

		return *reinterpret_cast<T**>((uint64_t)items + (0x20 + (idx * 0x8)));
	}
};
template<typename t_Function>
class UnmanagedPointer {
public:

	template<typename... t_FunctionParameters>
	auto operator()(t_FunctionParameters... params) {
		using result_type = decltype(std::declval<t_Function>()(std::declval<t_FunctionParameters>()...));
		using function_cdecl_ptr_t = result_type(__cdecl*)(t_FunctionParameters...);
		using function_stdcall_ptr_t = result_type(__stdcall*)(t_FunctionParameters...);
		using function_fastcall_ptr_t = result_type(_fastcall*)(t_FunctionParameters...);

		switch (this->m_CallingConvention) {
		case UnmanagedCdecl:
			return reinterpret_cast<function_cdecl_ptr_t>(this->m_Address)(params...);
		case UnmanagedStdcall:
			return reinterpret_cast<function_stdcall_ptr_t>(this->m_Address)(params...);
		case UnmanagedFastcall:
			return reinterpret_cast<function_fastcall_ptr_t>(this->m_Address)(params...);
		}
	}

	UnmanagedPointer(ptr_t dwAddress, UnmanagedCallingConvention unmCallingConvention) {
		this->m_Address = dwAddress;
		this->m_CallingConvention = unmCallingConvention;
	}
private:
	ptr_t m_Address;
	UnmanagedCallingConvention m_CallingConvention;
};
class SafeExecution {
public:
	static int fail(unsigned int code, struct _EXCEPTION_POINTERS* ep) {
		if (code == EXCEPTION_ACCESS_VIOLATION) {
			return EXCEPTION_EXECUTE_HANDLER;
		}
		else {
			return EXCEPTION_CONTINUE_SEARCH;
		};
	}
public:
	template<typename T = void*, typename R = void*, typename... Args>
	static T Execute(uint64_t ptr, R ret, Args... args) {
		__try {
			return reinterpret_cast<T(__stdcall*)(Args...)>(ptr)(args...);
		}
		__except (fail(GetExceptionCode(), GetExceptionInformation())) {
			return ret;
		}
	}
};

class _SafeExecution {
public:
	static int _fail(unsigned int code, struct _EXCEPTION_POINTERS* ep) {
		if (code == EXCEPTION_ACCESS_VIOLATION) {
			return EXCEPTION_EXECUTE_HANDLER;
		}
		else {
			return EXCEPTION_CONTINUE_SEARCH;
		};
	}
public:
	template<typename T = void*, typename R = void*, typename... Args>
	static T Execute(uint64_t ptr, R ret, Args... args) {
		__try {
			return reinterpret_cast<T(__stdcall*)(Args...)>(ptr)(args...);
		}
		__except (_fail(GetExceptionCode(), GetExceptionInformation())) {
			return ret;
		}
	}
};

#define STATIC_FUNCTION(method_path,name,ta) static inline UnmanagedPointer<ta> name = { METHOD(method_path), UnmanagedStdcall }

class Type {
public:
	static Type* GetType(const char* qualified_name) {
		static auto off = METHOD("mscorlib::System::Type::GetType(String): Type");
		return reinterpret_cast<Type * (__cdecl*)(il2cpp::String*)>(off)(il2cpp::String::New(qualified_name));
	}
	static Type* SkinnedMeshRenderer() {
		Type* type = GetType(("UnityEngine.SkinnedMeshRenderer, UnityEngine.CoreModule"));
		return type;
	}
	static Type* ItemModProjectile() {
		Type* type = GetType(("ItemModProjectile, Assembly-CSharp"));
		return type;
	}
	static Type* Renderer() {
		Type* type = GetType(("UnityEngine.Renderer, UnityEngine.CoreModule"));
		return type;
	}
	static Type* Material() {
		Type* type = GetType(("UnityEngine.Material, UnityEngine.CoreModule"));
		return type;
	}
	static Type* Projectile() {
		Type* type = GetType(("Projectile, Assembly-CSharp"));
		return type;
	}
};

class Transform {
public:
	Vector3 position() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_position(): Vector3");
		return SafeExecution::Execute<Vector3>(off, Vector3::Zero(), this);
	}
	Quaternion get_rotation() {
		if (!this) return Quaternion();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_rotation(): Quaternion");
		return reinterpret_cast<Quaternion(__fastcall*)(Transform*)>(off)(this);
	}
	Vector3 InverseTransformPoint(Vector3 position) {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::InverseTransformPoint(Vector3): Vector3");
		return SafeExecution::Execute<Vector3>(off, Vector3::Zero(), this, position);
	}
	void set_rotation(Quaternion value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::set_rotation(Quaternion): Void");
		reinterpret_cast<void(__fastcall*)(Transform*, Quaternion)>(off)(this, value);
	}
	Vector3 InverseTransformDirection(Vector3 position) {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::InverseTransformDirection(Vector3): Vector3");
		return SafeExecution::Execute<Vector3>(off, Vector3::Zero(), this, position);
	}
	Vector3 up() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_up(): Vector3");
		return SafeExecution::Execute<Vector3>(off, Vector3::Zero(), this);
	}
	void set_position(Vector3 value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::set_position(Vector3): Void");
		reinterpret_cast<void(__fastcall*)(Transform*, Vector3)>(off)(this, value);
	}
	void set_scale(Vector3 value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::set_localScale(Vector3): Void");
		reinterpret_cast<void(__fastcall*)(Transform*, Vector3)>(off)(this, value);
	}
};
class BasePlayer;
namespace ConVar {
	class Graphics {
	public:
		static float& _fov() {
			static auto clazz = CLASS("Assembly-CSharp::ConVar::Graphics");
			return *reinterpret_cast<float*>(std::uint64_t(clazz->static_fields) + 0x18);
		}
	};
}
class _LocalPlayer {
public:
	static BasePlayer* _Entity() {
		static auto clazz = CLASS("Assembly-CSharp::LocalPlayer");
		return *reinterpret_cast<BasePlayer**>(std::uint64_t(clazz->static_fields));
	}
};

class Object {
public:
	Transform* transform() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_transform(): Transform");
		return SafeExecution::Execute<Transform*>(off, nullptr, this);
	}

	template<typename T = Component>
	Array<T*>* GetComponentsInChildren(Type* type) {
		if (!this || !type) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::GetComponentsInChildren(Type): Component[]");
		return reinterpret_cast<Array<T*>*(__fastcall*)(Object*, Type*)>(off)(this, type);
	}
};

class GameObject {
public:
	int layer() {
		if (!this) return 0;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::GameObject::get_layer(): Int32");
		return reinterpret_cast<int(__fastcall*)(GameObject*)>(off)(this);
	}
	template<typename T = GameObject>
	T* GetComponent(Type* type) {
		if (!this || !type) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::GameObject::GetComponent(Type): Component");
		return SafeExecution::Execute<T*>(off, nullptr, this, type);
	}
};
class Component : public Object {
public:
	template<typename T = Component>
	T* GetComponent(Type* type) {
		if (!this || !type) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::GetComponent(Type): Component");
		return reinterpret_cast<T * (__fastcall*)(Component*, Type*)>(off)(this, type);
	}
	GameObject* gameObject() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_gameObject(): GameObject");
		return reinterpret_cast<GameObject * (__fastcall*)(Component*)>(off)(this);
	}
	const char* _class_name() {
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
	uint32_t _class_name_hash() {
		if (!this) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		const char* name = *reinterpret_cast<char**>(oc + 0x10);
		return RUNTIME_CRC32(name);
	}
	const char* class_name_() {
		__try {
			if (!this) return "";
			auto oc = *reinterpret_cast<uint64_t*>(this);
			if (!oc) return "";
			if (!*reinterpret_cast<char**>(oc + 0x10)) return "";
			return *reinterpret_cast<char**>(oc + 0x10);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) { return ""; };
	}
	uint32_t class_name_hash_() {
		__try {
			if (!this) return 0;
			auto oc = *reinterpret_cast<uint64_t*>(this);
			if (!oc) return 0;
			if (!*reinterpret_cast<char**>(oc + 0x10)) return 0;
			const char* name = *reinterpret_cast<char**>(oc + 0x10);
			if (!name) return 0;
			return RUNTIME_CRC32(name);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) { return 0; };
	}
};
class Transform;
class GameManifest
{
public:
	static Object* GUIDToObject(il2cpp::String* guid) {
		static auto ptr = METHOD("Assembly-CSharp::GameManifest::GUIDToObject(String): Object");
		return reinterpret_cast<Object * (__fastcall*)(il2cpp::String*)>(ptr)(guid);
	}
};
template<typename T = Object>
class ResourceRef {
public:
	T* Get() {
		if (!this) return nullptr;
		il2cpp::String* guid = *reinterpret_cast<il2cpp::String**>(this + 0x10);
		T* _cachedObject = (T*)GameManifest::GUIDToObject(guid);

		return _cachedObject;
	}
};

class Model;
class ItemModProjectile {
public:
	static inline float(*GetRandomVelocity_)(ItemModProjectile*) = nullptr;

	float GetRandomVelocity() {
		return GetRandomVelocity_(this);
	}
	FIELD("Assembly-CSharp::ItemModProjectile::projectileVelocity", projectileVelocity, float);
	FIELD("Assembly-CSharp::ItemModProjectile::ammoType", ammoType, int);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileObject", projectileObject, ResourceRef<GameObject>*);
};
class BaseEntity;
class BaseNetworkable : public Component {
public:
	class EntityRealm {
	public:
		template<typename T = BaseNetworkable*> T Find(uint32_t uid) {
			static auto off = METHOD("Assembly-CSharp::EntityRealm::Find(NetworkableId): BaseNetworkable");
			return reinterpret_cast<T(__fastcall*)(EntityRealm*, uint32_t)>(off)(this, uid);
		}
		template<typename T = BaseNetworkable*>
		T FindClosest(uint32_t hash, BaseNetworkable* targetEnt, float dist) {
			T ent = nullptr;

			auto entityList = this->entityList();
			if (entityList) {
				for (int i = 1; i < entityList->vals->size; i++) {
					auto baseNetworkable = *reinterpret_cast<BaseNetworkable**>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
					if (!baseNetworkable) continue;

					if (baseNetworkable->_class_name_hash() == hash && baseNetworkable->transform()->position().distance(targetEnt->transform()->position()) <= dist) {
						ent = reinterpret_cast<T>(baseNetworkable);
						break;
					}
				}
			}

			return ent;
		}


		FIELD("Assembly-CSharp::EntityRealm::entityList", entityList, ListDictionary*);
	};
	const wchar_t* ShortPrefabName() {
		if (!this) return L"";
		static auto off = METHOD("Assembly-CSharp::BaseNetworkable::get_ShortPrefabName(): String");
		return reinterpret_cast<il2cpp::String * (__fastcall*)(BaseNetworkable*)>(off)(this)->buffer;
	}
	static EntityRealm* clientEntities() {
		static auto clazz = CLASS("Assembly-CSharp::BaseNetworkable");
		return *reinterpret_cast<EntityRealm**>(std::uint64_t(clazz->static_fields));
	}
};

class Shader : public Object {
public:

};

class Material_ {
public:
	void SetColor(rust::classes::string s, col c) {
		if (!this) return;
		auto off = reinterpret_cast<void(*)(Material_*, rust::classes::string, col)>(*reinterpret_cast<uintptr_t*>(il2cpp::_method(("Material"), ("SetColor"), 2, ("name"), ("UnityEngine"), 1)));
		return off(this, s, c);
	}
	void SetColorZV(rust::classes::string s, col c) {
		if (!this) return;
		auto off = reinterpret_cast<void(*)(Material_*, rust::classes::string, col)>(*reinterpret_cast<uintptr_t*>(il2cpp::_method(("Material"), ("SetColor"), 2, ("name"), ("UnityEngine"), 1)));
		return off(this, s, c);
	}
	void SetInt(char* name, int value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetInt(string name, int value): Void");
		return reinterpret_cast<void(__fastcall*)(Material_*, il2cpp::String*, int)>(off)(this, il2cpp::String::New(name), value);
	}
	void SetFloat(char* name, float value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetFloat(String,Single): Void");
		return reinterpret_cast<void(__fastcall*)(Material_*, il2cpp::String*, float)>(off)(this, il2cpp::String::New(name), value);
	}
	Shader* shader() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::get_shader");
		return reinterpret_cast<Shader * (__fastcall*)(Material_*)>(off)(this);
	}
	void SetShader(Shader* s) {
		if (!this) return;
		auto off = reinterpret_cast<void(*)(Material_*, Shader*)>(methods::resolve_icall(("UnityEngine.Material::set_shader(Shader value)")));
		return off(this, s);
	}
	StringIl* get_name()
	{
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Object::get_name(): String");
		return reinterpret_cast<StringIl * (__fastcall*)(Material_*)>(off)(this);
	}
};

class Skinnable {
public:
	FIELD("Assembly-CSharp::Skinnable::_sourceMaterials", _sourceMaterials, Array<Material_*>*);
};
class Random
{
public:
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Random::Range(Single,Single): Single", Range, float(float, float));
};

class BaseEntity : public BaseNetworkable {
public:
	enum class Signal {
		Attack,
		Alt_Attack,
		DryFire,
		Reload,
		Deploy,
		Flinch_Head,
		Flinch_Chest,
		Flinch_Stomach,
		Flinch_RearHead,
		Flinch_RearTorso,
		Throw,
		Relax,
		Gesture,
		PhysImpact,
		Eat,
		Startled
	};
	enum class Flags
	{
		Placeholder = 1,
		On = 2,
		OnFire = 4,
		Open = 8,
		Locked = 16,
		Debugging = 32,
		Disabled = 64,
		Reserved1 = 128,
		Reserved2 = 256,
		Reserved3 = 512,
		Reserved4 = 1024,
		Reserved5 = 2048,
		Broken = 4096,
		Busy = 8192,
		Reserved6 = 16384,
		Reserved7 = 32768,
		Reserved8 = 65536,
		Reserved9 = 131072,
		Reserved10 = 262144
	};

	Vector3 PivotPoint() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BaseEntity::PivotPoint(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BaseEntity*)>(off)(this);
	}
	float Distance(Vector3 pos) {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::Distance(Vector3): Single");
		return reinterpret_cast<float(__fastcall*)(BaseEntity*, Vector3)>(off)(this, pos);
	}
	Vector3 GetParentVelocity() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BaseEntity::GetParentVelocity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BaseEntity*)>(off)(this);
	}
	float BoundsPadding() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::BoundsPadding(): Single");
		return reinterpret_cast<float(__fastcall*)(BaseEntity*)>(off)(this);
	}
	Vector3 GetWorldVelocity() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BaseEntity::GetWorldVelocity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BaseEntity*)>(off)(this);
	}
	bool IsDestroyed() {
		if (!this) return true;
		static auto off = OFFSET("Assembly-CSharp::BaseNetworkable::<IsDestroyed>k__BackingField");
		return *reinterpret_cast<bool*>(this + off);
	}
	void SendSignalBroadcast(Signal a, const char* str = ("")) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::SendSignalBroadcast(Signal,String): Void");
		return reinterpret_cast<void(__fastcall*)(BaseEntity*, Signal, il2cpp::String*)>(off)(this, a, il2cpp::String::New(str));
	}
	bool IsValid() {
		if (!this) return false;
		return !this->IsDestroyed();
	}
	void _ServerRPC(const char* funcName) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::ServerRPC(String): Void");
		reinterpret_cast<void(__stdcall*)(BaseEntity*, il2cpp::String*)>(off)(this, il2cpp::String::New(funcName));
	}
	FIELD("Assembly-CSharp::BaseEntity::model", model, Model*);
};

class RaycastHit {
public:
	Vector3 point;
	Vector3 normal;
	int m_Collider;
	RaycastHit()
	{
		point = Vector3::Zero();
		normal = Vector3::Zero();
		m_Collider = 0;
	}
};

class Weather {
public:


	STATIC_FUNCTION("Assembly-CSharp::ConVar::Weather::set_rain(Single): Void", set_rain, float(float));
	STATIC_FUNCTION("Assembly-CSharp::ConVar::Weather::set_atmosphere_rayleigh(Single): Void", set_rayleigh, float(float));
	STATIC_FUNCTION("Assembly-CSharp::ConVar::Weather::set_atmosphere_brightness(Single): Void", set_brightness, float(float));
	STATIC_FUNCTION("Assembly-CSharp::ConVar::Weather::set_atmosphere_mie(Single): Void", set_mie, float(float));

};
class RenderSettings {
public:
	enum class AmbientMode {
		Skybox,
		Trilight,
		Flat,
		Custom
	};
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientEquatorColor(Color): Void", set_ambientEquatorColor, void(Color));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientSkyColor(Color): Void", set_ambientSkyColor, void(Color));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientMode(Rendering.AmbientMode): Void", set_ambientMode, void(AmbientMode));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientIntensity(Single): Void", set_ambientIntensity, void(float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientLight(Color): Void", set_ambientLight, void(Color));
};
class MapNote
{
public:
	FIELD("Rust.Data::ProtoBuf::MapNote::worldPosition", worldPosition, Vector3);
	FIELD("Rust.Data::ProtoBuf::MapNote::noteType", noteType, int);
};

float GLOBAL_TIME = 0.f;
class BasePlayer;

class CursorManager {
public:
	static inline void(*Update_)(CursorManager*) = nullptr;
	void Update() {
		return Update_(this);
	}
	static void set_visible(bool value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Cursor::set_visible(Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(bool)>(off)(value);
	}
	static void set_lockstate(int value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Cursor::set_lockState(CursorLockMode): Void");
		return reinterpret_cast<void(__fastcall*)(int)>(off)(value);
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
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return "";
		return *reinterpret_cast<char**>(oc + 0x10);
	}
	uint32_t ClassNameHash() {
		if (!this) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		const char* name = *reinterpret_cast<char**>(oc + 0x10);
		return RUNTIME_CRC32(name);
	}

	bool IsPlayer() {
		if (!this) return false;
		return !strcmp(this->ClassName(), ("BasePlayer")) ||
			!strcmp(this->ClassName(), ("NPCPlayerApex")) ||
			!strcmp(this->ClassName(), ("NPCMurderer")) ||
			!strcmp(this->ClassName(), ("NPCPlayer")) ||
			!strcmp(this->ClassName(), ("HumanNPC")) ||
			!strcmp(this->ClassName(), ("Scientist")) ||
			!strcmp(this->ClassName(), ("TunnelDweller")) ||
			!strcmp(this->ClassName(), ("HTNPlayer")) ||
			!strcmp(this->ClassName(), ("HumanNPCNew")) ||
			!strcmp(this->ClassName(), ("ScientistNPCNew")) ||
			!strcmp(this->ClassName(), ("BanditGuard")) ||
			!strcmp(this->ClassName(), ("ScientistNPC")) ||
			!strcmp(this->ClassName(), ("NPCMissionProvider")) ||
			!strcmp(this->ClassName(), ("NPCShopkeeper"));
	}

	FIELD("Assembly-CSharp::BaseCombatEntity::sendsHitNotification", sendsHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", sendsMeleeHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", lastNotifyFrame, int);
	FIELD("Assembly-CSharp::BaseCombatEntity::lifestate", lifestate, LifeState);

	bool is_alive() {
		if (!this) return false;
		return this->lifestate() == LifeState::Alive;
	}
};
class PlayerProjectileUpdate {
public:
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::projectileID", projectileID, int);
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::curPosition", curPosition, Vector3);
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::curVelocity", curVelocity, Vector3);
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::travelTime", travelTime, float);
};

class TerrainHeightMap {
public:
	FIELD("Assembly-CSharp::TerrainHeightMap::GetNormal", GetNormal, Vector3);

	Vector3 GetNormal(Vector3 worldPos)
	{
		if (!this || worldPos == Vector3::Zero()) return Vector3::Zero();

		static auto off = METHOD("Assembly-CSharp::TerrainHeightMap::GetNormal(Vector3): Vector3");

		return reinterpret_cast<Vector3(__fastcall*)(TerrainHeightMap*, Vector3)>(off)(this, worldPos);
	}
};

class TerrainMeta {
public:
	FIELD("Assembly-CSharp::TerrainMeta::get_HeightMap", HeightMap, TerrainHeightMap*);

	static TerrainMeta* New()
	{
		return il2cpp::il2cpp_object_new_<TerrainMeta*>(CLASS("Assembly-CSharp::TerrainMeta"));
	}
};	

class Time {
public:

	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_time(): Single", time, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_deltaTime(): Single", deltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_fixedTime(): Single", fixedTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_unscaledTime(): Single", unscaledTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_timeScale(): Single", timeScale, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_unscaledDeltaTime(): Single", unscaledDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_fixedDeltaTime(): Single", fixedDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_maximumDeltaTime(): Single", maximumDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_smoothDeltaTime(): Single", smoothDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_renderedFrameCount(): Int32", renderedFrameCount, int());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_realtimeSinceStartup(): Single", realtimeSinceStartup, float());
};

class Physics {
public:
	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::get_gravity(): Vector3", get_gravity, Vector3());
	static void IgnoreLayerCollision(int layer1, int layer2, bool ignore) {
		return reinterpret_cast<void(*)(int, int, bool)>(il2cpp::il2cpp_resolve_icall(("UnityEngine.Physics::IgnoreLayerCollision")))(layer1, layer2, ignore);
	}
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::CheckCapsule(Vector3,Vector3,Single,Int32,QueryTriggerInteraction): Boolean", CheckCapsule, bool(Vector3, Vector3, float, int, QueryTriggerInteraction));

	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::Raycast(Ray,Single,Int32): Boolean",
		Raycast,
		bool(Ray,
			float,
			int));

	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::Raycast(Ray,RaycastHit&,Single,Int32,QueryTriggerInteraction): Boolean", Raycast_, bool(Ray, RaycastHit, float, int, QueryTriggerInteraction));

	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::SphereCast(Ray,Single,RaycastHit&,Single,Int32,QueryTriggerInteraction): Boolean", SphereCast_, bool(Ray, float, RaycastHit, float, int, QueryTriggerInteraction));

	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::SphereCast(Ray,Single,Single,Int32): Boolean",
		SphereCast,
		bool(Ray,
			float,
			float,
			int));
};

class ItemDefinition : public Component {
public:
	FIELD("Assembly-CSharp::ItemDefinition::itemid", itemid, int);
	const wchar_t* shortname() {
		if (!this) return L"";
		static auto off = OFFSET("Assembly-CSharp::ItemDefinition::shortname");
		return (*reinterpret_cast<il2cpp::String**>(this + off))->buffer;
	}
};
class AttackEntity : public BaseEntity {
public:
	FIELD("Assembly-CSharp::AttackEntity::lastTickTime", lastTickTime, float);
	FIELD("Assembly-CSharp::AttackEntity::repeatDelay", repeatDelay, float);
	FIELD("Assembly-CSharp::AttackEntity::deployDelay", deployDelay, float);
	FIELD("Assembly-CSharp::AttackEntity::timeSinceDeploy", timeSinceDeploy, float);
	FIELD("Assembly-CSharp::AttackEntity::nextAttackTime", nextAttackTime, float);
	bool HasAttackCooldown()
	{
		if (!this) return false;

		static auto off = METHOD("Assembly-CSharp::AttackEntity::HasAttackCooldown(): Boolean");

		return reinterpret_cast<bool(__fastcall*)(AttackEntity*)>(off)(this);
	}

	float get_NextAttackTime() {
		if (!this) return false;
		static auto off = OFFSET("Assembly-CSharp::AttackEntity::get_NextAttackTime");
		return *reinterpret_cast<float*>(this + off);
	}
};
class HitTest;

class CompoundBowWeapon {
public:
	FIELD("Assembly-CSharp::CompoundBowWeapon::currentHoldProgress", currentHoldProgress, float);
	float GetProjectileVelocityScale(bool getmax = false) {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::CompoundBowWeapon::GetProjectileVelocityScale(Boolean): Single");
		return reinterpret_cast<float(__fastcall*)(CompoundBowWeapon*, bool)>(off)(this, getmax);
	}
};
class Misc {
public:
	static float Magnitude(Vector3 a)
	{
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Vector3::Magnitude(Vector3): Single");
		return reinterpret_cast<float(*)(Vector3)>(off)(a);
	}
	static float Magnitude2D(Vector3 v)
	{
		static auto off = METHOD("Rust.Global::UnityEngine::Vector3Ex::Magnitude2D(Vector3): Single");
		return reinterpret_cast<float(*)(Vector3)>(off)(v);
	}
};

class BaseProjectile : public AttackEntity {
public:
	class Magazine {
	public:
		FIELD("Assembly-CSharp::Magazine::ammoType", ammoType, ItemDefinition*);
		FIELD("Assembly-CSharp::Magazine::contents", contents, int);
	};

	FIELD("Assembly-CSharp::AttackEntity::repeatDelay", repeatDelay, float);
	FIELD("Assembly-CSharp::BaseProjectile::primaryMagazine", primaryMagazine, Magazine*);
	FIELD("Assembly-CSharp::BaseProjectile::projectileVelocityScale", projectileVelocityScale, float);
	FIELD("Assembly-CSharp::BaseProjectile::reloadTime", reloadTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::nextReloadTime", nextReloadTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::lastShotTime", lastShotTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::automatic", automatic, bool);
	FIELD("Assembly-CSharp::BaseProjectile::aimSway", aimSway, float);
	FIELD("Assembly-CSharp::BaseProjectile::aimSwaySpeed", aimSwaySpeed, float);
	FIELD("Assembly-CSharp::BaseProjectile::reloadPressTime", reloadPressTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::isReloading", isReloading, bool);

	FIELD("Assembly-CSharp::BowWeapon::arrowBack", arrowBack, float);
	FIELD("Assembly-CSharp::BowWeapon::attackReady", attackReady, bool);

	void DoAttack()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::DoAttack(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}

	void LaunchProjectile()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::LaunchProjectile(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void DoThrow()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseMelee::DoThrow(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void ShotFired()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::ShotFired(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void UpdateAmmoDisplay()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::UpdateAmmoDisplay(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void DidAttackClientside()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::DidAttackClientside(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void BeginCycle()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::BeginCycle(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	bool Empty() {
		if (!this) return true;
		if (!this->primaryMagazine()) return true;

		return this->primaryMagazine()->contents() <= 0;
	}
	const char* class_name() {
		__try {
			if (!this) return "";
			auto oc = *reinterpret_cast<uint64_t*>(this);
			if (!oc) return "";
			if (!*reinterpret_cast<char**>(oc + 0x10)) return "";
			return *reinterpret_cast<char**>(oc + 0x10);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) { return ""; };
	}
	uint32_t class_name_hash() {
		__try {
			if (!this) return 0;
			auto oc = *reinterpret_cast<uint64_t*>(this);
			if (!oc) return 0;
			if (!*reinterpret_cast<char**>(oc + 0x10)) return 0;
			const char* name = *reinterpret_cast<char**>(oc + 0x10);
			if (!name) return 0;
			return RUNTIME_CRC32(name);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) { return 0; };
	}
	bool HasReloadCooldown() {
		return GLOBAL_TIME < this->nextReloadTime();
	}
	float CalculateCooldownTime(float nextTime, float cooldown) {
		float num = GLOBAL_TIME;
		float num2 = 0.f;

		float ret = nextTime;

		if (ret < 0.f) {
			ret = max(0.f, num + cooldown - num2);
		}
		else if (num - ret <= num2) {
			ret = min(ret + cooldown, num + cooldown);
		}
		else {
			ret = max(ret + cooldown, num + cooldown - num2);
		}
		return ret;
	}
	void SendSignalBroadcast(Signal a, const char* str = ("")) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::SendSignalBroadcast(Signal,String): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*, Signal, il2cpp::String*)>(off)(this, a, il2cpp::String::New(str));
	}
};

class DamageTypeList {
public:
	enum class DamageType {
		Generic,
		Hunger,
		Thirst,
		Cold,
		Drowned,
		Heat,
		Bleeding,
		Poison,
		Suicide,
		Bullet,
		Slash,
		Blunt,
		Fall,
		Radiation,
		Bite,
		Stab,
		Explosion,
		RadiationExposure,
		ColdExposure,
		Decay,
		ElectricShock,
		Arrow,
		AntiVehicle,
		Collision,
		Fun_Water,
		LAST
	};
	float Total() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::Rust::DamageTypeList::Total(): Single");
		return reinterpret_cast<float(__fastcall*)(DamageTypeList*)>(off)(this);
	}
};
class HitInfo {
public:
	FIELD("Assembly-CSharp::HitInfo::HitEntity", _HitEntity, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::Initiator", Initiator, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::WeaponPrefab", WeaponPrefab, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::DoHitEffects", DoHitEffects, bool);
	FIELD("Assembly-CSharp::HitInfo::DoDecals", DoDecals, bool);
	FIELD("Assembly-CSharp::HitInfo::IsPredicting", IsPredicting, bool);
	FIELD("Assembly-CSharp::HitInfo::UseProtection", UseProtection, bool);
	FIELD("Assembly-CSharp::HitInfo::DidHit", DidHit, bool);
	FIELD("Assembly-CSharp::HitInfo::HitEntity", HitEntity, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::HitBone", HitBone, uint32_t);
	FIELD("Assembly-CSharp::HitInfo::HitPart", HitPart, uint32_t);
	FIELD("Assembly-CSharp::HitInfo::HitMaterial", HitMaterial, uint32_t);
	FIELD("Assembly-CSharp::HitInfo::HitPositionWorld", HitPositionWorld, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitPositionLocal", HitPositionLocal, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitNormalWorld", HitNormalWorld, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitNormalLocal", HitNormalLocal, Vector3);
	FIELD("Assembly-CSharp::HitInfo::PointStart", PointStart, Vector3);
	FIELD("Assembly-CSharp::HitInfo::PointEnd", PointEnd, Vector3);
	FIELD("Assembly-CSharp::HitInfo::ProjectileID", ProjectileID, int);
	FIELD("Assembly-CSharp::Projectile::ProjectileID", _ProjectileID, int);
	FIELD("Assembly-CSharp::HitInfo::ProjectileHits", ProjectileHits, int);
	FIELD("Assembly-CSharp::HitInfo::ProjectileDistance", ProjectileDistance, float);
	FIELD("Assembly-CSharp::HitInfo::ProjectileIntegrity", ProjectileIntegrity, float);
	FIELD("Assembly-CSharp::HitInfo::ProjectileTravelTime", ProjectileTravelTime, float);
	FIELD("Assembly-CSharp::HitInfo::gatherScale", gatherScale, float);
	FIELD("Assembly-CSharp::HitInfo::ProjectileTrajectoryMismatch", ProjectileTrajectoryMismatch, float);
	FIELD("Assembly-CSharp::HitInfo::ProjectileVelocity", ProjectileVelocity, Vector3);
	FIELD("Assembly-CSharp::HitInfo::damageTypes", damageTypes, DamageTypeList*);
};
struct ProjectileWeaponModModifier {
};
class TOD_Sky {
public:
};
class BossFormController {
public:
};
class Collider {
public:
};
class Effect {
public:
};
class RigidBody {
public:
	Vector3 velocity() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.PhysicsModule::UnityEngine::Rigidbody::get_velocity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(RigidBody*)>(off)(this);
	}
	void set_velocity(Vector3 value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.PhysicsModule::UnityEngine::Rigidbody::set_velocity(Vector3): Void");
		return reinterpret_cast<void(__fastcall*)(RigidBody*, Vector3)>(off)(this, value);
	}
};
class ModelState;
class CapsuleCollider {
public:
	void set_radius(float value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.PhysicsModule::UnityEngine::CapsuleCollider::set_radius(Single): Void");
		return reinterpret_cast<void(__fastcall*)(CapsuleCollider*, float)>(off)(this, value);
	}
};
class PlayerWalkMovement {
public:
	FIELD("Assembly-CSharp::PlayerWalkMovement::capsule", capsule, CapsuleCollider*);
	FIELD("Assembly-CSharp::BaseMovement::<Ducking>k__BackingField", Ducking, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::body", body, RigidBody*);
	FIELD("Assembly-CSharp::PlayerWalkMovement::flying", flying, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::maxAngleWalking", maxAngleWalking, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::maxVelocity", maxVelocity, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundAngle", groundAngle, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundAngleNew", groundAngleNew, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundNormal", groundNormal, Vector3);
	FIELD("Assembly-CSharp::PlayerWalkMovement::jumpTime", jumpTime, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::landTime", landTime, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundTime", groundTime, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::gravityMultiplier", gravityMultiplier, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::climbing", climbing, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::sliding", sliding, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::grounded", grounded, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::jumping", jumping, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::swimming", swimming, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::ladder", ladder, void*);
	FIELD("Assembly-CSharp::BaseMovement::<TargetMovement>k__BackingField", TargetMovement, Vector3);

	void TeleportTo(Vector3 pos) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::PlayerWalkMovement::TeleportTo(Vector3,BasePlayer): Void");
		return reinterpret_cast<void(__fastcall*)(PlayerWalkMovement*, Vector3, BasePlayer*)>(off)(this, pos, _LocalPlayer::_Entity());
	}

	void BaseTeleportTo(Vector3 pos) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseMovement::TeleportTo(Vector3,BasePlayer): Void");
		return reinterpret_cast<void(__fastcall*)(PlayerWalkMovement*, Vector3, BasePlayer*)>(off)(this, pos, _LocalPlayer::_Entity());
	}

	void Jump(ModelState* state)
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::PlayerWalkMovement::Jump(ModelState,Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(PlayerWalkMovement*, ModelState*, bool)>(off)(this, state, false);
	}
};
class _Render;
class SkinnedMeshRenderer;
class Wearable : public Component {
public:
};
class ItemModWearable {
public:
	Wearable* targetWearable() {
		if (!this) return nullptr;
		static auto off = METHOD("Assembly-CSharp::ItemModWearable::get_targetWearable(): Wearable");
		return reinterpret_cast<Wearable * (__fastcall*)(ItemModWearable*)>(off)(this);
	}
};
class InputMessage {
public:
	FIELD("Rust.Data::InputMessage::buttons", buttons, int);
	FIELD("Rust.Data::InputMessage::mouseDelta", mouseDelta, Vector3);
	FIELD("Rust.Data::InputMessage::aimAngles", aimAngles, Vector3);
	FIELD("Rust.Data::InputMessage::_disposed", _disposed, bool);
};
enum Button_o {
	FORWARD = 2,
	BACKWARD = 4,
	LEFT = 8,
	RIGHT = 16,
	JUMP = 32,
	DUCK = 64,
	SPRINT = 128,
	USE = 256,
	FIRE_PRIMARY = 1024,
	FIRE_SECONDARY = 2048,
	RELOAD = 8192,
	FIRE_THIRD = 134217728,
};
class InputState {
public:
	FIELD("Assembly-CSharp::InputState::current", current, InputMessage*);
	FIELD("Assembly-CSharp::InputState::previous", previous, InputMessage*);
	/*bool IsDown(Button b) {
		if (!this) return false;
		return reinterpret_cast<bool(__fastcall*)(InputState*, Button)>(vars::stor::gBase + CO::IsDown)(this, b);
	}*/

};
class TeamMember {
public:
	bool online() {
		return *reinterpret_cast<bool*>(this + 0x30);
	}
	uint64_t& userID() {
		return *reinterpret_cast<uint64_t*>(this + 0x18);
	}
	Vector3& position() {
		return *reinterpret_cast<Vector3*>(this + 0x24);
	}
	const wchar_t* displayName() {
		if (!this) return L"---";
		return (*reinterpret_cast<il2cpp::String**>(this + 0x10))->buffer;
	}
};
class PlayerTeam {
public:
	List<TeamMember*>* members() {
		return *reinterpret_cast<List<TeamMember*>**>(this + 0x28);
	}
};
class ModelState {
public:
	void set_jumped(bool value) {
		if (!this) return;
		static auto off = METHOD("Rust.Data::ModelState::set_jumped(Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(ModelState*, bool)>(off)(this, value);
	}
	void set_ducked(bool value) {
		if (!this) return;
		static auto off = METHOD("Rust.Data::ModelState::set_ducked(Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(ModelState*, bool)>(off)(this, value);
	}
	void set_mounted(bool value) {
		if (!this) return;
		static auto off = METHOD("Rust.Data::ModelState::set_mounted(Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(ModelState*, bool)>(off)(this, value);
	}
	bool mounted() {
		if (!this) return false;
		static auto ptr = METHOD("Rust.Data::ModelState::get_mounted(): Boolean");
		return reinterpret_cast<bool(*)(ModelState*)>(ptr)(this);
	}

	FIELD("Rust.Data::ModelState::flags", flags, int);
};

class HeldEntity {
public:
};
class BaseMountable {
public:
	FIELD("Assembly-CSharp::BaseMountable::canWieldItems", canWieldItems, bool);
	BaseMountable* GetVehicleParent() {
		if (!this) return {};
		static auto off = METHOD("Assembly-CSharp::BaseVehicleMountPoint::GetVehicleParent(): BaseVehicle");
		return reinterpret_cast<BaseMountable * (*)(BaseMountable*)>(off)(this);
	}

	const char* _class_name() {
		if (!this) return "";
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return "";
		return *reinterpret_cast<char**>(oc + 0x10);
	}
	uint32_t _class_name_hash() {
		if (!this) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		const char* name = *reinterpret_cast<char**>(oc + 0x10);
		return RUNTIME_CRC32(name);
	}
};
class PlayerProjectileAttack {
public:
};
class TraceInfo {
public:
};

class ViewModel {
public:
};
class ViewmodelSway
{
public:
	FIELD("Assembly-CSharp::ViewmodelSway::positionalSwaySpeed", positionalSwaySpeed, float);
	FIELD("Assembly-CSharp::ViewmodelSway::positionalSwayAmount", positionalSwayAmount, float);
	FIELD("Assembly-CSharp::ViewmodelSway::rotationSwaySpeed", rotationSwaySpeed, float);
	FIELD("Assembly-CSharp::ViewmodelSway::rotationSwayAmount", rotationSwayAmount, float);
};

class ViewmodelLower
{
public:
	FIELD("Assembly-CSharp::ViewmodelLower::shouldLower", shouldLower, bool);
};

class ViewmodelBob
{
public:
	FIELD("Assembly-CSharp::ViewmodelBob::bobSpeedWalk", bobSpeedWalk, float);
	FIELD("Assembly-CSharp::ViewmodelBob::bobSpeedRun", bobSpeedRun, float);
	FIELD("Assembly-CSharp::ViewmodelBob::bobAmountWalk", bobAmountWalk, float);
	FIELD("Assembly-CSharp::ViewmodelBob::bobAmountRun", bobAmountRun, float);
};
class Animator
{
public:
	auto set_speed(float value) -> void {
		static auto off = METHOD("UnityEngine.AnimationModule::UnityEngine::Animator::set_speed(Single): Void");
		return reinterpret_cast<void(__fastcall*)(Animator*, float)>(off)(this, value);
	}
};
class BaseViewModel : public Object {
public:
	FIELD("Assembly-CSharp::BaseViewModel::sway", sway, ViewmodelSway*);
	FIELD("Assembly-CSharp::BaseViewModel::lower", lower, ViewmodelLower*);
	FIELD("Assembly-CSharp::BaseViewModel::bob", bob, ViewmodelBob*);
	FIELD("Assembly-CSharp::BaseViewModel::useViewModelCamera", useViewModelCamera, bool);
	FIELD("Assembly-CSharp::BaseViewModel::animator", animator, Animator*);
	static auto ActiveModel() -> BaseViewModel* {
		static auto off = METHOD("Assembly-CSharp::BaseViewModel::get_ActiveModel(): BaseViewModel");
		return reinterpret_cast<BaseViewModel * (__fastcall*)()>(off)();
	}
	static auto AddHandsModel() -> BaseViewModel* {
		static auto off = METHOD("Assembly-CSharp::BaseViewModel::AddHandsModel(): BaseViewModel");
		return reinterpret_cast<BaseViewModel * (__fastcall*)()>(off)();
	}
	static auto Play() -> BaseViewModel* {
		static auto off = METHOD("Assembly-CSharp::BaseViewModel::Play(string anim, int layer = 0): BaseViewModel");
		return reinterpret_cast<BaseViewModel * (__fastcall*)()>(off)();
	}
};

class ItemIcon {
public:
	FIELD("Assembly-CSharp::ItemIcon::queuedForLooting", queuedForLooting, bool);

	static inline void (*StartCoroutine_)(ItemIcon*) = nullptr;
	void TryToMove() {
		return StartCoroutine_(this);
	}

	void RunTimedAction() {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::ItemIcon::RunTimedAction(): Void");
		return reinterpret_cast<void(__fastcall*)(ItemIcon*)>(off)(this);
	}
};

class Renderer_ {
public:
	Material_* material() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_material(): Material");
		return reinterpret_cast<Material_ * (__fastcall*)(Renderer_*)>(off)(this);
	}
	void set_material(Material_* value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::set_material(Material): Void");
		return reinterpret_cast<void(__fastcall*)(Renderer_*, Material_*)>(off)(this, value);
	}
	bool isVisible() {
		if (!this) return false;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_isVisible(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Renderer_*)>(off)(this);
	}
	Array<Material_*>* materials() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_materials(): Material[]");
		return reinterpret_cast<Array<Material_*>*(__fastcall*)(Renderer_*)>(off)(this);
	}
};
class PlayerNameID {
public:
	wchar_t* username() {
		auto username = (pUncStr)(*reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10));
		return username->str;
	}

	unsigned long user_id() {
		return *reinterpret_cast<unsigned long*>((uintptr_t)this + 0x18);
	}
};
class _Renderer : public Component {
public:
	Material_* GetMaterial() {
		if (!this) return nullptr;
		auto off = reinterpret_cast<Material_ * (*)(_Renderer*)>(*reinterpret_cast<uintptr_t*>(il2cpp::_method(("Renderer"), ("get_material"), 0, (""), ("UnityEngine"))));
		return off(this);
	}
	void set_material(Material_* value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::set_material(Material): Void");
		return reinterpret_cast<void(__fastcall*)(_Renderer*, Material_*)>(off)(this, value);
	}
};
class Material : public Object {
public:
	Shader* GetShader() {
		if (!this) return nullptr;
		auto off = reinterpret_cast<Shader * (*)(Material*)>(*reinterpret_cast<uintptr_t*>(il2cpp::_method(("Material"), ("get_shader"), 0, (""), ("UnityEngine"))));
		return off(this);
	}
	void SetColor_(char* proper, Color value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetColor(String,Color): Void");
		return reinterpret_cast<void(__fastcall*)(Material*, il2cpp::String*, Color)>(off)(this, il2cpp::String::New(proper), value);
	}
	void SetInt(char* name, int value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetInt(String,Int32): Void");
		return reinterpret_cast<void(__fastcall*)(Material*, il2cpp::String*, int)>(off)(this, il2cpp::String::New(name), value);
	}
	void SetFloat(char* name, float value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetFloat(String,Single): Void");
		return reinterpret_cast<void(__fastcall*)(Material*, il2cpp::String*, float)>(off)(this, il2cpp::String::New(name), value);
	}
	Shader* shader() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::get_shader(): Shader");
		return reinterpret_cast<Shader * (__fastcall*)(Material*)>(off)(this);
	}
	void SetShader(Shader* s) {
		if (!this) return;
		auto off = reinterpret_cast<void(*)(Material*, Shader*)>(methods::resolve_icall(("UnityEngine.Material::set_shader()")));
		return off(this, s);
	}
	void set_shader(Shader* val, static uint64_t off) {
		static int exceptionCounter = 0;
		__try {
			if (exceptionCounter <= 10) {
				exceptionCounter++;
				return;
			}
			if (!this || !val || !off) return;

			return reinterpret_cast<void(__fastcall*)(Material*, Shader*)>(off)(this, val);
		}
		__except (SafeExecution::fail(GetExceptionCode(), GetExceptionInformation())) {
			exceptionCounter = 0;
		};
	}
	//void SetColor(rust::classes::string s, col c) {
	//	if (!this) return;
	//	auto off = reinterpret_cast<void(*)(Material*, rust::classes::string, col)>(*reinterpret_cast<uintptr_t*>(il2cpp::_method(("Material"), ("SetColor"), 2, ("name"), ("UnityEngine"), 1)));
	//	return off(this, s, c);
	//}
};

class PlayerModel;
class SkinnedMultiMesh {
public:
	__System::list<_Renderer*>* get_Renderers() {
		if (!this) return nullptr;
		auto off = reinterpret_cast<__System::list<_Renderer*>*(*)(SkinnedMultiMesh*)>(*reinterpret_cast<uintptr_t*>(il2cpp::_method(("SkinnedMultiMesh"), ("get_Renderers"), 0, (""), (""))));
		return off(this);
	}
	List<Renderer_*>* Renderers() {
		if (!this) return nullptr;
		static auto off = OFFSET("Assembly-CSharp::SkinnedMultiMesh::<Renderers>k__BackingField");
		return *reinterpret_cast<List<Renderer_*>**>(this + off);
	}
	static inline void(*RebuildModel_)(SkinnedMultiMesh*, PlayerModel*, bool) = nullptr;
	void RebuildModel(PlayerModel* model, bool reset) {
		return RebuildModel_(this, model, reset);
	}
};
class PlayerModel {
public:
	Vector3 newVelocity() {
		if (!this) return Vector3::Zero();
		static auto off = OFFSET("Assembly-CSharp::PlayerModel::newVelocity");
		return *reinterpret_cast<Vector3*>(this + off);
	}
	bool isNpc() {
		if (!this) return false;
		static auto off = OFFSET("Assembly-CSharp::PlayerModel::<IsNpc>k__BackingField");
		return *reinterpret_cast<bool*>(this + off);
	}

	FIELD("Assembly-CSharp::BaseCombatEntity::_maxHealth", maxHealth, float);
	Vector3 position() {
		if (!this) return Vector3::Zero();
		static auto off = Offsets::playermodel_position;
		return *reinterpret_cast<Vector3*>(this + off);
	}
	FIELD("Assembly-CSharp::PlayerModel::isLocalPlayer", isLocalPlayer, bool);
	FIELD("Assembly-CSharp::PlayerModel::_multiMesh", _multiMesh, SkinnedMultiMesh*);
};
class Camera {
public:
	static uintptr_t MainCamera() {
		return reinterpret_cast<uintptr_t(*)()>(il2cpp::il2cpp_resolve_icall(("UnityEngine.Camera::get_main()")))();
	}
	static void SetAspect(float act) {
		return reinterpret_cast<void(*)(uintptr_t, float)>(il2cpp::il2cpp_resolve_icall(("UnityEngine.Camera::set_aspect()")))(MainCamera(), act);
	}
};
class PlayerEyes : public Component {
public:
	FIELD("Assembly-CSharp::PlayerEyes::viewOffset", viewOffset, Vector3);
	Quaternion rotation() {
		if (!this) return Quaternion{};
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_rotation(): Quaternion");
		return reinterpret_cast<Quaternion(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 get_position() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_position(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 center() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_center(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 MovementForward() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::MovementForward(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 MovementRight() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::MovementRight(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 HeadForward() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::HeadForward(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 BodyForward() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::BodyForward(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	static Vector3 EyeOffset() {
		static auto clazz = CLASS("Assembly-CSharp::PlayerEyes");
		return *reinterpret_cast<Vector3*>(std::uint64_t(clazz->static_fields));
	}
	Vector3 GetCenter() {
		if (!this) return Vector3(0, 0, 0);
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_center(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 position() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_position(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	static inline Vector3(*BodyLeanOffset_)(PlayerEyes*) = nullptr;
	Vector3 BodyLeanOffset() {
		return BodyLeanOffset_(this);
	}
	static inline void(*DoFirstPersonCamera_)(PlayerEyes*, Component*) = nullptr;
	void DoFirstPersonCamera(Component* cam) {
		return DoFirstPersonCamera_(this, cam);
	}
};

class PlayerTick {
public:
	Vector3 tick_position() {
		Vector3 th = read(this + Offsets::playermodel_position, Vector3);
		if (!th.empty()) {
			return th;
		}
		else { return Vector3::Zero(); }
	}
	FIELD("Rust.Data::PlayerTick::position", __position, Vector3);

};
class ConsoleOptions {
public:
	bool IsFromServer() { return read(this + 0x6, bool); }
};

struct Ammo {
	int id[2];
	float speed;
};
struct Weapon_M {
	int id;
	const char* name;
	Ammo ammo[4];
	int category; //-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
};
Weapon_M infom_t[]{
Weapon_M{1090916276, ("Pitchfork"), {Ammo{{0}, 25}}, 1 },
Weapon_M{1540934679, ("Wooden Spear"), {Ammo{{0}, 25}}, 1 },
Weapon_M{1814288539, ("Bone Knife"), {Ammo{{0}, 20}}, 1 },
Weapon_M{-363689972, ("Snowball"), {Ammo{{0}, 20}}, 1 },
Weapon_M{1789825282, ("Candy Cane Club"), {Ammo{{0}, 20}}, 1 },
Weapon_M{-1137865085, ("Machete"), {Ammo{{0}, 20}}, 1 },
Weapon_M{1711033574, ("Bone Club"), {Ammo{{0}, 20}}, 1 },
Weapon_M{-1966748496, ("Mace"), {Ammo{{0}, 18}}, 1 },
Weapon_M{-194509282, ("Butcher Knife"), {Ammo{{0}, 20}}, 1 },
Weapon_M{1326180354, ("Salvaged Sword"), {Ammo{{0}, 20}}, 1 },
Weapon_M{-1469578201, ("Longsword"), {Ammo{{0}, 18}}, 1 },
Weapon_M{-1978999529, ("Salvaged Cleaver"), {Ammo{{0}, 18}}, 1 },
Weapon_M{1602646136, ("Stone Spear"), {Ammo{{0}, 30}}, 1 },
Weapon_M{2040726127, ("Combat Knife"), {Ammo{{0}, 30}}, 1 },
Weapon_M{963906841, ("Rock"), {Ammo{{0}, 18}}, 1 },
};

class Item {
public:
	FIELD("Assembly-CSharp::Item::info", info_, ItemDefinition*);
	template<typename T = void*>
	T* heldEntity() {
		if (!this) return nullptr;
		static auto off = OFFSET("Assembly-CSharp::Item::heldEntity");
		return *reinterpret_cast<T**>(this + off);
	}
	uintptr_t entity() {
		return read(this + Offsets::item_heldEntity, uintptr_t); // private EntityRef heldEntity;
	}
	Weapon_M infom_() {
		int ID = info_()->itemid();
		for (Weapon_M k : infom_t) {
			if (k.id == ID) {
				return k;
			}
		}
		return Weapon_M{ 0 };
	}
	FIELD("Assembly-CSharp::Item::info", info1337, ItemDefinition*);
	FIELD("Assembly-CSharp::ItemDefinition::itemid", GetID_, int);

	int GetID() {
		DWORD64 Info = read((DWORD64)this + Offsets::item_info, DWORD64); // public ItemDefinition info;
		int ID = read(Info + Offsets::itemdefinition_itemid, int); // public int itemid; //ItemDefinition
		return ID;
	}
	char* ClassName() {
		return (char*)read(read(this->entity(), DWORD64) + 0x10, DWORD64); //0x10 //private string _className;
	}

	int32_t get_item_definition_id()
	{
		const auto     item_definition = *reinterpret_cast<uintptr_t*>((uintptr_t)this + Offsets::item_info);
		if (!item_definition)
			return 0;

		return *reinterpret_cast<int32_t*>(item_definition + Offsets::itemdefinition_itemid);
	}

	BaseProjectile* get_base_projetile() {
		return *reinterpret_cast<BaseProjectile**>((uintptr_t)this + Offsets::item_heldEntity);
	}
	int LoadedAmmo()
	{
		const auto Held = read(this + Offsets::item_heldEntity, DWORD64);
		if (Held <= 0)
			return 0;
		const auto Magazine = read(Held + Offsets::baseprojectile_primaryMagazine, DWORD64);
		if (Magazine <= 0, Magazine == 0x3F000000)
		{
			return 0;
		}
		const auto ammoType = read(Magazine + 0x20, DWORD64);
		if (ammoType <= 0, ammoType == 0x3F000000)
		{
			return 0;
		}
		const int ammo = read(ammoType + Offsets::itemdefinition_itemid, int);
		return ammo;
	}
	wchar_t* get_name() {
		uintptr_t Info = read(this + Offsets::item_info, uintptr_t);
		uintptr_t DispName = read(Info + Offsets::ItemDefinition_displayName, uintptr_t);
		pUncStr Str = ((pUncStr)read(DispName + 0x18, uintptr_t)); // default
		if (!Str) return nullptr; return Str->str;
	}

	int count() {
		return read(this + 0x30, int);
	}
	int uid() {
		return read(this + Offsets::Item_uid, int);
	}
	void NoSway() {
		DWORD64 Heldd = this->entity();
		if (settings::weapons::no_sway) {
			write(Heldd + Offsets::baseprojectile_aimSway, 0.f, float);
			write(Heldd + Offsets::baseprojectile_aimSwaySpeed, 0.f, float);
		}
	}
	void SetAutomatic() {
		if (settings::weapons::automatic) {
			DWORD64 Heldd = this->entity();
			write(Heldd + Offsets::baseprojectile_automatic, 1, bool);
		}
	}
	void EokaTap() {
		if (settings::weapons::eokatap) {
			DWORD64 Heldd = this->entity();
			write(Heldd + Offsets::successFraction, 1.f, float); // successFraction
			write(Heldd + Offsets::_didSparkThisFrame, true, bool); // didSparkThisFrame
		}
	}
};
class ItemContainer {
public:
	FIELD("Assembly-CSharp::ItemContainer::itemList", itemList, List_<Item*>*);
};
class PlayerInventory {
public:
	FIELD("Assembly-CSharp::PlayerInventory::containerBelt", containerBelt, ItemContainer*);
	FIELD("Assembly-CSharp::PlayerInventory::containerWear", containerWear, ItemContainer*);
	FIELD("Assembly-CSharp::PlayerInventory::containerMain", containerMain, ItemContainer*);
};
class PlayerInput {
public:
	FIELD("Assembly-CSharp::PlayerInput::state", state, InputState*);
	FIELD("Assembly-CSharp::PlayerInput::recoilAngles", recoilAngles, Vector3);
	FIELD("Assembly-CSharp::PlayerInput::bodyAngles", bodyAngles, Vector3);
	FIELD("Assembly-CSharp::PlayerInput::headAngles", headAngles, Vector3);
};

Shader* wireframe;
Shader* settrought;
Shader* list_shader;
Shader* huy;
Shader* chamsShader;
Material* GalaxyMaterial;
class BasePlayer : public BaseCombatEntity {
public:
	static inline void(*OnLand_)(BasePlayer*, float) = nullptr;
	void OnLand(float fVelocity) {
		return OnLand_(this, fVelocity);
	}
	static inline void(*SendClientTick_)(BasePlayer*) = nullptr;
	void SendClientTick() {
		return SendClientTick_(this);
	}
	FIELD("Assembly-CSharp::BasePlayer::playerFlags", playerFlags, int);
	const wchar_t* _displayName() {
		if (!this) return L"";
		static auto off = OFFSET("Assembly-CSharp::BasePlayer::_displayName");
		return (*reinterpret_cast<il2cpp::String**>(this + off))->buffer;
	}
	const wchar_t* get_player_name() {
		if (!this) return L"";
		return (*reinterpret_cast<il2cpp::String**>(this ? this + Offsets::__displayName : 0x0))->buffer;
	}

	FIELD("Assembly-CSharp::BasePlayer::playerModel", _playerModel, PlayerModel*);
	FIELD("Assembly-CSharp::BasePlayer::userID", userID, uint64_t);
	FIELD("Assembly-CSharp::BasePlayer::eyes", eyes, PlayerEyes*);
	FIELD("Assembly-CSharp::BasePlayer::mounted", mounted, BaseMountable*);
	FIELD("Assembly-CSharp::BasePlayer::input", input, PlayerInput*);
	FIELD("Assembly-CSharp::BasePlayer::clientTickInterval", clientTickInterval, float);
	FIELD("Assembly-CSharp::BasePlayer::movement", movement, PlayerWalkMovement*);
	FIELD("Assembly-CSharp::BasePlayer::inventory", inventory, PlayerInventory*);
	FIELD("Assembly-CSharp::BasePlayer::clActiveItem", clActiveItem, uint32_t);
	FIELD("Assembly-CSharp::BasePlayer::lastSentTick", lastSentTick, PlayerTick*);
	FIELD("Assembly-CSharp::BasePlayer::modelState", modelState, ModelState*);
	FIELD("Assembly-CSharp::BasePlayer::clientTeam", clientTeam, PlayerTeam*);
	FIELD("Assembly-CSharp::BasePlayer::lastSentTickTime", lastSentTickTime, float);

	FIELD("Assembly-CSharp::BasePlayer::clothingMoveSpeedReduction", clothingMoveSpeedReduction, float);

	void* ConsoleMessage_(const char* path) {
		static auto off = METHOD("Assembly-CSharp::BasePlayer::ConsoleMessage(String): Void");
		return reinterpret_cast<void* (*)(il2cpp::String*)>(off)(il2cpp::String::New(path));
	}
	Vector3 GetMountVelocity() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetMountVelocity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BasePlayer*)>(off)(this);
	}
	void SPU(PlayerProjectileUpdate* a1) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::SendProjectileUpdate(PlayerProjectileUpdate): Void");
		return reinterpret_cast<void(__fastcall*)(BasePlayer*, PlayerProjectileUpdate*)>(off)(this, a1);
	}
	FIELD("Assembly-CSharp::BasePlayer::ClientCurrentMapNote", ClientCurrentMapNote, MapNote*);

	PlayerWalkMovement* get_movement() {
		return *reinterpret_cast<PlayerWalkMovement**>((uintptr_t)this + Offsets::BasePlayer_movement);
	}
	void set_viewangles(const Vector2& VA) {
		DWORD64 Input = read(this + Offsets::BasePlayer_input, DWORD64);
		write(Input + Offsets::PlayerInput_bodyAngles, VA, Vector2);
	}
	Vector2 viewangles() {
		DWORD64 Input = read(this + Offsets::BasePlayer_input, DWORD64);
		return read(Input + Offsets::PlayerInput_bodyAngles, Vector2);
	}
	Vector3 newVelocity() {
		DWORD64 PlayerModel = read(this + Offsets::player_model, DWORD64);
		return read(PlayerModel + Offsets::playermodel_newVelocity, Vector3);
	}

	bool IsNpc() {
		DWORD64 PlayerModel = read(this + Offsets::player_model, DWORD64);
		return read(PlayerModel + Offsets::IsNpc, bool); // private bool <IsNpc>k__BackingField;
	}

	ULONG64 mono_transform(int bone) {
		DWORD64 entity_model = read(this + Offsets::baseentity_model, DWORD64);
		DWORD64 bone_dict = read(entity_model + 0x48, DWORD64);
		DWORD64 val = read(bone_dict + 0x20 + bone * 0x8, DWORD64);
		return val;
	}

	bool get_flag(int Flg) {
		return (read(this + Offsets::BasePlayer_playerFlags, int) & Flg);
	}

	FIELD("Assembly-CSharp::Model::boneTransforms", boneTransforms, Array<Transform*>*);
	FIELD("Assembly-CSharp::Model::boneNames", boneNames, Array<il2cpp::String*>*);
	Vector3 GetBoneByID(BoneList bone) {
		uintptr_t player_model = read(this + Offsets::baseentity_model, uintptr_t);// public Model model
		uintptr_t boneTransforms = read(player_model + Offsets::bone_boneTransforms, uintptr_t);//public Transform[] boneTransforms;
		Transform* transform = read(boneTransforms + 0x20 + bone * 0x8, Transform*); //0x10 // 0x68 // 0x78 //
		//const Transform* transform = read(BoneValue + 0x10, Transform*);

		if (!transform)
			return Vector3::Zero();
		return transform->position();
	}


	Transform* transform_(BoneList bone) {
		uintptr_t player_model = read(this + Offsets::baseentity_model, uintptr_t);// public Model model
		uintptr_t boneTransforms = read(player_model + Offsets::bone_boneTransforms, uintptr_t);//public Transform[] boneTransforms;
		Transform* transform = read(boneTransforms + 0x20 + bone * 0x8, Transform*);
		return transform;
	}

	Vector3 GetVelocity() {
		DWORD64 PlayerModel = read(this + Offsets::player_model, DWORD64);
		return read(PlayerModel + Offsets::PlayerModel_newVelocity, Vector3);
	}
	bool IsVisible() {

		DWORD64 PlayerModel = safe_read(this + Offsets::player_model, DWORD64);
		return safe_read(PlayerModel + Offsets::visible, bool);

	}
	bool is_teammate(BasePlayer* BasePlayer) {
		//  0x5A0
		auto TeamId = *(int*)(BasePlayer + Offsets::currentTeam);
		auto LocalTeamId = *(int*)(this + Offsets::currentTeam);

		if (LocalTeamId == 0) return false;
		if (TeamId == LocalTeamId) return true;

		return false;
	}
	bool IsDucked() { // lad don't fancy calling functions in a non-game thread, eh, thy lad shall recreate it.
		if (!this) return false;

		if (this->movement() != nullptr)
			return this->movement()->Ducking() > 0.5f;

		return this->modelState() != nullptr && this->modelState()->flags() & 1;
	}

	void add_modelstate_flag(ModelStateFlag flag) {
		DWORD64 mstate = read(this + Offsets::BasePlayer_modelState, DWORD64);
		int flags = read(mstate + Offsets::ModelState_flags, int);
		write(mstate + Offsets::ModelState_flags, flags |= (int)flag, int);
	}
	void remove_modelstate_flag(ModelStateFlag flag) {
		DWORD64 mstate = read(this + Offsets::BasePlayer_modelState, DWORD64);
		int flags = read(mstate + Offsets::ModelState_flags, int);
		write(mstate + Offsets::ModelState_flags, flags &= (int)flag, int);
	}
	bool has_modelstate_flag(ModelStateFlag flag) {
		DWORD64 mstate = read(this + Offsets::BasePlayer_modelState, DWORD64);
		int flags = read(mstate + Offsets::ModelState_flags, int);
		return flags & (int)flag;
	}
	bool OnLadder() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::OnLadder(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(BasePlayer*)>(off)(this);
	}
	float GetRadius() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetRadius(): Single");
		return reinterpret_cast<float(__fastcall*)(BasePlayer*)>(off)(this);
	}

	bool is_dead() {
		if (!this) return false;
		return this->lifestate() == LifeState::Dead;
	}

	float GetHeight(bool ducked) {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetHeight(Boolean): Single");
		return reinterpret_cast<float(__fastcall*)(BasePlayer*, bool)>(off)(this, ducked);
	}
	float GetJumpHeight() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetJumpHeight(): Single");
		if (!off) return 0.f;
		return reinterpret_cast<float(__fastcall*)(BasePlayer*)>(off)(this);
	}
	float GetMaxSpeed() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetMaxSpeed(): Single");
		return reinterpret_cast<float(__fastcall*)(BasePlayer*)>(off)(this);
	}
	float MaxVelocity() {
		if (!this) return 0.f;

		if (this->mounted())
			return this->GetMaxSpeed() * 4;

		return this->GetMaxSpeed();
	}

	Item* GetWeaponInfo(int Id) {
		DWORD64 Inventory = read(this + Offsets::BasePlayer_inventory, DWORD64);
		DWORD64 Belt = read(Inventory + Offsets::PlayerInventory_containerBelt, DWORD64); // containerBelt
		DWORD64 ItemList = read(Belt + Offsets::ItemContainer_itemList, DWORD64);// public List<Item> itemList;
		DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (Item*)read(Items + 0x20 + (Id * 0x8), DWORD64);
	}

	List<Item*>* item_list_b() {
		DWORD64 Inventory = read(this + Offsets::BasePlayer_inventory, DWORD64);
		DWORD64 Belt = read(Inventory + Offsets::PlayerInventory_containerBelt, DWORD64); // containerBelt
		return read(Belt + 0x40, List<Item*>*);// public List<Item> itemList;
	}

	Item* GetClothesInfo(int Id) {
		DWORD64 Inventory = read(this + Offsets::BasePlayer_inventory, DWORD64);
		DWORD64 Belt = read(Inventory + Offsets::PlayerInventory_containerWear, DWORD64); // containerWear
		DWORD64 ItemList = read(Belt + Offsets::ItemContainer_itemList, DWORD64);// public List<Item> itemList;
		DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (Item*)read(Items + 0x20 + (Id * 0x8), DWORD64);
	}

	List<Item*>* item_list_w() {
		DWORD64 Inventory = read(this + Offsets::BasePlayer_inventory, DWORD64);
		DWORD64 Belt = read(Inventory + Offsets::PlayerInventory_containerWear, DWORD64); // containerWear
		return read(Belt + 0x40, List<Item*>*);// public List<Item> itemList;
	}

	Item* GetActiveWeapon() {
		int ActUID = read(this + Offsets::BasePlayer_clActiveItem, int);
		if (!ActUID) return nullptr;
		Item* ActiveWeapon;
		for (int i = 0; i < 6; i++)
			if (ActUID == (ActiveWeapon = GetWeaponInfo(i))->uid())
				return ActiveWeapon;
		return nullptr;
	}

	void FakeAdmin() {
		int Flags = read(this + Offsets::BasePlayer_playerFlags, int);
		write(this + Offsets::BasePlayer_playerFlags, (Flags |= 4), int);
	}

	void UnloadFakeAdmin() {
		int Flags = read(this + Offsets::BasePlayer_playerFlags, int);
		write(this + Offsets::BasePlayer_playerFlags, (Flags ^= 4), int);
	}

	static float& Admintime() {
		static auto clazz = CLASS("Assembly-CSharp::ConVar::Admin");
		return *reinterpret_cast<float*>(std::uint64_t(clazz->static_fields) + 0x0);
	}

	void LongNeck() {
		DWORD64 pedic = read(this + Offsets::BasePlayer_eyes, DWORD64);
		write(pedic + Offsets::PlayerEyes_viewOffset, Vector3(0, 1.5f, 0), Vector3);
	}

	template<typename T = HeldEntity>
	T* GetHeldEntity() {
		if (!this) return nullptr;

		auto inventory = this->inventory();
		if (!inventory) return nullptr;

		auto belt = inventory->containerBelt();
		if (!belt) return nullptr;

		auto item_list = belt->itemList();
		if (!item_list) return nullptr;

		for (int i = 0; i < item_list->size; i++) {
			auto item = reinterpret_cast<Item*>(item_list->get(i));
			if (!item) continue;

			if (item->uid() == this->clActiveItem())
				return item->heldEntity<T>();
		}

		return nullptr;
	}

	Item* GetHeldItem() {
		if (!this) return nullptr;

		auto inventory = this->inventory();
		if (!inventory) return nullptr;

		auto belt = inventory->containerBelt();
		if (!belt) return nullptr;

		auto item_list = belt->itemList();
		if (!item_list) return nullptr;

		for (int i = 0; i < item_list->size; i++) {
			auto item = reinterpret_cast<Item*>(item_list->get(i));
			if (!item) continue;

			if (item->uid() == this->clActiveItem())
				return item;
		}

		return nullptr;
	}

	bool HasPlayerFlag(PlayerFlags flag) {
		if (!this) return false;

		return (PlayerFlags() & flag) == flag;
	}

	bool IsCrawling() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::IsCrawling(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(BasePlayer*)>(off)(this);
	}

	bool HasParent() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::BaseNetworkable::HasParent(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(BasePlayer*)>(off)(this);
	}

	static Vector3 EyePositionForPlayer(BasePlayer* player)
	{
		bool mounted = player->HasParent();
		if (!mounted)
		{
			return Vector3::Zero();
		}
		return player->eyes()->position();
	}

	Vector3 GetNetworkEyePosition() {
		Vector3 viewOffset;

		if (this->IsCrawling())
		{
			viewOffset = Vector3(0.f, -1.15f, 0.175f);
		}
		else if (this->IsDucked())
		{
			viewOffset = Vector3(0.f, -0.6f, 0.f);
		}
		else
		{
			viewOffset = Vector3::Zero();
		}

		if (this->mounted())
		{
			return this->lastSentTick()->__position() + this->transform()->get_rotation() * (Vector3(0.f, 1.5f, 0.f) + viewOffset) + Vector3::Zero();
		}

		Vector3 vector = EyePositionForPlayer(this);

		if (vector != Vector3::Zero())
		{
			return vector;
		}

		return this->lastSentTick()->__position() + this->transform()->up() * (1.5f + 0) + Vector3::Zero();
	}

	FIELD("Assembly-CSharp::BasePlayer::playerModel", playerModel, PlayerModel*);
};
class LocalPlayer {
public:
	static BasePlayer* Entity() {
		static auto clazz = CLASS("Assembly-CSharp::LocalPlayer");
		return *reinterpret_cast<BasePlayer**>(std::uint64_t(clazz->static_fields));
	}
};
class Attack {
public:
	FIELD("Rust.Data::ProtoBuf::Attack::hitID", hitID, uint32_t);
	FIELD("Rust.Data::ProtoBuf::Attack::hitBone", hitBone, uint32_t);
	FIELD("Rust.Data::ProtoBuf::Attack::hitMaterialID", hitMaterialID, uint32_t);
	FIELD("Rust.Data::ProtoBuf::Attack::hitPositionWorld", hitPositionWorld, Vector3);
	FIELD("Rust.Data::ProtoBuf::Attack::hitNormalWorld", hitNormalWorld, Vector3);
	FIELD("Rust.Data::ProtoBuf::Attack::pointStart", pointStart, Vector3);
	FIELD("Rust.Data::ProtoBuf::Attack::pointEnd", pointEnd, Vector3);
};
class PlayerAttack {
public:
	FIELD("Rust.Data::ProtoBuf::PlayerAttack::attack", attack, Attack*);
};
class BaseMelee : public AttackEntity {
public:
	void StartAttackCooldown(float cooldown)
	{
		if (!this) return;

		static auto off = METHOD("Assembly-CSharp::AttackEntity::StartAttackCooldown(Single): Void");

		return reinterpret_cast<void(__fastcall*)(AttackEntity*, float)>(off)(this, cooldown);
	}
	bool HasAttackCooldown()
	{
		if (!this) return false;

		static auto off = METHOD("Assembly-CSharp::AttackEntity::HasAttackCooldown(): Boolean");

		return reinterpret_cast<bool(__fastcall*)(AttackEntity*)>(off)(this);
	}
	void DoAttack(HitTest* test)
	{
		if (!this) return;

		static auto off = METHOD("Assembly-CSharp::BaseMelee::ProcessAttack(HitTest): Void");

		return reinterpret_cast<void(__fastcall*)(BaseMelee*, HitTest*)>(off)(this, test);
	}
	void DoThrow()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseMelee::DoThrow(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseMelee*)>(off)(this);
	}
	bool get_CanThrow()
	{
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::BaseMelee::get_CanThrow(): Boolean");
		return reinterpret_cast<bool(*)(BaseMelee*)>(off)(this);
	}
	FIELD("Assembly-CSharp::BaseMelee::canThrowAsProjectile", canThrowAsProjectile, bool);

	FIELD("Assembly-CSharp::BaseMelee::maxDistance", maxDistance, float);
	FIELD("Assembly-CSharp::BaseMelee::throwready", throwready, bool);
	static inline void (*ProcessAttack_)(BaseMelee*, HitTest*) = nullptr;
	void ProcessAttack(HitTest* test) {
		return ProcessAttack_(this, test);
	}

};
class Networkable {
public:
	unsigned int get_id() {
		return *reinterpret_cast<unsigned int*>((uintptr_t)this + 0x10);
	}

	//template<typename T = uintptr_t>
	//T* GetComponent(uintptr_t type) {
	//	if (!this || !type) return nullptr;
	//	return (T*)get_component((uintptr_t)this, type);
	//}


};

class Mathf {
public:
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Sin(Single): Single", Sin, float(float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Cos(Single): Single", Cos, float(float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::FloorToInt(Single): Int32", FloorToInt, int(float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Max(Single,Single): Single", Max, float(float, float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Min(Single,Single): Single", Min, float(float, float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Clamp(Single,Single,Single): Single", Clamp, float(float, float, float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Abs(Single): Single", Abs, float(float));
};

class Mathx {
public:
	STATIC_FUNCTION("Rust.Global::Mathx::Decrement(Single): Single", Decrement, float(float));
	STATIC_FUNCTION("Rust.Global::Mathx::Increment(Single): Single", Increment, float(float));
	STATIC_FUNCTION("Rust.Global::Mathx::Max(Single,Single,Single): Single", Max, float(float, float, float));
};


class Vector3_ {
public:
	static inline Vector3(*MoveTowards_)(Vector3, Vector3, float) = nullptr;

	static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta) {
		return MoveTowards_(current, target, maxDistanceDelta);
	}
};

class DDraw {
public:
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Line(Vector3,Vector3,Color,Single,Boolean,Boolean): Void", Line, void(Vector3, Vector3, Color, float, bool, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Sphere(Vector3,Single,Color,Single,Boolean,Boolean): Void", Sphere_invis, void(Vector3, float, Color, float, bool, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Sphere(Vector3,Single,Color,Single,Boolean,Boolean): Void", Sphere, void(Vector3, float, Color, float, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Capsule(Vector3,Quaternion,Single,Single,Color,Single,Boolean,Boolean): Void", Capsule, void(Vector3, Quaternion, float, float, Color, float, bool));

	//STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Line(Vector3,Vector3,Color,Single,Boolean,Boolean): Void", Line, void(Vector3, Vector3, Color, float, bool, bool));
	//STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Sphere(Vector3,Single,Color,Single,Boolean): Void", Sphere, void(Vector3, float, Color, float, bool));
	//STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Text(String,Vector3,Color,Single): Void", Text, void(il2cpp::String*, Vector3, Color, float));
	//STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Arrow(Vector3,Vector3,Single,Color,Single): Void", Arrow, void(Vector3, Vector3, float, Color, float));
	//STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Capsule(Vector3,Quaternion,Single,Single,Color,Single,Boolean): Void", Capsule, void(Vector3, Quaternion, float, float, Color, float, bool));
	//STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Box(Vector3,Single,Color,Single,Boolean): Void", Box, void(Vector3, float, Color, float, bool));
	//STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Get(): DDraw", Get, DDraw* ());
};
class AssetBundle {
public:
	Array<il2cpp::String*>* GetAllAssetNames() {
		if (!this) return {};
		static auto off = METHOD("UnityEngine.AssetBundleModule::UnityEngine::AssetBundle::GetAllAssetNames(): String[]");
		return reinterpret_cast<Array<il2cpp::String*>*(*)(AssetBundle*)>(off)(this);
	}
	template<typename T = Object>
	T* LoadAsset(const char* name, Type* type) {
		if (!this) return {};
		static auto off = METHOD("UnityEngine.AssetBundleModule::UnityEngine::AssetBundle::LoadAsset(String,Type): Object");
		return reinterpret_cast<T * (*)(AssetBundle*, il2cpp::String*, Type*)>(off)(this, il2cpp::String::New(name), type);
	}
	static AssetBundle* LoadFromFile(const char* path) {
		static auto off = METHOD("UnityEngine.AssetBundleModule::UnityEngine::AssetBundle::LoadFromFile(String): AssetBundle");
		return reinterpret_cast<AssetBundle * (*)(il2cpp::String*)>(off)(il2cpp::String::New(path));
	}
};

class Attack;

class HitTest {
public:
	FIELD("Assembly-CSharp::HitTest::HitEntity", HitEntity, BaseEntity*);

	static HitTest* New()
	{
		HitTest* hitTest = il2cpp::il2cpp_object_new_<HitTest*>(CLASS("Assembly-CSharp::HitTest"));

		return hitTest;
	}

	static inline Attack* (*BuildAttackMessage_)(HitTest*, BaseEntity*) = nullptr;
	Attack* BuildAttackMessage(BaseEntity* a1) {
		return BuildAttackMessage_(this, a1);
	}

	FIELD("Assembly-CSharp::HitTest::damageProperties", damageProperties, uintptr_t);
	FIELD("Assembly-CSharp::HitTest::AttackRay", AttackRay, Ray);
	FIELD("Assembly-CSharp::HitTest::Radius", Radius, float);
	FIELD("Assembly-CSharp::HitTest::Forgiveness", Forgiveness, float);
	FIELD("Assembly-CSharp::HitTest::MaxDistance", MaxDistance, float);
	FIELD("Assembly-CSharp::HitTest::BestHit", BestHit, bool);
	FIELD("Assembly-CSharp::HitTest::DidHit", DidHit, bool);
	FIELD("Assembly-CSharp::HitTest::ignoreEntity", ignoreEntity, BaseEntity*);
	FIELD("Assembly-CSharp::HitTest::HitPoint", HitPoint, Vector3);
	FIELD("Assembly-CSharp::HitTest::HitNormal", HitNormal, Vector3);
	FIELD("Assembly-CSharp::HitTest::HitMaterial", HitMaterial, il2cpp::String*);
	FIELD("Assembly-CSharp::HitTest::HitDistance", HitDistance, float);
	FIELD("Assembly-CSharp::HitTest::HitTransform", HitTransform, Transform*);
	FIELD("Assembly-CSharp::HitTest::HitMaterial", HitMaterial_, il2cpp::String*);
	FIELD("Assembly-CSharp::HitTest::MultiHit", MultiHit, bool);

	FIELD("Assembly-CSharp::HitTest::HitEntity", _HitEntity, BaseNetworkable*);
	Vector3 HitPointWorld() {
		if (!this) return Vector3();
		static auto off = METHOD("Assembly-CSharp::HitTest::HitPointWorld(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(HitTest*)>(off)(this);
	}

	Vector3 HitNormalWorld() {
		if (!this) return Vector3();
		static auto off = METHOD("Assembly-CSharp::HitTest::HitNormalWorld(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(HitTest*)>(off)(this);
	}



	GameObject* gameObject() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_gameObject(): GameObject");
		return SafeExecution::Execute<GameObject*>(off, nullptr, this);
	}
};

Material_* Ice;
Material_* Glitch;
Material_* Glitch2;
Material_* Glitch3;
Material_* Glitch4;
Material_* Glitch5;
Material_* GalaxyPerple;
Material_* GalaxyGreen;
Material_* GalaxyPink;
Material_* DesolveMat;
Material_* GalaxyBlue;
Material_* GalaxyFire;
Material_* GalaxyNightFire;
Material_* Rainbow;
Material_* GredSpace;
Material_* Fade;
Material_* Frame;
Material_* Gold;
Material_* Glitter;
Material_* Ghost;
Material_* Ghost2;
Material_* DamascusMat;
Material_* Outline;
Material_* Slick;
Material_* gaga;
Material_* Pixel;
Material_* Silver;
Material_* gagahga;
Material_* afagfgtqag;

class SteamPlatform {
public:
	void set_UserName(const char* str) {
		static auto off = METHOD("Rust::Platform::Steam::set_UserName(String): Void");
		return reinterpret_cast<void(__fastcall*)(SteamPlatform*, const char*)>(off)(this, str);
	}
};
class Projectile {
public:

	void UpdateVelocity(float delta) {
		static auto off = METHOD("Assembly-CSharp::Projectile::UpdateVelocity(Single): Void");
		return reinterpret_cast<void(__fastcall*)(Projectile*, float)>(off)(this, delta);
	}

	Transform* transform() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_transform(): Transform");
		return SafeExecution::Execute<Transform*>(off, nullptr, this);
	}
	FIELD("Assembly-CSharp::Projectile::initialDistance", __initialDistance, Vector3);
	FIELD("Assembly-CSharp::Projectile::damageProperties", damageProperties, uintptr_t);
	FIELD("Assembly-CSharp::ItemModProjectile::ammoType", ammoType, int);
	FIELD("Assembly-CSharp::Projectile::integrity", _integrity, float);
	FIELD("Assembly-CSharp::Projectile::initialDistance", _initialDistance, float);
	FIELD("Assembly-CSharp::Projectile::projectileID", _projectileID, int);
	FIELD("Assembly-CSharp::Projectile::penetrationPower", penetrationPower, float);
	FIELD("Assembly-CSharp::Projectile::swimRandom", swimRandom, float);
	FIELD("Assembly-CSharp::Projectile::swimScale", swimScale, Vector3);
	FIELD("Assembly-CSharp::Projectile::tumbleAxis", tumbleAxis, Vector3);
	FIELD("Assembly-CSharp::Projectile::swimSpeed", swimSpeed, Vector3);
	FIELD("Assembly-CSharp::Projectile::tumbleSpeed", tumbleSpeed, float);
	FIELD("Assembly-CSharp::Projectile::traveledTime", traveledTime, float);
	FIELD("Assembly-CSharp::Projectile::sentPosition", sentPosition, Vector3);
	FIELD("Assembly-CSharp::Projectile::launchTime", launchTime, float);

	FIELD("Assembly-CSharp::Projectile::closeFlybyDistance", closeFlybyDistance, float);
	FIELD("Assembly-CSharp::Projectile::drag", drag, float);
	FIELD("Assembly-CSharp::Projectile::thickness", thickness, float);
	FIELD("Assembly-CSharp::Projectile::projectileID", projectileID, int);
	FIELD("Assembly-CSharp::Projectile::mod", mod, ItemModProjectile*);
	FIELD("Assembly-CSharp::Projectile::traveledDistance", traveledDistance, float);
	FIELD("Assembly-CSharp::Projectile::initialDistance", initialDistance, float);
	FIELD("Assembly-CSharp::Projectile::integrity", integrity, float);
	FIELD("Assembly-CSharp::Projectile::ricochetChance", ricochetChance, float);
	FIELD("Assembly-CSharp::Projectile::currentPosition", currentPosition, Vector3);
	FIELD("Assembly-CSharp::Projectile::hitTest", hitTest, HitTest*);
	FIELD("Assembly-CSharp::Projectile::currentVelocity", currentVelocity, Vector3);
	FIELD("Assembly-CSharp::Projectile::gravityModifier", gravityModifier, float);
	FIELD("Assembly-CSharp::Projectile::previousVelocity", previousVelocity, Vector3);
	FIELD("Assembly-CSharp::Projectile::previousPosition", previousPosition, Vector3);
	FIELD("Assembly-CSharp::Projectile::initialVelocity", initialVelocity, Vector3);
	BasePlayer* owner() { return (BasePlayer*)read(this + 0xD0, uintptr_t); }

	bool DoHit(HitTest* test, Vector3 point, Vector3 normal) {
		static auto off = METHOD("Assembly-CSharp::Projectile::DoHit(HitTest,Vector3,Vector3): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Projectile*, HitTest*, Vector3, Vector3)>(off)(this, test, point, normal);
	}

	void Update()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::Projectile::Update(): Void");
		return reinterpret_cast<void(__fastcall*)(Projectile*)>(off)(this);
	}
	bool isAuthoritative() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::Projectile::get_isAuthoritative(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Projectile*)>(off)(this);
	}
	bool isAlive() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::Projectile::get_isAlive(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Projectile*)>(off)(this);
	}
};

class GamePhysics {
public:
	enum class QueryTriggerInteraction {
		UseGlobal = 0,
		Ignore = 1,
		Collide = 2,
	};
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::LineOfSight(Vector3,Vector3,Int32,Single,BaseEntity): Boolean", LineOfSight_, bool(Vector3, Vector3, int, float, uintptr_t));
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::LineOfSight(Vector3,Vector3,Int32,Single,Single,BaseEntity): Boolean", LineOfSight, bool(Vector3, Vector3, int, float, float, uintptr_t));
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::LineOfSight(Vector3,Vector3,Int32,BaseEntity): Boolean", LineOfSight_invis, bool(Vector3, Vector3, int, float));
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::LineOfSightRadius(Vector3,Vector3,Int32,Single,BaseEntity): Boolean", LineOfSightRadius, bool(Vector3, Vector3, int, float, float));

	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::Verify(RaycastHit,BaseEntity): Boolean", Verify, bool(RaycastHit, float));
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::CheckCapsule(Vector3,Vector3,Single,Int32,QueryTriggerInteraction): Boolean", CheckCapsule, bool(Vector3, Vector3, float, int, QueryTriggerInteraction));
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::Trace(Ray,Single,RaycastHit&,Single,Int32,QueryTriggerInteraction,BaseEntity): Boolean", Trace, bool(Ray, float, RaycastHit, float, int, QueryTriggerInteraction, BaseEntity*));
};

bool LineOfSightRadius(Vector3 p0, Vector3 p1, int layerMask, float radius) {
	bool result = GamePhysics::LineOfSightRadius(p0, p1, layerMask, radius, 0.f) && GamePhysics::LineOfSightRadius(p1, p0, layerMask, radius, 0.f);
	return result;
}

namespace utils {
	bool w2s(const Vector3& EntityPos, Vector2& ScreenPos)
	{
		if (EntityPos.x == 0 && EntityPos.y == 0 && EntityPos.z == 0)
			return false;

		auto matrix = il2cpp::unity::find_matrix();
		if (!matrix) 
			return false;

		Vector3 TransVec = Vector3(matrix->_14, matrix->_24, matrix->_34);
		Vector3 RightVec = Vector3(matrix->_11, matrix->_21, matrix->_31);
		Vector3 UpVec = Vector3(matrix->_12, matrix->_22, matrix->_32);
		float w = Math::Dot(TransVec, EntityPos) + matrix->_44;

		
		float y = Math::Dot(UpVec, EntityPos) + matrix->_42;
		float x = Math::Dot(RightVec, EntityPos) + matrix->_41;
		
		
		ScreenPos = Vector2((settings::screen_size.x / 2) * (1.f + x / w), (settings::screen_size.y / 2) * (1.f - y / w));
		if (w < 0.1f) return false;
		if (ScreenPos.x < 0 || ScreenPos.x > settings::screen_size.x ||
			ScreenPos.y < 0 || ScreenPos.y > settings::screen_size.y)
			return false;
		return true;
	}


	Vector3 ClosestPoint(BasePlayer* player, Vector3 p) {

		static auto off = METHOD("Assembly-CSharp::BaseEntity::ClosestPoint(Vector3): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BasePlayer*, Vector3)>(off)(player, p);
	}

	bool LineOfSight(Vector3 a, Vector3 b) {
		bool result = false;
		if (a != Vector3::Zero() && b != Vector3::Zero())
		{
			int mask = settings::weapons::penetrate ? 2162688 | 8388608 | 134217728 : 1503731969 | 2162688 | 8388608 | 2097152 | 1 | 2097152 | 32768 | 65536; // projectile los, flyhack mask, intellisense reload
			result = GamePhysics::LineOfSight_invis(a, b, mask, 0.f) && GamePhysics::LineOfSight_invis(b, a, mask, 0.f);
		}
		return result;
	}

	class StringPool {
	public:
		static uint32_t Get(const char* str) {
			static auto off = METHOD("Assembly-CSharp::StringPool::Get(String): UInt32");
			return reinterpret_cast<uint32_t(__fastcall*)(il2cpp::String*)>(off)(il2cpp::String::New(str));
		}

		static il2cpp::String* Get(uint32_t i) {
			static auto off = METHOD("Assembly-CSharp::StringPool::Get(UInt32): String");
			return reinterpret_cast<il2cpp::String * (__fastcall*)(uint32_t)>(off)(i);
		}
	};
}
class Model : public Component {
public:
	FIELD("Assembly-CSharp::Model::boneTransforms", boneTransforms, Array<Transform*>*);
	FIELD("Assembly-CSharp::Model::boneNames", boneNames, Array<il2cpp::String*>*);
};
enum class EventType : int {
	Zero = 0,
	Repaint = 7
};
class Event {
public:
	STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::Event::get_current(): Event", get_current, Event* ());
	EventType get_type() {
		if (!this) return EventType::Zero;
		static auto off = METHOD("UnityEngine.IMGUIModule::UnityEngine::Event::get_type(): EventType");
		return reinterpret_cast<EventType(__fastcall*)(Event*)>(off)(this);
	}
};
namespace Network {
	enum class MessageType {
		auth = 2,
		requestuserinformation = 17,
		giveuserinformation = 18
	};
	class Client {
	public:

		bool IsConnected() {
			if (!this) return false;
			static auto off = METHOD("Facepunch.Network::Network::Client::IsConnected(): Boolean");
			return reinterpret_cast<bool(__fastcall*)(Client*)>(off)(this);
		}

	};
}

class WaterLevel {
public:
	STATIC_FUNCTION("Assembly-CSharp::WaterLevel::Test(Vector3,Boolean,Boolean,BaseEntity): Boolean", Test, bool(Vector3, bool, bool, BaseEntity*));
};

struct TimeAverageValueData
{
public:
	int Calculate()
	{
		float realtimeSinceStartup = Time::realtimeSinceStartup();
		float num = realtimeSinceStartup - refreshTime;
		if (num >= 1.0)
		{
			counterPrev = (int)(counterNext / num + 0.5);
			counterNext = 0;
			refreshTime = realtimeSinceStartup;
			num = 0;
		}
		return (int)(counterPrev * (1.0 - num)) + counterNext;
	}

	void Increment()
	{
		this->Calculate();
		counterNext += 1;
	}

	void Reset()
	{
		counterPrev = 0;
		counterNext = 0;
	}

	float refreshTime;

	int counterPrev;

	int counterNext;
};

inline TimeAverageValueData Total_Counter = { 0, 0, 0 };
inline TimeAverageValueData RPC_Counter = { 0, 0, 0 };
inline TimeAverageValueData RPC_Counter2 = { 0, 0, 0 };
inline TimeAverageValueData RPC_Counter3 = { 0, 0, 0 };
inline TimeAverageValueData RPC_Counter5 = { 0, 0, 0 };

inline TimeAverageValueData Signal_Counter = { 0, 0, 0 };
#define minm( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#define maxx( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )

namespace AntiHack
{
	float noclip_margin_dismount = 0.22f;
	float noclip_backtracking = 0.01f;
	bool reporting = false;
	bool admincheat = true;
	bool objectplacement = true;
	bool modelstate = true;
	bool forceposition = true;
	int userlevel = 2;
	int enforcementlevel = 1;
	float maxdesync = 1.f;
	float maxdeltatime = 1.f;
	float tickhistorytime = 0.5f;
	float tickhistoryforgiveness = 0.1f;
	float relaxationrate = 0.1f;
	float relaxationpause = 10.f;
	float maxviolation = 100.f;
	int terrain_protection = 1;
	int terrain_timeslice = 64;
	float terrain_padding = 0.3f;
	float terrain_penalty = 100.f;
	bool terrain_kill = true;
	bool terrain_check_geometry = false;
	int noclip_protection = 3;
	bool noclip_reject = true;
	float noclip_penalty = 0.f;
	float noclip_margin = 0.09f;
	float noclip_stepsize = 0.1f;
	int noclip_maxsteps = 15;
	int speedhack_protection = 2;
	bool speedhack_reject = true;
	float speedhack_penalty = 0.f;
	float speedhack_forgiveness = 2.f;
	float speedhack_forgiveness_inertia = 10.f;
	float speedhack_slopespeed = 10.f;
	int flyhack_protection = 3;
	bool flyhack_reject = false;
	float flyhack_penalty = 100.f;
	float flyhack_forgiveness_vertical = 1.5f;
	float flyhack_forgiveness_vertical_inertia = 10.f;
	float flyhack_forgiveness_horizontal = 1.5f;
	float flyhack_forgiveness_horizontal_inertia = 10.f;
	float flyhack_extrusion = 2.f;
	float flyhack_margin = 0.05f;
	float flyhack_stepsize = 0.1f;
	int flyhack_maxsteps = 15;
	int projectile_protection = 6;
	float projectile_penalty = 0.f;
	float projectile_forgiveness = 0.5f;
	float projectile_serverframes = 2.f;
	float projectile_clientframes = 2.f;
	float projectile_trajectory = 1.f;
	float projectile_anglechange = 60.f;
	float projectile_velocitychange = 1.1f;
	float projectile_backtracking = 0.01f;
	float projectile_losforgiveness = 0.2f;
	int projectile_damagedepth = 2;
	int projectile_impactspawndepth = 1;
	bool projectile_terraincheck = true;
	int melee_protection = 4;
	float melee_penalty = 0.f;
	float melee_forgiveness = 0.5f;
	float melee_serverframes = 2.f;
	float melee_clientframes = 2.f;
	float melee_backtracking = 0.01f;
	float melee_losforgiveness = 0.2f;
	bool melee_terraincheck = true;
	int eye_protection = 4;
	float eye_penalty = 0.f;
	float eye_forgiveness = 0.5f;
	float eye_serverframes = 2.f;
	float eye_clientframes = 2.f;
	bool eye_terraincheck = true;
	float eye_noclip_cutoff = 0.06f;
	float eye_noclip_margin = 0.21f;
	float eye_noclip_backtracking = 0.01f;
	float eye_losradius = 0.18f;
	float eye_history_penalty = 100.f;
	float eye_history_forgiveness = 0.1f;
	float build_losradius = 0.01f;
	float build_losradius_sleepingbag = 0.3f;
	bool build_terraincheck = true;
	int build_inside_check = 2;
	int debuglevel = 1;
	bool eye_vehiclecheck = true;
};
