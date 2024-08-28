#include <iostream>
#include <chrono>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "FunctionLibrary.hpp"
#include "MainLevel.hpp"
#include "BaseMaterial.hpp"
#include "CubeActor.hpp"
#include "CollisionSolver.hpp"
#include "MeshFactory.hpp"

// Struct to store input state
struct InputState {
    bool WPressed = false;
    bool SPressed = false;
    bool APressed = false;
    bool DPressed = false;
    bool SPACEPressed = false;
    bool CPressed = false;
};

InputState inputState;

void ResizeCallback(GLFWwindow *Window, int32_t FramebufferWidth, int32_t FramebufferHeight)
{
    glViewport(0, 0, FramebufferWidth, FramebufferHeight);
    CFDMainLevel *MainLevel = ForceCast<CFDMainLevel *>(glfwGetWindowUserPointer(Window));
    MainLevel->ResizeCallback(FramebufferWidth, FramebufferHeight);
}

void MouseCallback(GLFWwindow* Window, double X, double Y)
{
    CFDMainLevel *MainLevel = ForceCast<CFDMainLevel *>(glfwGetWindowUserPointer(Window));
    MainLevel->MouseCallback(X, Y);
}

void KeyCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    // Update input state based on the key pressed or released
    if (Action == GLFW_PRESS || Action == GLFW_RELEASE) {
        bool isPressed = (Action == GLFW_PRESS);

        switch (Key) {
            case GLFW_KEY_W: inputState.WPressed = isPressed; break;
            case GLFW_KEY_S: inputState.SPressed = isPressed; break;
            case GLFW_KEY_A: inputState.APressed = isPressed; break;
            case GLFW_KEY_D: inputState.DPressed = isPressed; break;
            case GLFW_KEY_SPACE: inputState.SPACEPressed = isPressed; break;
            case GLFW_KEY_C: inputState.CPressed = isPressed; break;
            default: break;
        }
    }
}

// Function to process input and update the CubeActor
void ProcessInputAndMoveActor(CFDCubeActor *CubeActor, float DeltaTime)
{
    CTransform CubeActorTransform = CubeActor->GetTransform();
    CPlayerController *Controller = Cast<CPlayerController *>(CubeActor->GetController());
    CCamera *Camera = Controller->GetCameraComponent()->GetCamera();
    glm::vec3 CameraForward = Camera->CalculateFront();
    glm::vec3 CameraRight = Camera->CalculateRight();
    glm::vec3 CameraUp = Camera->CalculateUp();
    float MovementSpeed = 5.0f * DeltaTime;

    if (inputState.WPressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() + CameraForward * MovementSpeed);
    }
    if (inputState.SPressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() - CameraForward * MovementSpeed);
    }
    if (inputState.APressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() - CameraRight * MovementSpeed);
    }
    if (inputState.DPressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() + CameraRight * MovementSpeed);
    }
    if (inputState.SPACEPressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() + CameraUp * MovementSpeed);
    }
    if (inputState.CPressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() - CameraUp * MovementSpeed);
    }

    CubeActor->SetTransform(CubeActorTransform);
}


int main(void)
{
    if (!glfwInit()) {
        return -1;
    }

    uint32_t WindowWidth = 1920;
    uint32_t WindowHeight = 1080;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::string WindowTitle = "Prism";
    GLFWwindow *Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle.c_str(), NULL, NULL);
    if (!Window) {
        std::cerr << "Failed to create GLFW Window!\n" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(Window);
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Glew failed to initialize!" << std::endl;
        return -1;
    }

    CFDMainLevel *MainLevel = new CFDMainLevel();
    MainLevel->ResizeCallback(WindowWidth, WindowHeight);

    glfwSetWindowUserPointer(Window, (void *) MainLevel);

    glfwSetFramebufferSizeCallback(Window, ResizeCallback);
    glfwSetCursorPosCallback(Window, MouseCallback);
    glfwSetKeyCallback(Window, KeyCallback);

    glEnable(GL_DEPTH_TEST);

    glm::vec3 Point = glm::vec3(0.2f, 0.0f, 0.0f);
    CTransform Ellipsoid = CTransform();
    Ellipsoid.SetScale(glm::vec3(0.4f, 1.0f, 1.0f));

    std::cout << (CCollisionSolver::SolvePointEllipsoid(Point, Ellipsoid) ? "Collision" : "No Collision") << std::endl;

    CFDCubeActor *CubeActor = Cast<CFDCubeActor *>(MainLevel->GetActor(0));
    
    auto LastTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(Window)) {
        auto CurrentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> ElapsedTime = CurrentTime - LastTime;
        float DeltaTime = ElapsedTime.count();
        LastTime = CurrentTime;

        ProcessInputAndMoveActor(CubeActor, DeltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MainLevel->Tick(DeltaTime);
        MainLevel->Draw();

        glfwSwapBuffers(Window);
        glfwPollEvents();
    }

    delete MainLevel;

    glfwDestroyWindow(Window);
    glfwTerminate();
    return 0;
}
