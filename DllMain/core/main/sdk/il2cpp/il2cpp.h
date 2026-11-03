#include "../math/crc32.h"

namespace il2cpp {
	#define ToLower(Char) ((Char >= 'A' && Char <= 'Z') ? (Char + 32) : Char)
	uintptr_t main_camera = 0;

	template <typename T>
	constexpr uint32_t static_crc32(const T& data)
	{
		constexpr uint32_t table[256] = {
		};

		uint32_t crc = 0xFFFFFFFF;
		for (size_t i = 0; i < sizeof(data); ++i) {
			crc = table[(crc ^ reinterpret_cast<const uint8_t*>(&data)[i]) & 0xFF] ^ (crc >> 8);
		}
		return crc ^ 0xFFFFFFFF;
	}
	template <typename StrType, typename StrType2>
	bool StrCmp(StrType Str, StrType2 InStr, bool Two)
	{
		if (!Str || !InStr) return false;
		wchar_t c1, c2;
		do
		{
			c1 = *Str++; c2 = *InStr++;
			c1 = ToLower(c1); c2 = ToLower(c2);
			if (!c1 && (Two ? !c2 : 1))
				return true;
		} while (c1 == c2); return false;
	}
	inline bool strcmp(const char* a, const char* b) {
		if ((uintptr_t)a == 0x00000000ffffffff || (uintptr_t)b == 0x00000000ffffffff)
			return false;
		if ((uintptr_t)a == 0x000000000000007d || (uintptr_t)b == 0x000000000000007d)
			return false;

		if (!a || !b)
			return !a && !b;

		int ret = 0;
		unsigned char* p1 = (unsigned char*)a;
		unsigned char* p2 = (unsigned char*)b;
		while (!(ret = *p1 - *p2) && *p2)
			++p1, ++p2;

		return ret == 0;
	}
	inline bool m_strcmp(char* a, const char* b) {
		if ((uintptr_t)a == 0x00000000ffffffff || (uintptr_t)b == 0x00000000ffffffff)
			return false;
		if ((uintptr_t)a == 0x000000000000007d || (uintptr_t)b == 0x000000000000007d)
			return false;

		if (!a || !b) return !a && !b;

		int ret = 0;
		unsigned char* p1 = (unsigned char*)a;
		unsigned char* p2 = (unsigned char*)b;
		while (!(ret = *p1 - *p2) && *p2)
			++p1, ++p2;

		return ret == 0;
	}
	namespace methods {
		__forceinline PVOID GetExport(PBYTE hDll, const char* Name)
		{
			PIMAGE_NT_HEADERS NT_Head = (PIMAGE_NT_HEADERS)(hDll + ((PIMAGE_DOS_HEADER)hDll)->e_lfanew);
			PIMAGE_EXPORT_DIRECTORY ExportDir = (PIMAGE_EXPORT_DIRECTORY)(hDll + NT_Head->OptionalHeader.DataDirectory[0].VirtualAddress);

			for (DWORD i = 0; i < ExportDir->NumberOfNames; i++)
			{
				USHORT Ordinal = ((USHORT*)(hDll + ExportDir->AddressOfNameOrdinals))[i];
				const char* ExpName = (const char*)hDll + ((DWORD*)(hDll + ExportDir->AddressOfNames))[i];
				if (StrCmp(Name, ExpName, true))
					return (PVOID)(hDll + ((DWORD*)(hDll + ExportDir->AddressOfFunctions))[Ordinal]);
			} return nullptr;
		}

		typedef int(__stdcall* GPC)(DWORD64);
		typedef DWORD64(__stdcall* AGI)(DWORD64);
		typedef DWORD64(__stdcall* Dm)();
		typedef DWORD64(__stdcall* CFN)(DWORD64, const char*, const char*);
		typedef DWORD64(__stdcall* Call)(DWORD64, DWORD64);
		typedef DWORD64(*resolve)(const char*);
		typedef DWORD64(__stdcall* Ptr)(DWORD64, DWORD64*);
		typedef DWORD64* (__cdecl* DGA)(void* domain, DWORD64* size);
		typedef DWORD64(__stdcall* iCall)(const char*);
		typedef const char* (__stdcall* Ngp)(DWORD64, DWORD64 index);
		typedef const char* (__stdcall* Mgp)(DWORD64);
		typedef int(__stdcall* t_sprintf)(wchar_t* buffer, const wchar_t* format, ...);

