#include "ILogElement.h"

ILogElement::ILogElement(Position pos) : IGameObject(pos)
{
}

void ILogElement::addOut(Connection* con)
{
	outCon.push_back(con);
}

void ILogElement::addInX(Connection* con)
{
	inX = con;
}

void ILogElement::addInY(Connection* con)
{
	inY = con;
}
