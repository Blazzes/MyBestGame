#include "Game.h"
#include "TtfText.h"
#include "IGameObject.h"
#include "SEvent.h"
#include "LogEAnd.h"
#include <string>

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
	for (auto i : vectorOfObjects)
	{
		auto objPos = i->getPos();
		if (objPos.x < inPos.x && objPos.x + 144 > inPos.x &&
			objPos.y < inPos.y && objPos.y + 200 > inPos.y)
			return i;
	}
	return nullptr;
}

// 0 - map, 1 - A, 2 - B, 3 - Out, 4 - inE;
int Game::selectOut(IGameObject* chObj, Position selPos)
{
	int oX = chObj->getPos().x, oY = chObj->getPos().y;
	int mX = selPos.x, mY = selPos.y;
	if (mX > oX && mX < oX + 114 && mY > oY && mY < oY + 200)
	{
		if (mX > oX && mX < oX + 10 && mY > oY + 30 && mY < oY + 50) return 1;
		if (mX > oX && mX < oX + 10 && mY > oY + 150 && mY < oY + 170) return 2;
		if (mX > oX + 104 && mX < oX + 114 && mY > oY + 90 && mY < oY + 110) return 3;
		return 4;
	}
	else
		return 0;
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

	Position mousePos = EventGame->getPos();

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
				auto objPos = obj->getPos();
				tmpObj = obj;
				// 0 - map, 1 - A, 2 - B, 3 - Out, 4 - inE;
				switch (selectOut(obj, mousePos))
				{
				case 1:
					outSelect = 0;
					connected = true;
					break;
				case 2:
					outSelect = 1;
					connected = true;
					break;
				case 3:
					connected = true;
					break;
				case 4:
					isMoved = true;
					break;
				default:
					break;
				}
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
			auto obj = getObjectFromPosition(mousePos);
			if (obj != nullptr)
			{
				Connection* con;
				switch (selectOut(obj, mousePos))
				{
				case 1:
					con = new Connection(obj, tmpObj, 0);
					vectorOfObjects.push_back(con);
					break;
				case 2:
					con = new Connection(obj, tmpObj, 1);
					vectorOfObjects.push_back(con);
					break;
				case 3:
					con = new Connection(tmpObj, obj, outSelect);
					vectorOfObjects.push_back(con);
					break;
				default:
					break;
				}
			}
			connected = false;

			/*auto obj = getObjectFromPosition(mousePos);
			if (obj != nullptr)
			{
				auto objPos = obj->getPos();
				std::cout << objPos.x << " " << objPos.y << std::endl;
				if (mousePos.x > objPos.x + 104 && mousePos.x < objPos.x + 124 &&
					mousePos.y > objPos.y + 90 && mousePos.y < objPos.y + 110)
				{
					Connection* con = new Connection(tmpObj, obj, 0);
					static_cast<ILogElement*>(tmpObj)->addInX(con);
					static_cast<ILogElement*>(obj)->addOut(con);
					vectorOfObjects.push_back(con);
				}
			}*/
			connected = false;
		}
		else
		{

		}
	}
	if (EventGame->isMouseButPressed(SDL_BUTTON_RIGHT))
	{
		auto obj = getObjectFromPosition(mousePos);
		if (obj != nullptr)
		{
			for (int i = 0; i < vectorOfObjects.size(); i++)
			{
				if (vectorOfObjects[i] == obj)
				{
					delete static_cast<ILogElement*>(obj);
					vectorOfObjects.erase(vectorOfObjects.begin() + i);
					break;
				}
			}
		}
	}

	
}

void Game::Render()
{
	SDL_SetRenderDrawColor(win->getRenderer(), 199,208,204,255);
	SDL_RenderClear(win->getRenderer());
	TEXT->PrintText(FONTS::Cosmic,
		(std::to_string(EventGame->getMousePosX()) + ":" + std::to_string(EventGame->getMousePosY())).c_str(), 
		{ 0,0,0,255 }, 100, 100, 100, 20);
	for (auto i : vectorOfObjects) i->Render();
	SDL_RenderPresent(win->getRenderer());
}

void Game::StopGame()
{
	run_game = false;
}

//void Game::AddUpdateFuction(IGameObject* gameObj)
//{
//	vectorOfObjects.push_back(gameObj);
//}

void Game::deleteObject(IGameObject* obj)
{
	std::cout << "Vector size: " << vectorOfObjects.size() << std::endl;
	for (int i = 0; i < vectorOfObjects.size(); i++)
	{
		if (vectorOfObjects[i] == obj)
		{
			std::cout << "Delete from Vetor: " << obj << "-index->" << i << std::endl;
			vectorOfObjects.erase(vectorOfObjects.begin() + i);
			break;
		}
	}
}

bool Game::isRunneble()
{
	return run_game;
}
