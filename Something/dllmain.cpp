#include <Windows.h>

typedef void(__cdecl* _FunctionOne)();
_FunctionOne FunctionOne;

typedef void(__cdecl* _FunctionTwo)(const char* string);
_FunctionTwo FunctionTwo;

DWORD WINAPI MainThread(LPVOID param)
{
    uintptr_t modBase = (uintptr_t)GetModuleHandle(NULL);

    FunctionOne = (_FunctionOne)(modBase + 0x12370);

    FunctionTwo = (_FunctionTwo)(modBase + 0x123F0);

    while (!GetAsyncKeyState(VK_END))
    {
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            FunctionOne();
        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            FunctionTwo("FuntionTwo hacked!");
        }
    }
    FreeLibraryAndExitThread((HMODULE)param, 0);
    return 0;
}

BOOL WINAPI DllMain( HMODULE hModule, DWORD  dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, MainThread, hModule, 0, 0);
        break;
    }
    return TRUE;
}

