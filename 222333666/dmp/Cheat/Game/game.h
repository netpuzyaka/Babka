#include <array>
#include <map>


struct Ammo {
	int id[2];
	float speed;
};
struct Weapon {
	int id;
	const char* name;
	Ammo ammo[4];
	int category; //-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
};
Weapon iinfo[]{
Weapon{1588298435, ("Bolt Action Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 375.f}, Ammo{{1712070256} /*HV 5.56*/, 788 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 394}}, 2 },
Weapon{-778367295, ("L96 Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 625.f}, Ammo{{1712070256} /*HV 5.56*/, 1350 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 675}}, 2 },

Weapon{-1367281941, ("Waterpipe Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 185.f}, Ammo{{588596902, -1036635990}/*gray, blue*/, 80}}, 2 },
Weapon{-765183617, ("Double Barrel Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 185.f}, Ammo{{588596902, -1036635990}/*gray, blue*/, 80}}, 2 },
Weapon{-41440462, ("Spas-12 Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 185.f}, Ammo{{588596902, -1036635990}/*gray, blue*/, 80}}, 2 },
Weapon{795371088, ("Pump Shotgun"), { Ammo{{-727717969, -1685290200}/*green, red*/, 185.f}, Ammo{{588596902, -1036635990}/*gray, blue*/, 80}}, 2 },
Weapon{-75944661, ("Eoka Pistol"), { Ammo{{-727717969, -1685290200}/*green, red*/, 185.f}, Ammo{{588596902, -1036635990}/*gray, blue*/, 80}}, -1 },

Weapon{1965232394, ("Crossbow"), { Ammo{{-1234735557}/*normal arrow*/, 78.f}, Ammo{{14241751} /*fire arrow*/, 61.f}, Ammo{{215754713} /*bone arrow*/, 66.f}, Ammo{{-1023065463} /*HV arrow*/, 120.f}}, 2 },
Weapon{884424049, ("Compound Bow"), { Ammo{{-1234735557}/*normal arrow*/, 50.f}, Ammo{{14241751} /*fire arrow*/, 40}, Ammo{{215754713} /*bone arrow*/, 45}, Ammo{{-1023065463} /*HV arrow*/, 78.8f}}, 2 }, //TODO on zoom velocity x2
Weapon{1443579727, ("Hunting Bow"), { Ammo{{-1234735557}/*normal arrow*/, 50.f}, Ammo{{14241751} /*fire arrow*/, 40}, Ammo{{215754713} /*bone arrow*/, 45}, Ammo{{-1023065463} /*HV arrow*/, 80} }, -2 },

Weapon{1318558775, ("MP5A4"), { Ammo{{785728077}/*normal pistol*/, 190.f}, Ammo{{-1691396643} /*HV pistol*/, 290.f}, Ammo{{51984655} /*inc pistol*/, 145.f}}, 3 },
Weapon{1796682209, ("Custom SMG"), { Ammo{{785728077}/*normal pistol*/, 205.f}, Ammo{{-1691396643} /*HV pistol*/, 300.f}, Ammo{{51984655} /*inc pistol*/, 145.f}}, 3 },
Weapon{649912614, ("Revolver"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 2 },
Weapon{818877484, ("Semi-Automatic Pistol"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 2 },
Weapon{-852563019, ("M92 Pistol"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 2 },
Weapon{1373971859, ("Python Revolver"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol 225*/, 225}}, 2 },
Weapon{-1758372725, ("Thompson"), { Ammo{{785728077}/*normal pistol*/, 300}, Ammo{{-1691396643} /*HV pistol*/, 400}, Ammo{{51984655} /*inc pistol*/, 225}}, 3 },

Weapon{-1812555177, ("LR-300 Assault Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 375}, Ammo{{1712070256} /*HV 5.56*/, 450 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 225}}, 3 },
Weapon{-904863145, ("Semi-Automatic Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 375}, Ammo{{1712070256} /*HV 5.56*/, 450 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 225}}, 2 },
Weapon{1545779598, ("Assault Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 375}, Ammo{{1712070256} /*HV 5.56*/, 450 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 225}}, 3 },
Weapon{-1335497659, ("Assault Rifle Ice"), { Ammo{{-1211166256}/*normal 5.56*/, 375}, Ammo{{1712070256} /*HV 5.56*/, 450 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 225}}, 3 },
Weapon{-2069578888, ("M249"), { Ammo{{-1211166256}/*normal 5.56*/, 375.f}, Ammo{{1712070256} /*HV 5.56*/, 585 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 293}}, 3 },
Weapon{-1214542497, ("HMLMG"), { Ammo{{-1211166256}/*normal 5.56*/, 375.f}, Ammo{{1712070256} /*HV 5.56*/, 585 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 293}}, 3 },
Weapon{28201841, ("M39 Rifle"), { Ammo{{-1211166256}/*normal 5.56*/, 469}, Ammo{{1712070256} /*HV 5.56*/, 563 }, Ammo{{-1321651331, 605467368}/*inc, ex 5.56*/, 281}}, 2 },

Weapon{1090916276, ("Pitchfork"), {Ammo{{0}, 25}}, 1 },
Weapon{1540934679, ("Wooden Spear"), {Ammo{{0}, 25}}, 1 },
Weapon{1814288539, ("Bone Knife"), {Ammo{{0}, 20}}, 1 },
Weapon{-363689972, ("Snowball"), {Ammo{{0}, 20}}, 1 },
Weapon{1789825282, ("Candy Cane Club"), {Ammo{{0}, 20}}, 1 },
Weapon{-1137865085, ("Machete"), {Ammo{{0}, 20}}, 1 },
Weapon{1711033574, ("Bone Club"), {Ammo{{0}, 20}}, 1 },
Weapon{-1966748496, ("Mace"), {Ammo{{0}, 18}}, 1 },
Weapon{-194509282, ("Butcher Knife"), {Ammo{{0}, 20}}, 1 },
Weapon{1326180354, ("Salvaged Sword"), {Ammo{{0}, 20}}, 1 },
Weapon{-1469578201, ("Longsword"), {Ammo{{0}, 18}}, 1 },
Weapon{-1978999529, ("Salvaged Cleaver"), {Ammo{{0}, 18}}, 1 },
Weapon{1602646136, ("Stone Spear"), {Ammo{{0}, 30}}, 1 },
Weapon{2040726127, ("Combat Knife"), {Ammo{{0}, 30}}, 1 },
Weapon{963906841, ("Rock"), {Ammo{{0}, 18}}, 1 },

Weapon{1953903201, ("Nailgun"), { Ammo{{-2097376851}/*nails*/, 50}}, 2 },
Weapon{-1123473824, ("Multiple Grenade Launcher"), { Ammo{{915408809, 349762871}/*smoke, exp*/, 100}, Ammo{{1055319033}, 225}/*shotgun*/}, 2 },
Weapon{442886268, ("Rocket Launcher"), 0, 69 },
Weapon{-1215753368, ("Flame Thrower"), 0, 0 },
Weapon{200773292, ("Hammer"), {0}, -3 }
};

Vector3 cLastTickPos{};
unsigned int m_wcslen(wchar_t* str)
{
	int cnt = 0;
	if (!str)
		return 0;
	for (; *str != '\0'; ++str)
		++cnt;
	return cnt;
}
namespace __System {
	template<typename T = void*>
	class Array {
	public:
		uint32_t size() {
			if (!this) return 0;
			return *reinterpret_cast<uint32_t*>(this + 0x18);
		}
		T get(int idx) {
			if (!this) return T{};
			return *reinterpret_cast<T*>(this + (0x20 + (idx * 0x8)));
		}
		void add(int idx, T value) {
			if (!this) return;
			*reinterpret_cast<T*>(this + (0x20 + (idx * 0x8))) = value;
		}
	};

	template<typename T>
	class list {
	public:
		T get(uint32_t idx)
		{
			const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T get_value(uint32_t idx)
		{
			const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
			const auto internal_list = list + 0x20;
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T operator[](uint32_t idx) { return get(idx); }

		const uint32_t get_size() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }

		template<typename F>
		void for_each(const F callback)
		{
			for (auto i = 0; i < get_size(); i++) {
				auto object = this->get(i);
				if (!object)
					continue;
				callback(object, i);
			}
		}

		void add(int idx, T value) {
			if (!this) return;
			*reinterpret_cast<T*>(this + (0x20 + (idx * 0x8))) = value;
		}
	};

	class string {
	public:
		char zpad[0x10];
		int size;
		wchar_t str[128 + 1];
		string() {}
		string(const wchar_t* st) {
			size = min(m_wcslen((wchar_t*)st), 128);
			for (int i = 0; i < size; i++) {
				str[i] = st[i];
			}
			str[size] = 0;
		}
	};
}
namespace rust {
	enum class layer : uint32_t {
		Default = 0,
		TransparentFX = 1,
		Ignore_Raycast = 2,
		Reserved1 = 3,
		Water = 4,
		UI = 5,
		Reserved2 = 6,
		Reserved3 = 7,
		Deployed = 8,
		Ragdoll = 9,
		Invisible = 10,
		AI = 11,
		PlayerMovement = 12,
		Vehicle_Detailed = 13,
		Game_Trace = 14,
		Vehicle_World = 15,
		World = 16,
		Player_Server = 17,
		Trigger = 18,
		Player_Model_Rendering = 19,
		Physics_Projectile = 20,
		Construction = 21,
		Construction_Socket = 22,
		Terrain = 23,
		Transparent = 24,
		Clutter = 25,
		Debris = 26,
		Vehicle_Large = 27,
		Prevent_Movement = 28,
		Prevent_Building = 29,
		Tree = 30,
		Unused2 = 31
	};
	namespace classes {
		enum class HitTestType
		{
			Generic = 0,
			ProjectileEffect = 1,
			Projectile = 2,
			MeleeAttack = 3,
			Use = 4,
		};
		class string {
		public:
			char zpad[0x10];

			int size;
			wchar_t str[128 + 1];
			string(const wchar_t* st) {
				size = min(m_wcslen((wchar_t*)st), 128);
				for (int i = 0; i < size; i++) {
					str[i] = st[i];
				}
				str[size] = 0;
			}
		};
		class Rect {
		public:
			float x; // 0x10
			float y; // 0x14
			float wid; // 0x18
			float hei; // 0x1C
			Rect(float x, float y/*top left*/, float x_rightsize, float y_downsize) {
				this->x = x;
				this->y = y;
				wid = x_rightsize;
				hei = y_downsize;
			}
			Rect() {
				this->x = 0;
				this->y = 0;
				wid = 0;
				hei = 0;
			}
			bool Contains(Vector2 point)
			{
				return point.x >= x && point.x < (x + wid) && point.y >= y && point.y < (y + hei);
			}
		};
		class list {
		public:
			template <typename T>
			T get_value() {
				auto list = *reinterpret_cast<uintptr_t*>(this + 0x10);
				if (!list)
					return 0;

				auto value = *reinterpret_cast<T*>(list + 0x28);
				if (!value)
					return 0;
				return value;
			}

			template <typename T>
			T get_buffer() {
				auto value = get_value<uintptr_t>();

				return *reinterpret_cast<uintptr_t*>(value + 0x18);
			}
		};
	}
}
class col {
public:
	float r;
	float g;
	float b;
	float a;
	col(float rr, float gg, float bb, float aa) {
		r = rr;
		g = gg;
		b = bb;
		a = aa;
	}
};

//static auto get_components_in_children = reinterpret_cast<uintptr_t(*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::_method(("Component"), ("GetComponentsInChildren"), 0, (""), ("UnityEngine"))));
//void init_bp() {
//	get_components_in_children = reinterpret_cast<uintptr_t(*)(uintptr_t, uintptr_t)>(*reinterpret_cast<uintptr_t*>(il2cpp::_method(("Component"), ("GetComponentsInChildren"), 0, (""), ("UnityEngine"))));
//}
uintptr_t bundle;
uintptr_t galaxy_bundle;
uintptr_t bundle_font;
uintptr_t chams_shader_normal;
uintptr_t chams_shader_seethru;
uintptr_t chams_shader_wireframe;
uintptr_t chams_shader_lit;
uintptr_t font_ptr;
uintptr_t galaxy_material;
//
//uintptr_t GetType(const char* space, const char* name) {
//	return il2cpp::type_object(space, name);
//}
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

#define STATIC_FUNCTION(method_path,name,ta) static inline UnmanagedPointer<ta> name = { METHOD(method_path), UnmanagedStdcall }

class Transform {
public:
	Vector3 position() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_position(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(Transform*)>(off)(this);
	}

	Vector3 InverseTransformPoint(Vector3 position) {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::InverseTransformPoint(Vector3): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(Transform*, Vector3)>(off)(this, position);
	}

	Vector3 InverseTransformDirection(Vector3 position) {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::InverseTransformDirection(Vector3): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(Transform*, Vector3)>(off)(this, position);
	}

	Vector3 up() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_up(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(Transform*)>(off)(this);
	}
	void set_position(Vector3 value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::set_position(Vector3): Void");
		reinterpret_cast<void(__fastcall*)(Transform*, Vector3)>(off)(this, value);
	}

	void set_localPosition(Vector3 value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::set_localPosition(Vector3): Void");
		reinterpret_cast<void(__fastcall*)(Transform*, Vector3)>(off)(this, value);
	}

	void set_scale(Vector3 value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::set_localScale(Vector3): Void");
		reinterpret_cast<void(__fastcall*)(Transform*, Vector3)>(off)(this, value);
	}
};
class BasePlayer;
BasePlayer* target_player = nullptr;

class Type {
public:
	static Type* GetType(const char* qualified_name) {
		static auto off = METHOD("mscorlib::System::Type::GetType(String): Type");
		return reinterpret_cast<Type * (__cdecl*)(il2cpp::String*)>(off)(il2cpp::String::New(qualified_name));
	}
	static Type* SkinnedMeshRenderer() {
		Type* type = GetType(
			
			
			
			
			
			("UnityEngine.SkinnedMeshRenderer, UnityEngine.CoreModule"));
		return type;
	}
	static Type* Renderer() {
		Type* type = GetType(("UnityEngine.Renderer, UnityEngine.CoreModule"));
		return type;
	}
	static Type* Shader() {
		Type* type = GetType(("UnityEngine.Shader, UnityEngine.CoreModule"));
		return type;
	}
	static Type* Projectile() {
		Type* type = GetType(("Projectile, Assembly-CSharp"));
		return type;
	}
	static Type* ItemModProjectile() {
		Type* type = GetType(("ItemModProjectile, Assembly-CSharp"));
		return type;
	}
};

class _LocalPlayer {
public:
	static BasePlayer* _Entity() {
		static auto clazz = CLASS("Assembly-CSharp::LocalPlayer");
		return *reinterpret_cast<BasePlayer**>(std::uint64_t(clazz->static_fields));
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
		return reinterpret_cast<T * (__fastcall*)(GameObject*, Type*)>(off)(this, type);
	}
};
class Object {
public:
	Transform* transform() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_transform(): Transform");
		return reinterpret_cast<Transform * (__fastcall*)(Object*)>(off)(this);
	}
	auto name() -> pUncStr
	{
		//	METHOD(String * (**)(Object*), get_name);
		//	return get_name(this);
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Object::get_name(): String");
		return reinterpret_cast<pUncStr(__cdecl*)()>(off)();
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
	uint32_t _class_name_hash() {
		if (!this) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		const char* name = *reinterpret_cast<char**>(oc + 0x10);
		return RUNTIME_CRC32(name);
	}

};
class Transform;
class Bone {
public:
	Vector3 position;
	bool visible;
	Transform* transform;
	Bone() {
		this->position = Vector3::Zero();
		this->visible = false;
	}
	Bone(Vector3 position, bool visible) {
		this->position = position;
		this->visible = visible;
		this->transform = nullptr;
	}
	Bone(Vector3 position, bool visible, Transform* traa) {
		this->position = position;
		this->visible = visible;
		this->transform = traa;
	}

};
class Model;

class BaseEntity;
class BaseNetworkable : public Component {
public:
	class EntityRealm {
	public:
		template<typename T = BaseNetworkable*> T Find(uint32_t uid) {
			static auto off = METHOD("Assembly-CSharp::EntityRealm::Find(UInt32): BaseNetworkable");
			return reinterpret_cast<T(__fastcall*)(EntityRealm*, uint32_t)>(off)(this, uid);
		}
		template<typename T = BaseNetworkable*>
		T FindClosest(uint32_t hash, BaseNetworkable* targetEnt, float dist)
		{
			T ent = nullptr;

			auto entityList = this->entityList();
			if (entityList)
			{
				for (int i = 1; i < entityList->vals->size; i++) {
					auto baseNetworkable = *reinterpret_cast<BaseNetworkable**>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
					if (!baseNetworkable) continue;
					if (!baseNetworkable->IsValid()) continue;
					if (baseNetworkable->_class_name_hash() != hash) continue;

					if (baseNetworkable->transform()->position().distance(targetEnt->transform()->position()) <= dist) {
						ent = reinterpret_cast<T>(baseNetworkable);
						break;
					}
				}
			}

			return ent;
		}
		FIELD("Assembly-CSharp::EntityRealm::entityList", entityList, ListDictionary*);
	};

	bool IsDestroyed() {
		if (!this) return true;
		static auto off = OFFSET("Assembly-CSharp::BaseNetworkable::<IsDestroyed>k__BackingField");
		return *reinterpret_cast<bool*>(this + off);
	}

	bool IsValid() {
		if (!this) return false;
		return !this->IsDestroyed();
	}

	static EntityRealm* clientEntities() {
		static auto clazz = CLASS("Assembly-CSharp::BaseNetworkable");
		return *reinterpret_cast<EntityRealm**>(std::uint64_t(clazz->static_fields));
	}
};
class Material;
class Skinnable {
public:
	FIELD("Assembly-CSharp::Skinnable::_sourceMaterials", _sourceMaterials, Array<Material*>*);
};
class ItemSkin {
public:
	FIELD("Assembly-CSharp::ItemSkin::Skinnable", _Skinnable, Skinnable*);
	FIELD("Assembly-CSharp::ItemSkin::Materials", Materials, Array<Material*>*);
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
	Vector3 PivotPoint() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BaseEntity::PivotPoint(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BaseEntity*)>(off)(this);
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
	void SendSignalBroadcast(Signal a, char* str = ("")) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::SendSignalBroadcast(Signal,String): Void");
		return reinterpret_cast<void(__fastcall*)(BaseEntity*, Signal, il2cpp::String*)>(off)(this, a, il2cpp::String::New(str));
	}
	Vector3 ClosestPoint(Vector3 p) {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BaseEntity::ClosestPoint(Vector3): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BaseEntity*, Vector3)>(off)(this, p);
	}
	float Distance(Vector3 pos) {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::Distance(Vector3): Single");
		return reinterpret_cast<float(__fastcall*)(BaseEntity*, Vector3)>(off)(this, pos);
	}
	FIELD("Assembly-CSharp::BaseEntity::model", model, Model*);
};
class RenderSettings {
public:
	enum class AmbientMode {
		Skybox,
		Trilight,
		Flat,
		Custom
	};
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientMode(Rendering.AmbientMode): Void", set_ambientMode, void(AmbientMode));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientIntensity(Single): Void", set_ambientIntensity, void(float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientLight(Color): Void", set_ambientLight, void(Color));

	//STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientSkyColor(Color): Void", set_skycolor, void(Color));
	//STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_skybox(Rendering.Material): Void", set_skybox, void(Material));
};
class Input {
public:
	STATIC_FUNCTION("UnityEngine.InputLegacyModule::UnityEngine::Input::GetKeyDown(KeyCode): Boolean", GetKeyDown, bool(KeyCode));
	STATIC_FUNCTION("UnityEngine.InputLegacyModule::UnityEngine::Input::GetKey(KeyCode): Boolean", GetKey, bool(KeyCode));
};
float GLOBAL_TIME = 0.f;
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
	FIELD("Assembly-CSharp::BaseCombatEntity::_health", health, float);
	FIELD("Assembly-CSharp::BaseCombatEntity::_maxHealth", maxHealth, float);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsHitNotification", sendsHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", sendsMeleeHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", lastNotifyFrame, int);
	FIELD("Assembly-CSharp::BaseCombatEntity::lifestate", lifestate, LifeState);

	bool IsDestroyed() {
		if (!this) return true;
		static auto off = OFFSET("Assembly-CSharp::BaseNetworkable::<IsDestroyed>k__BackingField");
		return *reinterpret_cast<bool*>(this + off);
	}


	bool is_alive() {
		if (!this) return false;
		return this->lifestate() == LifeState::Alive;
	}
};
class Phrase {
public:
	const wchar_t* english() {
		if (!this) return L"";
		static auto off = OFFSET("Rust.Localization::Phrase::english");
		return (*reinterpret_cast<il2cpp::String**>(this + off))->buffer;
	}
};

class Time {
public:
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_time(): Single", time, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_deltaTime(): Single", deltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_fixedTime(): Single", fixedTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_unscaledTime(): Single", unscaledTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_unscaledDeltaTime(): Single", unscaledDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_fixedDeltaTime(): Single", fixedDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_maximumDeltaTime(): Single", maximumDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_smoothDeltaTime(): Single", smoothDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_timeScale(): Single", timeScale, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_frameCount(): Int32", frameCount, int());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_renderedFrameCount(): Int32", renderedFrameCount, int());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_realtimeSinceStartup(): Single", realtimeSinceStartup, float());
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
class RaycastHit {
public:
	Vector3 point;
	Vector3 normal;
	RaycastHit()
	{
		point = Vector3::Zero();
		normal = Vector3::Zero();
	}
};
class Physics {
public:
	static bool RayCapsule(Vector3 ray, Vector3 xuy, RaycastHit* hitInfo, float maxDistance, int layerMask) {
		return SafeExecution::Execute<bool>(InGame::stor::gBase + 0x1B69470, false, ray, xuy, hitInfo, maxDistance, layerMask); // Raycast(Vector3 origin, Vector3 direction, out RaycastHit hitInfo, float maxDistance, int layerMask, QueryTriggerInteraction queryTriggerInteraction)
	}
	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::get_gravity(): Vector3", get_gravity, Vector3());
	static void IgnoreLayerCollision(int layer1, int layer2, bool ignore) {
		return reinterpret_cast<void(*)(int, int, bool)>(il2cpp::il2cpp_resolve_icall(("UnityEngine.Physics::IgnoreLayerCollision")))(layer1, layer2, ignore);
	}
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::CheckCapsule(Vector3,Vector3,Single,Int32,QueryTriggerInteraction): Boolean", CheckCapsule, bool(Vector3, Vector3, float, int, QueryTriggerInteraction));

	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::Raycast(Vector3,Vector3,RaycastHit&,Single,Int32,QueryTriggerInteraction): Boolean",
		Raycast,
		bool(Vector3,
			Vector3,
			RaycastHit*,
			float,
			int,
			QueryTriggerInteraction));

	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::Raycast(Ray,Single,Int32): Boolean",
		Raycast1,
		bool(Ray,
			float,
			int));
	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::SphereCast(Ray,Single,Single,Int32): Boolean",
		SphereCast,
		bool(Ray,
			float,
			float,
			int));
	//STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::LineOfSight(Vector3,Vector3,RaycastHit&,Int32): Boolean", LineOfSight, bool(Vector3, Vector3, RaycastHit*
	// , int));

};

class ItemDefinition : public Component {
public:
	FIELD("Assembly-CSharp::ItemDefinition::displayName", displayName, Phrase*);
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
class BaseMelee : public AttackEntity {
public:
	void StartAttackCooldown(float cooldown)
	{
		if (!this) return;

		static auto off = METHOD("Assembly-CSharp::AttackEntity::StartAttackCooldown(Single): Void");

		return reinterpret_cast<void(__fastcall*)(AttackEntity*, float)>(off)(this, cooldown);
	}
	//bool HasAttackCooldown()
	//{
	//	if (!this) return false;

	//	static auto off = METHOD("Assembly-CSharp::AttackEntity::HasAttackCooldown(): Boolean");

	//	return reinterpret_cast<bool(__fastcall*)(AttackEntity*)>(off)(this);
	//}
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
	FIELD("Assembly-CSharp::BaseMelee::throwReady", throwReady, bool);
	static inline void (*ProcessAttack_)(BaseMelee*, HitTest*) = nullptr;
	void ProcessAttack(HitTest* test) {
		return ProcessAttack_(this, test);
	}

};
class CompoundBowWeapon {
public:
	FIELD("Assembly-CSharp::CompoundBowWeapon::currentHoldProgress", currentHoldProgress, float);
	float GetProjectileVelocityScale(bool getmax = false) {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::CompoundBowWeapon::GetProjectileVelocityScale(Boolean): Single");
		return reinterpret_cast<float(__fastcall*)(CompoundBowWeapon*, bool)>(off)(this, getmax);
	}
};
class BaseProjectile : public AttackEntity {
public:
	class Magazine {
	public:
		FIELD("Assembly-CSharp::Magazine::ammoType", ammoType, ItemDefinition*);
		FIELD("Assembly-CSharp::Magazine::contents", contents, int);
	};
	FIELD("Assembly-CSharp::BaseProjectile::primaryMagazine", primaryMagazine, Magazine*);
	FIELD("Assembly-CSharp::BaseProjectile::projectileVelocityScale", projectileVelocityScale, float);
	FIELD("Assembly-CSharp::BaseProjectile::aimCone", aimCone, float);
	FIELD("Assembly-CSharp::BaseProjectile::hipAimCone", hipAimCone, float);
	FIELD("Assembly-CSharp::BaseProjectile::nextReloadTime", nextReloadTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::lastShotTime", lastShotTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::reloadPressTime", reloadPressTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::reloadTime", reloadTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::automatic", automatic, bool);
	FIELD("Assembly-CSharp::BaseProjectile::aimSway", aimSway, float);
	FIELD("Assembly-CSharp::BaseProjectile::aimSwaySpeed", aimSwaySpeed, float);
	FIELD("Assembly-CSharp::BowWeapon::arrowBack", arrowBack, float);
	FIELD("Assembly-CSharp::BaseProjectile::isReloading", isReloading, bool);
	static inline void (*LaunchProjectile_)(BaseProjectile*) = nullptr;
	void LaunchProjectile() {
		return LaunchProjectile_(this);
	}
	void DoAttack()
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::DoAttack(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	//void LaunchProjectile()
	//{
	//	if (!this) return;
	//	static auto off = METHOD("Assembly-CSharp::BaseProjectile::LaunchProjectile(): Void");
	//	return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	//}
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
	void SendSignalBroadcast(Signal a, char* str = ("")) {
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

class TOD_AtmosphereParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_AtmosphereParameters::RayleighMultiplier", RayleighMultiplier, float);
	FIELD("Assembly-CSharp-firstpass::TOD_AtmosphereParameters::Fogginess", Fogginess, float);
};

class TOD_NightParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_NightParameters::AmbientMultiplier", AmbientMultiplier, float);
};
class TOD_SunParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_SunParameters::MeshSize", MeshSize, float);
	FIELD("Assembly-CSharp-firstpass::TOD_SunParameters::MeshBrightness", MeshBrightness, float);
	FIELD("Assembly-CSharp-firstpass::TOD_SunParameters::MeshContrast", MeshContrast, float);
};
class TOD_StarParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_StarParameters::Size", Size, float);
	FIELD("Assembly-CSharp-firstpass::TOD_StarParameters::Brightness", Brightness, float);
};
enum TOD_FogType {
	None = 0,
	Atmosphere = 1,
	Directional = 2,
	//Gradient = 3
};
class TOD_FogParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_FogParameters::Mode", Mode, TOD_FogType);
	FIELD("Assembly-CSharp-firstpass::TOD_FogParameters::HeightBias", HeightBias, float);
};
class TOD_CloudParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_CloudParameters::Size", Size, float);
	FIELD("Assembly-CSharp-firstpass::TOD_CloudParameters::Opacity", Opacity, float);
	FIELD("Assembly-CSharp-firstpass::TOD_CloudParameters::Coverage", Coverage, float);
	FIELD("Assembly-CSharp-firstpass::TOD_CloudParameters::Brightness", Brightness, float);
};
class TOD_DayParameters {
public:
	//FIELD("Assembly-CSharp-firstpass::TOD_DayParameters::", AmbientColor, );

	FIELD("Assembly-CSharp-firstpass::TOD_DayParameters::AmbientMultiplier", AmbientMultiplier, float);
	FIELD("Assembly-CSharp-firstpass::TOD_DayParameters::ReflectionMultiplier", ReflectionMultiplier, float);
};
class TOD_CycleParameters {
public:
	FIELD("Assembly-CSharp-firstpass::TOD_CycleParameters::Hour", Hour, float);
};
class TOD_Sky {
public:
	static List<TOD_Sky*>* instances() {
		static auto clazz = CLASS("Assembly-CSharp-firstpass::TOD_Sky");
		return *reinterpret_cast<List<TOD_Sky*>**>(std::uint64_t(clazz->static_fields));
	}

	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Atmosphere", Atmosphere, TOD_AtmosphereParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Night", Night, TOD_NightParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Sun", Sun, TOD_SunParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Day", Day, TOD_DayParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Cycle", Cycle, TOD_CycleParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Stars", Stars, TOD_StarParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Clouds", Clouds, TOD_CloudParameters*);
	FIELD("Assembly-CSharp-firstpass::TOD_Sky::Fog", Fog, TOD_FogParameters*);

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
class AimConeUtil {
public:
	static inline Vector3(*GetModifiedAimConeDirection_)(float, Vector3, bool) = nullptr;
	static Vector3 GetModifiedAimConeDirection(float aimCone, Vector3 inputVec, bool anywhereInside = true) {
		return GetModifiedAimConeDirection_(aimCone, inputVec, anywhereInside);
	}
};

class PlayerWalkMovement {
public:
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
	FIELD("Assembly-CSharp::PlayerWalkMovement::capsule", capsule, CapsuleCollider*);

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

	void Jump(ModelState* state)
	{
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::PlayerWalkMovement::Jump(ModelState,Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(PlayerWalkMovement*, ModelState*, bool)>(off)(this, state, false);
	}
	uintptr_t pasta1() {

		static UINT_PTR Capusle = 0x402402;

		if (Capusle == 0x402402)
		{
			Capusle = 0xA0;// public class PlayerWalkMovement || capsule
		}

		return *(uintptr_t*)(this + Capusle);

		return 0;
	}
	void SPC(float Obema) {

		static UINT_PTR var = 0x402402;

		if (var == 0x402402)
		{
			var = 0x1B64BA0;
		}

		typedef void Capusle(uintptr_t, float);
		((Capusle*)(InGame::stor::gBase + var))(pasta1(), Obema);
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
	FIELD("Rust.Data::InputMessage::ShouldPool", ShouldPool, bool);
	FIELD("Rust.Data::InputMessage::_disposed", _disposed, bool);
};
enum Button {
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
		static auto off = METHOD("Assembly-CSharp::BaseVehicleMountPoint::VehicleParent(): BaseVehicle");
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
class BaseViewModel {
public:
	FIELD("Assembly-CSharp::BaseViewModel::sway", sway, ViewmodelSway*);
	FIELD("Assembly-CSharp::BaseViewModel::lower", lower, ViewmodelLower*);
	FIELD("Assembly-CSharp::BaseViewModel::bob", bob, ViewmodelBob*);
	FIELD("Assembly-CSharp::BaseViewModel::animator", animator, Animator*);
	static auto ActiveModel() -> BaseViewModel* {
		static auto off = METHOD("Assembly-CSharp::BaseViewModel::get_ActiveModel(): BaseViewModel");
		return reinterpret_cast<BaseViewModel * (__fastcall*)()>(off)();
	}
};
class Renderer_ {
public:
	Material* material() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_material(): Material");
		return reinterpret_cast<Material * (__fastcall*)(Renderer_*)>(off)(this);
	}
	void set_material(Material* value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::set_material(Material): Void");
		return reinterpret_cast<void(__fastcall*)(Renderer_*, Material*)>(off)(this, value);
	}
	bool isVisible() {
		if (!this) return false;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_isVisible(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Renderer_*)>(off)(this);
	}
	Array<Material*>* materials() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_materials(): Material[]");
		return reinterpret_cast<Array<Material*>*(__fastcall*)(Renderer_*)>(off)(this);
	}
};
class PlayerNameID {
public:
	wchar_t* username() {
		auto username = (pUncStr)(*reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x18));
		return username->str;
	}

	unsigned long user_id() {
		return *reinterpret_cast<unsigned long*>((uintptr_t)this + 0x20);
	}
};
class Shader : public Object {
public:
	static Shader* Find(char* name) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Shader::Find(String): Shader");
		return reinterpret_cast<Shader * (__fastcall*)(il2cpp::String*)>(off)(il2cpp::String::New(name));
	}
	static int PropertyToID(char* name) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Shader::PropertyToID(String): Int32");
		return reinterpret_cast<int(__fastcall*)(il2cpp::String*)>(off)(il2cpp::String::New(name));
	}
};

class Material {
public:

	/*void SetColor(int proper, Color value) {
			if (!this) return;
			static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetColor(Int32,Color): Void");
			return reinterpret_cast<void(__fastcall*)(Material*, int, Color)>(off)(this, proper, value);
		}*/
	void SetColor(char* proper, Color value) {
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

};
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
class ItemModProjectile {
public:
	static inline float(*GetRandomVelocity_)(ItemModProjectile*) = nullptr;

	float GetRandomVelocity() {
		return GetRandomVelocity_(this);
	}
	FIELD("Assembly-CSharp::ItemModProjectile::numProjectiles", numProjectiles, int);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileVelocity", projectileVelocity, float);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileSpread", projectileSpread, float);
	FIELD("Assembly-CSharp::ItemModProjectile::ammoType", ammoType, int);
	FIELD("Assembly-CSharp::ItemModProjectile::projectileVelocitySpread", projectileVelocitySpread, float);

	FIELD("Assembly-CSharp::ItemModProjectile::projectileObject", projectileObject, ResourceRef<GameObject>*);
};
class PlayerModel;
class SkinnedMultiMesh {
public:
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
	Vector3 position() {
		if (!this) return Vector3::Zero();
		static auto off = OFFSET("Assembly-CSharp::PlayerModel::position");
		return *reinterpret_cast<Vector3*>(this + off);
	}
	FIELD("Assembly-CSharp::PlayerModel::isLocalPlayer", isLocalPlayer, bool);
	FIELD("Assembly-CSharp::PlayerModel::_multiMesh", _multiMesh, SkinnedMultiMesh*);
};
class PlayerEyes : public Component {
public:
	FIELD("Assembly-CSharp::PlayerEyes::viewOffset", viewOffset, Vector3);
	Quaternion get_rotation() {
		if (!this) return Quaternion{};
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_rotation(): Quaternion");
		return reinterpret_cast<Quaternion(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 get_position() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_position(): Vector3");
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
class Camera {
public:

	static uintptr_t MainCamera() {
		return reinterpret_cast<uintptr_t(*)()>(il2cpp::il2cpp_resolve_icall(("UnityEngine.Camera::get_main()")))();
	}
	static void SetAspect(float act) {
		return reinterpret_cast<void(*)(uintptr_t, float)>(il2cpp::il2cpp_resolve_icall(("UnityEngine.Camera::set_aspect()")))(MainCamera(), act);
	}
};
class PlayerTick {
public:
	FIELD("Rust.Data::PlayerTick::position", __position, Vector3);
	FIELD("Rust.Data::PlayerTick::position", position, Vector3);
};
class ConsoleOptions {
public:
	bool IsFromServer() { return read(this + 0x6, bool); }
};
class Item {
public:
	FIELD("Assembly-CSharp::Item::uid", uid, uint32_t);
	FIELD("Assembly-CSharp::Item::amount", amount, int);
	FIELD("Assembly-CSharp::Item::info", info, ItemDefinition*);
	uintptr_t entity() {
		return read(this + 0x98, uintptr_t); // private EntityRef heldEntity;
	}
	template<typename T = void*>
	T* heldEntity() {
		if (!this) return nullptr;
		static auto off = OFFSET("Assembly-CSharp::Item::heldEntity");
		return *reinterpret_cast<T**>(this + off);
	}
	Weapon Info() {
		int ID = GetID();
		for (Weapon k : iinfo) {
			if (k.id == ID) {
				return k;
			}
		}
		return Weapon{ 0 };
	}
	int LoadedAmmo() {
		uintptr_t Held = this->entity();
		if (!Held) return 0;

		uintptr_t Magazine = read(Held + 0x2a0, uintptr_t);
		if (!Magazine) return 0;

		uintptr_t ammoType = read(Magazine + 0x20, uintptr_t); //public ItemDefinition ammoType;
		if (!ammoType) return 0;

		int ammo = read(ammoType + 0x18, int);
		return ammo;
	}
	int GetID() {
		DWORD64 Info = read((DWORD64)this + 0x20, DWORD64); // public ItemDefinition info;
		int ID = read(Info + 0x18, int); // public int itemid; //ItemDefinition
		return ID;
	}
};
class PlayerProjectileUpdate {
public:
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::projectileID", projectileID, int);
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::curPosition", curPosition, Vector3);
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::curVelocity", curVelocity, Vector3);
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileUpdate::travelTime", travelTime, float);
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

Shader* chamsShader;
Shader* GalaxyMaterial;
class Random
{
public:
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Random::Range(Single,Single): Single", Range, float(float, float));
};

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
	const wchar_t* _displayName() {
		if (!this) return L"";
		static auto off = OFFSET("Assembly-CSharp::BasePlayer::_displayName");
		return (*reinterpret_cast<il2cpp::String**>(this + off))->buffer;
	}
	FIELD("Assembly-CSharp::BasePlayer::playerModel", _playerModel, PlayerModel*);
	FIELD("Assembly-CSharp::BasePlayer::userID", userID, uint64_t);
	FIELD("Assembly-CSharp::BasePlayer::eyes", eyes, PlayerEyes*);
	FIELD("Assembly-CSharp::BasePlayer::mounted", mounted, BaseMountable*);
	FIELD("Assembly-CSharp::BasePlayer::clientTickInterval", clientTickInterval, float);
	FIELD("Assembly-CSharp::BasePlayer::movement", movement, PlayerWalkMovement*);
	FIELD("Assembly-CSharp::BasePlayer::playerFlags", playerFlags, int);
	FIELD("Assembly-CSharp::BasePlayer::inventory", inventory, PlayerInventory*);
	FIELD("Assembly-CSharp::BasePlayer::clActiveItem", clActiveItem, uint32_t);
	FIELD("Assembly-CSharp::BasePlayer::lastSentTick", lastSentTick, PlayerTick*);
	FIELD("Assembly-CSharp::BasePlayer::modelState", modelState, ModelState*);
	FIELD("Assembly-CSharp::BasePlayer::clientTeam", clientTeam, PlayerTeam*);
	FIELD("Assembly-CSharp::BasePlayer::lastSentTickTime", lastSentTickTime, float);
	FIELD("Assembly-CSharp::Model::boneTransforms", boneTransforms, Array<Transform*>*);
	FIELD("Assembly-CSharp::Model::boneNames", boneNames, Array<il2cpp::String*>*);
	void unloadadm() {
		int Flags = playerFlags();
		playerFlags() = (Flags == 4);
	}
	Vector3 GetBoneByID(BoneList bone) {
		uintptr_t player_model = read(this + 0x118, uintptr_t);// public Model model
		uintptr_t boneTransforms = read(player_model + 0x48, uintptr_t);//public Transform[] boneTransforms;
		Transform* transform = read(boneTransforms + 0x20 + bone * 0x8, Transform*); //0x10 // 0x68 // 0x78 //
		//const Transform* transform = read(BoneValue + 0x10, Transform*);

		if (!transform)
			return Vector3::Zero();
		return transform->position();
	}
	Vector3 get_bone_pos(BoneList bone) {
		uintptr_t player_model = read(this + 0x118, uintptr_t);// public Model model
		uintptr_t boneTransforms = read(player_model + 0x48, uintptr_t);//public Transform[] boneTransforms;
		Transform* transform = read(boneTransforms + 0x20 + bone * 0x8, Transform*);
		if (!transform)
			return Vector3::Zero();
		return transform->position();
	}
	Transform* transform_(BoneList bone) {
		uintptr_t player_model = read(this + 0x118, uintptr_t);// public Model model
		uintptr_t boneTransforms = read(player_model + 0x48, uintptr_t);//public Transform[] boneTransforms;
		Transform* transform = read(boneTransforms + 0x20 + bone * 0x8, Transform*);
		return transform;
	}
	Item* GetWeaponInfo(int Id) {
		DWORD64 Inventory = read(this + 0x608, DWORD64);
		DWORD64 Belt = read(Inventory + 0x28, DWORD64); // containerBelt
		DWORD64 ItemList = read(Belt + 0x38, DWORD64);// public List<Item> itemList;
		DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (Item*)read(Items + 0x20 + (Id * 0x8), DWORD64);
	}
	Item* GetActiveWeapon() {
		int ActUID = read(this + 0x570, int);
		if (!ActUID) return nullptr;
		Item* ActiveWeapon;
		for (int i = 0; i < 6; i++)
			if (ActUID == (ActiveWeapon = GetWeaponInfo(i))->uid())
				return ActiveWeapon;
		return nullptr;
	}
	bool has_modelstate_flag(ModelStateFlag flag) {
		DWORD64 mstate = read(this + 0x588, DWORD64);
		int flags = read(mstate + 0x24, int);
		return flags & (int)flag;
	}
	Vector3 newVelocity() {
		DWORD64 PlayerModel = read(this + 0x4a8, DWORD64);
		return read(PlayerModel + 0x1fc, Vector3);
	}

	//bool is_teammate(uintptr_t BasePlayer) {
	//	//  0x5A0
	//	if (!this) return false;
	//	auto TeamId = *(int*)(BasePlayer + 0x630);
	//	auto LocalTeamId = *(int*)(this + 0x630);

	//	if (LocalTeamId == 0) return false;
	//	if (target_player != nullptr) {
	//		if (TeamId == LocalTeamId) return true;
	//	}

	//	return false;
	//}
	bool is_teammate(uintptr_t BasePlayer) {
		//  0x5A0
		if (!this) return false;
		auto TeamId = *(int*)(BasePlayer + 0x598);
		auto LocalTeamId = *(int*)(this + 0x598);

		if (LocalTeamId == 0) return false;
		if (target_player != nullptr) {
			if (TeamId == LocalTeamId) return true;
		}

		return false;
	}
	bool get_flag(int Flg) {
		return (read(this + 0x5f8, int) & Flg);
	}
	bool is_target() {
		if (!target_player)
			return false;

		if (!this)
			return false;

		return this->userID() == target_player->userID();
	}
	bool IsDucked() { // lad don't fancy calling functions in a non-game thread, eh, thy lad shall recreate it.
		if (!this) return false;

		if (this->movement() != nullptr)
			return this->movement()->Ducking() > 0.5f;

		return this->modelState() != nullptr && this->modelState()->flags() & 1;
	}
	void add_modelstate_flag(ModelStateFlag flag) {
		int flags = this->modelState()->flags();
		this->modelState()->flags() = flags |= (int)flag;
	}
	void remove_modelstate_flag(ModelStateFlag flag) {
		int flags = this->modelState()->flags();
		this->modelState()->flags() = flags &= (int)flag;
	}
	bool get_flagMS(int flag) {
		if (!this) return false;

		return (this->modelState()->flags() & flag) == flag;
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
	float GetHeight(bool ducked) {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetHeight(Boolean): Single");
		return reinterpret_cast<float(__fastcall*)(BasePlayer*, bool)>(off)(this, ducked);
	}
	float GetJumpHeight() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetJumpHeight(): Single");
		return reinterpret_cast<float(__fastcall*)(BasePlayer*)>(off)(this);
	}
	float GetMaxSpeed() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetMaxSpeed(): Single");
		return reinterpret_cast<float(__fastcall*)(BasePlayer*)>(off)(this);
	}
	float MaxVelocity() {
		if (!this) return 0.f;
		if (this->mounted()) return this->GetMaxSpeed() * 4;
		return this->GetMaxSpeed();
	}

	static float& Admintime() {
		static auto clazz = CLASS("Assembly-CSharp::ConVar::Admin");
		return *reinterpret_cast<float*>(std::uint64_t(clazz->static_fields) + 0x0);
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
	bool in_minicopter() {
		if (!this)
			return false;

		if (!this->mounted())
			return false;

		if (this->mounted()->GetVehicleParent()->_class_name_hash() == STATIC_CRC32("MiniCopter")) {
			return true;
		}

		return false;
	}
	bool teamete(BasePlayer* BasePlayer) {
		//  0x5A0
		auto TeamId = *(int*)(BasePlayer + 0x598);
		auto LocalTeamId = *(int*)(this + 0x598);

		if (LocalTeamId == 0) return false;
		if (TeamId == LocalTeamId) return true;

		return false;
	}
	bool HasPlayerFlag(PlayerFlags flag) {
		if (!this) return false;

		return (playerFlags() & flag) == flag;
	}

	void SPU(PlayerProjectileUpdate* a1) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::SendProjectileUpdate(PlayerProjectileUpdate): Void");
		return reinterpret_cast<void(__fastcall*)(BasePlayer*, PlayerProjectileUpdate*)>(off)(this, a1);
	}
	bool IsNpc() {
		DWORD64 PlayerModel = read(this + 0x4a8, DWORD64);
		return read(PlayerModel + 0x2c0, bool); //private bool <IsNpc>k__BackingField;
	}
	void SendProjectileUpdate(uintptr_t update)
	{
		typedef float(__stdcall* spu)(uintptr_t, uintptr_t);
		((spu)(InGame::stor::gBase + 0x98E740))((uintptr_t)this, update);
	}
	bool IsDead() {
		if (!this)
			return 0;
		const auto life_state = Read<uint32_t>((uintptr_t)this + 0x204);
		return life_state == 0;
	}
	FIELD("Assembly-CSharp::BasePlayer::playerModel", playerModel, PlayerModel*);
	void Chams()
	{
		if (!this) return;
		if (this->health() <= 5.0f || this->lifestate() == BaseCombatEntity::LifeState::Dead) return;

		if (!this->playerModel()) return;
		if (!this->playerModel()->_multiMesh()) return;
		if (!this->playerModel()->_multiMesh()->Renderers()) return;

		List<Renderer_*>* renderers = this->playerModel()->_multiMesh()->Renderers();


		for (int i = 0; i < renderers->size; i++)
		{
			Renderer_* renderer = reinterpret_cast<Renderer_*>(renderers->get(i));
			if (!renderer) continue;
			if (!renderer->material()) continue;

			auto material = renderer->material();

			auto shader = material->shader();

			if (material)
			{

				if (!chamsShader)
					chamsShader = Shader::Find(("Hidden/Internal-Colored"));

				material->SetInt((char*)"_ZTest", 8);
				Color visible = Color::red();

				material->SetColor((char*)"_Color", visible);
				static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::set_shader(Shader): Void");
				if (off) {
					//	material->set_shader(chamsShader, off);
				}
			}

		}

	}
};
class LocalPlayer {
public:
	static BasePlayer* Entity() {
		static auto clazz = CLASS("Assembly-CSharp::LocalPlayer");
		return *reinterpret_cast<BasePlayer**>(std::uint64_t(clazz->static_fields));
	}
};
class Local_Player {
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
class PlayerProjectileAttack_ {
public:
	FIELD("Rust.Data::ProtoBuf::PlayerProjectileAttack::playerAttack", playerAttack, PlayerAttack*);
};

class Networkable {
public:
	unsigned int get_id() {
		return *reinterpret_cast<unsigned int*>((uintptr_t)this + 0x10);
	}
};

class Mathf {
public:

	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::FloorToInt(Single): Int32", FloorToInt, int(float));

	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Max(Single,Single): Single", Max, float(float, float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Mathf::Abs(Single): Single", Abs, float(float));

	static float Clamp(float value, float min, float max) {
		return reinterpret_cast<float(_fastcall*)(float, float, float)>(InGame::stor::gBase + 0x136BE10)(value, min, max);
	}

	static float Min(float a, float b) {
		return reinterpret_cast<float(_fastcall*)(float, float)>(InGame::stor::gBase + 0x136c680)(a, b);
	}
};

class Mathx {
public:
	static float Decrement(float f) {
		return reinterpret_cast<float(_fastcall*)(float)>(InGame::stor::gBase + 0x18803D0)(f);
	}
	static float Increment(float f) {
		return reinterpret_cast<float(_fastcall*)(float)>(InGame::stor::gBase + 0x18804D0)(f);
	}
	static float Max(float f1, float f2, float f3) {
		return reinterpret_cast<float(_fastcall*)(float, float, float)>(InGame::stor::gBase + 0x1880820)(f1, f2, f3);
	}
};

class Vector3_ {
public:
	static inline Vector3(*MoveTowards_)(Vector3, Vector3, float) = nullptr;

	static Vector3 MoveTowards(Vector3 current, Vector3 target, float maxDistanceDelta) {
		return MoveTowards_(current, target, maxDistanceDelta);
	}
};
class FlintStrikeWeapon : public BaseProjectile {
public:
	FIELD("Assembly-CSharp::FlintStrikeWeapon::successFraction", successFraction, float);
	FIELD("Assembly-CSharp::FlintStrikeWeapon::_didSparkThisFrame", _didSparkThisFrame, bool);

	static inline void(*DoAttack_)(FlintStrikeWeapon*) = nullptr;
	void DoAttack() {
		return DoAttack_(this);
	}
};

class DDraw {
public:
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Line(Vector3,Vector3,Color,Single,Boolean,Boolean): Void", Line, void(Vector3, Vector3, Color, float, bool, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Sphere(Vector3,Single,Color,Single,Boolean): Void", Sphere, void(Vector3, float, Color, float, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::SphereGizmo(Vector3,Single,Color,Single,Boolean,Boolean): Void", SphereGizmoZV, void(Vector3, float, Color, float, bool, bool));
	//STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Text(String,Vector3,Color,Single): Void", Text, void(il2cpp::String*, Vector3, Color, float));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Arrow(Vector3,Vector3,Single,Color,Single): Void", Arrow, void(Vector3, Vector3, float, Color, float));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Capsule(Vector3,Quaternion,Single,Single,Color,Single,Boolean): Void", Capsule, void(Vector3, Quaternion, float, float, Color, float, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Box(Vector3,Single,Color,Single,Boolean): Void", Box, void(Vector3, float, Color, float, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Get(): DDraw", Get, DDraw* ());
	static inline void(*OnGUI_)(DDraw*) = nullptr;
	void OnGUI() {
		return OnGUI_(this);
	}
};
void Circle3D(Vector3 pos, Color clr, float radius, float penis = 0) {
	Vector3 prev = Vector3(pos.x + radius, pos.y, pos.z);
	for (float num = 0.f; num < 6.2831855f; num += 0.05f) {

		float val_x = cos(num) * radius;
		float val_z = sin(num) * radius;
		Vector3 newPos = Vector3(pos.x + val_x, pos.y + penis, pos.z + val_z);

		DDraw::Line(prev, newPos, clr, 0.01, false, true);

		prev = newPos;
	}
}
class AssetBundle {
public:
	Array<il2cpp::String*>* GetAllAssetNames() {
		if (!this) return {};
		static auto off = METHOD("UnityEngine.AssetBundleModule::UnityEngine::AssetBundle::GetAllAssetNames(): String[]");
		return reinterpret_cast<Array<il2cpp::String*>*(*)(AssetBundle*)>(off)(this);
	}
	template<typename T = Object>
	T* LoadAsset(char* name, Type* type) {
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
	static HitTest* New()
	{
		HitTest* hitTest = il2cpp::il2cpp_object_new_<HitTest*>(CLASS("Assembly-CSharp::HitTest"));

		return hitTest;
	}
	//static HitTest* New() {
	//	static auto clazz = CLASS("Assembly-CSharp::HitTest");
	//	return *reinterpret_cast<HitTest**>(std::uint64_t(clazz->static_fields));
	//}
	FIELD("Assembly-CSharp::HitTest::type", type, Type);
	FIELD("Assembly-CSharp::HitTest::HitEntity", _HitEntity, BaseNetworkable*);

	FIELD("Assembly-CSharp::HitTest::Radius", Radius, float);
	FIELD("Assembly-CSharp::HitTest::Forgiveness", Forgiveness, float);
	FIELD("Assembly-CSharp::HitTest::MaxDistance", MaxDistance, float);
	FIELD("Assembly-CSharp::HitTest::MultiHit", MultiHit, bool);
	FIELD("Assembly-CSharp::HitTest::BestHit", BestHit, bool);
	FIELD("Assembly-CSharp::HitTest::AttackRay", AttackRay, Ray);
	FIELD("Assembly-CSharp::HitTest::DidHit", DidHit, bool);
	FIELD("Assembly-CSharp::HitTest::gameObject", gameObject_, GameObject*);
	FIELD("Assembly-CSharp::HitTest::ignoreEntity", ignoreEntity, BaseEntity*);
	FIELD("Assembly-CSharp::HitTest::HitEntity", HitEntity, BaseEntity*);
	FIELD("Assembly-CSharp::HitTest::HitEntity", HitEntity_, BaseNetworkable*);

	FIELD("Assembly-CSharp::HitTest::HitPoint", HitPoint, Vector3);
	FIELD("Assembly-CSharp::HitTest::HitNormal", HitNormal, Vector3);
	FIELD("Assembly-CSharp::HitTest::HitDistance", HitDistance, float);
	FIELD("Assembly-CSharp::HitTest::HitTransform", HitTransform, Transform*);
	FIELD("Assembly-CSharp::HitTest::HitPart", HitPart, uint32_t);
	FIELD("Assembly-CSharp::HitTest::HitMaterial", HitMaterial, uint32_t);
	FIELD("Assembly-CSharp::HitTest::HitMaterial", HitMaterial_, il2cpp::String*);
	FIELD("Assembly-CSharp::HitTest::damageProperties", damageProperties, uintptr_t);

	Vector3 HitPointWorld() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::HitTest::HitPointWorld(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(HitTest*)>(off)(this);
	}

	Vector3 HitNormalWorld() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::HitTest::HitNormalWorld(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(HitTest*)>(off)(this);
	}


	static inline Attack* (*BuildAttackMessage_)(HitTest*) = nullptr;
	Attack* _BuildAttackMessage() {
		return BuildAttackMessage_(this);
	}
	Attack* BuildAttackMessage() {
		return BuildAttackMessage_(this);
	}
};
class CursorManager {
public:
	FIELD("Assembly-CSharp::CursorManager::iHoldOpen", iHoldOpen, int);
	FIELD("Assembly-CSharp::CursorManager::iPreviousOpen", iPreviousOpen, int);
	static inline void (*Update_)(CursorManager*, bool) = nullptr;
	void Update(bool op) {
		return Update_(this, op);
	}
};
class Projectile {
public:
	FIELD("Assembly-CSharp::ItemModProjectile::ammoType", ammoType, int);
	FIELD("Assembly-CSharp::Projectile::integrity", _integrity, float);
	FIELD("Assembly-CSharp::Projectile::initialDistance", _initialDistance, float);
	FIELD("Assembly-CSharp::Projectile::projectileID", _projectileID, int);
	FIELD("Assembly-CSharp::Projectile::penetrationPower", penetrationPower, float);
	FIELD("Assembly-CSharp::Projectile::swimRandom", swimRandom, float);
	FIELD("Assembly-CSharp::Projectile::swimScale", swimScale, Vector3);
	FIELD("Assembly-CSharp::Projectile::tumbleAxis", tumbleAxis, Vector3);
	FIELD("Assembly-CSharp::Projectile::tumbleSpeed", tumbleSpeed, float);
	FIELD("Assembly-CSharp::Projectile::traveledTime", traveledTime, float);
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
	FIELD("Assembly-CSharp::Projectile::damageProperties", damageProperties, uintptr_t);
	void currVel(Vector3 a) { write(this + 0x118, a, Vector3); }
	void currPos(Vector3 a) { write(this + 0x124, a, Vector3); }
	Transform* transform() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_transform(): Transform");
		return reinterpret_cast<Transform * (__fastcall*)(Projectile*)>(off)(this);
	}
	static inline void(*SetEffectScale_)(Projectile*, float) = nullptr;
	void SetEffectScale(float sca) {
		return SetEffectScale_(this, sca);
	}
	static inline void(*DoMovement_)(Projectile*, float) = nullptr;
	void DoMovement(float deltaTime) {
		return DoMovement_(this, deltaTime);
	}
	bool DoHit(HitTest* test, Vector3 point, Vector3 normal) {
		static auto off = METHOD("Assembly-CSharp::Projectile::DoHit(HitTest,Vector3,Vector3): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Projectile*, HitTest*, Vector3, Vector3)>(off)(this, test, point, normal);
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
	void UpdateVelocity(float delta) {
		static auto off = METHOD("Assembly-CSharp::Projectile::UpdateVelocity(Single): Void");
		return reinterpret_cast<void(__fastcall*)(Projectile*, float)>(off)(this, delta);
	}
	void Update() {
		static auto off = METHOD("Assembly-CSharp::Projectile::Update(): Void");
		return reinterpret_cast<void(__fastcall*)(Projectile*)>(off)(this);
	}
};

class WaterLevel {
public:
	STATIC_FUNCTION("Assembly-CSharp::WaterLevel::Test(Vector3,Boolean,BaseEntity): Boolean", Test, bool(Vector3, bool, BaseEntity*));
};
class GamePhysics {
public:
	enum class QueryTriggerInteraction {
		UseGlobal = 0,
		Ignore = 1,
		Collide = 2,
	};

	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::LineOfSight(Vector3,Vector3,Int32,Single): Boolean", LineOfSight_, bool(Vector3, Vector3, int, float));
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::LineOfSight(Vector3,Vector3,Int32,Single): Boolean", LineOfSight, bool(Vector3, Vector3, int, float));
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::CheckCapsule(Vector3,Vector3,Single,Int32,QueryTriggerInteraction): Boolean", CheckCapsule, bool(Vector3, Vector3, float, int, QueryTriggerInteraction));
	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::Trace(Ray,Single,RaycastHit&,Single,Int32,QueryTriggerInteraction): Boolean", Trace, bool(Ray, float, RaycastHit*, float, int));
};
Matrix matrix = {};
namespace utils {

	bool w2s(Vector3 world, Vector2& screen) {
		const auto matrix = il2cpp::unity::getViewMatrix().transpose();

		const Vector3 translation = { matrix[3][0], matrix[3][1], matrix[3][2] };
		const Vector3 up = { matrix[1][0], matrix[1][1], matrix[1][2] };
		const Vector3 right = { matrix[0][0], matrix[0][1], matrix[0][2] };

		const auto w = translation.dot_product(world) + matrix[3][3];

		if (w < 0.1f)
			return false;

		const auto x = right.dot_product(world) + matrix[0][3];
		const auto y = up.dot_product(world) + matrix[1][3];

		screen =
		{
			(vars::stuff::ScreenWidth / 2) * (1.f + x / w),
			(vars::stuff::ScreenHeight / 2) * (1.f - y / w)
		};

		return true;
	}

	bool OOF(BasePlayer* ply) {
		Vector3 pos = ply->get_bone_pos(head);
		Vector2 screen;

		if (!utils::w2s(pos, screen))
			return true;

		float num = Math::Distance_2D(screen_center, screen);
		return num > 1000.f;
	}
	Vector3 GetEntityPosition(std::uint64_t entity) {
		if (!entity) return Vector3::Zero();

		uintptr_t plyVis = read(entity + 0x8, uintptr_t);
		if (!plyVis) return Vector3::Zero();

		uintptr_t visualState = read(plyVis + 0x38, uintptr_t);
		if (!visualState) return Vector3::Zero();

		Vector3 ret = read(visualState + 0x90, Vector3);
		return ret;
	}

	Vector3 ClosestPoint(BasePlayer* player, Vector3 p) {

		static auto off = METHOD("Assembly-CSharp::BaseEntity::ClosestPoint(Vector3): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BasePlayer*, Vector3)>(off)(player, p);
	}
	bool LineOfSight(Vector3 a, Vector3 b) {
		int mask = vars::weapons::penetrate ? 10551296 : 1503731969; // projectile los, flyhack mask

		bool result = GamePhysics::LineOfSight(a, b, mask, 0.f) && GamePhysics::LineOfSight(b, a, mask, 0.f);
		return result;
	}

	//bool LineOfSight(Vector3 a, Vector3 b)
	//{
	//	RaycastHit hit;
	//	return Physics::LineOfSight(a, b, &hit, 10551296);
	//}

	void ServerRPC(DWORD64 ent, Str funcName) {
		static auto off = METHOD("Assembly-CSharp::BaseEntity::ServerRPC(String): Void");
		reinterpret_cast<void(__stdcall*)(DWORD64, Str)>(off)(ent, funcName);
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
std::array<int, 20> valid_bones = {
		1, 2, 3, 5, 6, 14, 15, 17, 18, 21, 23, 24, 25, 26, 27, 48, 55, 56, 57, 76
};

class Model : public Component {
public:
	FIELD("Assembly-CSharp::Model::boneTransforms", boneTransforms, Array<Transform*>*);
	FIELD("Assembly-CSharp::Model::boneNames", boneNames, Array<il2cpp::String*>*);

	Bone* resolve(uint32_t hash) {
		if (!this) return nullptr;

		if (!this->boneNames() || !this->boneTransforms()) return nullptr;

		auto bone_names = this->boneNames();
		auto bone_transforms = this->boneTransforms();

		for (int i = 0; i < bone_names->size(); i++) {
			auto bone_name = bone_names->get(i);
			auto bone_transform = bone_transforms->get(i);
			if (!bone_name || !bone_transform) continue;

			if (RUNTIME_CRC32_W(bone_name->buffer) == hash)
				return new Bone(bone_transform->position(), utils::LineOfSight(bone_transform->position(), LocalPlayer::Entity()->eyes()->get_position()));
		}

		return nullptr;
	}

	std::pair<Transform*, bool> find_bone(Vector3 from) {

		std::pair<Transform*, bool> ret = std::pair<Transform*, bool>(nullptr, false);
		if (!this || !std::uint64_t(this))	return ret;// < std::uint64_t(GetModuleHandleA("GameAssembly.dll"))) return ret;

		std::vector<std::pair<Transform*, float>> distances = std::vector<std::pair<Transform*, float>>();

		auto arr = this->boneTransforms();
		if (!arr)
			return ret;

		for (auto j : valid_bones) {
			if (!j || !arr)
				continue;
			auto bone = arr->get(j);
			if (!bone)
				continue;

			float dist = bone->position().distance(from);

			distances.push_back({ bone, dist });
		}


		// find smallest from float (second)
		std::pair<Transform*, float> temp = { nullptr, 99999.f };
		for (int i = 0; i < distances.size(); i++) {
			if (distances[i].second < temp.second) {
				temp.first = distances[i].first;
				temp.second = distances[i].second;
			}
		}

		ret.first = temp.first;
		ret.second = true;

		return ret;
		//__except (SafeExecution::fail(GetExceptionCode(), GetExceptionInformation())) { return std::pair<Transform*, bool>(nullptr, false);; };
	}
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

class SteamId
{

};
class SteamClient {
public:
	static SteamId* steamid() {
		static auto clazz = CLASS("Facepunch.Steamworks::SteamClient::SteamId");
		return *reinterpret_cast<SteamId**>(std::uint64_t(clazz->static_fields));
	}
	static rust::classes::string* Name() {
		static auto clazz = CLASS("Facepunch.Steamworks::SteamClient::Name");
		return *reinterpret_cast<rust::classes::string**>(std::uint64_t(clazz->static_fields));
	}
};
namespace Network {
	enum class MessageType {
		auth = 2,
		requestuserinformation = 17,
		giveuserinformation = 18
	};

	class BaseNetwork {

	};
	class NetWrite : public BaseNetwork {
	public:
		static bool Start() {
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::Start(): Boolean");
			return reinterpret_cast<bool (*)()>(off)();
		}
		void PacketID(char val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::PacketID(Message.Type): Void");
			return reinterpret_cast<void(*)(NetWrite*, char)>(off)(this, val);
		}

		void UInt8(char val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::UInt8(UInt8): Void");
			return reinterpret_cast<void(*)(NetWrite*, char)>(off)(this, val);
		}

		void UInt16(uint16_t val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::UInt16(UInt16): Void");
			return reinterpret_cast<void(*)(NetWrite*, uint16_t)>(off)(this, val);
		}

		void UInt32(uint32_t val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::UInt32(UInt32): Void");
			return reinterpret_cast<void(*)(NetWrite*, uint32_t)>(off)(this, val);
		}

		void UInt64A(uint64_t val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::UInt64(UInt64): Void");
			return reinterpret_cast<void(*)(NetWrite*, uint64_t)>(off)(this, val);
		}

		void _String(rust::classes::string* val) {
			if (!this) return;
			static auto off = METHOD("Facepunch.Network::Network::NetWrite::String(String): Void");
			return reinterpret_cast<void (*)(NetWrite*, rust::classes::string*)>(off)(this, val);
		}
	};
	class Message {
	public:
		//FIELD("Facepunch.Network::Network::Message::write", write, NetWrite*);
	};
	class AuthTicket {

	};
	class Client {
	public:
		AuthTicket* GetAuthTicket() {
			if (!this) return nullptr;
			static auto off = METHOD("Facepunch.Network::Network::Client::GetAuthTicket(): Auth.Ticket");
			return reinterpret_cast<AuthTicket * (__fastcall*)(Client*)>(off)(this);
		}
		bool IsConnected() {
			if (!this) return false;
			static auto off = METHOD("Facepunch.Network::Network::Client::IsConnected(): Boolean");
			return reinterpret_cast<bool(__fastcall*)(Client*)>(off)(this);
		}
		rust::classes::string* ConnectedAddress() {
			return *reinterpret_cast<rust::classes::string**>(this + 0x40);
		}
	};
	class Net {
	public:
		static Client* cl() {
			static auto clazz = CLASS("Facepunch.Network::Network::Net");
			return *reinterpret_cast<Client**>(std::uint64_t(clazz->static_fields));
		}
	};
}
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

inline TimeAverageValueData RPC_Counter = { 0, 0, 0 };
