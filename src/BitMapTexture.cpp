#include "BitMapTexture.h"

BitMapTexture::BitMapTexture(std::string texturePath)
{
	tex = SDL_CreateTextureFromSurface(SGame->getRenderer(), IMG_Load(texturePath.c_str()));

}

SDL_Texture* BitMapTexture::getTexture()
{
	return tex;
}

SDL_Rect BitMapTexture::getTexturePosition(Uint32 bitMapTexPos)
{
	if (bitMapTexPos == 0) return { 0, 0, 114, 200 };
	if (bitMapTexPos == BITMAP::INPONE) return { 114, 0, 114, 200 };
	if (bitMapTexPos == BITMAP::INPTWO) return { 228, 0, 114, 200 };
	if (bitMapTexPos == BITMAP::OUTPUT) return { 798, 0, 114, 200 };
	if (bitMapTexPos == (BITMAP::INPONE | BITMAP::INPTWO)) return { 342, 0, 114, 200 };
	if (bitMapTexPos == (BITMAP::INPONE | BITMAP::OUTPUT)) return { 456, 0, 114, 200 };
	if (bitMapTexPos == (BITMAP::INPTWO | BITMAP::OUTPUT)) return { 570, 0, 114, 200 };
	if (bitMapTexPos == (BITMAP::INPONE | BITMAP::INPTWO | BITMAP::OUTPUT)) return { 684, 0, 114, 200 };
}
