#ifndef CFD_MAIN_LEVEL_H
#define CFD_MAIN_LEVEL_H

#include "Level.h"

class CFDPlayer;
class CFDPerlinGrid;

class CFDMainLevel : public CLevel {
public:
    CFDMainLevel();
    void Tick(float DeltaTime) override;
    ~CFDMainLevel() override;

    CFDPlayer *Player;
    CFDPerlinGrid *PerlinGrid;

    double LastX;
    double LastY;

    void MouseCallback(double X, double Y);
    void ResizeCallback(int32_t Width, int32_t Height);
};

#endif