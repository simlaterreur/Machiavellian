#include "entity.h"

Entity::Entity() : m_pos(0,0,0), m_currentAnim(0)
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
    if (m_texture != NULL)
        m_texture->Release();
}

void Entity::init(const LPDIRECT3DDEVICE9& device, const std::string& name)
{
    // create texture
    std::string texturePath = "./Resources/" + name + ".png";
    D3DXCreateTextureFromFile(device, texturePath.c_str(), &m_texture);

    // create anim list
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
        Animation animation;
        *entree >> animation;
        if(!(*entree)) break;
        animation.m_frameSize = frameSize;
        m_animIndex[animation.m_name] = m_animList.size();
        m_animList.push_back(animation);
    }

    delete entree;
}

void Entity::setCurrentAnimation(const std::string& animName)
{
    try 
    {
        m_currentAnim = m_animIndex.at(animName);
        m_animList[m_currentAnim].m_currentFrame = 1;
        m_animList[m_currentAnim].m_finished = false;
    } 
    catch (const std::out_of_range&)
    {
        // error message
        return;
    }
}

void Entity::update(long int elapsed)
{
    m_animList[m_currentAnim].updateAnimation(elapsed);
}

void Entity::render(const LPD3DXSPRITE& sprite) const
{
    RECT rectangle = m_animList[m_currentAnim].getCurrentFrame();
    sprite->Draw(m_texture, &rectangle, NULL, &m_pos, 0xFFFFFFFF);
}

