// Приведенный ниже блок ifdef — это стандартный метод создания макросов, упрощающий процедуру
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа MY3DMAXIMPORT_EXPORTS
// Символ, определенный в командной строке. Этот символ не должен быть определен в каком-либо проекте,
// использующем данную DLL. Благодаря этому любой другой проект, исходные файлы которого включают данный файл, видит
// функции MY3DMAXIMPORT_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifdef C2M_3DMAX_IMPORT_EXPORTS
#define C2M_3DMAX_IMPORT_API __declspec(dllexport)
#else
#define C2M_3DMAX_IMPORT_API __declspec(dllimport)
#endif

// Этот класс экспортирован из библиотеки DLL
class C2M_3DMAX_IMPORT_API C2M_3dMaxImporter {
public:
	C2M_3dMaxImporter(void);
	// TODO: добавьте сюда свои методы.
};

extern C2M_3DMAX_IMPORT_API int n_C2M_3dMaxImport;

C2M_3DMAX_IMPORT_API int fn_C2M_3dMaxImport(void);
