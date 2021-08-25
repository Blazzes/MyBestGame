#include "LogEXnor.h"

LogEXnor::LogEXnor(Position pos) : ILogElement(pos)
{
}

void LogEXnor::Update()
{
	bool out = false;
	out = (inX ? inX->signal : false) ^ (inY ? inY->signal : false);
	for (auto i : outCon) i->signal = !out;
}

void LogEXnor::Render()
{
	static BitMapTexture* tex = new BitMapTexture("./Textures/MEGATextureXnor.png");
	SDL_Rect c = tex->getTexturePosition(conTex);
	auto i = SGame->getShiftPosition();
	SDL_Rect r = { getPos().x - i.x, getPos().y - i.y, 114, 200 };
	SDL_RenderCopy(SGame->getRenderer(), tex->getTexture(), &c, &r);
}
