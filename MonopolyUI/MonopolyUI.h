#ifndef Monopoly_H
#define Monopoly_H

typedef void (__stdcall *CallbackType)();

class Monopoly {
public:
	__declspec(dllexport) void DoSomething();
	__declspec(dllexport) void FireEvent();
	__declspec(dllexport) void RegisterListener(void* p_listener);
	__declspec(dllexport) void UnregisterListener(void* p_listener);

private:
	void* m_eventListener;
};

#endif // Monopoly_H