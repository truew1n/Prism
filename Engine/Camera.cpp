#include "Camera.h"

CCamera::CCamera()
{
    AspectRatio = 1920.0f / 1080.0f;
    FieldOfView = glm::radians(90.0f);
    NearPlane = 0.1f;
    FarPlane = 100.0f;

    Yaw = -90.0f;
    Pitch = 0.0f;
    Roll = 0.0f;
}

CCamera::~CCamera()
{

}

glm::vec3 CCamera::CalculateFront()
{
    glm::vec3 Front;
    Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front.y = sin(glm::radians(Pitch));
    Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    return glm::normalize(Front);
}

glm::vec3 CCamera::CalculateRight()
{
    return glm::normalize(glm::cross(CalculateFront(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

glm::vec3 CCamera::CalculateUp()
{
    return glm::normalize(glm::cross(CalculateRight(), CalculateFront()));
}

glm::mat4 CCamera::GetViewMatrix(glm::mat4 WorldTransform, CTransform LocalTransform)
{
    glm::vec3 Location = glm::vec3(WorldTransform * glm::vec4(LocalTransform.GetLocation(), 1.0f));
    return glm::lookAt(Location, Location + CalculateFront(), CalculateUp());
}

glm::mat4 CCamera::GetProjectionMatrix()
{
    return glm::perspective(FieldOfView, AspectRatio, NearPlane, FarPlane);
}