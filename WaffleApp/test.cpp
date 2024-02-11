#include "WaffleEngine.hpp"
#include "App.hpp"
#include "Timer.hpp"
#include "Input.hpp"
#include "Texture.hpp"
#include "ShaderManager.hpp"
#include "GLCheckError.hpp"


#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <iostream>

class TestLayer : public Waffle::Layer
{
public:
    TestLayer() : Layer() {}
    virtual ~TestLayer() = default;

    Waffle::Timer timer;
    Waffle::ShaderManager shader;
    Waffle::Texture texture;
    Waffle::Texture skybox;
    unsigned int VBO, VAO;

    void OnAttach() override
    {
        std::cout << "TestLayer attached" << std::endl;

        // enable OpenGL debug context if context allows for debug context
        int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
        {
            std::cout << "OpenGL debug context enabled" << std::endl;
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
            glDebugMessageCallback(glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }

        timer.start();
        shader.start();

        //--------------------- Shader ---------------------
        
        shader.addShaderFromFile("assets/test.frag", GL_FRAGMENT_SHADER);
        shader.addShaderFromFile("assets/test.vert", GL_VERTEX_SHADER);
        shader.linkProgram();

        //--------------------- Texture ---------------------

        texture.SetPath("assets/texture.jpeg");
        uint32_t textureID = texture.Load();
        uint32_t skyboxID  = skybox.LoadCubemap({
            "assets/skybox1/px-2.png",
            "assets/skybox1/nx-2.png",
            "assets/skybox1/py-2.png",
            "assets/skybox1/ny-2.png",
            "assets/skybox1/pz-2.png",
            "assets/skybox1/nz-2.png",
        });

        //--------------------- Vertex Array ---------------------

    }

    void OnDetach() override
    {
        std::cout << "TestLayer detached" << std::endl;
        timer.stop();

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        texture.Unbind();
        skybox.Unbind();
    }

    void OnUpdate(float ts) override
    {
        glm::vec2 mousePosition{Waffle::Input::GetMousePosition()};
        // std::cout << "Mouse position: " << mousePosition.x << ", " << mousePosition.y << std::endl;
        shader.use();

        shader.setUniform("u_Time", (float)timer.elapsedMilliseconds());
        shader.setUniform("u_Mouse", mousePosition);

        shader.setUniform("u_Texture", 0);
        shader.setUniform("u_Skybox", 1);

        texture.Bind(0);
        skybox.Bind(1);
        
    }

    void OnUIRender() override
    {
        ImGui::Begin("TestLayer");
        ImGui::Text("Hello, world!");
        ImGui::End();
    }
};

Waffle::App *Waffle::CreateApp(int argc, char **argv)
{
    Waffle::App *app = new Waffle::App();
    app->PushLayer<TestLayer>();
    return app;
}
