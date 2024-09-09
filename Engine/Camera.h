#ifndef PE_CAMERA_H
#define PE_CAMERA_H

#include "Uniform.h"
#include "Transform.h"

class CCamera {
private:
    float AspectRatio;
    float FieldOfView;
    float NearPlane;
    float FarPlane;

    float Yaw;
    float Pitch;
    float Roll;

public:
    glm::vec3 CalculateFront();
    glm::vec3 CalculateRight();
    glm::vec3 CalculateUp();

    CCamera();
    ~CCamera();

    glm::mat4 GetViewMatrix(glm::mat4 WorldTransform, CTransform LocalTransform);
    glm::mat4 GetProjectionMatrix();

    float GetYaw() const { return Yaw; }
    void SetYaw(float NewYaw) { Yaw = NewYaw; }

    float GetPitch() const { return Pitch; }
    void SetPitch(float NewPitch) { Pitch = NewPitch; }

    float GetRoll() const { return Roll; }
    void SetRoll(float NewRoll) { Roll = NewRoll; }

    float GetAspectRatio() const { return AspectRatio; }
    void SetAspectRatio(float NewAspectRatio) { AspectRatio = NewAspectRatio; }

    float GetFieldOfView() const { return FieldOfView; }
    void SetFieldOfView(float NewFieldOfView) { FieldOfView = NewFieldOfView; }

    float GetNearPlane() const { return NearPlane; }
    void SetNearPlane(float NewNearPlane) { NearPlane = NewNearPlane; }

    float GetFarPlane() const { return FarPlane; }
    void SetFarPlane(float NewFarPlane) { FarPlane = NewFarPlane; }
};

#endif
