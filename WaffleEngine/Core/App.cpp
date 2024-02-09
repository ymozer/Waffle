#include "App.hpp"
#include "Log.hpp"
#include "Window.hpp"

App::App() {
    Log::Init();
    Log::Print("App started");
    // Initialize GLFW here or in the Window constructor
}

App::~App() {
    Log::Print("App closing");
}

void App::Run() {
    Window window("WaffleEngine", 800, 600);

    while (!window.ShouldClose()) {
        window.OnUpdate();
    }
}
