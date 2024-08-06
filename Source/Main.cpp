#include <iostream>
#include <chrono>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "ElementBuffer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"


void ResizeCallback(GLFWwindow *Window, int32_t FrameBufferWidth, int32_t FrameBufferHeight)
{
    glViewport(0, 0, FrameBufferWidth, FrameBufferHeight);
}

void GeneratePlaneRing(float InnerRadius, float OuterRadius, int Segments, std::vector<SVertex>& Vertices, std::vector<uint32_t>& Indices)
{
    float AngleStep = 2.0f * M_PI / Segments;

    Vertices.clear();
    for (int i = 0; i < Segments; ++i) {
        float Angle = i * AngleStep;
        float XOuter = OuterRadius * cos(Angle);
        float YOuter = OuterRadius * sin(Angle);
        float XInner = InnerRadius * cos(Angle);
        float YInner = InnerRadius * sin(Angle);

        Vertices.push_back(SVertex(glm::vec3(XOuter, YOuter, 0.0f), glm::vec2((XOuter / OuterRadius + 1.0f) / 2.0f, (YOuter / OuterRadius + 1.0f) / 2.0f)));
        Vertices.push_back(SVertex(glm::vec3(XInner, YInner, 0.0f), glm::vec2((XInner / InnerRadius + 1.0f) / 2.0f, (YInner / InnerRadius + 1.0f) / 2.0f)));
    }

    Indices.clear();
    for (int i = 0; i < Segments; ++i) {
        int Next = (i + 1) % Segments;
        
        Indices.push_back(i * 2);
        Indices.push_back(Next * 2);
        Indices.push_back(i * 2 + 1);

        Indices.push_back(Next * 2);
        Indices.push_back(Next * 2 + 1);
        Indices.push_back(i * 2 + 1);
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

    std::string WindowTitle = "Procedural Animation";
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

    CShader DefaultShader;
    DefaultShader.Create();
    DefaultShader.Load("Source\\Resource\\Default.vert", EShaderType::VERTEX);
    DefaultShader.Load("Source\\Resource\\Default.frag", EShaderType::FRAGMENT);
    DefaultShader.Activate();

    std::vector<SVertex> Vertices = {
        SVertex(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)),
        SVertex(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
        SVertex(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
        SVertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f))
    };

    std::vector<uint32_t> Indices = {
        0, 1, 2,
        0, 2, 3
    };

    CVertexArray VertexArray;
    VertexArray.Bind();
    CVertexBuffer VertexBuffer(Vertices);
    CElementBuffer ElementBuffer(Indices);

    VertexArray.LinkAttribute(VertexBuffer, 0, 3, GL_FLOAT, sizeof(SVertex), (void*)0);
    VertexArray.LinkAttribute(VertexBuffer, 1, 2, GL_FLOAT, sizeof(SVertex), (void*)(3 * sizeof(float)));
    VertexArray.Unbind();

    float AspectRatio = static_cast<float>(WindowWidth) / WindowHeight;
    float FOV = glm::radians(120.0f);
    float NearPlane = 0.1f;
    float FarPlane = 100.0f;

    glm::mat4 ProjectionMatrix = glm::perspective(FOV, AspectRatio, NearPlane, FarPlane);

    DefaultShader.Activate();
    GLint ProjectionLoc = glGetUniformLocation(DefaultShader.GetId(), "Projection");
    glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

    glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    float CameraSpeed = 10.0f;

    glm::mat4 ViewMatrix = glm::translate(glm::mat4(1.0f), -CameraPosition);
    GLint ViewLoc = glGetUniformLocation(DefaultShader.GetId(), "View");
    glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, glm::value_ptr(ViewMatrix));

    CTexture SomeTexture = CTexture("Assets/Textures/Font/Font.png", "Diffuse", 0);
    SomeTexture.TextureUnit(DefaultShader, "Diffuse", 0);
    SomeTexture.Bind();

    GLint WorldPositionLocation = glGetUniformLocation(DefaultShader.GetId(), "WorldPosition");
    glUniform3fv(WorldPositionLocation, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float DeltaSum = 0.0f;
    int j = 0, i = 0;
    auto LastTime = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(Window)) {
        auto CurrentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> ElapsedTime = CurrentTime - LastTime;
        float DeltaTime = ElapsedTime.count();
        LastTime = CurrentTime;
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        GLint UniformX = glGetUniformLocation(DefaultShader.GetId(), "X");
        glUniform1i(UniformX, i);

        GLint UniformY = glGetUniformLocation(DefaultShader.GetId(), "Y");
        glUniform1i(UniformY, j);

        VertexArray.Bind();
        glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
        VertexArray.Unbind();

        if(DeltaSum >= 1.0f) {
            if(++i == 18) {
                i = 0;
                if(++j == 7) {
                    j = 0;
                }
            }
            DeltaSum = 0.0f;
        }

        DeltaSum += DeltaTime;

        glfwSwapBuffers(Window);
        glfwPollEvents();
    }

    glfwDestroyWindow(Window);
    glfwTerminate();
    return 0;
}
