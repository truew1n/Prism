#ifndef PE_TRANSFORM_HPP
#define PE_TRANSFORM_HPP

#include <glm/glm.hpp>

class CTransform {
private:
    glm::vec3 Location;
    glm::vec3 Rotation;
    glm::vec3 Scale;
public:
    glm::vec3 GetLocation();
    glm::vec3 GetRotation();
    glm::vec3 GetScale();
};

#endif