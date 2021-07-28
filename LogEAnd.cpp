#include "LogEAnd.h"

LogEAnd::LogEAnd(int x, int y) : xPos(x), yPos(y)
{
	SGame->AddUpdateFuction(this);
	tex = new BitMapTexture("./Textures/MEGATextureAnd.png");
}

void LogEAnd::Update()
{
	//for (auto i : inNextElem) { *i = x && y; }
}

void LogEAnd::Render()
{
	SDL_Rect r = { xPos, yPos, 114, 200 };
	SDL_Rect c = tex->getTexturePosition(BITMAP::NOTCON);
	SDL_RenderCopy(SGame->getRenderer(), tex->getTexture(), &c, &r);
}

int LogEAnd::getPosX()
{
	return xPos;
}

int LogEAnd::getPosY()
{
	return yPos;
}

void LogEAnd::updatePosition(int x, int y)
{
	xPos = x;
	yPos = y;
}

void LogEAnd::addOut(Connection* elem)
{
}

void LogEAnd::delOut(Connection* elem)
{
}
