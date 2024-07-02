#define STB_IMAGE_IMPLEMENTATION
#include "../includes/stb_image.h"

#include "glad/glad.h"
#include <iostream>

unsigned int load_texture(const char* texturePath, int* width, int* height, int* nrChannels)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath, width, height, nrChannels, 0);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = GL_RGB;

    if (*nrChannels == 4)
        format = GL_RGBA;

    if (!data)
    {
        std::cout << "Failed to load texture" << std::endl;
        return -1;
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *width, *height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        return texture;
    }
}

