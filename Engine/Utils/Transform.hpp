#ifndef PE_TRANSFORM_HPP
#define PE_TRANSFORM_HPP

#include <glm/glm.hpp>

class CTransform {
private:
    glm::vec3 Location;
    glm::vec3 Rotation;
    glm::vec3 Scale;
public:
    CTransform() : Location(0.0f), Rotation(0.0f), Scale(0.0f) {}
    CTransform(glm::vec3 ILocation, glm::vec3 IRotation = glm::vec3(0.0f), glm::vec3 IScale = glm::vec3(1.0f))
        : Location(ILocation), Rotation(IRotation), Scale(IScale) {}
    
    glm::vec3 GetLocation() const { return Location; }
    void SetLocation(glm::vec3 NewLocation) { Location = NewLocation; }
    glm::vec3 GetRotation() const { return Rotation; }
    void SetRotation(glm::vec3 NewRotation) { Rotation = NewRotation; }
    glm::vec3 GetScale() const { return Scale; }
    void SetScale(glm::vec3 NewScale) { Scale = NewScale; }

    CTransform operator+(const CTransform& Other) const {
        return CTransform(
            Location + Other.Location,
            Rotation + Other.Rotation,
            Scale + Other.Scale
        );
    }

    CTransform operator-(const CTransform& Other) const {
        return CTransform(
            Location - Other.Location,
            Rotation - Other.Rotation,
            Scale - Other.Scale
        );
    }

    CTransform operator*(const CTransform& Other) const {
        return CTransform(
            Location * Other.Location,
            Rotation * Other.Rotation,
            Scale * Other.Scale
        );
    }

    CTransform operator/(const CTransform& Other) const {
        return CTransform(
            Location / Other.Location,
            Rotation / Other.Rotation,
            Scale / Other.Scale
        );
    }

    CTransform operator*(float Scalar) const {
        return CTransform(
            Location * Scalar,
            Rotation * Scalar,
            Scale * Scalar
        );
    }

    CTransform operator/(float Scalar) const {
        return CTransform(
            Location / Scalar,
            Rotation / Scalar,
            Scale / Scalar
        );
    }

};

#endif
