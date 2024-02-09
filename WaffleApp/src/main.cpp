#include "Waffle.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <string>


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


void printMatrix(const glm::mat4& mat) {
    const float* pMat = glm::value_ptr(mat);
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            std::cout << pMat[col * 4 + row] << " ";
        }
        std::cout << std::endl;
    }
}

void test_glm() {
    // Create a vector
    glm::vec3 vec(1.0f, 2.0f, 3.0f);
    std::cout << "Original vector: (" << vec.x << ", " << vec.y << ", " << vec.z << ")\n";

    // Scale the vector
    vec *= 2.0f;
    std::cout << "Scaled vector: (" << vec.x << ", " << vec.y << ", " << vec.z << ")\n";

    // Create a transformation matrix (translate + rotate)
    glm::mat4 trans = glm::mat4(1.0f); // Identity matrix
    trans = glm::translate(trans, glm::vec3(1.0f, 2.0f, 3.0f)); // Translate
    trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate 90 degrees around the Z axis

    std::cout << "Transformation matrix:\n";
    printMatrix(trans);

    // Apply the transformation to the vector
    glm::vec4 transformedVec = trans * glm::vec4(vec, 1.0f);
    std::cout << "Transformed vector: (" << transformedVec.x << ", " << transformedVec.y << ", " << transformedVec.z << ")\n";
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui + GLFW + GLAD + GLM Example", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD
    if (!gladLoaderLoadGL()) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

	test_glm();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark(); // Set style

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render ImGui
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}