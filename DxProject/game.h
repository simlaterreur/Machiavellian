#pragma once

#include "stdafx.h"
#include "playablecharacter.h"
#include <set>
#include <memory>

typedef std::shared_ptr<Entity> Entity_ptr;

class Game
{
public:
    Game();

    void update(long int elapsed);
    void render(const LPD3DXSPRITE&);

    void loadMap(const std::string&, const LPDIRECT3DDEVICE9&); // TODO: remove d3ddevice

private:

    std::set<Entity_ptr> background;
    std::set<Entity_ptr> gameobjectlist;
};