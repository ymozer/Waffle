#include "Texture.hpp"


#include <glad/gl.h>

#include <vector>
#include <iostream>



namespace Waffle{

    Texture::Texture()
        : m_Path(""), m_RendererID(0), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
    {
    }


    uint32_t Texture::Load()
    {
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
        glBindTexture(GL_TEXTURE_2D, 0);

        if (m_LocalBuffer)
        {
            stbi_image_free(m_LocalBuffer);
        }
        return m_RendererID;
    }

    /*
    GL_TEXTURE_CUBE_MAP_POSITIVE_X	Right
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X	Left
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y	Top
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y	Bottom
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z	Back
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z	Front
    */
    uint32_t Texture::LoadCubemap(std::vector<std::string> faces)
    {
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);     

        return m_RendererID;
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void Texture::Bind(unsigned int slot = 0) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

    void Texture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }


}
