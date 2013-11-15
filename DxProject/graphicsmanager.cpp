#include "graphicsmanager.h"

bool GraphicsManager::Init(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp;            // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));      // clear out the struct for use
    d3dpp.Windowed = TRUE;                  // program windowed, not fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
    d3dpp.hDeviceWindow = hWnd;             // set the window to be used by Direct3D

    // create a device class using this information and the info from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);

    // setup the sprite handler
    sprite = NULL;
    D3DXCreateSprite(d3ddev, &sprite);

    return true; // TODO return false if failed
}

void GraphicsManager::Release()
{
    d3ddev->Release();  // close and release the 3D device
    d3d->Release();     // close and release Direct3D
}

void GraphicsManager::CreateTexture(const std::string & path, LPDIRECT3DTEXTURE9 * texture)
{
    D3DXCreateTextureFromFile(d3ddev, path.c_str(), &*texture);
}

void GraphicsManager::BeginRender()
{
    // clear the window to an arbitrary color
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
    d3ddev->BeginScene();    
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void GraphicsManager::EndRender()
{
    sprite->End();
    d3ddev->EndScene();
    d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}

void GraphicsManager::Draw(LPDIRECT3DTEXTURE9 texture, const RECT & rectangle, const D3DXVECTOR3 & pos, const D3DXMATRIX & trans)
{
    // TODO: pourrait tout mettre le positionnement dans la matrice de transformation sans avoir besoin d'utiliser le vecteur pos.
    sprite->SetTransform(&trans);
    sprite->Draw(texture, &rectangle, NULL, &pos, 0xFFFFFFFF);
}
