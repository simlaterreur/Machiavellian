// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include "game.h"
#include "controlmanager.h"
#include "graphicsmanager.h"

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{

    // TODO: init files manager

    // create window
    HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "WindowClass";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL,
                          "WindowClass",
                          "DirectX project",
                          WS_OVERLAPPEDWINDOW,
                          300, 300,
                          320, 320,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hWnd, nCmdShow);

    // init the graphics manager and attach it to the window
    GraphicsManager::getInstance().Init(hWnd);
    
    // init the control manager and link it to the application window
    ControlManager::getInstance().Init(hInstance, hWnd);

    // init Game
    Game * game = new Game();
    game->loadMap("Gym");  // TODO: pick the default map from the config file loaded by the files manager

    // enter the main loop:
    MSG msg;

    long int start = GetTickCount();
    while(TRUE)
    {
        while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if(msg.message == WM_QUIT)
            break;

        long int end = GetTickCount();
        long int elapsed = end - start;

        game->update(elapsed);
        game->render();

        start = end;
    }


    // clean up before quitting
    ControlManager::getInstance().Release();
    GraphicsManager::getInstance().Release();

    delete game;

    return msg.wParam;
}


// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}
