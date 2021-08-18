#include "InitWindow.h"
#include <iostream>
InitWindow::InitWindow(const char* title, int x, int y, int w, int h, Uint32 Win_flags, Uint32 Ren_flags): myWinPosition(WinPos(x, y, w, h))
{
    SDL_Init(SDL_INIT_EVERYTHING);
    win = SDL_CreateWindow(title, x, y, w, h, Win_flags);
    ren = SDL_CreateRenderer(win, -1, Ren_flags);
    std::cout << "win Constructor" << std::endl;
}

WinPos InitWindow::getWinPos() const
{
    return myWinPosition;
}

SDL_Renderer* InitWindow::getRenderer()
{
    return ren;
}

SDL_Window* InitWindow::getWindow()
{
    return win;
}
