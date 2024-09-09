#ifndef PE_COLLISION_H
#define PE_COLLISION_H

#include "Transform.h"


class CCollisionSolver {
public:
    static bool SolvePointEllipsoid(glm::vec3 Point, CTransform Ellipsoid);
};

#endif