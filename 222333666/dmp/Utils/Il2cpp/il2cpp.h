#include <map>
#include "lazy_importer.hpp"
Matrix viewMatrix = {};
typedef DWORD64(*AGI)(DWORD64);
AGI type_get_object = 0;
AGI class_get_type = 0;

template<typename T1, typename T2> bool map_contains_key(T1 map, T2 key) {
	return map.count(key) > 0;
}
bool mrx_found = false;
bool m_strcmp(char* a, char* b) {
	if (!a || !b) return !a && !b;

	int ret = 0;
	unsigned char* p1 = (unsigned char*)a;
	unsigned char* p2 = (unsigned char*)b;
	while (!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;

	return ret == 0;
}
namespace methods {
	using il2cpp_domain_get = uintptr_t(*)();

	static auto domain_get = LI_FIND_DEF(il2cpp_domain_get);

	using il2cpp_class_get_methods = uintptr_t(*)(uintptr_t, uintptr_t*);

	static auto class_get_methods = LI_FIND_DEF(il2cpp_class_get_methods);

	using il2cpp_method_get_param_count = int (*)(uintptr_t);

	static auto method_get_param_count = LI_FIND_DEF(il2cpp_method_get_param_count);

	using il2cpp_assembly_get_image = uintptr_t(*)(uintptr_t);

	static auto assembly_get_image = LI_FIND_DEF(il2cpp_assembly_get_image);

	using il2cpp_domain_get_assemblies = uintptr_t * (*)(void* domain, uintptr_t* size);

	static auto domain_get_assemblies = LI_FIND_DEF(il2cpp_domain_get_assemblies);

	using il2cpp_object_new = uintptr_t(*)(uintptr_t);

	static auto object_new = LI_FIND_DEF(il2cpp_object_new);

	using il2cpp_class_from_name = uintptr_t(*)(uintptr_t, const char*, const char*);

	static auto class_from_name = LI_FIND_DEF(il2cpp_class_from_name);

	using il2cpp_resolve_icall = uintptr_t(*)(const char*);

	static auto resolve_icall = LI_FIND_DEF(il2cpp_resolve_icall);

	using il2cpp_field_static_get_value = uintptr_t(*)(uintptr_t, uintptr_t*);

	static auto field_static_get_value = LI_FIND_DEF(il2cpp_field_static_get_value);

	using il2cpp_class_get_fields = uintptr_t(*)(uintptr_t, uintptr_t*);

	static auto class_get_fields = LI_FIND_DEF(il2cpp_class_get_fields);

	using il2cpp_field_get_offset = uintptr_t(*)(uintptr_t);

	static auto field_get_offset = LI_FIND_DEF(il2cpp_field_get_offset);

	using il2cpp_runtime_class_init = uintptr_t(*)(uintptr_t);

	static auto runtime_class_init = LI_FIND_DEF(il2cpp_runtime_class_init);

	using il2cpp_string_new_wrapper = uintptr_t(*)(const char*);
	static auto new_string = LI_FIND_DEF(il2cpp_string_new_wrapper);

	using il2cpp_type_get_object = uintptr_t(*)(uintptr_t);
	static auto type_get_object = LI_FIND_DEF(il2cpp_type_get_object);

	using il2cpp_class_get_type = uintptr_t(*)(uintptr_t);
	static auto class_get_type = LI_FIND_DEF(il2cpp_class_get_type);
}
namespace il2cpp {
	auto gameAssembly = GetModuleHandleA(
		
		("GameAssembly.dll"));
	static std::map<uint32_t, uint64_t> offsets = std::map<uint32_t, uint64_t>();
#define ProcAddr(func) GetProcAddress(gameAssembly, func)

	template<typename T, typename... Args>
	inline T call(const char* func, Args... args) {
		return reinterpret_cast<T(__fastcall*)(Args...)>(ProcAddr(func))(args...);
	}
	class Object_ {
	public:

	};
	class String : public Object_ {
	public:
		char pad_0000[0x10];
		int len;
		wchar_t buffer[0];

		static String* New(const char* str) {
			return call<String*, const char*>(("il2cpp_string_new"), str);
		}
	};
	class Il2CppType {
	public:
		char* name() {
			return call<char*, Il2CppType*>(("il2cpp_type_get_name"), this);
		}
	};
	uintptr_t _init_class(const char* name, const char* name_space = ("")) {

		uintptr_t domain = methods::domain_get();

		uintptr_t nrofassemblies = 0;
		uintptr_t* assemblies;
		assemblies = methods::domain_get_assemblies((void*)domain, &nrofassemblies);

		for (int i = 0; i < nrofassemblies; i++) {
			uintptr_t img = methods::assembly_get_image(assemblies[i]);

			uintptr_t kl = methods::class_from_name(img, name_space, name);
			if (!kl) continue;

			return kl;
		}
		return 0;
	}
	uintptr_t TypeGetObject(const char* name_space, const char* name)
	{
		auto klass = _init_class(name, name_space);
		return type_get_object(class_get_type(klass));
	}

	class Il2CppMethod {
	public:
		uint32_t paramCount() {
			return call<uint32_t, Il2CppMethod*>(("il2cpp_method_get_param_count"), this);
		}

		Il2CppType* retType() {
			return call<Il2CppType*, Il2CppMethod*>(("il2cpp_method_get_return_type"), this);
		}

		Il2CppType* getParam(uint32_t idx) {
			return call<Il2CppType*, Il2CppMethod*, uint32_t>(("il2cpp_method_get_param"), this, idx);
		}

		char* name() {
			return call<char*, Il2CppMethod*>(("il2cpp_method_get_name"), this);
		}
	};

	uint64_t il2cpp_resolve_icall(const char* str) {
		return call<uint64_t, const char*>(("il2cpp_resolve_icall"), str);
	}
	uint64_t il2cpp_object_new(uint64_t klass) {
		return call<uint64_t, uint64_t>(("il2cpp_object_new"), klass);
	}

	class Il2CppField {
	public:
		char* name() {
			return call<char*, Il2CppField*>(("il2cpp_field_get_name"), this);
		}

		uint32_t offset() {
			return call<uint32_t, Il2CppField*>(("il2cpp_field_get_offset"), this);
		}
	};

	class Il2CppClass {
	public:
		class Il2CppImage* image; //0x0000
		char pad_0008[8]; //0x0008
		char* name; //0x0010
		char* namespaze; //0x0018
		char pad_0020[152]; //0x0020
		void* static_fields; //0x00B8

		Il2CppMethod* methods(void* iter) {
			return call<Il2CppMethod*, Il2CppClass*, void*>(("il2cpp_class_get_methods"), this, iter);
		}

		Il2CppField* fields(void* iter) {
			return call<Il2CppField*, Il2CppClass*, void*>(("il2cpp_class_get_fields"), this, iter);
		}
	}; //Size: 0x00C0

	class Il2CppImage {
	public:
		char* assemblyName; //0x0000
		char* name; //0x0008

		uint64_t classcount() {
			return call<uint64_t, Il2CppImage*>(("il2cpp_image_get_class_count"), this);
		}

		Il2CppClass* get_class(uint64_t idx) {
			return call<Il2CppClass*, Il2CppImage*, uint64_t>(("il2cpp_image_get_class"), this, idx);
		}
	}; //Size: 0x0010

	template<typename T = uint64_t>
	T il2cpp_array_new(Il2CppClass* klazz, uint64_t length) {
		return call<T, Il2CppClass*, uint64_t>(("il2cpp_array_new"), klazz, length);
	}
	template<typename T>
	T il2cpp_object_new_(Il2CppClass* klazz)
	{
		return call<T, Il2CppClass*>(("il2cpp_object_new"), klazz);
	}
	class Il2CppAssembly {
	public:
		uint64_t buffer;
	};

	class Il2CppDomain {
	public:
		size_t assemblyCount() {
			size_t size = 0;
			auto assemblies = call<Il2CppAssembly**, Il2CppDomain*, void*>(("il2cpp_domain_get_assemblies"), this, &size);

			return size;

		}

		Il2CppAssembly** assemblies() {
			size_t size = 0;

			return call<Il2CppAssembly**, Il2CppDomain*, void*>(("il2cpp_domain_get_assemblies"), this, &size);
		}
	};

	Il2CppDomain* il2cpp_domain_get() {
		return call<Il2CppDomain*>(("il2cpp_domain_get"));
	}

	void* il2cpp_runtime_invoke(void* method_ptr, void* obj, void** param, void** exc) {
		return call<void*, void*, void*, void**, void**>(("il2cpp_runtime_invoke"), method_ptr, obj, param, exc);
	}

	void* il2cpp_object_get_virtual_method(void* obj, void* method) {
		return call<void*, void*, void*>(("il2cpp_object_get_virtual_method"), obj, method);
	}

	Il2CppClass* klass(uint32_t path) {
		if (map_contains_key(offsets, path))
			return reinterpret_cast<Il2CppClass*>(offsets[path]);

		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				temp.erase(temp.find((".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + ("::") + name;
				else
					temp = temp + ("::") + ns + ("::") + name;

				if (path == RUNTIME_CRC32(temp.c_str())) {
					uint64_t ptr = std::uint64_t(klass);

					offsets.insert(std::make_pair(path, ptr));
					return klass;
				}
			}
		}

		return nullptr;
	}
	uint64_t method(uint32_t path) {
		if (map_contains_key(offsets, path))
			return offsets[path];

		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				temp.erase(temp.find((".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				if (!klass) continue;

				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + ("::") + name;
				else
					temp = temp + ("::") + ns + ("::") + name;

				Il2CppMethod* mthd;
				void* iter = NULL;
				while (mthd = klass->methods(&iter)) {
					if (!mthd) continue;

					std::string temp2(temp + ("::") + mthd->name());

					if (mthd->paramCount() > 0) {
						temp2 = temp2 + ("(");
						for (int p = 0; p < mthd->paramCount(); p++) {
							std::string t(mthd->getParam(p)->name());
							t = t.substr(t.find((".")) + 1);
							temp2 = temp2 + t + (",");
						}
						std::string t(mthd->retType()->name());
						temp2 = temp2.substr(0, temp2.size() - 1);
						temp2 = temp2 + ("): ") + t.substr(t.find(".") + 1);
					}
					else {
						std::string t(mthd->retType()->name());
						temp2 = temp2 + ("(): ") + t.substr(t.find(".") + 1);
					}

					if (RUNTIME_CRC32(temp2.c_str()) == path) {
						offsets.insert(std::make_pair(path, std::uint64_t(mthd)));

						return std::uint64_t(mthd);
					}
				}
			}
		}

		return 0;
	}

	uint64_t field(uint32_t path) {
		if (map_contains_key(offsets, path))
			return std::uint32_t(offsets[path]);

		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				temp.erase(temp.find((".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + ("::") + name;
				else
					temp = temp + ("::") + ns + ("::") + name;

				Il2CppField* field;
				void* iter = NULL;
				while (field = klass->fields(&iter)) {
					if (!field) continue;

					std::string t(temp + ("::") + field->name());
					if (RUNTIME_CRC32(t.c_str()) == path) {
						uint32_t off = field->offset();
						offsets.insert(std::make_pair(path, off));

						return off;
					}
				}
			}
		}

		return 0;
	}
	void init_classes() {
		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				//temp.erase(temp.find((".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + ("::") + name;
				else
					temp = temp + ("::") + ns + ("::") + name;

				uint64_t ptr = std::uint64_t(klass);

				offsets.insert(std::make_pair(RUNTIME_CRC32(temp.c_str()), ptr));
			}
		}
	}
	void init_methods() {
		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				//temp.erase(temp.find((".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				if (!klass) continue;

				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + ("::") + name;
				else
					temp = temp + ("::") + ns + ("::") + name;

				Il2CppMethod* mthd;
				void* iter = NULL;
				while (mthd = klass->methods(&iter)) {
					if (!mthd) continue;

					std::string temp2(temp + ("::") + mthd->name());

					if (mthd->paramCount() > 0) {
						temp2 = temp2 + ("(");
						for (int p = 0; p < mthd->paramCount(); p++) {
							std::string t(mthd->getParam(p)->name());
							t = t.substr(t.find((".")) + 1);
							temp2 = temp2 + t + (",");
						}
						std::string t(mthd->retType()->name());
						temp2 = temp2.substr(0, temp2.size() - 1);
						temp2 = temp2 + ("): ") + t.substr(t.find(".") + 1);
					}
					else {
						std::string t(mthd->retType()->name());
						temp2 = temp2 + ("(): ") + t.substr(t.find(".") + 1);
					}

					offsets.insert(std::make_pair(RUNTIME_CRC32(temp2.c_str()), std::uint64_t(mthd)));
				}
			}
		}
	}
	void init_fields() {
		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				//temp.erase(temp.find((".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + ("::") + name;
				else
					temp = temp + ("::") + ns + ("::") + name;

				Il2CppField* field;
				void* iter = NULL;
				while (field = klass->fields(&iter)) {
					if (!field) continue;

					std::string t(temp + ("::") + field->name());
					uint32_t off = field->offset();
					offsets.insert(std::make_pair(RUNTIME_CRC32(t.c_str()), off));
				}
			}
		}
	}
	class default_t {
	public:
		template<typename T>
		operator T() const { return T(); }
	};

	default_t const defaultt = default_t();
