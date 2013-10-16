#pragma once

#include <memory>
#include <string>
#include "stdafx.h"

class Resource
{
public:
    virtual void LoadResource(const LPDIRECT3DDEVICE9& d3ddev, const std::string& name) = 0;
};

class Texture : public Resource
{
public:
    Texture();
    ~Texture();

    virtual void LoadResource(const LPDIRECT3DDEVICE9& d3ddev, const std::string& name);
    LPDIRECT3DTEXTURE9 getTexture() const;

    bool operator< (const Texture&);

private:
    std::string m_id;   // for debug purposes, could be removed
    LPDIRECT3DTEXTURE9 m_texture;
};

typedef std::shared_ptr<Resource> Resource_ptr;
typedef std::shared_ptr<Texture> Texture_ptr;