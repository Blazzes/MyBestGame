#pragma once
#include "Game.h"
#include <iostream>
#include <vector>

struct Position
{
	Position(int x, int y) : x(x), y(y) { }
	Position(std::pair<int, int> pos) { x = pos.first; y = pos.second; }
	int x, y;
	Position operator+(Position addPos) {
		return Position(x + addPos.x, y + addPos.y);
	}
	Position operator-(Position addPos) {
		return Position(x - addPos.x, y - addPos.y);
	}
};

class IGameObject
{
public:
	IGameObject(Position pos);
	Position getPos();
	void setPos(Position pos);
	virtual void Update() = 0;
	virtual void Render() = 0;
	
protected:
	Position pos;
};

