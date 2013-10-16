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
    resource->LoadResource(d3ddev, name);
    m_cacheIndex[name] = m_resourcesCache.size();
    m_resourcesCache.push_back(resource);
    return resource;
}

std::shared_ptr<AnimationGroup> ResourcesManager::loadAnimationGroup(const std::string& name)
{
    // check first if resource is already loaded
    std::map<std::string, int>::iterator iter = m_animIndex.find(name);

    // if so, return pointer to it
    if (iter != m_animIndex.end())
    {
        return m_animCache[iter->second];
    }

    // if not, load new animation group
    std::shared_ptr<AnimationGroup> animGroup(new AnimationGroup);
    animGroup->LoadAnimGroup(name);
    m_animIndex[name] = m_animCache.size();
    m_animCache.push_back(animGroup);
    return animGroup;
}

void ResourcesManager::emptyCache()
{
    // double check if need to release resources manually
    m_resourcesCache.clear();
    m_cacheIndex.clear();

    // 
    m_animCache.clear();
    m_animIndex.clear();
}