		static Call  method_get_param = (methods::Call)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_method_get_param"));
		static AGI   method_get_return_type = (methods::AGI)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_method_get_return_type"));
		static Mgp   type_get_name = (methods::Mgp)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_type_get_name"));

		Mgp image_get_name = (methods::Mgp)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_image_get_name"));
		AGI image_get_class_count = (methods::AGI)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_image_get_class_count"));
		Call image_get_class = (methods::Call)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_image_get_class"));
		Mgp class_get_name = (methods::Mgp)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_get_name"));
		Mgp class_get_namespace = (methods::Mgp)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_get_namespace"));
		Mgp field_get_name = (methods::Mgp)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_field_get_name"));
		t_sprintf f_swprint = (t_sprintf)GetExport((PBYTE)GetModuleHandleA(("msvcrt.dll")), ("_swprintf"));
		Ngp method_get_param_name = (Ngp)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_method_get_param_name"));
		Mgp method_get_name = (Mgp)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_method_get_name"));
		Ptr class_get_methods = (Ptr)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_get_methods"));
		Ptr class_get_fields = (Ptr)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_get_fields"));
		Dm domain_get = (Dm)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_domain_get"));
		DGA domain_get_assemblies = (DGA)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_domain_get_assemblies"));
		AGI assembly_get_image = (AGI)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_assembly_get_image"));
		CFN class_from_name = (CFN)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_from_name"));
		AGI field_get_offset = (AGI)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_field_get_offset"));
		AGI runtime_class_init = (AGI)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_runtime_class_init"));
		Ptr field_static_get_value = (Ptr)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_field_static_get_value"));
		GPC method_get_param_count = (GPC)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_method_get_param_count"));
		Call array_new = (Call)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_array_new"));
		AGI object_new = (AGI)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_object_new"));
		iCall resolve_icall = (iCall)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_resolve_icall"));
		AGI type_get_object = (AGI)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_type_get_object"));
		AGI class_get_type = (AGI)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_get_type"));
		resolve new_string = (resolve)GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_string_new"));

		class Il2CppClass {
		public:
			class Il2CppImage* image; //0x0000
			char pad_0008[8]; //0x0008
			char* name; //0x0010
			char* namespaze; //0x0018
			char pad_0020[152]; //0x0020
			void* static_fields; //0x00B8
		}; 

	}

	inline void init() {
		methods::method_get_param = (methods::Call)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_method_get_param"));
		methods::method_get_return_type = (methods::AGI)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_method_get_return_type"));
		methods::type_get_name = (methods::Mgp)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_type_get_name"));

		methods::image_get_name = (methods::Mgp)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_image_get_name"));
		methods::image_get_class_count = (methods::AGI)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_image_get_class_count"));
		methods::image_get_class = (methods::Call)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_image_get_class"));
		methods::class_get_name = (methods::Mgp)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_get_name"));
		methods::class_get_namespace = (methods::Mgp)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_get_namespace"));
		methods::field_get_name = (methods::Mgp)methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_field_get_name"));

		methods::f_swprint = (methods::t_sprintf)(methods::GetExport((PBYTE)GetModuleHandleA(("msvcrt.dll")), ("_swprintf")));
		methods::runtime_class_init = (methods::AGI)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_runtime_class_init")));
		methods::method_get_param_name = (methods::Ngp)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_method_get_param_name")));
		methods::method_get_name = (methods::Mgp)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_method_get_name")));
		methods::method_get_param_count = (methods::GPC)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_method_get_param_count")));
		methods::field_static_get_value = (methods::Ptr)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_field_static_get_value")));
		methods::field_get_offset = (methods::AGI)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_field_get_offset")));
		methods::class_from_name = (methods::CFN)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_from_name")));
		methods::assembly_get_image = (methods::AGI)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_assembly_get_image")));
		methods::domain_get_assemblies = (methods::DGA)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_domain_get_assemblies")));
		methods::domain_get = (methods::Dm)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_domain_get")));
		methods::class_get_fields = (methods::Ptr)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_get_fields")));
		methods::class_get_methods = (methods::Ptr)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_get_methods")));
		methods::array_new = (methods::Call)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_array_new")));
		methods::object_new = (methods::AGI)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_object_new")));
		methods::resolve_icall = (methods::iCall)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_resolve_icall")));
		methods::type_get_object = (methods::AGI)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_type_get_object")));
		methods::class_get_type = (methods::AGI)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_class_get_type")));
		methods::new_string = (methods::resolve)(methods::GetExport((PBYTE)GetModuleHandleA(("GameAssembly.dll")), ("il2cpp_string_new")));
	}
	class String {
	public:
		char pad_0000[0x10];
		int len;
		wchar_t buffer[0];

