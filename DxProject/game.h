#pragma once

#include "stdafx.h"
#include "playablecharacter.h"
#include <set>
#include <memory>

class Game
{
public:
    Game();

    void update(long int elapsed);
    void render();

    void loadMap(const std::string&);

private:

    std::set<Entity_ptr> background;
    std::set<Entity_ptr> gameobjectlist;
};