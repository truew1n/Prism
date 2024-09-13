#ifndef PE_OVERLAP_EVENT_H
#define PE_OVERLAP_EVENT_H

struct SOverlapInfo;

class IOverlapEvent {
public:
    virtual void OnOverlapBegin(SOverlapInfo OverlapInfo) = 0;
    virtual void OnOverlapEnd(SOverlapInfo OverlapInfo) = 0;
    virtual void OnOverlapStay(SOverlapInfo OverlapInfo) = 0;

    virtual ~IOverlapEvent() = default;
};

#endif
