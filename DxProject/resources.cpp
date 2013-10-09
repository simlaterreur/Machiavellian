#include "resources.h"

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

void Texture::loadResource(const LPDIRECT3DDEVICE9& d3ddev, const std::string& name)
{
    m_id = name;
    std::string texturePath = "./Resources/" + name + ".png";
    D3DXCreateTextureFromFile(d3ddev, texturePath.c_str(), &m_texture);
}

LPDIRECT3DTEXTURE9 Texture::getTexture() const
{
    return m_texture;
}