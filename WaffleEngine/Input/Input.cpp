#include "Input.hpp"
#include "Core/App.hpp"

namespace Waffle {

int Input::m_KeyStates[512] = {0};
int Input::m_MouseButtonStates[8] = {0};
glm::vec2 Input::m_MousePosition = glm::vec2(0.0f, 0.0f);
Input::CursorMode Input::m_CursorMode = Input::CursorMode::Normal;
GLFWwindow* Input::s_WindowHandle = nullptr;

void Input::Init(GLFWwindow* windowHandle) {
    s_WindowHandle = windowHandle;
    glfwSetKeyCallback(windowHandle, KeyCallback);
    glfwSetMouseButtonCallback(windowHandle, MouseButtonCallback);
    glfwSetCursorPosCallback(windowHandle, MousePositionCallback);
}

void Input::SetCursorMode(CursorMode mode) {
    glfwSetInputMode(s_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + static_cast<int>(mode));
}

bool Input::IsKeyDown(KeyCode keycode) {
    int state = glfwGetKey(s_WindowHandle, static_cast<int>(keycode));
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsKeyPressed(KeyCode keycode) {
	int state = glfwGetKey(s_WindowHandle, static_cast<int>(keycode));
	return state == GLFW_PRESS;
}

bool Input::IsKeyReleased(KeyCode keycode) {
	int state = glfwGetKey(s_WindowHandle, static_cast<int>(keycode));
	return state == GLFW_RELEASE;
}

bool Input::IsKeyCombinationPressedRecursive(const std::vector<KeyCode>& keys, size_t currentIndex) {
    // Base case: if all keys have been checked and they were all pressed, return true
    if (currentIndex == keys.size()) {
        return true;
    }

    // Base case: if any key in the combination is not pressed, return false
    if (!IsKeyPressed(keys[currentIndex])) {
        return false;
    }

    // Recursive case: move to the next key in the combination
    return IsKeyCombinationPressedRecursive(keys, currentIndex + 1);
}

bool Input::IsKeyCombinationPressed(const std::vector<KeyCode>& keys) {
    // Start the recursion from the first key in the combination
    return IsKeyCombinationPressedRecursive(keys, 0);
}

bool Input::IsMouseButtonDown(MouseButton button) {
    int state = glfwGetMouseButton(s_WindowHandle, static_cast<int>(button));
    return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition() {
    double x, y;
    glfwGetCursorPos(s_WindowHandle, &x, &y);
    return glm::vec2(static_cast<float>(x), static_cast<float>(y));
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_RELEASE) {
        m_KeyStates[key] = action;
    }
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_RELEASE) {
        m_MouseButtonStates[button] = action;
    }
}

void Input::MousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
    m_MousePosition.x = static_cast<float>(xpos);
    m_MousePosition.y = static_cast<float>(ypos);
}

}
