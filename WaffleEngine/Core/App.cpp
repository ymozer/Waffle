#include "App.hpp"
#include "Log.hpp"
#include "Input/Input.hpp"


#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <memory>
#include <iostream>

// globals
extern bool g_ApplicationRunning;

// statics
static Waffle::App *s_Instance = nullptr;

static void SetupImGui(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

static void CleanupImGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

static void glfw_framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void glfw_window_close_callback(GLFWwindow *window)
{
    g_ApplicationRunning = false;
    glfwSetWindowShouldClose(window, GLFW_FALSE);
}

static void glfw_window_focus_callback(GLFWwindow *window, int focused)
{
    if (focused)
    {
        std::cout << "Window focused" << std::endl;
    }
    else
    {
        std::cout << "Window unfocused" << std::endl;
    }
}

namespace Waffle
{

    App::App(const AppSpecs &specs)
        : m_Specs(specs)
    {
        s_Instance = this;
        Init();
        SetupImGui(m_Window);
    }

    App::~App()
    {
        Shutdown();
        s_Instance = nullptr;
    }

    App &App::Get()
    {
        return *s_Instance;
    }

    GLFWwindow *App::GetNativeWindow() const
    {
        return m_Window;
    }

    void App::SetVSync(bool enabled)
    {
        m_isVSync = enabled;
        glfwSwapInterval(m_isVSync ? 1 : 0);
    }

    void App::Init()
    {
        std::cout << "Initializing Waffle Engine" << std::endl;
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            exit(-1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#ifdef DEBUG_MODE
        std::cout << "Debug mode enabled - GLFW Window Hint" << std::endl;
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); // comment this line in a release build! 
#endif

        m_Window = glfwCreateWindow(m_Specs.Width, m_Specs.Height, m_Specs.Name.c_str(), NULL, NULL);
        if (!m_Window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(-1);
        }

        glfwMakeContextCurrent(m_Window);
        if (m_Window == nullptr)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            exit(-1);
        }

        SetVSync(true);

        Input::Init(m_Window);
        // glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_TRUE);
        // glfwSetInputMode(m_Window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
        // glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        glfwSetFramebufferSizeCallback(m_Window, glfw_framebuffer_size_callback);
        glfwSetWindowCloseCallback(m_Window, glfw_window_close_callback);
        glfwSetWindowFocusCallback(m_Window, glfw_window_focus_callback);

        int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0)
        {
            printf("Failed to initialize OpenGL context\n");
            exit(-1);
        }

        // Successfully loaded OpenGL
        printf("Loaded OpenGL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
        glViewport(0, 0, m_Specs.Width, m_Specs.Height);
    }

    void App::ToggleMaximized()
    {
        if (m_Maximized)
        {
            m_Maximized = false;
            glfwRestoreWindow(m_Window);
        }
        else
        {
            m_Maximized = true;
            glfwMaximizeWindow(m_Window);
        }
    }

    void App::ToggleFullScreen()
    {
        if (m_FullScreen)
        {
            m_FullScreen = false;
            glfwSetWindowMonitor(m_Window, nullptr, 100, 100, m_Specs.Width, m_Specs.Height, GLFW_DONT_CARE);
        }
        else
        {
            m_FullScreen = true;
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
    }

    float App::GetTime()
    {
        return (float)glfwGetTime();
    }

    void App::Run()
    {
        m_running = true;
        bool isFullScreenToggled = false;
        bool isMaximizedToggled = false;
        ImGuiIO &io = ImGui::GetIO();

        while (glfwWindowShouldClose(m_Window) == 0 && m_running)
        {
            if (g_ApplicationRunning)
            {
                glfwPollEvents();
            }
            else
            {
                exit(0);
            }

            if (Waffle::Input::IsKeyCombinationPressed({KeyCode::LeftControl, KeyCode::Q}))
            {
                glfw_window_close_callback(m_Window);
            }

            if (Waffle::Input::IsKeyPressed(KeyCode::F))
            {
                if (!isFullScreenToggled)
                {
                    ToggleFullScreen();
                    isFullScreenToggled = true;
                }
            }
            else
            {
                isFullScreenToggled = false;
            }

            if (Waffle::Input::IsKeyPressed(KeyCode::M))
            {
                if (!isMaximizedToggled)
                {
                    ToggleMaximized();
                    isMaximizedToggled = true;
                }
            }
            else
            {
                isMaximizedToggled = false;
            }

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // ----------------- Render -----------------
            if (glfwGetWindowAttrib(m_Window, GLFW_FOCUSED))
            {
                for (auto &layer : m_LayerStack)
                {
                    layer->OnUpdate(m_TimeStep);
                }

                // ----------------- UI -----------------
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                for (auto &layer : m_LayerStack)
                {
                    layer->OnUIRender();
                }

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }
            glfwSwapBuffers(m_Window);
            float time = GetTime();
            m_FrameTime = time - m_LastFrameTime;
            m_TimeStep = glm::min<float>(m_FrameTime, 0.0333f);
            m_LastFrameTime = time;
        }
    }

    void App::Shutdown()
    {
        CleanupImGui();
        glfwDestroyWindow(m_Window);
        glfwTerminate();
        m_running = false;
        m_LayerStack.clear();
    }

} // namespace Waffle
