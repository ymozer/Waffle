#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class Window {
public:
    Window(const char* title, int width, int height);
    ~Window();

    void OnUpdate();

    bool ShouldClose() const;
    GLFWwindow* GetNativeWindow() const;

private:
    GLFWwindow* m_Window;
    void Init(const char* title, int width, int height);
    void Shutdown();
};
