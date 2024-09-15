#ifndef PE_COLLISION_MANAGER_H
#define PE_COLLISION_MANAGER_H

#include <stdint.h>

#include "CollisionSolver.h"
#include "CollisionEvent.h"
#include "OverlapEvent.h"
#include "HitEvent.h"


enum class ECollisionChannel : uint16_t {
	Object0,
	Object1,
	Object2
};

class CCollisionManager {
	
};

#endif