#ifndef PE_BOUNDING_VOLUME_H
#define PE_BOUNDING_VOLUME_H

#include <cstdint>
#include "Transform.h"

enum class EBoundingVolumeType : int8_t {
    Sphere = 0,
    AxisAlignedBoundingBox = 1,
    OrientedBoundingBox = 2,
    EightDirectionalOrientedPolytope = 3,
    ConvexHull = 4
};

class CBoundingVolume {
private:
	EBoundingVolumeType MType;
public:
    CBoundingVolume() = default;
	virtual bool InFrustum(glm::mat4 *CameraTransform, glm::mat4 *WorldTransform);
    ~CBoundingVolume() = default;

    EBoundingVolumeType GetType();
    void SetType(EBoundingVolumeType Type);
};

#endif
