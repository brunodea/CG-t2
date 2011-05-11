#ifndef _BRUNODEA_CG_T2_FPS_HPP_
#define _BRUNODEA_CG_T2_FPS_HPP_

/*
 * Classe que guarda o valor de interpolacao para ajustar o update onde for necessário.
 */

class FPS
{
public:
    static FPS &instance()
    {
        if(m_sInstance == NULL)
            m_sInstance = new FPS();
        return *m_sInstance;
    }

    void setInterpolation(float d) { m_dInterpolation = d; }
    float getInterpolation() { return m_dInterpolation; }

private:
    FPS() : m_dInterpolation(1) {}
    static FPS *m_sInstance;
    float m_dInterpolation;

}; //end of class FPS.

#endif
