#pragma once
#include "IGameObject.h"

class Connection :
	public IGameObject
{
public:
	Connection(IGameObject* inElem, IGameObject* outElem);
	~Connection();
	bool signal = false;
private:
	IGameObject* pInElem;
	IGameObject* pOutElem;
};

