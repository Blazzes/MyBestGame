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

	void AddUpdateFuction(IGameObject* gameObj);

	bool isRunneble();

private:
	Game(const char* title);
	Game(const char* title, int x, int y, int w, int h);
	~Game();
	//std::list<IGameObject*> listOfObjects;
	std::vector<IGameObject*> vectorOfObjects;
	InitWindow* win;
	bool run_game = true;
	IGameObject* getObjectFromPosition(Position inPos);
	int select_elem = 0;
	//-----TEMPORAL VARS-----
	bool connected = false;
	bool isMoved = false;
	IGameObject* tmpObj = nullptr;
};

// воду в кастрюлю, до кипения
// картошку до кипения(немного варить)
// окунаю тефтельки
// ждать закипания и всплытия
// домашние макарошки(не более 5 мин)
// if!ported