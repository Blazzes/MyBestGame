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

IGameObject* Game::getObjectFromPosition(Position inPos)
{
	//inPos.x -= 144 / 2;
	//inPos.y -= 200 / 2;
	for (auto i : vectorOfObjects)
	{
		auto objPos = i->getPos();
		if (objPos.x < inPos.x && objPos.x + 144 > inPos.x &&
			objPos.y < inPos.y && objPos.y + 200 > inPos.y)
			return i;
	}
	return nullptr;
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

	//-------MOUSE AND KEYBOAR------
	//----------GAME LOGIC----------

	auto mousePos = EventGame->getPos();

	if (EventGame->isButPressed(SDLK_ESCAPE)) run_game = false;

	if (EventGame->isButPressed(SDLK_1)) select_elem = 1;

	if (EventGame->isMouseButPressed(SDL_BUTTON_LEFT))
	{
		if (isMoved)
		{
			tmpObj->setPos(mousePos - Position(57, 100));
		}
		else if (connected)
		{

		}
		else
		{
			auto obj = getObjectFromPosition(mousePos);
			if (obj == nullptr)
			{
				switch (select_elem)
				{
				case 0:
				case 1:
					vectorOfObjects.push_back(new LogEAnd(mousePos - Position(57, 100)));
					break;
				default:
					break;
				}
			}
			else
			{
				isMoved = true;
				tmpObj = obj;
			}
		}
	}
	else
	{
		if (isMoved)
		{
			isMoved = false;
		}
		else if (connected)
		{
			connected = false;
		}
		else
		{

		}
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
