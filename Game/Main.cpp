#include <iostream>
#include <chrono>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "MeshFactory.hpp"
#include "BaseMaterial.hpp"

// Global camera variables
glm::vec3 CameraPosition(0.0f, 0.0f, 3.0f);
glm::vec3 CameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 CameraUp(0.0f, 1.0f, 0.0f);
float Yaw = -90.0f;
float Pitch = 0.0f;
float LastX = 800.0f;
float LastY = 600.0f;
bool FirstMouse = true;
float CameraSpeed = 10.0f;

void ResizeCallback(GLFWwindow *Window, int32_t FrameBufferWidth, int32_t FrameBufferHeight)
{
    glViewport(0, 0, FrameBufferWidth, FrameBufferHeight);
    float AspectRatio = static_cast<float>(FrameBufferWidth) / FrameBufferHeight;
    float FOV = glm::radians(45.0f);
    float NearPlane = 0.1f;
    float FarPlane = 100.0f;

    glm::mat4 ProjectionMatrix = glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
    CFDBaseMaterial *BaseMaterial = static_cast<CFDBaseMaterial*>(glfwGetWindowUserPointer(Window));
    BaseMaterial->SetProjection(ProjectionMatrix);
}

void MouseCallback(GLFWwindow* Window, double xpos, double ypos)
{
    int cursorMode = glfwGetInputMode(Window, GLFW_CURSOR);
    
    if (cursorMode == GLFW_CURSOR_DISABLED) {
        if (FirstMouse) {
            LastX = xpos;
            LastY = ypos;
            FirstMouse = false;
        }

        float xoffset = xpos - LastX;
        float yoffset = LastY - ypos; // reversed since y-coordinates go from bottom to top
        LastX = xpos;
        LastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        CameraFront = glm::normalize(front);
    }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        static bool cursorVisible = false;
        cursorVisible = !cursorVisible;
        
        if (cursorVisible) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
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
        std::cerr << "Failed to create GLFW Window!\n" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(Window, ResizeCallback);
    glfwSetCursorPosCallback(Window, MouseCallback);
    glfwSetKeyCallback(Window, KeyCallback); // Register key callback

    glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(Window);
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Glew failed to initialize!" << std::endl;
        return -1;
    }

    CFDBaseMaterial *BaseMaterial = new CFDBaseMaterial();
    BaseMaterial->Bind();
    glfwSetWindowUserPointer(Window, BaseMaterial);

    CMesh *First = new CMesh();
    First->SetMaterial(BaseMaterial);

    CMesh *Second = new CMesh();
    Second->SetMaterial(BaseMaterial);
    
    CMesh *Third = CMeshFactory::GenerateSphere(1.0f, 32, 32);
    Third->SetMaterial(BaseMaterial);

    // Set initial projection matrix
    float AspectRatio = static_cast<float>(WindowWidth) / WindowHeight;
    float FOV = glm::radians(45.0f);
    float NearPlane = 0.1f;
    float FarPlane = 100.0f;

    glm::mat4 ProjectionMatrix = glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
    BaseMaterial->SetProjection(ProjectionMatrix);

    glEnable(GL_DEPTH_TEST);
    
    bool IsPressed = false;
    bool Mode = false;

    auto LastTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(Window)) {
        auto CurrentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> ElapsedTime = CurrentTime - LastTime;
        float DeltaTime = ElapsedTime.count();
        LastTime = CurrentTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS) {
            CameraPosition -= glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed * DeltaTime;
        }
        if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS) {
            CameraPosition += glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed * DeltaTime;
        }
        if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS) {
            CameraPosition += CameraFront * CameraSpeed * DeltaTime;
        }
        if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS) {
            CameraPosition -= CameraFront * CameraSpeed * DeltaTime;
        }
        if (glfwGetKey(Window, GLFW_KEY_E) == GLFW_PRESS) {
            if(!IsPressed) {
                if(Mode) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    Mode = false;
                } else {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    Mode = true;
                }
                IsPressed = true;
            }
        }
        if(glfwGetKey(Window, GLFW_KEY_E) == GLFW_RELEASE) {
            IsPressed = false;
        }

        // Update view matrix based on camera position and direction
        glm::mat4 ViewMatrix = glm::lookAt(CameraPosition, CameraPosition + CameraFront, CameraUp);
        BaseMaterial->SetView(ViewMatrix);

        BaseMaterial->SetWorldPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        First->Draw();

        BaseMaterial->SetWorldPosition(glm::vec3(2.0f, 0.0f, 0.0f));
        Second->Draw();

        BaseMaterial->SetWorldPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
        Third->Draw();

        glfwSwapBuffers(Window);
        glfwPollEvents();
    }

    delete BaseMaterial;
    delete First;
    delete Second;
    delete Third;

    glfwDestroyWindow(Window);
    glfwTerminate();
    return 0;
}
