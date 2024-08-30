#include "Mesh.hpp"

CMesh::CMesh()
{
    SVertex StackVertices[4] = {
        SVertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
        SVertex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        SVertex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
        SVertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f))
    };
    CArray<SVertex> *Vertices = CArray<SVertex>::From(StackVertices, sizeof(StackVertices)/sizeof(StackVertices[0]));

    uint32_t StackIndices[6] = {
        0, 1, 2,
        0, 2, 3
    };
    CArray<uint32_t> *Indices = CArray<uint32_t>::From(StackIndices, sizeof(StackIndices)/sizeof(StackIndices[0]));

    VertexArray.Bind();
    CVertexBuffer VertexBuffer(Vertices);
    CElementBuffer ElementBuffer(Indices);

    VertexArray.LinkAttribute(&VertexBuffer, 0, 3, GL_FLOAT, sizeof(SVertex), (void*)0);
    VertexArray.LinkAttribute(&VertexBuffer, 1, 3, GL_FLOAT, sizeof(SVertex), (void*)(3 * sizeof(float)));
    VertexArray.LinkAttribute(&VertexBuffer, 2, 2, GL_FLOAT, sizeof(SVertex), (void*)(6 * sizeof(float)));
    VertexArray.Unbind();

    TriangleCount = Indices->Num();

    delete Vertices;
    delete Indices;
}

CMesh::CMesh(CArray<SVertex> *Vertices, CArray<uint32_t> *Indices)
{
    VertexArray.Bind();
    CVertexBuffer VertexBuffer(Vertices);
    CElementBuffer ElementBuffer(Indices);

    VertexArray.LinkAttribute(&VertexBuffer, 0, 3, GL_FLOAT, sizeof(SVertex), (void*)0);
    VertexArray.LinkAttribute(&VertexBuffer, 1, 3, GL_FLOAT, sizeof(SVertex), (void*)(3 * sizeof(float)));
    VertexArray.LinkAttribute(&VertexBuffer, 2, 2, GL_FLOAT, sizeof(SVertex), (void*)(6 * sizeof(float)));
    VertexArray.Unbind();

    TriangleCount = Indices->Num();
}

void CMesh::Draw()
{
    VertexArray.Bind();
    glDrawElements(GL_TRIANGLES, TriangleCount, GL_UNSIGNED_INT, 0);
    VertexArray.Unbind();
}

CMesh::~CMesh()
{
    VertexArray.Delete();
}

void CMesh::SetMaterial(CMaterial *NewMaterial)
{
    Material = NewMaterial;
}

CMaterial *CMesh::GetMaterial()
{
    return Material;
}