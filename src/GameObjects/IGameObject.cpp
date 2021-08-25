#include "IGameObject.h"

IGameObject::IGameObject(Position pos_) : pos(pos_)
{
	std::cout << pos.x << "::" << pos.y << std::endl;
}

Position IGameObject::getPos()
{
	return pos;
}

void IGameObject::setPos(Position pos)
{
	this->pos = pos;
}
