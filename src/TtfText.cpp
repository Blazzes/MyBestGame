#include "TtfText.h"

TtfText::TtfText()
{
    TTF_Init();
    fonts_map.insert({FONTS::Cosmic, TTF_OpenFont("./Fonts/comic.ttf", 64)});
}

TtfText* TtfText::instance()
{
    static TtfText* ttf = new TtfText();
    return ttf;
}

void TtfText::PrintText(FONTS font, const char* text, SDL_Color color, int x, int y, int w, int h)
{
    SDL_Surface* sur = TTF_RenderText_Blended(fonts_map[font], text, color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(SGame->getRenderer(), sur);
    SDL_Rect r = { x, y, w, h };
    //td::cout << text << std::endl;
    SDL_RenderCopy(SGame->getRenderer(), tex, NULL, &r);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(sur);
}
