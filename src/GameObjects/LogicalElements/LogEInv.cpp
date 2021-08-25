#include "LogEInv.h"

LogEInv::LogEInv(Position pos) : ILogElement(pos)
{}

void LogEInv::Update()
{
	bool out = false;
	out = inX ? !inX->signal : true;
	for (auto i : outCon) i->signal = out;
}

void LogEInv::Render()
{
	static BitMapTexture* tex = new BitMapTexture("./Textures/MEGATextureInv.png");
	SDL_Rect c = tex->getTexturePosition(conTex);
	auto i = SGame->getShiftPosition();
	SDL_Rect r = { getPos().x - i.x, getPos().y - i.y, 114, 200 };
	SDL_RenderCopy(SGame->getRenderer(), tex->getTexture(), &c, &r);
}
