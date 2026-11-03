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
template<typename T = uintptr_t, typename A>
T& read(A address) {
	auto addresss = (DWORD64)address;
	if (addresss > 0x40000 && (addresss + sizeof(T)) < 0x7FFFFFFF0000)
		return *(T*)addresss;

	auto n = nullptr;
	return reinterpret_cast<T&>(n);
}
template <typename T>
void write(uintptr_t address, T data) {
	if (address > 0x40000 && (address + sizeof(T)) < 0x7FFFFFFF0000)
		*(T*)(address) = data;
}