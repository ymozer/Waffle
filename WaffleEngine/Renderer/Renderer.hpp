#pragma once

namespace Waffle
{
    class Renderer
    {
    public:
        virtual Renderer();
        virtual ~Renderer();
 
        virtual void Init();
        virtual void Shutdown();
        virtual void OnUpdate();
        virtual void OnRender();

    };
} 
