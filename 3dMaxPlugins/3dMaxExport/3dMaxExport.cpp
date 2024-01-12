// 3dMaxExport.cpp : Определяет экспортируемые функции для DLL.
//

#include "3dMaxExport.h"

#pragma warning (disable : 4530)

static C2M_3dMaxExporterDesc c2mExporterDesc;
ClassDesc2 *Get3dMaxExporterDesc() { return &c2mExporterDesc; }


// Конструктор для экспортированного класса.
C2M_3dMaxExporter::C2M_3dMaxExporter()
{
    return;
}

int C2M_3dMaxExporter::ExtCount()
{
    return 1;
}

const TCHAR *C2M_3dMaxExporter::Ext(int n)
{
    return _T("c2m");
}

const TCHAR *C2M_3dMaxExporter::LongDesc()
{
    return _T("Export to the Cossaks2 and HoAE model format");
}

const TCHAR *C2M_3dMaxExporter::ShortDesc()
{
    return _T("c2m ModelObject");
}

const TCHAR *C2M_3dMaxExporter::AuthorName()
{
    return _T("Ilya-Sadocok");
}

const TCHAR *C2M_3dMaxExporter::CopyrightMessage()
{
    return _T("Copyright(C) 2023 C2 and HoAE Community");
}

const TCHAR *C2M_3dMaxExporter::OtherMessage1()
{
    return _T("");
}

const TCHAR *C2M_3dMaxExporter::OtherMessage2()
{
    return _T("");
}

unsigned int C2M_3dMaxExporter::Version()
{
    return 100;
}

void C2M_3dMaxExporter::ShowAbout(HWND hWnd)
{
}

// Export function
int C2M_3dMaxExporter::DoExport(const TCHAR *filename, ExpInterface *ei, Interface *i, BOOL suppressPrompts, DWORD options)
{
    // Getting the root node of the scene
    INode *rootNode = i->GetRootNode();

    // Open file for write
    FILE *file = _tfopen(filename, _T("w"));
    if (!file) {
        return FALSE;
    }

    // Recording information about the format version
    fprintf(file, "C2M_FORMAT_VERSION=1.0\n");

    // Go around all the objects in the scene
    for (int j = 0; j < i->GetRootNode()->NumberOfChildren(); j++) {
        INode *node = rootNode->GetChildNode(j);
        Object *obj = node->EvalWorldState(i->GetTime()).obj;

        // Checking if the object is a 3D model
        if (obj->CanConvertToType(triObjectClassID)) {
            TriObject *triObj = (TriObject *)obj->ConvertToType(i->GetTime(), triObjectClassID);
            Mesh &mesh = triObj->GetMesh();

            // Recording information about the mesh: the number of vertices and polygons
            fprintf(file, "MESH_VERTEX_COUNT=%d\n", mesh.getNumVerts());
            fprintf(file, "MESH_POLYGON_COUNT=%d\n", mesh.getNumFaces());

            // Writing down the vertices of the mesh
            fprintf(file, "MESH_VERTICES=");
            for (int k = 0; k < mesh.getNumVerts(); k++) {
                Point3 vertex = mesh.getVert(k);
                fprintf(file, "%f %f %f ", vertex.x, vertex.y, vertex.z);
            }
            fprintf(file, "\n");

            // Recording the mesh polygons
            fprintf(file, "MESH_POLYGONS=");
            for (int k = 0; k < mesh.getNumFaces(); k++) {
                Face face = mesh.faces[k];
                fprintf(file, "%d %d %d ", face.v[0], face.v[1], face.v[2]);
            }
            fprintf(file, "\n");
        }
    }

    // Write file
    fclose(file);

    return TRUE;
    
}
