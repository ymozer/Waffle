#include "Window.hpp"

Window::Window(const char* title, int width, int height)
    : m_Window(nullptr) {
    Init(title, width, height);
}

Window::~Window() {
    Shutdown();
}

void Window::Init(const char* title, int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (m_Window == nullptr) {
        // Handle error
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_Window);
}

void Window::Shutdown() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Window::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_Window);
}

GLFWwindow* Window::GetNativeWindow() const {
    return m_Window;
}