#define METHOD(path) *reinterpret_cast<uint64_t*>(il2cpp::method(STATIC_CRC32(path)))
#define CLASS(path) il2cpp::klass(STATIC_CRC32(path))
#define ASSIGN_HOOK(method_path,hook) hook = reinterpret_cast<decltype(hook)>(METHOD(method_path))
#define OFFSET(path) il2cpp::field(STATIC_CRC32(path))
#define NP(type) type nonptr = il2cpp::defaultt; if(!this) return nonptr;
#define FIELD(field_path,name,type) type& name() { \
		NP(type) \
		static auto off = OFFSET(field_path); \
		return *reinterpret_cast<type*>(this + off); }
	char* memstr(char* haystack, const char* needle, int size) {
		char* p;
		char needlesize = strlen(needle);
		for (p = haystack; p <= (haystack - needlesize + size); p++) {
			if (memcmp(p, needle, needlesize) == 0)
				return p; /* found */
		}
		return NULL;
	}
	namespace unity {
		// getting camera using header scanning (epic)
		uint64_t get_camera() {
			const auto base = (uint64_t)GetModuleHandleA(("UnityPlayer.dll"));
			if (!base)
				return 0;
			const auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
			const auto nt_header = reinterpret_cast<IMAGE_NT_HEADERS64*>(base + dos_header->e_lfanew);
			uint64_t data_base;
			uint64_t data_size;
			for (int i = 0;;) {
				const auto section = reinterpret_cast<IMAGE_SECTION_HEADER*>(
					base + dos_header->e_lfanew + // nt_header base 
					sizeof(IMAGE_NT_HEADERS64) +  // start of section headers
					(i * sizeof(IMAGE_SECTION_HEADER))); // section header at our index
				if (strcmp((char*)section->Name, (".data")) == 0) {
					data_base = section->VirtualAddress + base;
					data_size = section->SizeOfRawData;
					break;
				}
				i++;
				if (i >= nt_header->FileHeader.NumberOfSections) {
					Beep(500, 1000);
					return 0;
				}
			}
			uint64_t camera_table = 0;
			const auto camera_string = memstr((char*)data_base, ("AllCameras"), data_size);
			for (auto walker = (uint64_t*)camera_string; walker > 0; walker -= 1) {
				if (*walker > 0x100000 && *walker < 0xF00000000000000) {
					// [[[[unityplayer.dll + ctable offset]]] + 0x30] = Camera
					camera_table = *walker;
					break;
				}
			}
			if (camera_table)
				return camera_table;
			//Beep(500, 1000);
			return 0;
		}

		Matrix getViewMatrix() {
			static auto camera_list = get_camera();
			if (!camera_list) return Matrix();

			auto camera_table = *reinterpret_cast<uint64_t*>(camera_list);
			auto cam = *reinterpret_cast<uint64_t*>(camera_table);
			mrx_found = true;

			return *reinterpret_cast<Matrix*>(cam + 0x2E4);
		}

		static bool world_to_screen(Vector3 world, Vector2& screen) {
			const auto matrix = viewMatrix.transpose();

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
				screen_center.x * (1.f + x / w),
				screen_center.y * (1.f - y / w)
			};

			return true;
		}
	}

	static void init() {
		init_classes();
		init_methods();
		init_fields();
	}
}