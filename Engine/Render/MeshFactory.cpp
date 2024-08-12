#include "MeshFactory.hpp"

CMesh CMeshFactory::GeneratePlaneRing(float InnerRadius, float OuterRadius, int32_t SegmentCount)
{
    float AngleStep = 2.0f * M_PI / SegmentCount;
    
    CArray<SVertex> Vertices = CArray<SVertex>();
    for (int i = 0; i < SegmentCount; ++i) {
        float Angle = i * AngleStep;
        float XOuter = OuterRadius * cos(Angle);
        float YOuter = OuterRadius * sin(Angle);
        float XInner = InnerRadius * cos(Angle);
        float YInner = InnerRadius * sin(Angle);

        Vertices.Add(
            SVertex(glm::vec3(XOuter, YOuter, 0.0f), glm::vec2((XOuter / OuterRadius + 1.0f) / 2.0f, (YOuter / OuterRadius + 1.0f) / 2.0f))
        );
        Vertices.Add(
            SVertex(glm::vec3(XInner, YInner, 0.0f), glm::vec2((XInner / InnerRadius + 1.0f) / 2.0f, (YInner / InnerRadius + 1.0f) / 2.0f))
        );
    }

    CArray<uint32_t> Indices = CArray<uint32_t>();
    for (int i = 0; i < SegmentCount; ++i) {
        int Next = (i + 1) % SegmentCount;
        
        Indices.Add(i * 2);
        Indices.Add(Next * 2);
        Indices.Add(i * 2 + 1);

        Indices.Add(Next * 2);
        Indices.Add(Next * 2 + 1);
        Indices.Add(i * 2 + 1);
    }

    CMesh ReturnMesh = CMesh(Vertices, Indices);
    Vertices.Free();
    Indices.Free();
    return ReturnMesh;
}