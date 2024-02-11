#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


namespace Waffle {
    class UI {
    public:
        UI(GLFWwindow* window);

        void initialize();
        void shutdown();
        void renderStart();
        void renderFinalize();

    private:
        GLFWwindow* window;
    };
}