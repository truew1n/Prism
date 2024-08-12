#ifndef PE_MESH_HPP
#define PE_MESH_HPP

#include "ElementBuffer.hpp"
#include "VertexArray.hpp"
#include "Material.hpp"

class CMesh {
private:
    CVertexArray VertexArray;
    uint32_t TriangleCount;
    CMaterial *Material;
public:
    CMesh();
    CMesh(CArray<SVertex> &Vertices, CArray<uint32_t> &Indices);
    void Draw();
    void Delete();

    void SetMaterial(CMaterial *NewMaterial);
    CMaterial *GetMaterial();
};

#endif