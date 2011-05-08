#ifndef _BRUNODEA_CG_T2_FUNCTIONS_HPP_
#define _BRUNODEA_CG_T2_FUNCTIONS_HPP_

#include "glfw.h"

inline GLuint loadTexture(const char *path)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    if(glfwLoadTexture2D(path, GLFW_BUILD_MIPMAPS_BIT | GLFW_ALPHA_MAP_BIT))
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        //std::cout << "Image " << path << " successfully loaded." << std::endl;
        return texture;
    }
        
    //std::cout << "Image " << path << " couldn't be loaded." << std::endl;
    return -1;
}

#endif
