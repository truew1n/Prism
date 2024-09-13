#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>

#include "FunctionLibrary.h"
#include "MainLevel.h"
#include "BaseMaterial.h"
#include "Player.h"
#include "CollisionSolver.h"
#include "MeshFactory.h"


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
bool IsWireframe = false;
bool IsCursorCaptured = true;

void ResizeCallback(GLFWwindow *Window, int32_t FramebufferWidth, int32_t FramebufferHeight)
{
    glViewport(0, 0, FramebufferWidth, FramebufferHeight);
    CFDMainLevel *MainLevel = ForceCast<CFDMainLevel *>(glfwGetWindowUserPointer(Window));
    MainLevel->ResizeCallback(FramebufferWidth, FramebufferHeight);
}

void MouseCallback(GLFWwindow *Window, double X, double Y)
{
    if (!IsCursorCaptured) return;

    CFDMainLevel *MainLevel = ForceCast<CFDMainLevel *>(glfwGetWindowUserPointer(Window));
    MainLevel->MouseCallback(X, Y);
}

void KeyCallback(GLFWwindow *Window, int Key, int Scancode, int Action, int Mods)
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
                if (IsPressed) {
                    if (IsWireframe) {
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        IsWireframe = false;
                    }
                    else {
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        IsWireframe = true;
                    }
                }
                break;
            }
            case GLFW_KEY_ESCAPE: {
                if (IsPressed) {
                    if (IsCursorCaptured) {
                        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                        IsCursorCaptured = false;
                    }
                }
                break;
            }
            default: break;
        }
    }
}

void MouseButtonCallback(GLFWwindow *Window, int Button, int Action, int Mods)
{
    if (Button == GLFW_MOUSE_BUTTON_LEFT && Action == GLFW_PRESS) {
        if (!IsCursorCaptured) {
            glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            IsCursorCaptured = true;
        }
    }
}

float Speed = 5.0f;

void ProcessInputAndMoveActor(CFDPlayer *Player, float DeltaTime)
{
    CTransform *PlayerTransform = Player->GetTransformRef();
    CPlayerController *Controller = Cast<CPlayerController *>(Player->GetController());
    CCamera *Camera = Controller->GetCameraComponent()->GetCamera();
    glm::vec3 CameraForward = Camera->CalculateFront();
    glm::vec3 CameraRight = Camera->CalculateRight();
    glm::vec3 CameraUp = Camera->CalculateUp();

    float MovementSpeed = Speed * DeltaTime;

    if (InputState.WPressed) {
        PlayerTransform->Translate(CameraForward * MovementSpeed);
    }
    if (InputState.SPressed) {
        PlayerTransform->Translate(CameraForward * -MovementSpeed);
    }
    if (InputState.APressed) {
        PlayerTransform->Translate(CameraRight * -MovementSpeed);
    }
    if (InputState.DPressed) {
        PlayerTransform->Translate(CameraRight * MovementSpeed);
    }
    if (InputState.SPACEPressed) {
        PlayerTransform->Translate(glm::vec3(0.0f, 1.0f, 0.0f) * MovementSpeed);
    }
    if (InputState.CPressed) {
        PlayerTransform->Translate(glm::vec3(0.0f, 1.0f, 0.0f) * -MovementSpeed);
    }
    if (InputState.SHIFTPressed) {
        Speed = 50.0f;
    }
    if (!InputState.SHIFTPressed) {
        Speed = 5.0f;
    }
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

    glfwSetWindowUserPointer(Window, (void *)MainLevel);

    glfwSetFramebufferSizeCallback(Window, ResizeCallback);
    glfwSetCursorPosCallback(Window, MouseCallback);
    glfwSetKeyCallback(Window, KeyCallback);
    glfwSetMouseButtonCallback(Window, MouseButtonCallback);

    glEnable(GL_DEPTH_TEST);

     glEnable(GL_CULL_FACE);
     glCullFace(GL_BACK);
     glFrontFace(GL_CCW);

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    CFDPlayer *Player = Cast<CFDPlayer *>(MainLevel->GetActor(0));

    glClearColor(0.251f, 0.62f, 0.902f, 1.0f);
    auto LastTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(Window)) {
        auto CurrentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> ElapsedTime = CurrentTime - LastTime;
        float DeltaTime = ElapsedTime.count();
        LastTime = CurrentTime;

        ProcessInputAndMoveActor(Player, DeltaTime);

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
