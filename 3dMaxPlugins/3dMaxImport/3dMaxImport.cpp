// 3dMaxImport.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "3dMaxImport.h"


// Пример экспортированной переменной
C2M_3DMAX_IMPORT_API int n_C2M_3dMaxImport =0;

// Пример экспортированной функции.
C2M_3DMAX_IMPORT_API int fn_C2M_3dMaxImport(void)
{
    return 0;
}

// Конструктор для экспортированного класса.
C2M_3dMaxImporter::C2M_3dMaxImporter()
{
    return;
}
