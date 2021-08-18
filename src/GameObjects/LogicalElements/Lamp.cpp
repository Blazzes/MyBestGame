#include "Lamp.h"

Lamp::Lamp(Position pos) : ILogElement(pos)
{
}

void Lamp::Update()
{
}

void Lamp::Render()
{
	static BitMapTexture* tex = new BitMapTexture("./Textures/MEGATextureLamp.png");
	SDL_Rect c;// = tex->getTexturePosition();
	if (inX)
	{
		if (inX->signal) c = { 228, 0, 114, 200 };
		else c = { 114, 0, 114, 200 };
	}
	else c = { 0,0, 114, 200 };
	SDL_Rect r = { pos.x, pos.y, 114, 200 };
	SDL_RenderCopy(SGame->getRenderer(), tex->getTexture(), &c, &r);
}
