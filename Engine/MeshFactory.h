#ifndef PE_MESH_FACTORY_H
#define PE_MESH_FACTORY_H

#include "Mesh.h"
#include "FunctionLibrary.h"
#include <glm/ext/scalar_constants.hpp>

class CMeshFactory {
public:
    static CMesh *GenerateCube(float SideLength);
    static CMesh *GeneratePlaneRing(float InnerRadius, float OuterRadius, int32_t SegmentCount);
    static CMesh *GenerateSphere(float Radius, int32_t LatitudeSegments, int32_t LongitudeSegments);
    static CMesh *GenerateTerrain(int32_t Width, int32_t Depth, float RightStep, float LeftStep, float Scale, float HeightMultiplier, int32_t Octaves, float Persistence, float Lacunarity);
    static CMesh *GenerateCuboid(glm::vec3 Minimum, glm::vec3 Maximum);
};

#endif