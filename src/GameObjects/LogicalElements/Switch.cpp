#include "Switch.h"

Switch::Switch(Position pos) : ILogElement(pos)
{
}

void Switch::Update()
{
	for (auto i : outCon)
	{
		i->signal = state;
	}
}

void Switch::Render()
{
	static BitMapTexture* tex = new BitMapTexture("./Textures/MEGATextureSR.png");
	SDL_Rect c = tex->getTexturePosition((state ? BITMAP::INPTWO : 0) | (outCon.size() ? BITMAP::INPONE : 0));
	SDL_Rect r = { pos.x, pos.y, 114, 200 };
	SDL_RenderCopy(SGame->getRenderer(), tex->getTexture(), &c, &r);
}

void Switch::Toggle()
{
	state = !state;
	std::cout << "Switch " << state << std::endl;
}
