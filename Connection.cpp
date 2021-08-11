#include "Connection.h"

Connection::Connection(IGameObject* inElem, IGameObject* outElem, bool outSelect)
	: pInElem(inElem), pOutElem(outElem), IGameObject(Position(0, 0)), select(outSelect)
{
	
}

Connection::~Connection()
{
	
}

void Connection::Update()
{
}

void Connection::Render()
{
	auto objAPos = pInElem->getPos();
	auto objBPos = pOutElem->getPos();
	if(signal)SDL_SetRenderDrawColor(SGame->getRenderer(), 255, 0, 0, 255);
	else SDL_SetRenderDrawColor(SGame->getRenderer(), 0, 0, 0, 255);
	int y_;
	if (select)// 0 - A; 1 - B
		y_ = 200 - 40;
	else
		y_ = 40;
	SDL_RenderDrawLine(SGame->getRenderer(), objAPos.x, objAPos.y + y_, objBPos.x + 114, objBPos.y + 100);
	//std::cout << "CONNECTOR" << std::endl;
}
