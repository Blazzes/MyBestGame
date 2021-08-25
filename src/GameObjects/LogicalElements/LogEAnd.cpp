#include "LogEAnd.h"

LogEAnd::LogEAnd(Position pos) : ILogElement(pos)
{
	//SGame->AddUpdateFuction(this);
	std::cout << "create: " << this << std::endl;
}

void LogEAnd::Update()
{
	bool out = false;
	if(inX != nullptr && inY != nullptr)
		out = inX->signal && inY->signal;
	for (auto i : outCon) i->signal = out;
}

void LogEAnd::Render()
{
	static BitMapTexture* tex = new BitMapTexture("./Textures/MEGATextureAnd.png");
	SDL_Rect c = tex->getTexturePosition(conTex);
	auto i = SGame->getShiftPosition();
	SDL_Rect r = { getPos().x - i.x, getPos().y - i.y, 114, 200 };
	SDL_RenderCopy(SGame->getRenderer(), tex->getTexture(), &c, &r);
}

