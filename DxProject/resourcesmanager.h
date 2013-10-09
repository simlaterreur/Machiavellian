#pragma once

#include "stdafx.h"
#include "resources.h"
#include <memory>
#include <map>
#include <vector>

class ResourcesManager
{
public:
    static ResourcesManager& getInstance()
    {
        static ResourcesManager instance;
        return instance;
    }

    Texture_ptr loadResourceTexture(const LPDIRECT3DDEVICE9&, const std::string&);
    void emptyCache();

private:
    ResourcesManager() {}; // vide
    ResourcesManager(const ResourcesManager &) {}; // vide
    void operator=(const ResourcesManager &) {}; // vide

    std::map<std::string, int> m_cacheIndex;
    std::vector<Texture_ptr> m_resourcesCache; // could be a fixed size
};
