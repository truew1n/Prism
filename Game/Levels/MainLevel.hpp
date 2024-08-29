#ifndef CFD_MAIN_LEVEL_HPP
#define CFD_MAIN_LEVEL_HPP

#include "Level.hpp"

class CFDCubeActor;
class CFDSphereActor;

class CFDMainLevel : public CLevel {
public:
    CFDMainLevel();
    void Tick(float DeltaTime) override;
    ~CFDMainLevel() override;

    CFDCubeActor *CubeActor;
    CFDSphereActor *SphereActor;

    double LastX;
    double LastY;

    void MouseCallback(double X, double Y);
    void ResizeCallback(int32_t Width, int32_t Height);
};

#endif