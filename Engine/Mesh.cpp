#include "Mesh.h"


void CMesh::InitMembers()
{
    MTriangleCount = 0;
    MMaterial = nullptr;
    MBoundingVolume = nullptr;
    HasBoundingVolume = false;
}

CMesh::CMesh()
{
    InitMembers();

    SVertex StackVertices[4] = {
        SVertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
        SVertex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        SVertex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
        SVertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f))
    };
    CArray<SVertex> *Vertices = CArray<SVertex>::From(StackVertices, sizeof(StackVertices) / sizeof(StackVertices[0]));

    uint32_t StackIndices[6] = {
        0, 1, 2,
        0, 2, 3
    };
    CArray<uint32_t> *Indices = CArray<uint32_t>::From(StackIndices, sizeof(StackIndices) / sizeof(StackIndices[0]));

    MVertexArray.Bind();
    CVertexBuffer VertexBuffer(Vertices);
    CElementBuffer ElementBuffer(Indices);

    MVertexArray.LinkAttribute(&VertexBuffer, 0, 3, GL_FLOAT, sizeof(SVertex), (void *)0);
    MVertexArray.LinkAttribute(&VertexBuffer, 1, 3, GL_FLOAT, sizeof(SVertex), (void *)(3 * sizeof(float)));
    MVertexArray.LinkAttribute(&VertexBuffer, 2, 2, GL_FLOAT, sizeof(SVertex), (void *)(6 * sizeof(float)));
    MVertexArray.Unbind();

    MTriangleCount = Indices->Num();

    delete Vertices;
    delete Indices;
}

CMesh::CMesh(CArray<SVertex> *IVertices, CArray<uint32_t> *IIndices)
{
    InitMembers();

    MVertexArray.Bind();
    CVertexBuffer VertexBuffer(IVertices);
    CElementBuffer ElementBuffer(IIndices);

    MVertexArray.LinkAttribute(&VertexBuffer, 0, 3, GL_FLOAT, sizeof(SVertex), (void *)0);
    MVertexArray.LinkAttribute(&VertexBuffer, 1, 3, GL_FLOAT, sizeof(SVertex), (void *)(3 * sizeof(float)));
    MVertexArray.LinkAttribute(&VertexBuffer, 2, 2, GL_FLOAT, sizeof(SVertex), (void *)(6 * sizeof(float)));
    MVertexArray.Unbind();

    MTriangleCount = IIndices->Num();
}

CMesh::CMesh(CArray<SVertex> *IVertices, CArray<uint32_t> *IIndices, CBoundingVolume *IBoundingVolume)
{
    InitMembers();

    MVertexArray.Bind();
    CVertexBuffer VertexBuffer(IVertices);
    CElementBuffer ElementBuffer(IIndices);

    MVertexArray.LinkAttribute(&VertexBuffer, 0, 3, GL_FLOAT, sizeof(SVertex), (void *)0);
    MVertexArray.LinkAttribute(&VertexBuffer, 1, 3, GL_FLOAT, sizeof(SVertex), (void *)(3 * sizeof(float)));
    MVertexArray.LinkAttribute(&VertexBuffer, 2, 2, GL_FLOAT, sizeof(SVertex), (void *)(6 * sizeof(float)));
    MVertexArray.Unbind();

    MTriangleCount = IIndices->Num();

    MBoundingVolume = IBoundingVolume;
}

void CMesh::Draw()
{
    MVertexArray.Bind();
    glDrawElements(GL_TRIANGLES, MTriangleCount, GL_UNSIGNED_INT, 0);
    MVertexArray.Unbind();
}

CMesh::~CMesh()
{
    MVertexArray.Delete();
}

void CMesh::SetMaterial(CMaterial *NewMaterial)
{
    MMaterial = NewMaterial;
}

CMaterial *CMesh::GetMaterial()
{
    return MMaterial;
}

void CMesh::SetBoundingVolume(CBoundingVolume *BoundingVolume)
{
    if (!BoundingVolume) {
        HasBoundingVolume = false;
    } else {
        HasBoundingVolume = true;
    }
    MBoundingVolume = BoundingVolume;
}

CBoundingVolume *CMesh::GetBoundingVolume()
{
    return MBoundingVolume;
}
