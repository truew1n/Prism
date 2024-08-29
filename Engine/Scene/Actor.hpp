#ifndef PE_ACTOR_HPP
#define PE_ACTOR_HPP

#include "Object.hpp"
#include "SceneComponent.hpp"
#include "Transform.hpp"

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