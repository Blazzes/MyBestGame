#pragma once
#include <SDL.h>
struct WinPos
{
	WinPos(int _x, int _y, int _w, int _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}

	int x, y, w, h;
};

class InitWindow
{
public:
	InitWindow(const char* title, int x, int y, int w, int h, Uint32 Win_flags, Uint32 Ren_flags);
	WinPos getWinPos() const;
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
private:
	WinPos myWinPosition;
	SDL_Window* win;
	SDL_Renderer* ren;
};

