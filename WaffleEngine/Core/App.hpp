#pragma once
#include "Layer.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <memory>

namespace Waffle
{
    struct AppSpecs
    {
        std::string Name = "Waffle App";
        uint32_t Width = 1280;
        uint32_t Height = 720;
    };
    class App
    {
    public:
        App(const AppSpecs &specs = AppSpecs());
        ~App();

        template <typename T>
        void PushLayer()
        {
            static_assert(std::is_base_of<Layer, T>::value, "Pushed type is not subclass of Layer!");
            m_LayerStack.emplace_back(std::make_shared<T>())->OnAttach();
        }

        void PushLayer(const std::shared_ptr<Layer> &layer)
        {
            m_LayerStack.emplace_back(layer);
            layer->OnAttach();
        }

        static App &Get();

        AppSpecs GetSpecs() const { return m_Specs; }

        GLFWwindow *GetNativeWindow() const;
        GLFWwindow *GetWindowHandle() const { return m_Window; }

        float GetTime();
        float GetFrameTime() { return m_FrameTime; }
        float GetTimeStep() { return m_TimeStep; }

        void SetVSync(bool enabled);
        bool IsVSync() const { return m_isVSync; }

        void ToggleFullScreen();
        void ToggleMaximized();

        void Init();
        void Run();
        void Shutdown();

    private:
        bool m_running = false;
        bool m_isVSync = true;
        GLFWwindow *m_Window;
        AppSpecs m_Specs;
        std::vector<std::shared_ptr<Layer>> m_LayerStack;
        bool m_FullScreen = false;
        bool m_Maximized = false;

        float m_LastFrameTime = 0.0f;
        float m_FrameTime = 0.0f;
        float m_TimeStep = 0.0f;
    };
    App *CreateApp(int argc, char **argv);
}
