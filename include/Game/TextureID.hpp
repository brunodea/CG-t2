#ifndef _BRUNODEA_CG_T2_TEXTURE_ID_HPP_
#define _BRUNODEA_CG_T2_TEXTURE_ID_HPP_

/*
 * Classe usada apenas para carregar texturas e guardar suas ids em um vetor estatico.
 */

#include "glfw.h"
#include "macros.h"

namespace Game
{
    enum TexID //ID da textura.
    {
        TEX_PLAYER = 0,
        TEX_NORMAL_SHOT = 1,
        TEX_NORMAL_ENEMY = 2,
        SIZE = 3 //tamanho do vetor (numero de texturas).
    };

    class TextureID
    {
    public:
        static GLuint m_sTextureID[SIZE]; //vetor com a id das texturas.

        static void initTextures()
        {
            m_sTextureID[TEX_PLAYER] = loadTexture("resources/player_ship.tga");
            m_sTextureID[TEX_NORMAL_SHOT] = loadTexture("resources/normal_shot_ball.tga");
            m_sTextureID[TEX_NORMAL_ENEMY] = loadTexture("resources/normal_enemy.tga");
        }

        static void clear()
        {
            for(int i = 0; i < SIZE; i++)
            {
                if(m_sTextureID[i] >= 0)
                    glDeleteTextures(1, &m_sTextureID[i]);
            }
        }

    private:
        static GLuint loadTexture(const char *path)
        {
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            if(glfwLoadTexture2D(path, GLFW_BUILD_MIPMAPS_BIT | GLFW_ALPHA_MAP_BIT))
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                std::cout << "Image " << path << " successfully loaded." << std::endl;
                return texture;
            }
        
            std::cout << "Image " << path << " couldn't be loaded." << std::endl;
            return -1;
        }
    }; //end of struct TextureID.
} //end of namespace Game.
#endif
