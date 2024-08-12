#ifndef PE_MESH_FACTORY_HPP
#define PE_MESH_FACTORY_HPP

#include "Mesh.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

class CMeshFactory {
public:
    static CMesh GeneratePlaneRing(float InnerRadius, float OuterRadius, int32_t SegmentCount);
};

#endif