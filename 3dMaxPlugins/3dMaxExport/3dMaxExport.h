// Приведенный ниже блок ifdef — это стандартный метод создания макросов, упрощающий процедуру
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа MY3DMAXEXPORT_EXPORTS
// Символ, определенный в командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы которого включают данный файл, видит
// функции MY3DMAXEXPORT_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef C2M_3DMAX_EXPORT_EXPORTS
#define C2M_3DMAX_EXPORT_API __declspec(dllexport)
#else
#define C2M_3DMAX_EXPORT_API __declspec(dllimport)
#endif

#include "pch.h"
#include "framework.h"

#include <max.h>
#include <istdplug.h>
#include <iparamm2.h>
#include <iparamb2.h>

// http://100byte.ru/mxscrptxmpls/sdk/sdk.html
#define C2M_EXPORTER_CLASS_ID Class_ID(0x2a71a045, 0x340d6436)


extern TCHAR *GetString(int id);

// Этот класс экспортирован из библиотеки DLL
class C2M_3dMaxExporter: public SceneExport
{
public:
	C2M_3dMaxExporter(void);

	int ExtCount(); // Number of extensions supported

    const TCHAR *Ext(int n);                    // Extension #n (i.e. "3DS")
    const TCHAR *LongDesc();                    // Long ASCII description (i.e. "Autodesk 3D Studio File")
    const TCHAR *ShortDesc();                   // Short ASCII description (i.e. "3D Studio")
    const TCHAR *AuthorName();                  // ASCII Author name
    const TCHAR *CopyrightMessage();            // ASCII Copyright message
    const TCHAR *OtherMessage1();               // Other message #1
    const TCHAR *OtherMessage2();               // Other message #2
    
    unsigned int Version();                     // Version number * 100 (i.e. v3.01 = 301)
    
    void         ShowAbout(HWND hWnd);          // Show DLL's "About..." box
    int          DoExport(const TCHAR *filename, ExpInterface *ei, Interface *i,
        BOOL suppressPrompts = FALSE, DWORD options = 0);

};

class C2M_3dMaxExporterDesc : public ClassDesc2
{
public:
    int             IsPublic() { return TRUE; }
    void            *Create(BOOL loading = FALSE) { return new C2M_3dMaxExporter(); }
    const TCHAR     *ClassName() { return GetString(IDS_CLASS_NAME); }
    SClass_ID       SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
    Class_ID        ClassID() { return C2M_EXPORTER_CLASS_ID; }
    const TCHAR     *Category() { return GetString(IDS_CATEGORY); }
    const TCHAR     *InternalName() { return _T("c2mExporter"); }     // returns fixed parsable name (scripter-visible name)
    HINSTANCE        HInstance() { return hInstance; }                // returns owning module handle
                                                                      
   
// virtual TCHAR   *GetRsrcString(INT_PTR id) { return _T("c2mExporter"); }

}; // class maxExporterClassDesc 
