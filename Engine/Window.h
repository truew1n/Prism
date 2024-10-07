#ifndef PE_WINDOW_H
#define PE_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <stdexcept>

enum class EWindowHint : int32_t {
    ContextVersionMajor = GLFW_CONTEXT_VERSION_MAJOR,
    ContextVersionMinor = GLFW_CONTEXT_VERSION_MINOR,
    OpenGLProfile = GLFW_OPENGL_PROFILE
};

enum class EWindowHintValue : int32_t {
    OpenGLCoreProfile = GLFW_OPENGL_CORE_PROFILE
};

enum class EInputMode : int32_t {
    Cursor = GLFW_CURSOR
};

enum class EInputModeValue : int32_t {
    CursorDisabled = GLFW_CURSOR_DISABLED,
    CursorNormal = GLFW_CURSOR_NORMAL,
};

class CWindow {
//private:
public:
    GLFWwindow *Window;
    int32_t Width;
    int32_t Height;
public:
    CWindow();
    ~CWindow();

    static int InitializeGLFW();
    static int InitializeGLEW();

    static void Hint(EWindowHint Hint, EWindowHintValue HintValue);
    static void Hint(EWindowHint Hint, int32_t HintValue);
    
    static CWindow *Create(int32_t Width, int32_t Height, const char *Title);

    static void MakeContextCurrent(CWindow *Window);
    static void SwapInterval(int32_t Interval);

    static void PollEvents();

    static void GetError(const char **ErrorMessage);
    static void Terminate();

    void SetInputMode(EInputMode Mode, EInputModeValue ModeValue);
    void SetWindowStorage(void *Data);
    void *GetWindowStorage();
    bool ShouldClose() const;
    void SwapBuffers() const;

    void MouseButtonCallback(GLFWwindow *Window, int32_t Button, int32_t Action, int32_t Mods) {}
    void KeyCallback(GLFWwindow *Window, int32_t Key, int32_t Scancode, int32_t Action, int32_t Mods) {}
    void MouseCallback(GLFWwindow *Window, double X, double Y) {}
    void ResizeCallback(GLFWwindow *Window, int32_t FramebufferWidth, int32_t FramebufferHeight) {}

    int32_t GetWidth() const { return Width; }
    int32_t GetHeight() const { return Height; }
};

#endif
