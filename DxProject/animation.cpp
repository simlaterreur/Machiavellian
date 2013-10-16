#include "animation.h"
#include <assert.h>
#include <fstream>

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

void AnimationGroup::LoadAnimGroup(const std::string& name)
{
    std::string animPath = "./Resources/" + name + ".anim";
    std::istream* entree = new std::ifstream(animPath);
    if(entree->fail()) 
    {
        // add message erreur
    }

    int nbAnims;
    (*entree) >> nbAnims;
    m_animList.reserve(nbAnims);

    int frameSize;
    (*entree) >> frameSize;

    while(*entree)
    {
        Animation anim;
        *entree >> anim;
        if(!(*entree)) break;
        anim.m_frameSize = frameSize;
        m_animIndex[anim.m_name] = m_animList.size();
        m_animList.push_back(anim);
    }

    delete entree;
}

AnimationPlayer::AnimationPlayer() : 
    m_currentFrame(1), 
    m_currentAnimation(0), 
    m_lastUpdate(0),
    m_finished(false)
{}

bool AnimationPlayer::Completed() const
{
    return m_finished;
}

void AnimationPlayer::UpdateAnimation (long int elapsed)
{
    m_lastUpdate += elapsed;

    if (m_lastUpdate >= TIME_BETWEEN_ANIM_UPDATES)
    {
        if (m_currentFrame >= m_animGroup->m_animList[m_currentAnimation].m_frames) // si dernier frame de l'anim
        {
            if (m_animGroup->m_animList[m_currentAnimation].m_loop) m_currentFrame = 1; // retour au premier frame
            else m_finished = true;
        }
        else m_currentFrame++;

        m_lastUpdate -= TIME_BETWEEN_ANIM_UPDATES;
    }
}

RECT AnimationPlayer::GetCurrentFrame() const
{
    RECT rectangle;

    rectangle.left = m_animGroup->m_animList[m_currentAnimation].m_startFrameCorner.first + 
                    (m_animGroup->m_animList[m_currentAnimation].m_frameSize * (m_currentFrame - 1));
    rectangle.top = m_animGroup->m_animList[m_currentAnimation].m_startFrameCorner.second;
    
    rectangle.right = m_animGroup->m_animList[m_currentAnimation].m_startFrameCorner.first + 
                    (m_animGroup->m_animList[m_currentAnimation].m_frameSize * m_currentFrame);
    rectangle.bottom = m_animGroup->m_animList[m_currentAnimation].m_startFrameCorner.second + m_animGroup->m_animList[m_currentAnimation].m_frameSize;

    return rectangle;
}

void AnimationPlayer::SetAnimGroup(std::shared_ptr<AnimationGroup> animGroup)
{
    m_animGroup = animGroup;
}

void AnimationPlayer::PlayAnimation(const std::string& name)
{
    m_currentAnimation = m_animGroup->m_animIndex.at(name);
    m_currentFrame = 1;
    m_finished = false;
}

void AnimationPlayer::SetAnimationOffset(int offset)
{
    m_currentFrame += offset;
}