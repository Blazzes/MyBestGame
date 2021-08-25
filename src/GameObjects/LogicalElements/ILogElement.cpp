#include "ILogElement.h"

ILogElement::ILogElement(Position pos) : IGameObject(pos)
{
}

ILogElement::~ILogElement()
{
	std::cout << "delete Element: " << this << std::endl;
	delete static_cast<Connection*>(inX);
	delete static_cast<Connection*>(inY);
	for (auto i : outCon)
	{
		delete static_cast<Connection*>(i);
	}
	SGame->deleteObject(this);
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

void ILogElement::delOut(Connection* con)
{
	for (size_t i = 0; i < outCon.size(); i++)
	{
		if (outCon[i] == con)
		{
			std::cout << "Delete out: " << con << std::endl;
			outCon.erase(outCon.begin() + i);
			break;
		}
	}
	if (outCon.size() == 0) conTex &= ~BITMAP::OUTPUT;
}

void ILogElement::delInX()
{
	std::cout << "Delete X: " << inX << std::endl;
	inX = nullptr;
	conTex &= ~BITMAP::INPONE;
}

void ILogElement::delInY()
{
	std::cout << "Delete Y: " << inY << std::endl;
	inY = nullptr;
	conTex &= ~BITMAP::INPTWO;
}

void ILogElement::delConnection(int connectionType)
{
	switch (connectionType)
	{
	case 1:
	case 2: 
		delete static_cast<Connection*>(inX);
		break;
	case 3:
		delete static_cast<Connection*>(inY);
		break;
	case 4:
		for (auto i : outCon)
		{
			delete static_cast<Connection*>(i);
		}
		break;
	case 5:
		delete this;
		break;
	}
}
