#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Game.h"

namespace BITMAP
{
	const Uint32 NOTCON = 0x00;
	const Uint32 INPONE = 0x01;
	const Uint32 INPTWO = 0x02;
	const Uint32 OUTPUT = 0x04;
}

class BitMapTexture
{
public:
	BitMapTexture(std::string texturePath);
	SDL_Texture* getTexture();
	SDL_Rect getTexturePosition(Uint32 bitMapTexPos);
private:
	SDL_Texture* tex;
};