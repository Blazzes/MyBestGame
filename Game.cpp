#include "Game.h"
#include "TtfText.h"
#include "IGameObject.h"
#include "SEvent.h"
#include "LogEAnd.h"
Game::Game(const char* title)
{
	win = new InitWindow(title, 0,0,0,0, SDL_WINDOW_FULLSCREEN || SDL_WINDOW_OPENGL, SDL_RENDERER_ACCELERATED);
}

Game::Game(const char* title, int x, int y, int w, int h)
{
	win = new InitWindow(title, x, y, w, h, SDL_WINDOW_OPENGL, SDL_RENDERER_ACCELERATED);
}

Game::~Game()
{
	SDL_DestroyWindow(win->getWindow());
	SDL_DestroyRenderer(win->getRenderer());
	SDL_Quit();
}

bool Game::isConnectionBlock()
{
	
	return false;
}

bool Game::checkBlock(int x, int y)
{
	for (auto i : vectorOfObjects)
	{
		auto objPosX = i->getPosX();
		auto objPosY = i->getPosY();
		if (objPosX <= x && objPosY <= y && objPosX + 114 >= x && objPosY + 200 >= y)
		{
			return true;
		}
	}
	return false;
}

bool Game::checkBlock(IGameObject* obj, int x, int y)
{
	auto objPosX = obj->getPosX();
	auto objPosY = obj->getPosY();
	if (objPosX <= x && objPosY <= y && objPosX + 114 >= x && objPosY + 200 >= y)
	{
		return true;
	}
	return false;
}

Game* Game::instance()
{
	static Game* singleGame = new Game("test");
	return singleGame;
}

SDL_Renderer* Game::getRenderer()
{
	return win->getRenderer();
}

void Game::Update()
{
	EventGame->Update();
	for (auto i : vectorOfObjects)
	{
		i->Update();
	}

	// Блок обработки все игровой логики

	if (EventGame->isButPressed(SDLK_ESCAPE)) run_game = false;
	if (EventGame->isButPressed(SDLK_DELETE))
	{
		int x = EventGame->getMousePosX();
		int y = EventGame->getMousePosY();
		for (auto i = 0; i < vectorOfObjects.size(); ++i)
		{
			if (checkBlock(vectorOfObjects.at(i), x, y))
			{
				vectorOfObjects.erase(vectorOfObjects.begin() + i);
				break;
			}
		}
	}
	if (EventGame->isButPressed(SDLK_1)) elem = 1;
	if (EventGame->isMouseButPressed(SDL_BUTTON_LEFT))
	{
		int x = EventGame->getMousePosX();
		int y = EventGame->getMousePosY();
		
		for (auto i : vectorOfObjects)
		{
			if (checkBlock(i, x, y))
			{
				dynamic_cast<ILogElement*>(i)->updatePosition(x - 144/2, y - 200/2);
				return;
			}
		}

		if(!checkBlock(x,y)) AddUpdateFuction(new LogEAnd(x - 114 / 2, y - 200 / 2));
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(win->getRenderer(), 199,208,204,255);
	SDL_RenderClear(win->getRenderer());
	for (auto i : vectorOfObjects) i->Render();
	SDL_RenderPresent(win->getRenderer());
}

void Game::StopGame()
{
	run_game = false;
}

void Game::AddUpdateFuction(IGameObject* gameObj)
{
	vectorOfObjects.push_back(gameObj);
}

bool Game::isRunneble()
{
	return run_game;
}
