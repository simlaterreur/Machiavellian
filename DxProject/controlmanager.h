#pragma once

#define DIRECTINPUT_VERSION 0x0800 // pour éviter les warnings à la compilation
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

struct ControllerState
{
    // peux changer pour un bitset au lieu de plein de booleans
    bool up;
    bool left;
    bool down;
    bool right;
    bool a;
    bool b;
    bool start;

    ControllerState();
};

class ControlManager
{
    public:
    static ControlManager& getInstance()
    {
        static ControlManager instance;
        return instance;
    }

    bool Init(HINSTANCE, HWND);
    void Release();

    bool QueryInputs(ControllerState&);

private:
    ControlManager();
    ControlManager(const ControlManager &) {}; // vide
    void operator=(const ControlManager &) {}; // vide

    bool ReadKeyboard();
    void ProcessInput(ControllerState&);

    IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;

    unsigned char m_keyboardState[256];

};