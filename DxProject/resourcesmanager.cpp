#include "resourcesmanager.h"
#include <string>

Texture_ptr ResourcesManager::loadResourceTexture(const LPDIRECT3DDEVICE9& d3ddev, const std::string& name)
{
    // check first if resource is already loaded
    std::map<std::string, int>::iterator iter = m_cacheIndex.find(name);

    // if so, return pointer to it
    if (iter != m_cacheIndex.end())
    {
        return m_resourcesCache[iter->second];
    }


    // if not, load new resource
    Texture_ptr resource(new Texture);
    resource->loadResource(d3ddev, name);
    m_cacheIndex[name] = m_resourcesCache.size();
    m_resourcesCache.push_back(resource);
    return resource;
}

void ResourcesManager::emptyCache()
{
    // double check if need to release resources manually
    m_resourcesCache.clear();
}