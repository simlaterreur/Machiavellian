#include "game.h"

Game::Game()
{
}

void Game::update(long int elapsed)
{
    std::set<Entity_ptr>::iterator iter = gameobjectlist.begin();
    for (; iter != gameobjectlist.end(); ++iter)
    {
        (*iter)->update(elapsed);
    }
}

void Game::render(const LPD3DXSPRITE& sprite)
{
    std::set<Entity_ptr>::iterator iter = gameobjectlist.begin();
    for (; iter != gameobjectlist.end(); ++iter)
    {
        (*iter)->render(sprite);
    }
}

void Game::loadMap(const std::string& mapName, const LPDIRECT3DDEVICE9& d3ddev)
{
    // TODO: parse a .map file based on mapName


    // TEMP ****************************

    // manually adding stuff in the meantime
    Entity_ptr megaman(new PlayableCharacter);
    megaman->init(d3ddev, "MegaMan");
    gameobjectlist.insert(megaman);
    
    // *********************************
}