#include "CollisionSolver.hpp"

bool CCollisionSolver::SolvePointEllipsoid(glm::vec3 Point, CTransform Ellipsoid)
{
    glm::vec3 EllipsoidLocation = Ellipsoid.GetLocation();
    glm::quat EllipsoidRotation = Ellipsoid.GetRotation();
    glm::vec3 EllipsoidScale = Ellipsoid.GetScale();

    glm::mat4 Transform = glm::translate(glm::mat4(1.0f), EllipsoidLocation) *
                          glm::mat4_cast(EllipsoidRotation) *
                          glm::scale(glm::mat4(1.0f), EllipsoidScale);

    glm::mat4 InverseTransform = glm::inverse(Transform);
    glm::vec4 LocalPoint = InverseTransform * glm::vec4(Point, 1.0f);

    float P = (LocalPoint.x * LocalPoint.x) + (LocalPoint.y * LocalPoint.y) + (LocalPoint.z * LocalPoint.z);

    return P <= 1.0f;
}