#pragma once

#include "stdafx.h"
#include "animation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Entity
{
public:
    Entity();
    Entity(const Entity&);
    ~Entity();

    void init(const LPDIRECT3DDEVICE9&, const std::string&);
    
    void setCurrentAnimation(const std::string&);
    void update(long int elapsed);
    void render(const LPD3DXSPRITE&) const;

private:
    D3DXVECTOR3 m_pos;
    LPDIRECT3DTEXTURE9 m_texture;

    std::map<std::string, int> m_animIndex;
    std::vector<Animation> m_animList;
    int m_currentAnim;
};