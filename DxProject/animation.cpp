#include "animation.h"
#include <assert.h>

Animation::Animation() : 
    m_frames(1), 
    m_currentFrame(1), 
    m_frameSize(0),
    m_lastUpdate(0),
    m_loop(false), 
    m_finished(false)
{
    m_name = "";
}

bool Animation::isCompleted() const
{
    return m_finished;
}

bool Animation::operator < (const Animation & a) const
{
    return m_name < a.m_name;
}

void Animation::updateAnimation (long int elapsed)
{
    m_lastUpdate += elapsed;

    if (m_lastUpdate >= TIME_BETWEEN_ANIM_UPDATES)
    {
        if (m_currentFrame == m_frames) // si dernier frame de l'anim
        {
            if (m_loop) m_currentFrame = 1; // retour au premier frame
            else m_finished = true;
        }
        else m_currentFrame++;

        m_lastUpdate -= TIME_BETWEEN_ANIM_UPDATES;
    }
}

RECT Animation::getCurrentFrame() const
{
    RECT rectangle;

    rectangle.left = m_startFrameCorner.first + (m_frameSize * (m_currentFrame - 1));
    rectangle.top = m_startFrameCorner.second;
    
    rectangle.right = m_startFrameCorner.first + (m_frameSize * m_currentFrame);
    rectangle.bottom = m_startFrameCorner.second + m_frameSize;

    return rectangle;
}

std::istream& operator >> (std::istream& is, Animation& anim) {
    char tir, po, vir, pf;

    is >> tir;
    if(is){
        is >> anim.m_name;
        is >> po >> anim.m_startFrameCorner.first >> vir >> anim.m_startFrameCorner.second >> pf;
        is >> anim.m_frames;
        is >> anim.m_loop;

        assert(tir=='-');
        assert(po=='(');
        assert(vir==',');
        assert(pf==')');
    }

    return is;
}