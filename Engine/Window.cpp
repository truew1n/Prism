#include "Window.h"

CWindow::CWindow()
{
    Window = nullptr;
}

CWindow::~CWindow()
{
    if (Window) {
        glfwDestroyWindow(Window);
    }
    glfwTerminate();
}

int CWindow::InitializeGLFW()
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    return 1;
}

void CWindow::Hint(EWindowHint Hint, EWindowHintValue HintValue)
{
    glfwWindowHint(static_cast<int32_t>(Hint), static_cast<int32_t>(HintValue));
}

void CWindow::Hint(EWindowHint Hint, int32_t HintValue) {
    glfwWindowHint(static_cast<int32_t>(Hint), HintValue);
}

void CWindow::MakeContextCurrent(CWindow *Window)
{
    if (!Window) return;

    if (!Window->Window) return;

    glfwMakeContextCurrent(Window->Window);
}


CWindow *CWindow::Create(int32_t Width, int32_t Height, const char *Title)
{
    CWindow *NewWindow = new CWindow();
    NewWindow->Window = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);
    
    if (!NewWindow->Window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    return NewWindow;
}

void CWindow::SwapInterval(int32_t Interval)
{
    glfwSwapInterval(Interval);
}

void CWindow::PollEvents()
{
    glfwPollEvents();
}

void CWindow::GetError(const char **ErrorMessage)
{
    glfwGetError(ErrorMessage);
}

void CWindow::Terminate()
{
    glfwTerminate();
}


int CWindow::InitializeGLEW()
{
    return glewInit();
}

void CWindow::SetInputMode(EInputMode Mode, EInputModeValue ModeValue)
{
    glfwSetInputMode(Window, static_cast<int32_t>(Mode), static_cast<int32_t>(ModeValue));
}

void CWindow::SetWindowStorage(void *Data)
{
    glfwSetWindowUserPointer(Window, Data);
}

void *CWindow::GetWindowStorage()
{
    return glfwGetWindowUserPointer(Window);
}

bool CWindow::ShouldClose() const
{
    return glfwWindowShouldClose(Window);
}

void CWindow::SwapBuffers() const
{
    glfwSwapBuffers(Window);
}
