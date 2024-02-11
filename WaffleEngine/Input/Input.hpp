#pragma once

#include "KeyCodes.hpp"
#include "MouseButtonCodes.hpp"

#include <glm/glm.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Waffle
{

    class Input
    {
    public:
        enum class CursorMode
        {
            Normal = 0,
            Hidden = 1,
            Disabled = 2
        };

        // No constructor or destructor needed for a fully static class

        static void Init(GLFWwindow *windowHandle);

        static void SetCursorMode(CursorMode mode);

        static bool IsKeyDown(KeyCode keycode);
        static bool IsKeyPressed(KeyCode keycode);
        static bool IsKeyReleased(KeyCode keycode);
        static bool IsKeyCombinationPressed(const std::vector<KeyCode> &keys);
        static bool IsKeyCombinationPressedRecursive(const std::vector<KeyCode> &keys, size_t currentIndex);

        static bool IsMouseButtonDown(MouseButton button);
        static glm::vec2 GetMousePosition();

    private:
        static int m_KeyStates[512];
        static int m_MouseButtonStates[8];
        static glm::vec2 m_MousePosition;
        static CursorMode m_CursorMode;

        static GLFWwindow *s_WindowHandle;

        // Callback functions
        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        static void MousePositionCallback(GLFWwindow *window, double xpos, double ypos);
    };

}
