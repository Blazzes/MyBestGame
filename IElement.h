#pragma once
#include <SDL.h>

class IElement
{
public:
	virtual SDL_Texture* getBigTexture() = 0;
	virtual SDL_Rect& getSquareTexture(int Square_Number) = 0;
};

