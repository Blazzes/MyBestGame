#include "ILogElement.h"

ILogElement::ILogElement(Position pos) : IGameObject(pos)
{
}

void ILogElement::addOut(Connection* con)
{
	outCon.push_back(con);
	conTex |= BITMAP::OUTPUT;
}

void ILogElement::addInX(Connection* con)
{
	inX = con;
	conTex |= BITMAP::INPONE;
}

void ILogElement::addInY(Connection* con)
{
	inY = con;
	conTex |= BITMAP::INPTWO;
}
