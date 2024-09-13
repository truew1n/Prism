#ifndef PE_COLLISION_EVENT_H
#define PE_COLLISION_EVENT_H

struct SCollisionInfo;

class ICollisionEvent {
public:
    virtual void OnCollisionBegin(SCollisionInfo CollisionInfo) = 0;
    virtual void OnCollisionEnd(SCollisionInfo CollisionInfo) = 0;
    virtual void OnCollisionStay(SCollisionInfo CollisionInfo) = 0;

    virtual ~ICollisionEvent() = default;
};

#endif