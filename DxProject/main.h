#pragma once

// include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>
#include "stdafx.h"

// function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void render_frame();        // renders a single frame
void cleanD3D(void);        // closes Direct3D and releases memory

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
