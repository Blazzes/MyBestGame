#include "IGameObject.h"

IGameObject::IGameObject(Position pos_) : pos(pos_)
{
}

Position IGameObject::getPos()
{
	return pos;
}

void IGameObject::setPos(Position pos)
{
	this->pos = pos;
}
