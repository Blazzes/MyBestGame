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
	
}

bool Game::checkBlock(IGameObject* obj, int x, int y)
{
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
