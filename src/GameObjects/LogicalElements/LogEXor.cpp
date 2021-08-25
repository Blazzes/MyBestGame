#include "LogEXor.h"

LogEXor::LogEXor(Position pos) : ILogElement(pos)
{
}

void LogEXor::Update()
{
	bool out = false;
	out = (inX ? inX->signal : 0) ^ (inY ? inY->signal : 0);
	for (auto i : outCon) i->signal = out;
}

void LogEXor::Render()
{
	static BitMapTexture* tex = new BitMapTexture("./Textures/MEGATextureXor.png");
	SDL_Rect c = tex->getTexturePosition(conTex);
	auto i = SGame->getShiftPosition();
	SDL_Rect r = { getPos().x - i.x, getPos().y - i.y, 114, 200 };
	SDL_RenderCopy(SGame->getRenderer(), tex->getTexture(), &c, &r);
}
