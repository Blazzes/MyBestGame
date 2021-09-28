#pragma once
#include "InitWindow.h"
#include <vector>
#include <functional>
#include <iostream>
#include <list>

#define SGame Game::instance()

struct Position;
class IGameObject;

class Game
{
public:
	static Game* instance();

	SDL_Renderer* getRenderer();
	void Update();
	void Render();
	void StopGame();

	void deleteObject(IGameObject* obj);

	bool isRunneble();

	Position getShiftPosition();
	int getZoom();

private:
	Game(const char* title);
	Game(const char* title, int x, int y, int w, int h);
	~Game();
	std::vector<IGameObject*> vectorOfObjects;
	InitWindow* win;
	bool run_game = true;
	IGameObject* getObjectFromPosition(Position inPos);
	int select_elem = 0;
	int selectOut(IGameObject* chObj, Position selPos);
	int x = 0, y = 0;
	int zoom = 1;
	std::vector<std::string> quest = {
		"0 - LAMP",
		"1 - SWITCH",
		"2 - AND",
		"3 - NAND",
		"4 - OR",
		"5 - NOR",
		"6 - XOR",
		"7 - XNOR",
		"8 - INVERT",
		"9 - BUFFER"};
	//-----TEMPORAL VARS-----
	int connected = 0;
	bool isMoved = false;
	bool outSelect = false;
	bool sw = false;
	IGameObject* tmpObj = nullptr;
};
