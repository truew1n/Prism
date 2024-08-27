#ifndef PE_TRANSFORM_HPP
#define PE_TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include <iostream>

class CTransform {
private:
    glm::vec3 MLocation;
    glm::quat MRotation;
    glm::vec3 MScale;

public:
    CTransform() : MLocation(0.0f), MRotation(glm::vec3(0.0f)), MScale(1.0f) {}
    CTransform(glm::vec3 ILocation, glm::quat IRotation = glm::quat(), glm::vec3 IScale = glm::vec3(1.0f))
        : MLocation(ILocation), MRotation(IRotation), MScale(IScale) {}

    glm::vec3 GetLocation() const { return MLocation; }
    void SetLocation(glm::vec3 NewLocation) { MLocation = NewLocation; }
    
    glm::quat GetRotation() const { return MRotation; }
    void SetRotation(glm::quat NewRotation) { MRotation = NewRotation; }
    
    glm::vec3 GetScale() const { return MScale; }
    void SetScale(glm::vec3 NewScale) { MScale = NewScale; }

    void RotateX(float Angle)
    {
        glm::quat QuatRotationX = glm::angleAxis(glm::radians(Angle), glm::vec3(1.0f, 0.0f, 0.0f));
        MRotation = QuatRotationX * MRotation;
    }

    void RotateY(float Angle)
    {
        glm::quat QuatRotationY = glm::angleAxis(glm::radians(Angle), glm::vec3(0.0f, 1.0f, 0.0f));
        MRotation = QuatRotationY * MRotation;
    }

    void RotateZ(float Angle)
    {
        glm::quat QuatRotationZ = glm::angleAxis(glm::radians(Angle), glm::vec3(0.0f, 0.0f, 1.0f));
        MRotation = QuatRotationZ * MRotation;
    }

    void Rotate(float XAngle, float YAngle, float ZAngle)
    {
        RotateX(XAngle);
        RotateY(YAngle);
        RotateZ(ZAngle);
    }

    void TranslateX(float Offset)
    {
        MLocation.x += Offset;
    }

    void TranslateY(float Offset)
    {
        MLocation.y += Offset;
    }

    void TranslateZ(float Offset)
    {
        MLocation.z += Offset;
    }

    void Translate(float XOffset, float YOffset, float ZOffset)
    {
        TranslateX(XOffset);
        TranslateY(YOffset);
        TranslateZ(ZOffset);
    }

    void ScaleX(float Factor)
    {
        MScale.x *= Factor;
    }

    void ScaleY(float Factor)
    {
        MScale.y *= Factor;
    }

    void ScaleZ(float Factor)
    {
        MScale.z *= Factor;
    }

    void Scale(float XFactor, float YFactor, float ZFactor)
    {
        ScaleX(XFactor);
        ScaleY(YFactor);
        ScaleZ(ZFactor);
    }

    CTransform operator+(const CTransform& Other) const
    {
        return CTransform(
            MLocation + Other.MLocation,
            MRotation * Other.MRotation,
            MScale + Other.MScale
        );
    }

    CTransform operator-(const CTransform& Other) const
    {
        return CTransform(
            MLocation - Other.MLocation,
            MRotation * glm::inverse(Other.MRotation),
            MScale - Other.MScale
        );
    }

    CTransform operator*(float Scalar) const
    {
        return CTransform(
            MLocation * Scalar,
            glm::slerp(glm::quat(), MRotation, Scalar),
            MScale * Scalar
        );
    }

    CTransform operator/(float Scalar) const
    {
        return CTransform(
            MLocation / Scalar,
            glm::slerp(glm::quat(), MRotation, 1.0f / Scalar),
            MScale / Scalar
        );
    }

    glm::mat4 GetTransformMatrix()
    {
        glm::mat4 TransformMatrix = glm::mat4(1.0f);

        TransformMatrix = glm::translate(TransformMatrix, GetLocation());

        glm::mat4 RotationMatrix = glm::toMat4(GetRotation());
        TransformMatrix = TransformMatrix * RotationMatrix;
        
        TransformMatrix = glm::scale(TransformMatrix, GetScale());

        return TransformMatrix;
    }
};

#endif
