#include <iostream>
#include <chrono>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "MeshFactory.hpp"

#include "BaseMaterial.hpp"

void ResizeCallback(GLFWwindow *Window, int32_t FrameBufferWidth, int32_t FrameBufferHeight)
{
    glViewport(0, 0, FrameBufferWidth, FrameBufferHeight);
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
    glfwMakeContextCurrent(Window);
    glfwSwapInterval(0);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Glew failed to initialize!" << std::endl;
        return -1;
    }

    CFDBaseMaterial BaseMaterial = CFDBaseMaterial();
    BaseMaterial.Bind();

    CMesh First = CMesh();
    First.SetMaterial(&BaseMaterial);

    CMesh Second = CMesh();
    Second.SetMaterial(&BaseMaterial);

    CMesh Third = CMeshFactory::GeneratePlaneRing(0.4f, 1.0f, 32);
    Second.SetMaterial(&BaseMaterial);

    float AspectRatio = static_cast<float>(WindowWidth) / WindowHeight;
    float FOV = glm::radians(120.0f);
    float NearPlane = 0.1f;
    float FarPlane = 100.0f;

    glm::mat4 ProjectionMatrix = glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);
    BaseMaterial.SetProjection(ProjectionMatrix);

    glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    float CameraSpeed = 10.0f;

    glm::mat4 ViewMatrix = glm::translate(glm::mat4(1.0f), -CameraPosition);
    BaseMaterial.SetView(ViewMatrix);

    glm::vec3 WorldPosition1 = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 WorldPosition2 = glm::vec3(2.0f, 0.0f, 0.0f);
    glm::vec3 WorldPosition3 = glm::vec3(-2.0f, 0.0f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    bool IsPressed = false;
    bool Mode = false;

    float DeltaSum = 0.0f;
    int j = 0, i = 0;
    auto LastTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(Window)) {
        auto CurrentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> ElapsedTime = CurrentTime - LastTime;
        float DeltaTime = ElapsedTime.count();
        LastTime = CurrentTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS) {
            CameraPosition.x -= CameraSpeed * DeltaTime;
        }
        if(glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS) {
            CameraPosition.x += CameraSpeed * DeltaTime;
        }
        if(glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS) {
            CameraPosition.y += CameraSpeed * DeltaTime;
        }
        if(glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS) {
            CameraPosition.y -= CameraSpeed * DeltaTime;
        }
        if(glfwGetKey(Window, GLFW_KEY_E) == GLFW_PRESS) {
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
        if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            CameraPosition.z -= CameraSpeed * DeltaTime;
        }
        if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            CameraPosition.z += CameraSpeed * DeltaTime;
        }

        ViewMatrix = glm::translate(glm::mat4(1.0f), -CameraPosition);
        BaseMaterial.SetView(ViewMatrix);

        BaseMaterial.SetWorldPosition(WorldPosition1);
        First.Draw();

        BaseMaterial.SetWorldPosition(WorldPosition2);
        Second.Draw();

        BaseMaterial.SetWorldPosition(WorldPosition3);
        Third.Draw();

        glfwSwapBuffers(Window);
        glfwPollEvents();
    }

    BaseMaterial.Delete();

    glfwDestroyWindow(Window);
    glfwTerminate();
    return 0;
}
