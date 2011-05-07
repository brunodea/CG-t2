#include "FPS.h"

FPS *FPS::m_sInstance = 0;

FPS::FPS()
{
    m_fFPS = 0;
}

FPS *FPS::instance()
{
    if(m_sInstance == 0)
        m_sInstance = new FPS();
    return m_sInstance;
}


