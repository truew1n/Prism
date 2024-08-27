#ifndef PE_COLLISION_HPP
#define PE_COLLISION_HPP

#include "Transform.hpp"

// typedef struct SHit {
//     glm::vec3 Location;
//     glm::vec3 Actor;
// };

class CCollisionSolver {
public:
    static bool SolvePointEllipsoid(glm::vec3 Point, CTransform Ellipsoid);
};

#endif