#include "CuboidBoundingVolume.h"


bool CCuboidBoundingVolume::InFrustum(glm::mat4 *CameraTransform, glm::mat4 *WorldTransform)
{
    glm::vec3 Corners[8] = {
        MMinimum,
        glm::vec3(MMaximum.x, MMinimum.y, MMinimum.z),
        glm::vec3(MMinimum.x, MMaximum.y, MMinimum.z),
        glm::vec3(MMinimum.x, MMinimum.y, MMaximum.z),
        glm::vec3(MMaximum.x, MMaximum.y, MMinimum.z),
        glm::vec3(MMaximum.x, MMinimum.y, MMaximum.z),
        glm::vec3(MMinimum.x, MMaximum.y, MMaximum.z),
        MMaximum
    };

    glm::mat4 CombinedTransform = (*CameraTransform) * (*WorldTransform);
    glm::vec4 WorldPosition = glm::vec4(0.0f);

    for (int i = 0; i < 8; ++i) {
        WorldPosition = CombinedTransform * glm::vec4(Corners[i], 1.0f);

        if (WorldPosition.x >= -WorldPosition.w && WorldPosition.x <= WorldPosition.w &&
            WorldPosition.y >= -WorldPosition.w && WorldPosition.y <= WorldPosition.w &&
            WorldPosition.z >= 0.0f && WorldPosition.z <= WorldPosition.w) {
            return true;
        }
    }

    return false;
}

void CCuboidBoundingVolume::SetMinimum(glm::vec3 Minimum)
{
    MMinimum = Minimum;
}

glm::vec3 CCuboidBoundingVolume::GetMinimum()
{
    return MMinimum;
}

void CCuboidBoundingVolume::SetMaximum(glm::vec3 Maximum)
{
    MMaximum = Maximum;
}

glm::vec3 CCuboidBoundingVolume::GetMaximum()
{
    return MMaximum;
}