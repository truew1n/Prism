#ifndef PE_MESH_H
#define PE_MESH_H

#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Material.h"

class CMesh {
private:
    CVertexArray VertexArray;
    uint32_t TriangleCount;
    CMaterial *Material;
public:
    CMesh();
    CMesh(CArray<SVertex> *Vertices, CArray<uint32_t> *Indices);
    void Draw();
    ~CMesh();

    void SetMaterial(CMaterial *NewMaterial);
    CMaterial *GetMaterial();
};

#endif