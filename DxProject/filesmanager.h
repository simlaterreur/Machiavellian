#include "stdafx.h"

class FilesManager
{
    public:
    static FilesManager& getInstance()
    {
        static FilesManager instance;
        return instance;
    }

    bool Init(HINSTANCE, HWND);

private:
    FilesManager();
    FilesManager(const FilesManager &) {}; // vide
    void operator=(const FilesManager &) {}; // vide

};