		static String* New(const char* str) {
			return (String*)methods::new_string(str);
		}
	};
	uintptr_t init_class(const char* name, const char* name_space = ("")) {

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

	uintptr_t type_object(const char* name_space, const char* name)
	{
		auto klass = init_class(name, name_space);
		return methods::type_get_object(methods::class_get_type(klass));
	}

	uintptr_t method(const char* kl, const char* name, int argument_number = -1, const char* arg_name = (""), const char* name_space = (""), int selected_argument = -1) {
		uintptr_t iter = 0;
		uintptr_t f;
		auto klass = init_class(kl, name_space);

		while (f = methods::class_get_methods(klass, &iter)) {

			const char* st = methods::method_get_name(f);

			if (strcmp(st, (char*)name)) {
				if (selected_argument >= 0 && arg_name) {
					int method_count = methods::method_get_param_count(f);
					if (selected_argument > method_count || (argument_number >= 0 && method_count != argument_number)) continue;

					const char* argname;
					if (method_count > 0) {
						argname = methods::method_get_param_name(f, selected_argument - 1);
					}
					else
						argname = (char*)("-");

					if (!argname || !strcmp(argname, arg_name)) continue;
				}

				return f;
			}
		}
		return 0;
	}
	uintptr_t hook(void* our_func, const char* function_to_hook, const char* class_to_hook, const char* name_space = (""), int argument_number = -1, const char* argument_name = ("")) {
		auto il2cpp_method = method(class_to_hook, function_to_hook, argument_number, (char*)argument_name, name_space);

		*reinterpret_cast<void**>(il2cpp_method) = our_func;
		return il2cpp_method;
	}
	static uint32_t crc32_runtime(const char* s) {
		if (!s) return 0;
		uint32_t crc = 0xFFFFFFFFu;
		while (*s) {
			uint8_t byte = static_cast<uint8_t>(*s++);
			crc ^= byte;
			for (int i = 0; i < 8; ++i)
				crc = (crc >> 1) ^ (0xEDB88320u & (-(int32_t)(crc & 1)));
		}
		return crc ^ 0xFFFFFFFFu;
	}

	methods::Il2CppClass* klass_(uint32_t path) {
		DWORD64 domain = methods::domain_get();
		DWORD64 asm_count = 0;
		DWORD64* assemblies = methods::domain_get_assemblies((void*)domain, &asm_count);

		for (DWORD64 i = 0; i < asm_count; ++i) {
			DWORD64 image = methods::assembly_get_image(assemblies[i]);

			const char* img_name_c = methods::image_get_name ? methods::image_get_name(image) : nullptr;
			std::string img_name = img_name_c ? img_name_c : "";
			if (!img_name.empty()) {
				auto pos = img_name.rfind(".dll");
				if (pos != std::string::npos) img_name.erase(pos, 4);
			}

			DWORD64 class_count = methods::image_get_class_count(image);
			for (DWORD64 c = 0; c < class_count; ++c) {
				DWORD64 kaddr = methods::image_get_class(image, c);
				if (!kaddr) continue;

				methods::Il2CppClass* k = reinterpret_cast<methods::Il2CppClass*>(kaddr);

				const char* cname = methods::class_get_name(reinterpret_cast<DWORD64>(k));
				const char* cns = methods::class_get_namespace(reinterpret_cast<DWORD64>(k));

				std::string full = img_name;
				if (cns && *cns) {
					full += "::";
					full += cns;
					full += "::";
					full += (cname ? cname : "");
				}
				else {
					full += "::";
					full += (cname ? cname : "");
				}

				if (crc32_runtime(full.c_str()) == path) {
					return k;
				}
			}
		}
		return nullptr;
	}
	uintptr_t method_(uint32_t path) {

		DWORD64 domain = methods::domain_get();
		DWORD64 asm_count = 0;
		DWORD64* assemblies = methods::domain_get_assemblies((void*)domain, &asm_count);

		for (DWORD64 i = 0; i < asm_count; ++i) {
			DWORD64 image = methods::assembly_get_image(assemblies[i]);

			const char* img_name_c = methods::image_get_name ? methods::image_get_name(image) : nullptr;
			std::string img_name = img_name_c ? img_name_c : "";
			if (!img_name.empty()) {
				auto pos = img_name.rfind(".dll");
				if (pos != std::string::npos) img_name.erase(pos, 4);
			}

			DWORD64 class_count = methods::image_get_class_count(image);
			for (DWORD64 c = 0; c < class_count; ++c) {
				DWORD64 klass = methods::image_get_class(image, c);
				if (!klass) continue;

				const char* cname = methods::class_get_name(klass);
				const char* cns = methods::class_get_namespace(klass);

				std::string full = img_name;
				if (cns && *cns) {
					full += "::";
					full += cns;
					full += "::";
					full += (cname ? cname : "");
				}
				else {
					full += "::";
					full += (cname ? cname : "");
				}

				DWORD64 iter = 0;
				DWORD64 m = 0;
				while ((m = methods::class_get_methods(klass, &iter))) {
					const char* mname = methods::method_get_name(m);
					if (!mname) continue;

					std::string sig = full;
					sig += "::";
					sig += mname;

					int pc = methods::method_get_param_count(m);
					if (pc > 0) {
						sig += "(";
						for (int p = 0; p < pc; ++p) {
							DWORD64 ptype = methods::method_get_param(m, (DWORD64)p);
							const char* pname = methods::type_get_name(ptype);
							std::string t = pname ? pname : "";
							auto dot = t.rfind('.');
							if (dot != std::string::npos) t = t.substr(dot + 1);
							sig += t;
							sig += ",";
						}
						if (sig.back() == ',') sig.pop_back();

						DWORD64 rtype = methods::method_get_return_type(m);
						const char* rname = methods::type_get_name(rtype);
						std::string rt = rname ? rname : "";
						auto rdot = rt.rfind('.');
						if (rdot != std::string::npos) rt = rt.substr(rdot + 1);
						sig += "): ";
						sig += rt;
					}
					else {
						DWORD64 rtype = methods::method_get_return_type(m);
						const char* rname = methods::type_get_name(rtype);
						std::string rt = rname ? rname : "";
						auto rdot = rt.rfind('.');
						if (rdot != std::string::npos) rt = rt.substr(rdot + 1);
						sig += "(): ";
						sig += rt;
					}
					if (crc32_runtime(sig.c_str()) == path) {
						return (uintptr_t)m;
					}
				}
			}
		}
		return 0;
	}

	uintptr_t field(uintptr_t klass, char* field_name, bool get_offset = true) {
		uintptr_t out = 0;
		uintptr_t il2cpp_field;

		while (il2cpp_field = methods::class_get_fields(klass, &out)) {

			char* name = (char*)*reinterpret_cast<uintptr_t*>(il2cpp_field);
			if (!name)
				break;

			if (!m_strcmp(name, field_name)) {
				continue;
			}
			if (!get_offset)
				return il2cpp_field;

			uintptr_t offset = methods::field_get_offset(il2cpp_field);
			return offset;
		}
		return 0;
	}

	uintptr_t value(const char* kl, const char* name, bool get_offset = true) {

		auto klass = init_class(kl);

		if (get_offset) {
			auto field_offset = field(klass, (char*)name);
			return field_offset;
		}
		else
		{
			auto _field = field(klass, (char*)name, false);

			uintptr_t ret;
			methods::field_static_get_value(_field, &ret);
			return ret;
		}
		return 0;
	}
	uintptr_t hook_virtual_function(const char* classname, const char* function_to_hook, void* our_func, const char* name_space = ("")) {
		uintptr_t search = *reinterpret_cast<uintptr_t*>(il2cpp::method(classname, function_to_hook, -1, (""), name_space));
		uintptr_t table = il2cpp::init_class(classname, name_space);

		if (search == (uintptr_t)our_func)
			return (uintptr_t)our_func;

		for (uintptr_t i = table; i <= table + 0x1500; i += 0x1) {
			uintptr_t addr = *reinterpret_cast<uintptr_t*>(i);
			if (addr == search) {
				*reinterpret_cast<uintptr_t*>(i) = (uintptr_t)our_func;
				return addr;
			}
		}
		return (uintptr_t)our_func;
	}
	class default_t {
	public:
		template<typename T>
		operator T() const { return T(); }
	};

	uintptr_t field_(uint32_t path) {
		DWORD64 domain = methods::domain_get();
		DWORD64 asm_count = 0;
		DWORD64* assemblies = methods::domain_get_assemblies((void*)domain, &asm_count);

		for (DWORD64 i = 0; i < asm_count; ++i) {
			DWORD64 image = methods::assembly_get_image(assemblies[i]);
			const char* img_name_c = methods::image_get_name(image); 
			std::string img_name = img_name_c ? img_name_c : "";
			if (!img_name.empty()) {
				auto pos = img_name.rfind(".dll");
				if (pos != std::string::npos) img_name.erase(pos, 4);
			}

			DWORD64 class_count = methods::image_get_class_count(image);
			for (DWORD64 c = 0; c < class_count; ++c) {
				DWORD64 klass = methods::image_get_class(image, c);
				if (!klass) continue;

				const char* cname = methods::class_get_name(klass);
				const char* cns = methods::class_get_namespace(klass);

				std::string full = img_name;
				if (cns && *cns) {
					full += "::";
					full += cns;
					full += "::";
					full += (cname ? cname : "");
				}
				else {
					full += "::";
					full += (cname ? cname : "");
				}

				DWORD64 iter = 0;
				DWORD64 il2cpp_field = 0;
				while ((il2cpp_field = methods::class_get_fields(klass, &iter))) {
					const char* fname = methods::field_get_name(il2cpp_field);
					if (!fname) continue;

					std::string qualified = full;
					qualified += "::";
					qualified += fname;
					uintptr_t off = (uintptr_t)methods::field_get_offset(il2cpp_field);
					if (crc32_runtime(qualified.c_str()) == path) {
						uintptr_t off = (uintptr_t)methods::field_get_offset(il2cpp_field);
						return off;
					}
				}
			}
		}
		return 0;
	}

	static uintptr_t get_main_camera() {

		return reinterpret_cast<uintptr_t(*)()>(methods::resolve_icall(("UnityEngine.Camera::get_main()")))();
	}
	static Matrix4x4* find_matrix() {
		auto entity = *reinterpret_cast<DWORD64*>(main_camera + 0x10);
		Matrix4x4* pViewMatrix = (Matrix4x4*)(entity + 0x2E4);
		return pViewMatrix;
	}

	default_t const defaultt = default_t();
	#define METHOD(path) *reinterpret_cast<uint64_t*>(il2cpp::method_(STATIC_CRC32(path)))
	#define NP(type) type nonptr = il2cpp::defaultt; if(!this) return nonptr;
	#define OFFSET(path) il2cpp::field_(STATIC_CRC32(path))
	#define CLASS(path) il2cpp::klass_(STATIC_CRC32(path))

	#define FIELD(field_path,name,type) type& name() { \
		NP(type) \
		static auto off = OFFSET(field_path); \
		return *reinterpret_cast<type*>(this + off); }
}

