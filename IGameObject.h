#pragma once
#include "Game.h"
#include <iostream>
#include <vector>

class IGameObject
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual int getPosX() = 0;
	virtual int getPosY() = 0;
	
protected:
	int xPos, yPos;
};

