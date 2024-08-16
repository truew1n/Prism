#ifndef PE_LEVEL_HPP
#define PE_LEVEL_HPP

#include "Actor.hpp"
#include "Array.hpp"

class CLevel {
private:
    CArray<CActor *> *Actors;
public:
    CLevel();
    void Tick(float DeltaTime);
    ~CLevel();
};

#endif