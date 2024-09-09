#ifndef PE_SCENE_COMPONENT_HPP
#define PE_SCENE_COMPONENT_HPP

#include "ActorComponent.hpp"
#include "Transform.hpp"
#include "Array.hpp"

class CSceneComponent : public CActorComponent {
private:
    glm::mat4 WorldTransform;
    CTransform LocalTransform;

    CSceneComponent *Parent;
    CArray<CSceneComponent *> *SceneComponents;
public:
    CSceneComponent();
    virtual void Tick(float DeltaTime) override;
    virtual void Draw();
    ~CSceneComponent() override;

    CSceneComponent *GetParent();
    void SetParent(CSceneComponent *NewParent);    

    glm::mat4 GetWorldTransform();
    glm::mat4 *GetWorldTransformRef();
    void SetWorldTransform(glm::mat4 NewTransform);

    CTransform GetLocalTransform();
    CTransform *GetLocalTransformRef();
    void SetLocalTransform(CTransform NewTransform);

    glm::mat4 CalculateParentChildTransform();
    glm::mat4 GetSetParentChildTransform();
    void SetParentChildTransform();

    void AddComponent(CSceneComponent *SceneComponent);
    CSceneComponent *RemoveComponent(int32_t Index);
    void RegisterComponents(CActor *NewOwner);
};

#endif