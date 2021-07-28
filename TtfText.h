#pragma once
#include "Game.h"
#include <SDL_ttf.h>
#include <map>

#define TEXT TtfText::instance()

enum FONTS
{
	Cosmic, Aria
};

class TtfText
{
public:
	static TtfText* instance();

	void PrintText(FONTS font, const char* text, SDL_Color color, int x, int y, int w, int h);

private:
	TtfText();
	std::map<FONTS, TTF_Font*> fonts_map;
};

