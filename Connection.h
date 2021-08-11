#pragma once
#include "IGameObject.h"

class Connection :
	public IGameObject
{
public:
	Connection(IGameObject* inElem, IGameObject* outElem, bool outSelect); // 0 - A; 1 - B;
	~Connection();
	void Update() override;
	void Render() override;
	bool signal = false;
private:
	IGameObject* pInElem;
	IGameObject* pOutElem;
	bool select;
};

