#include "resources.h"
#include "graphicsmanager.h"

Texture::Texture()
{
    m_id = "";
    m_texture = NULL;
}

Texture::~Texture()
{
    if (m_texture != NULL)
        m_texture->Release();
}

void Texture::LoadResource(const std::string& name)
{
    m_id = name;
    std::string texturePath = "./Resources/" + name + ".png";
    GraphicsManager::getInstance().CreateTexture(texturePath, &m_texture);
}

LPDIRECT3DTEXTURE9 Texture::getTexture() const
{
    return m_texture;
}