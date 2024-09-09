#ifndef PE_ACTOR_H
#define PE_ACTOR_H

#include "Object.h"
#include "SceneComponent.h"
#include "Transform.h"

class CLevel;
class CController;

class CActor : public CObject {
private:
    CLevel *Level;
public:
    CController *Controller;
    CSceneComponent *RootComponent;

    CActor();
    void Draw();
    virtual void Tick(float DeltaTime) override;
    ~CActor() override;

    CLevel *GetLevel();
    void SetLevel(CLevel *NewLevel);

    CTransform GetTransform();
    CTransform *GetTransformRef();
    void SetTransform(CTransform NewTransform);

    CController *GetController();
    void SetController(CController *NewController);
};

#endif