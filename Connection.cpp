#include "Connection.h"
#include "ILogElement.h"

Connection::Connection(IGameObject* inElem, IGameObject* outElem, bool outSelect)
	: pInElem(inElem), pOutElem(outElem), IGameObject(Position(0, 0)), select(outSelect)
{
	if (!select)
		static_cast<ILogElement*>(pInElem)->addInX(this);
	else
		static_cast<ILogElement*>(pInElem)->addInY(this);
	static_cast<ILogElement*>(pOutElem)->addOut(this);

	std::cout << "create Con: " << this << " -> " << pInElem << ":" << pOutElem << std::endl;

}

Connection::~Connection()
{
	std::cout << "delete con: " << this << std::endl;
	if (select) static_cast<ILogElement*>(pInElem)->delInY();
	else static_cast<ILogElement*>(pInElem)->delInX();
	static_cast<ILogElement*>(pOutElem)->delOut(this);
	SGame->deleteObject(this);
}

void Connection::Update()
{}

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
	SDL_RenderDrawLine(SGame->getRenderer(), objAPos.x, objAPos.y + y_, objBPos.x + 110, objBPos.y + 100);
	//std::cout << "CONNECTOR" << std::endl;
}
