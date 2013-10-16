#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>

#define TIME_BETWEEN_ANIM_UPDATES 140 // à trouver le sweet spot

struct Animation
{
    std::string m_name;
    std::pair<int,int> m_startFrameCorner;
    int m_frames;
    int m_frameSize;   
    bool m_loop;

    friend std::istream& operator >> (std::istream&, Animation&);
};


struct AnimationGroup
{
    std::map<std::string, int> m_animIndex;
    std::vector<Animation> m_animList;

    void LoadAnimGroup(const std::string&);
};


class AnimationPlayer
{
public:
    AnimationPlayer();

    bool Completed() const;

    void UpdateAnimation(long int);
    RECT GetCurrentFrame() const;

    void SetAnimGroup(std::shared_ptr<AnimationGroup>);

    void PlayAnimation(const std::string&);
    void SetAnimationOffset(int);

private:
    int m_currentFrame;     
    int m_currentAnimation; // serait surement mieux avec un pointeur
    bool m_finished;            // indique fini de jouer le dernier frame d'une anim non loopante
    long int m_lastUpdate;      // quand le dernier changement de frame a eu lieu

    std::shared_ptr<AnimationGroup> m_animGroup;
};