#include "game.h"

Game::Game()
{
}

void Game::update(long int elapsed)
{
    std::set<Entity_ptr>::iterator iter = background.begin();
    for (; iter != background.end(); ++iter)
    {
        (*iter)->update(elapsed);
    }

    iter = gameobjectlist.begin();
    for (; iter != gameobjectlist.end(); ++iter)
    {
        (*iter)->update(elapsed);
    }
}

void Game::render(const LPD3DXSPRITE& sprite)
{
    std::set<Entity_ptr>::iterator iter = background.begin();
    for (; iter != background.end(); ++iter)
    {
        (*iter)->render(sprite);
    }

    iter = gameobjectlist.begin();
    for (; iter != gameobjectlist.end(); ++iter)
    {
        (*iter)->render(sprite);
    }
}

void Game::loadMap(const std::string& mapName, const LPDIRECT3DDEVICE9& d3ddev)
{
    // TEMP ****************************
    
    // manually adding stuff in the meantime
    Entity_ptr megaman(new PlayableCharacter);
    megaman->init(d3ddev, "MegaMan");
    gameobjectlist.insert(megaman);

    // TRÈSSSSSS TEMP
    std::string mapPath = "./Resources/" + mapName + ".map";
    std::istream* entree = new std::ifstream(mapPath);
    if(entree->fail()) 
    {
        // add message erreur
        return; //test
    }

    int x, y = 0;
    (*entree) >> x;
    (*entree) >> y;

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            std::string animName;
            *entree >> animName;
            //if(!(*entree) || animName == "-") break;
            Entity_ptr entity(new Entity);
            entity->init(d3ddev, mapName);
            entity->setPosition(j*16, i*16);
            entity->setCurrentAnimation(animName);
            background.insert(entity);
            // OMG, c'est tellement laid
        }
    }

    delete entree;

    // *********************************
}