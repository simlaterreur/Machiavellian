#include "game.h"

Game::Game()
{
}

void Game::update(long int elapsed)
{
    std::set<Entity_ptr>::iterator iter = background.begin();
    for (; iter != background.end(); ++iter)
    {
        (*iter)->Update(elapsed);
    }

    iter = gameobjectlist.begin();
    for (; iter != gameobjectlist.end(); ++iter)
    {
        (*iter)->Update(elapsed);
    }
}

void Game::render(const LPD3DXSPRITE& sprite)
{
    std::set<Entity_ptr>::iterator iter = background.begin();
    for (; iter != background.end(); ++iter)
    {
        (*iter)->Render(sprite);
    }

    iter = gameobjectlist.begin();
    for (; iter != gameobjectlist.end(); ++iter)
    {
        (*iter)->Render(sprite);
    }
}

void Game::loadMap(const std::string& mapName, const LPDIRECT3DDEVICE9& d3ddev)
{
    // TEMP ****************************
    
    // manually adding stuff in the meantime
    Entity_ptr megaman(new PlayableCharacter);
    megaman->Init(d3ddev, "MegaMan");
    megaman->SetPosition(32,192);
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
            int animOffset;
            *entree >> animOffset;
            Entity_ptr entity(new Entity);
            entity->Init(d3ddev, mapName);
            entity->SetPosition(j*16.0f, i*16.0f);
            entity->SetCurrentAnimation(animName, animOffset);
            background.insert(entity);
            // OMG, c'est tellement laid
        }
    }

    //delete entree;

    // *********************************
}