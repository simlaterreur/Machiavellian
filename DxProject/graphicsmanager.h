#include "stdafx.h"
#include "resources.h"
#include <string>

class GraphicsManager
{
    public:
    static GraphicsManager& getInstance()
    {
        static GraphicsManager instance;
        return instance;
    }

    bool Init(HWND);
    void Release();

    void CreateTexture(const std::string &, LPDIRECT3DTEXTURE9 *);

    void BeginRender();
    void EndRender();
    void Draw(LPDIRECT3DTEXTURE9, const RECT &, const D3DXVECTOR3 &, const D3DXMATRIX &);

private:
    GraphicsManager() {};
    GraphicsManager(const GraphicsManager &) {}; // vide
    void operator=(const GraphicsManager &) {}; // vide

    LPDIRECT3D9 d3d;            
    LPDIRECT3DDEVICE9 d3ddev;   
    LPD3DXSPRITE sprite;
};