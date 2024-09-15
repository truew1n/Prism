#ifndef  PE_CUBOID_BOUNDING_VOLUME_H
#define  PE_CUBOID_BOUNDING_VOLUME_H

#include "BoundingVolume.h"

class CCuboidBoundingVolume : public CBoundingVolume {
private:
	glm::vec3 MMinimum;
	glm::vec3 MMaximum;
public:
	CCuboidBoundingVolume() : MMinimum(0.0f), MMaximum(0.0f) {}
	CCuboidBoundingVolume(glm::vec3 IMinimum, glm::vec3 IMaximum) : MMinimum(IMinimum), MMaximum(IMaximum) {}
	virtual bool InFrustum(glm::mat4 *CameraTransform, glm::mat4 *WorldTransform) override;

	void SetMinimum(glm::vec3 Minimum);
	glm::vec3 GetMinimum();
	
	void SetMaximum(glm::vec3 Maximum);
	glm::vec3 GetMaximum();
};

#endif
