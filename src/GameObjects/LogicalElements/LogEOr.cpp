#include "LogEOr.h"

LogEOr::LogEOr(Position pos) : ILogElement(pos)
{
}

void LogEOr::Update()
{
	bool out = false;
	if (inX != nullptr) out = out || inX->signal;
	if (inY != nullptr) out = out || inY->signal;
	for (auto i : outCon) i->signal = out;
}

void LogEOr::Render()
{
	static BitMapTexture* tex = new BitMapTexture("./Textures/MEGATextureOr.png");
	SDL_Rect c = tex->getTexturePosition(conTex);
	SDL_Rect r = { pos.x, pos.y, 114, 200 };
	SDL_RenderCopy(SGame->getRenderer(), tex->getTexture(), &c, &r);
}
