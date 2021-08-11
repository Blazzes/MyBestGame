#include "Connection.h"

Connection::Connection(IGameObject* inElem, IGameObject* outElem) : pInElem(inElem), pOutElem(outElem), IGameObject(Position(0,0))
{
	//SGame->AddUpdateFuction(this);
}

Connection::~Connection()
{
	//pInElem->delOut(this);
}

void Connection::Update()
{
}

void Connection::Render()
{
	auto objAPos = pInElem->getPos();
	auto objBPos = pOutElem->getPos();
	SDL_SetRenderDrawColor(SGame->getRenderer(), 0, 0, 0, 255);
	SDL_RenderDrawLine(SGame->getRenderer(), objAPos.x, objAPos.y, objBPos.x, objBPos.y);
	//std::cout << "CONNECTOR" << std::endl;
}
