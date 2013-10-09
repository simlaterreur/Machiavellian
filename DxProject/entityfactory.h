#pragma once

#include "entity.h"

class EntityFactory
{
public:
    EntityFactory();

    Entity_ptr createEntity(const std::string&, const LPDIRECT3DDEVICE9&);

private:


};