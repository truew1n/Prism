#ifndef PE_MESH_H
#define PE_MESH_H

#include "ElementBuffer.h"
#include "VertexArray.h"
#include "Material.h"
#include "BoundingVolume.h"

class CMesh {
private:
    uint32_t MTriangleCount;
    CVertexArray MVertexArray;
    CMaterial *MMaterial;

    CBoundingVolume *MBoundingVolume;
public:
    bool HasBoundingVolume;

private:
    void InitMembers();
public:
    CMesh();
    CMesh(CArray<SVertex> *IVertices, CArray<uint32_t> *IIndices);
    CMesh(CArray<SVertex> *IVertices, CArray<uint32_t> *IIndices, CBoundingVolume *IBoundingVolume);
    void Draw();
    ~CMesh();

    void SetMaterial(CMaterial *Material);
    CMaterial *GetMaterial();

    void SetBoundingVolume(CBoundingVolume *BoundingVolume);
    CBoundingVolume *GetBoundingVolume();
};

#endif