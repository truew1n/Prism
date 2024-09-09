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
struct SInputState {
    bool WPressed = false;
    bool SPressed = false;
    bool APressed = false;
    bool DPressed = false;
    bool SPACEPressed = false;
    bool CPressed = false;
    bool SHIFTPressed = false;
};

SInputState InputState;

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

bool IsWireframe = false;

void KeyCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    if (Action == GLFW_PRESS || Action == GLFW_RELEASE) {
        bool IsPressed = (Action == GLFW_PRESS);

        switch (Key) {
            case GLFW_KEY_W: InputState.WPressed = IsPressed; break;
            case GLFW_KEY_S: InputState.SPressed = IsPressed; break;
            case GLFW_KEY_A: InputState.APressed = IsPressed; break;
            case GLFW_KEY_D: InputState.DPressed = IsPressed; break;
            case GLFW_KEY_SPACE: InputState.SPACEPressed = IsPressed; break;
            case GLFW_KEY_C: InputState.CPressed = IsPressed; break;
            case GLFW_KEY_LEFT_SHIFT: InputState.SHIFTPressed = IsPressed; break;
            case GLFW_KEY_E: {
                if(IsPressed) {
                    if(IsWireframe) {
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        IsWireframe = false;
                    } else {
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        IsWireframe = true;
                    }
                }
                break;
            }
            default: break;
        }
    }
}

float Speed = 5.0f;

void ProcessInputAndMoveActor(CFDCubeActor *CubeActor, float DeltaTime)
{
    CTransform CubeActorTransform = CubeActor->GetTransform();
    CPlayerController *Controller = Cast<CPlayerController *>(CubeActor->GetController());
    CCamera *Camera = Controller->GetCameraComponent()->GetCamera();
    glm::vec3 CameraForward = Camera->CalculateFront();
    glm::vec3 CameraRight = Camera->CalculateRight();
    glm::vec3 CameraUp = Camera->CalculateUp();
    
    float MovementSpeed = Speed * DeltaTime;

    if (InputState.WPressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() + CameraForward * MovementSpeed);
    }
    if (InputState.SPressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() - CameraForward * MovementSpeed);
    }
    if (InputState.APressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() - CameraRight * MovementSpeed);
    }
    if (InputState.DPressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() + CameraRight * MovementSpeed);
    }
    if (InputState.SPACEPressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() + glm::vec3(0.0f, 1.0f, 0.0f) * MovementSpeed);
    }
    if (InputState.CPressed) {
        CubeActorTransform.SetLocation(CubeActorTransform.GetLocation() - glm::vec3(0.0f, 1.0f, 0.0f) * MovementSpeed);
    }
    if (InputState.SHIFTPressed) {
        Speed = 50.0f;
    }
    if (!InputState.SHIFTPressed) {
        Speed = 5.0f;
    }

    CubeActor->SetTransform(CubeActorTransform);
}

#include "ShaderStorageBuffer.hpp"

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
        const char *Message;
        glfwGetError(&Message);
        std::cerr << "Failed to create GLFW Window!" << std::endl;
        std::cerr << Message << std::endl;
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

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
