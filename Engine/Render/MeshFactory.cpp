#include "MeshFactory.hpp"


CMesh* CMeshFactory::GenerateCube(float SideLength)
{
    float HalfSide = SideLength / 2.0f;

    CArray<SVertex>* Vertices = new CArray<SVertex>();

    // Top Face
    Vertices->Add(SVertex(glm::vec3(-HalfSide, HalfSide, HalfSide), glm::vec2(0.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(HalfSide, HalfSide, HalfSide), glm::vec2(1.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(HalfSide, HalfSide, -HalfSide), glm::vec2(1.0f, 1.0f)));
    Vertices->Add(SVertex(glm::vec3(-HalfSide, HalfSide, -HalfSide), glm::vec2(0.0f, 1.0f)));

    // Bottom Face
    Vertices->Add(SVertex(glm::vec3(-HalfSide, -HalfSide, -HalfSide), glm::vec2(0.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(HalfSide, -HalfSide, -HalfSide), glm::vec2(1.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(HalfSide, -HalfSide, HalfSide), glm::vec2(1.0f, 1.0f)));
    Vertices->Add(SVertex(glm::vec3(-HalfSide, -HalfSide, HalfSide), glm::vec2(0.0f, 1.0f)));

    // Front Face
    Vertices->Add(SVertex(glm::vec3(-HalfSide, -HalfSide, HalfSide), glm::vec2(0.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(HalfSide, -HalfSide, HalfSide), glm::vec2(1.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(HalfSide, HalfSide, HalfSide), glm::vec2(1.0f, 1.0f)));
    Vertices->Add(SVertex(glm::vec3(-HalfSide, HalfSide, HalfSide), glm::vec2(0.0f, 1.0f)));

    // Back Face
    Vertices->Add(SVertex(glm::vec3(HalfSide, -HalfSide, -HalfSide), glm::vec2(0.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(-HalfSide, -HalfSide, -HalfSide), glm::vec2(1.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(-HalfSide, HalfSide, -HalfSide), glm::vec2(1.0f, 1.0f)));
    Vertices->Add(SVertex(glm::vec3(HalfSide, HalfSide, -HalfSide), glm::vec2(0.0f, 1.0f)));

    // Left Face
    Vertices->Add(SVertex(glm::vec3(-HalfSide, -HalfSide, -HalfSide), glm::vec2(0.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(-HalfSide, -HalfSide, HalfSide), glm::vec2(1.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(-HalfSide, HalfSide, HalfSide), glm::vec2(1.0f, 1.0f)));
    Vertices->Add(SVertex(glm::vec3(-HalfSide, HalfSide, -HalfSide), glm::vec2(0.0f, 1.0f)));

    // Right Face
    Vertices->Add(SVertex(glm::vec3(HalfSide, -HalfSide, HalfSide), glm::vec2(0.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(HalfSide, -HalfSide, -HalfSide), glm::vec2(1.0f, 0.0f)));
    Vertices->Add(SVertex(glm::vec3(HalfSide, HalfSide, -HalfSide), glm::vec2(1.0f, 1.0f)));
    Vertices->Add(SVertex(glm::vec3(HalfSide, HalfSide, HalfSide), glm::vec2(0.0f, 1.0f)));

    CArray<uint32_t>* Indices = new CArray<uint32_t>();

    // Top Face
    Indices->Add(0); Indices->Add(1); Indices->Add(2);
    Indices->Add(2); Indices->Add(3); Indices->Add(0);

    // Bottom Face
    Indices->Add(4); Indices->Add(5); Indices->Add(6);
    Indices->Add(6); Indices->Add(7); Indices->Add(4);

    // Front Face
    Indices->Add(8); Indices->Add(9); Indices->Add(10);
    Indices->Add(10); Indices->Add(11); Indices->Add(8);

    // Back Face
    Indices->Add(12); Indices->Add(13); Indices->Add(14);
    Indices->Add(14); Indices->Add(15); Indices->Add(12);

    // Left Face
    Indices->Add(16); Indices->Add(17); Indices->Add(18);
    Indices->Add(18); Indices->Add(19); Indices->Add(16);

    // Right Face
    Indices->Add(20); Indices->Add(21); Indices->Add(22);
    Indices->Add(22); Indices->Add(23); Indices->Add(20);

    CMesh* ReturnMesh = new CMesh(Vertices, Indices);
    delete Vertices;
    delete Indices;
    return ReturnMesh;
}


CMesh *CMeshFactory::GeneratePlaneRing(float InnerRadius, float OuterRadius, int32_t SegmentCount)
{
    float AngleStep = 2.0f * M_PI / SegmentCount;
    
    CArray<SVertex> *Vertices = new CArray<SVertex>();
    for (int i = 0; i < SegmentCount; ++i) {
        float Angle = i * AngleStep;
        float XOuter = OuterRadius * cos(Angle);
        float YOuter = OuterRadius * sin(Angle);
        float XInner = InnerRadius * cos(Angle);
        float YInner = InnerRadius * sin(Angle);

        Vertices->Add(
            SVertex(glm::vec3(XOuter, YOuter, 0.0f), glm::vec2((XOuter / OuterRadius + 1.0f) / 2.0f, (YOuter / OuterRadius + 1.0f) / 2.0f))
        );
        Vertices->Add(
            SVertex(glm::vec3(XInner, YInner, 0.0f), glm::vec2((XInner / InnerRadius + 1.0f) / 2.0f, (YInner / InnerRadius + 1.0f) / 2.0f))
        );
    }

    CArray<uint32_t> *Indices = new CArray<uint32_t>();
    for (int i = 0; i < SegmentCount; ++i) {
        int Next = (i + 1) % SegmentCount;
        
        Indices->Add(i * 2);
        Indices->Add(Next * 2);
        Indices->Add(i * 2 + 1);

        Indices->Add(Next * 2);
        Indices->Add(Next * 2 + 1);
        Indices->Add(i * 2 + 1);
    }

    CMesh *ReturnMesh = new CMesh(Vertices, Indices);
    delete Vertices;
    delete Indices;
    return ReturnMesh;
}

CMesh *CMeshFactory::GenerateSphere(float Radius, int32_t LatitudeCount, int32_t LongitudeCount)
{
    if (LongitudeCount < 3)
        LongitudeCount = 3;
    if (LatitudeCount < 2)
        LatitudeCount = 2;

    CArray<SVertex> *Vertices = new CArray<SVertex>();
    CArray<uint32_t> *Indices = new CArray<uint32_t>();

    float DeltaLatitude = M_PI / LatitudeCount;
    float DeltaLongitude = 2.0f * M_PI / LongitudeCount;

    for (int32_t i = 0; i <= LatitudeCount; ++i) {
        float LatitudeAngle = M_PI / 2.0f - i * DeltaLatitude;
        float xy = Radius * cosf(LatitudeAngle);
        float z = Radius * sinf(LatitudeAngle);

        for (int32_t j = 0; j <= LongitudeCount; ++j) {
            float LongitudeAngle = j * DeltaLongitude;

            float x = xy * cosf(LongitudeAngle);
            float y = xy * sinf(LongitudeAngle);

            float s = (float)j / LongitudeCount;
            float t = (float)i / LatitudeCount;

            Vertices->Add(SVertex(glm::vec3(x, y, z), glm::vec2(s, t)));
        }
    }

    for (int32_t i = 0; i < LatitudeCount; ++i) {
        int32_t k1 = i * (LongitudeCount + 1);
        int32_t k2 = k1 + LongitudeCount + 1;

        for (int32_t j = 0; j < LongitudeCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                Indices->Add(k1);
                Indices->Add(k2);
                Indices->Add(k1 + 1);
            }

            if (i != LatitudeCount - 1) {
                Indices->Add(k1 + 1);
                Indices->Add(k2);
                Indices->Add(k2 + 1);
            }
        }
    }
    
    CMesh *ReturnMesh = new CMesh(Vertices, Indices);
    delete Vertices;
    delete Indices;
    return ReturnMesh;
}

float CMeshFactory::PerlinNoise(float x, float y) {
    return glm::perlin(glm::vec2(x, y));
}

CMesh *CMeshFactory::GenerateTerrain(int32_t Width, int32_t Depth, float Scale, float HeightMultiplier, int32_t Octaves, float Persistence, float Lacunarity)
{
    CArray<SVertex>* Vertices = new CArray<SVertex>(Depth * Width);
    CArray<uint32_t>* Indices = new CArray<uint32_t>(Depth * Width * 6);

    int32_t Counter = 0;
    for (int32_t z = 0; z < Depth; ++z) {
        for (int32_t x = 0; x < Width; ++x) {
            float Height = 0.0f;
            float Frequency = 1.0f;
            float Amplitude = 1.0f;
            float MaxValue = 0.0f;

            for (int32_t i = 0; i < Octaves; ++i) {
                float SampleX = (x / Scale) * Frequency;
                float SampleZ = (z / Scale) * Frequency;

                float NoiseValue = PerlinNoise(SampleX, SampleZ) * 2.0f - 1.0f;
                Height += NoiseValue * Amplitude;

                MaxValue += Amplitude;

                Amplitude *= Persistence;
                Frequency *= Lacunarity;
            }

            Height = (Height / MaxValue) * HeightMultiplier;

            Vertices->Set(SVertex(glm::vec3(x, Height, z), glm::vec2(x / (float)Width, z / (float)Depth)), Counter++);
        }
    }

    Counter = 0;
    for (int32_t z = 0; z < Depth - 1; ++z) {
        for (int32_t x = 0; x < Width - 1; ++x) {
            int32_t TopLeft = (z * Width) + x;
            int32_t TopRight = TopLeft + 1;
            int32_t BottomLeft = ((z + 1) * Width) + x;
            int32_t BottomRight = BottomLeft + 1;

            Indices->Set(TopLeft, Counter++);
            Indices->Set(BottomLeft, Counter++);
            Indices->Set(TopRight, Counter++);

            Indices->Set(TopRight, Counter++);
            Indices->Set(BottomLeft, Counter++);
            Indices->Set(BottomRight, Counter++);
        }
    }

    CMesh* ReturnMesh = new CMesh(Vertices, Indices);
    delete Vertices;
    delete Indices;
    return ReturnMesh;
}