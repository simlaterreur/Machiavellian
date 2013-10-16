#include "entity.h"
#include <math.h>

Entity::Entity() : 
    m_pos(0.0f, 0.0f),
    m_visible(true),
    m_facingLeft(false)
{
    m_texture = NULL;
}

Entity::Entity(const Entity& e) : m_pos(e.m_pos)
{
    // TODO
    m_texture = NULL;
}

Entity::~Entity()
{
}

void Entity::Init(const LPDIRECT3DDEVICE9& device, const std::string& name)
{
    // create texture
    m_texture = ResourcesManager::getInstance().loadResourceTexture(device, name);

    // create anim list
    m_animPlayer.SetAnimGroup(ResourcesManager::getInstance().loadAnimationGroup(name));
}

void Entity::SetCurrentAnimation(const std::string& animName)
{
    m_animPlayer.PlayAnimation(animName);

    //try 
    //{
    //} 
    //catch (const std::out_of_range&)
    //{
    //    // error message
    //    return;
    //}
}

void Entity::SetCurrentAnimation(const std::string& animName, int offSetFrame)
{
    m_animPlayer.PlayAnimation(animName);
    m_animPlayer.SetAnimationOffset(offSetFrame);
}

void Entity::SetPosition(float x, float y)
{
    m_pos.first = x;
    m_pos.second = y;
}

void Entity::Update(long int elapsed)
{
    m_animPlayer.UpdateAnimation(elapsed);
}

void Entity::Render(const LPD3DXSPRITE& sprite) const
{
    if (!m_visible) return;
    RECT rectangle = m_animPlayer.GetCurrentFrame();

    D3DXVECTOR3 pos(floor(m_pos.first), floor(m_pos.second), 0.0f); // rounds the position to the pixel (avoids smudging effect when in between pixels)

    D3DXMATRIX trans;
    if (m_facingLeft)
    {
        D3DXMatrixScaling(&trans, -1.0f, 1.0f, 1.0f);
        pos.x = -pos.x - 32; // TEMP offset 32 (sprite width) vu que la pos du sprite n'est pas au centre mais le top left corner
    }
    else
    {
        D3DXMatrixScaling(&trans, 1.0f, 1.0f, 1.0f);
    }

    sprite->SetTransform(&trans);  // TODO: pourrait tout mettre le positionnement dans la matrice de transformation sans avoir besoin d'utiliser le vecteur pos.
    sprite->Draw(m_texture->getTexture(), &rectangle, NULL, &pos, 0xFFFFFFFF);
}

