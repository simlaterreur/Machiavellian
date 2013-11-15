#include "stdafx.h"

class SoundManager
{
    public:
    static SoundManager& getInstance()
    {
        static SoundManager instance;
        return instance;
    }

    bool Init(HINSTANCE, HWND);

private:
    SoundManager();
    SoundManager(const SoundManager &) {}; // vide
    void operator=(const SoundManager &) {}; // vide

};