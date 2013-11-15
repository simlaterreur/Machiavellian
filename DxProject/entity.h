#pragma once

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
    void Render() const;

    void Init(const std::string&);

protected:
    std::pair<float, float> m_pos;
    Texture_ptr m_texture;

    AnimationPlayer m_animPlayer;

    bool m_visible;
    bool m_facingLeft;

private:

};

typedef std::shared_ptr<Entity> Entity_ptr;