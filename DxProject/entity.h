#pragma once

#include "stdafx.h"
#include "animation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "resources.h"
#include "resourcesmanager.h"

class Entity
{
public:
    Entity();
    Entity(const Entity&);
    ~Entity();
    
    void SetCurrentAnimation(const std::string&);
    void SetCurrentAnimation(const std::string&, int);
    void SetPosition(float, float);

    virtual void Update(long int elapsed);
    void Render(const LPD3DXSPRITE&) const;

    void Init(const LPDIRECT3DDEVICE9&, const std::string&);

protected:
    //D3DXVECTOR3 m_pos;
    std::pair<float, float> m_pos;
    Texture_ptr m_texture;
    //LPDIRECT3DTEXTURE9 m_texture;

    std::map<std::string, int> m_animIndex;
    std::vector<Animation> m_animList;
    int m_currentAnim;
    bool m_visible;
    bool m_facingLeft;

private:

    friend class EntityFactory; // à revoir l'approche
};

typedef std::shared_ptr<Entity> Entity_ptr;