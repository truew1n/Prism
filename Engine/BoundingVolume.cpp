#include "BoundingVolume.h"


bool CBoundingVolume::InFrustum(glm::mat4 *CameraTransform, glm::mat4 *WorldTransform)
{
	return true;
}

glm::vec3 CBoundingVolume::GetCentroid()
{
	return glm::vec3(0.0f);
}

float CBoundingVolume::GetDistance(glm::vec3 Origin)
{
	return 0.0f;
}

EBoundingVolumeType CBoundingVolume::GetType()
{
	return MType;
}

void CBoundingVolume::SetType(EBoundingVolumeType Type)
{
	MType = Type;
}