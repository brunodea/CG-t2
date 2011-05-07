#ifndef _BRUNODEA_CG_T2_FPS_HPP_
#define _BRUNODEA_CG_T2_FPS_HPP_

class FPS
{
public:
    static FPS *instance();

    inline void setFPS(float fps) { m_fFPS = fps; }
    inline float getFPS() { return m_fFPS; }

private:
    static FPS *m_sInstance;

    float m_fFPS;

private:
    FPS();

}; //end of class FPS.

#endif
