#ifndef PE_BOUNDING_VOLUME_H
#define PE_BOUNDING_VOLUME_H

#include <cstdint>
#include "Transform.h"

enum class EBoundingVolumeType : int8_t {
    None,
    Sphere,
    AxisAlignedBoundingBox,
    OrientedBoundingBox,
    EightDirectionalOrientedPolytope,
    ConvexHull
};

class CBoundingVolume {
private:
	EBoundingVolumeType MType;
public:
    CBoundingVolume() : MType(EBoundingVolumeType::None) {}
	virtual bool InFrustum(glm::mat4 *CameraTransform, glm::mat4 *WorldTransform);

    EBoundingVolumeType GetType();
    void SetType(EBoundingVolumeType Type);
};

#endif
