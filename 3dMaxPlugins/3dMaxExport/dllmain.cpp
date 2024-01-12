// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "3dMaxExport.h"

extern ClassDesc2 *Get3dMaxExporterDesc();

HINSTANCE hInstance;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, ULONG fdwReason, LPVOID)
{
    if (fdwReason == DLL_PROCESS_ATTACH) {
        hInstance = hinstDLL;
        DisableThreadLibraryCalls(hInstance);
    }
    return TRUE;
}

// This function returns a string that describes the DLL and where the user
// could purchase the DLL if they don't have it.
__declspec(dllexport) const TCHAR *LibDescription()
{
    return GetString(IDS_LIBDESCRIPTION);
}

// This function returns the number of plug-in classes this DLL
//TODO: Must change this number when adding a new class
__declspec(dllexport) int LibNumberClasses()
{
    return 1;
}

// This function returns the number of plug-in classes this DLL
__declspec(dllexport) ClassDesc *LibClassDesc(int i)
{
    switch (i) {
    case 0: return Get3dMaxExporterDesc();
    default: return 0;
    }
}

// This function returns a pre-defined constant indicating the version of 
// the system under which it was compiled.  It is used to allow the system
// to catch obsolete DLLs.
__declspec(dllexport) ULONG LibVersion()
{
    return VERSION_3DSMAX;
}

TCHAR *GetString(int id)
{
    static TCHAR buf[256];

    if (hInstance)
        return LoadString(hInstance, id, buf, sizeof(buf)) ? buf : NULL;
    return NULL;
}

//BOOL APIENTRY DllMain( HMODULE hModule,
//                       DWORD  ul_reason_for_call,
//                       LPVOID lpReserved
//                     )
//{
//    switch (ul_reason_for_call)
//    {
//    case DLL_PROCESS_ATTACH:
//    case DLL_THREAD_ATTACH:
//    case DLL_THREAD_DETACH:
//    case DLL_PROCESS_DETACH:
//        break;
//    }
//    return TRUE;
//}

