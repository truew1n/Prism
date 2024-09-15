#include "BoundingVolume.h"

bool CBoundingVolume::InFrustum(glm::mat4 *CameraTransform, glm::mat4 *WorldTransform)
{
	return true;
}

EBoundingVolumeType CBoundingVolume::GetType()
{
	return MType;
}

void CBoundingVolume::SetType(EBoundingVolumeType Type)
{
	MType = Type;
}