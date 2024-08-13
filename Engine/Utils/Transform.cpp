#include "Transform.hpp"


glm::vec3 CTransform::GetLocation()
{
    return Location;
}

glm::vec3 CTransform::GetRotation()
{
    return Rotation;
}

glm::vec3 CTransform::GetScale()
{
    return Scale;
}