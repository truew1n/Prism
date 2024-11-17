#ifndef CFD_MAIN_LEVEL_H
#define CFD_MAIN_LEVEL_H

#include "Level.h"

class GPlayer;
class GMapController;
class CAsset;

class CFDMainLevel : public CLevel {
public:
    CFDMainLevel();
    void Tick(float DeltaTime) override;
    ~CFDMainLevel() override;

    GPlayer *Player;
    GMapController *PerlinGrid;

    double LastX;
    double LastY;

    void MouseCallback(double X, double Y);
    void ResizeCallback(int32_t Width, int32_t Height);
};

#endif