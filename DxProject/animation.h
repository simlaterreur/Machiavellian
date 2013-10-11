#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>

#define TIME_BETWEEN_ANIM_UPDATES 140 // à trouver le sweet spot

class Animation
{
public:
    Animation();

    bool Completed() const;

    void UpdateAnimation(long int);
    RECT GetCurrentFrame() const;

    bool operator < (const Animation &) const;

//private:
    std::string m_name;     // id unique

    std::pair<int,int> m_startFrameCorner;

    int m_frames;               // nombre de frames dans l'anim
    int m_currentFrame;     
    int m_frameSize;    

    bool m_loop;            
    bool m_finished;            // indique fini de jouer le dernier frame d'une anim non loopante

    long int m_lastUpdate;     // quand le dernier changement de frame a eu lieu

    friend std::istream& operator >> (std::istream&, Animation&);
};