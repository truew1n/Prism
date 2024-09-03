#ifndef PE_MESH_FACTORY_HPP
#define PE_MESH_FACTORY_HPP

#include "Mesh.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/gtc/noise.hpp>

class CMeshFactory {
private:
    static float PerlinNoise(float x, float y);
public:
    static CMesh *GenerateCube(float SideLength);
    static CMesh *GeneratePlaneRing(float InnerRadius, float OuterRadius, int32_t SegmentCount);
    static CMesh *GenerateSphere(float Radius, int32_t LatitudeSegments, int32_t LongitudeSegments);
    static CMesh *GenerateTerrain(int32_t Width, int32_t Depth, float Scale, float HeightMultiplier, int32_t Octaves, float Persistence, float Lacunarity);
};

#endif