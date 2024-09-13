#ifndef PE_HIT_EVENT_H
#define PE_HIT_EVENT_H

struct SHitInfo;

class IHitEvent {
public:
    virtual void OnHit(SHitInfo HitInfo) = 0;

    virtual ~IHitEvent() = default;
};

#endif

