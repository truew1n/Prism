#include "Mesh.hpp"

CMesh::CMesh()
{
    CArray<SVertex> Vertices = CArray<SVertex>::From((SVertex[]){
        SVertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
        SVertex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        SVertex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
        SVertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f))
    }, 4);

    CArray<uint32_t> Indices = CArray<uint32_t>::From((uint32_t[]){
        0, 1, 2,
        0, 2, 3
    }, 6);

    VertexArray.Bind();
    CVertexBuffer VertexBuffer(Vertices);
    CElementBuffer ElementBuffer(Indices);

    VertexArray.LinkAttribute(VertexBuffer, 0, 3, GL_FLOAT, sizeof(SVertex), (void*)0);
    VertexArray.LinkAttribute(VertexBuffer, 1, 2, GL_FLOAT, sizeof(SVertex), (void*)(3 * sizeof(float)));
    VertexArray.Unbind();

    TriangleCount = Indices.Num();

    Vertices.Free();
    Indices.Free();
}

CMesh::CMesh(CArray<SVertex> &Vertices, CArray<uint32_t> &Indices)
{
    VertexArray.Bind();
    CVertexBuffer VertexBuffer1(Vertices);
    CElementBuffer ElementBuffer1(Indices);

    VertexArray.LinkAttribute(VertexBuffer1, 0, 3, GL_FLOAT, sizeof(SVertex), (void*)0);
    VertexArray.LinkAttribute(VertexBuffer1, 1, 2, GL_FLOAT, sizeof(SVertex), (void*)(3 * sizeof(float)));
    VertexArray.Unbind();

    TriangleCount = Indices.Num();
}

void CMesh::Draw()
{
    VertexArray.Bind();
    glDrawElements(GL_TRIANGLES, TriangleCount, GL_UNSIGNED_INT, 0);
    VertexArray.Unbind();
}

void CMesh::Delete()
{
    VertexArray.Delete();
    Material->Delete();   
}

void CMesh::SetMaterial(CMaterial *NewMaterial)
{
    Material = NewMaterial;
}

CMaterial *CMesh::GetMaterial()
{
    return Material;
}