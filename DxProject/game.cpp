#include "game.h"
#include "graphicsmanager.h"

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

void Game::render()
{
    GraphicsManager::getInstance().BeginRender();

    std::set<Entity_ptr>::iterator iter = background.begin();
    for (; iter != background.end(); ++iter)
    {
        (*iter)->Render();
    }

    iter = gameobjectlist.begin();
    for (; iter != gameobjectlist.end(); ++iter)
    {
        (*iter)->Render();
    }

    GraphicsManager::getInstance().EndRender();
}

void Game::loadMap(const std::string& mapName)
{
    // TEMP ****************************
    
    // manually adding stuff in the meantime
    Entity_ptr megaman(new PlayableCharacter);
    megaman->Init("MegaMan");
    megaman->SetPosition(32,-32);
    gameobjectlist.insert(megaman);

    // TRÈSSSSSS TEMP
    std::string mapPath = "./Resources/" + mapName + ".map";
    std::istream* entree = new std::ifstream(mapPath);
    if(entree->fail()) 
    {
        // add message erreur
        return; 
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
            entity->Init(mapName);
            entity->SetPosition(j*16.0f, i*16.0f);
            entity->SetCurrentAnimation(animName, animOffset);
            background.insert(entity);
        }
    }

    delete entree;

    // *********************************
}