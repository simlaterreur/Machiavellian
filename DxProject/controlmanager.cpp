#include "controlmanager.h"

ControllerState::ControllerState() : 
    up(false),
    left(false),
    down(false),
    right(false),
    a(false),
    b(false),
    start(false)
{}

ControlManager::ControlManager() : m_directInput(NULL), m_keyboard(NULL)
{
}

bool ControlManager::Init(HINSTANCE hinstance, HWND hwnd)
{
    HRESULT result;

    // Initialize the main direct input interface.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if(FAILED(result))
	{
		return false;
	}

    // Initialize the direct input interface for the keyboard.
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if(FAILED(result))
	{
		return false;
	}

    // Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(result))
	{
		return false;
	}

    // Set as exclusive pcq je ne gère pas encore les lost devices
    // Set the cooperative level of the keyboard to not share with other programs.
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if(FAILED(result))
	{
		return false;
	}

    // Now acquire the keyboard.
	result = m_keyboard->Acquire();
	if(FAILED(result))
	{
		return false;
	}

    return true; // init successful
}

void ControlManager::Release()
{
    // Release the keyboard.
	if(m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = NULL;
	}

	// Release the main interface to direct input.
	if(m_directInput)
	{
		m_directInput->Release();
		m_directInput = NULL;
	}

	return;
}

bool ControlManager::QueryInputs(ControllerState& controller)
{
    bool result;

	// Read the current state of the keyboard.
	result = ReadKeyboard();
	if(!result)
	{
		return false;
	}

	// Process the changes in the keyboard.
	ProcessInput(controller);

    return true;
}

bool ControlManager::ReadKeyboard()
{
    HRESULT result;

	// Read the keyboard device.
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if(FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
		
	return true;
}

void ControlManager::ProcessInput(ControllerState& controller)
{
    // vérifie le custom mapping des touches et traduit en commandes que l'on connait
    // TODO

    // Temp: hardcoded values WASD, space, etc
    (m_keyboardState[DIK_W] & 0x80) ? controller.up = true          : controller.up = false;
    (m_keyboardState[DIK_A] & 0x80) ? controller.left = true        : controller.left = false;
    (m_keyboardState[DIK_S] & 0x80) ? controller.down = true        : controller.down = false;
    (m_keyboardState[DIK_D] & 0x80) ? controller.right = true       : controller.right = false;
    (m_keyboardState[DIK_SPACE] & 0x80) ? controller.a = true       : controller.a = false;
    (m_keyboardState[DIK_K] & 0x80) ? controller.b = true           : controller.b = false;
    (m_keyboardState[DIK_ESCAPE] & 0x80) ? controller.start = true  : controller.start = false;
}