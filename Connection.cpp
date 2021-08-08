#include "Connection.h"

Connection::Connection(IGameObject* inElem, IGameObject* outElem) : pInElem(inElem), pOutElem(outElem), IGameObject(Position(0,0))
{
	//SGame->AddUpdateFuction(this);
}

Connection::~Connection()
{
	//pInElem->delOut(this);
}
