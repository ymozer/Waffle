#pragma once

#include <stb_image.h>
#include <string>

namespace Waffle
{
    class Texture
    {
    public:
        Texture();
        ~Texture();

        uint32_t Load();
        uint32_t LoadCubemap(std::vector<std::string> faces);

        void Bind(unsigned int slot) const;
        void Unbind() const;

        inline bool operator==(const Texture &other) const { return m_RendererID == other.m_RendererID; }

        // setters 
        inline void SetPath(const std::string &path) { m_Path = path; }
        inline void SetWidth(int width) { m_Width = width; }
        inline void SetHeight(int height) { m_Height = height; }

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

    private:
        std::string m_Path;
        unsigned int m_RendererID;
        unsigned char *m_LocalBuffer;
        int m_Width, m_Height, m_BPP;

    };
} // namespace Waffle
