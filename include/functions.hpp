#ifndef _BRUNODEA_CG_T2_FUNCTIONS_HPP_
#define _BRUNODEA_CG_T2_FUNCTIONS_HPP_

#include "glfw.h"

GLuint loadTexture(const char *path)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if(glfwLoadTexture2D(path, GLFW_BUILD_MIPMAPS_BIT))
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        return texture;
    }

    return -1;
}

#endif
