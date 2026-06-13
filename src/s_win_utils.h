#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmeapi.h>
#include <mmsystem.h>
#include <mmreg.h>

//Macro for assigning Windows procedure address to a function pointer
#define PROC(X)\
    X = (reinterpret_cast<decltype(X)>(GetProcAddress(lib, "wave"#X)))

inline struct WinMM {
    HMODULE lib;
    UINT    (WINAPI* OutGetNumDevs)();
    MMRESULT(WINAPI* OutGetDevCapsW)(UINT_PTR, WAVEOUTCAPS*, UINT);
    MMRESULT(WINAPI* OutOpen)(LPHWAVEOUT, UINT, LPCWAVEFORMATEX, DWORD_PTR, DWORD_PTR, DWORD);
    MMRESULT(WINAPI* OutPrepareHeader)(HWAVEOUT, LPWAVEHDR, UINT);
    MMRESULT(WINAPI* OutWrite)(HWAVEOUT, LPWAVEHDR, UINT);
    MMRESULT(WINAPI* OutClose)(HWAVEOUT);
    MMRESULT(WINAPI* OutUnprepareHeader)(HWAVEOUT, LPWAVEHDR, UINT);

    WinMM() : lib(LoadLibraryW(L"winmm.dll")) {
        if (!lib) return;
        PROC(OutGetNumDevs);
        PROC(OutGetDevCapsW);
        PROC(OutOpen);
        PROC(OutPrepareHeader);
        PROC(OutWrite);
        PROC(OutClose);
        PROC(OutUnprepareHeader);
    }
} winmm; //Instance

//Useful for sonora_win backend. Maybe assert it?
inline bool checkWinApi() { return winmm.lib; }