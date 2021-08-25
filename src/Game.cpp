#include <string>
#include "Game.h"
#include "SEvent.h"
#include "TtfText.h"
#include "GameObjects/IGameObject.h"
#include "GameObjects/LogicalElements/Lamp.h"
#include "GameObjects/LogicalElements/Switch.h"
#include "GameObjects/LogicalElements/LogEAnd.h"
#include "GameObjects/LogicalElements/LogENand.h"
#include "GameObjects/LogicalElements/LogEOr.h"
#include "GameObjects/LogicalElements/LogENor.h"
#include "GameObjects/LogicalElements/LogEXor.h"
#include "GameObjects/LogicalElements/LogEXnor.h"
#include "GameObjects/LogicalElements/LogEInv.h"
#include "GameObjects/LogicalElements/LogEBuf.h"

Game::Game(const char* title)
{
	std::cout << "gameConstr" << std::endl;
	win = new InitWindow(title, 0,0,0,0, SDL_WINDOW_OPENGL || SDL_WINDOW_SHOWN, SDL_RENDERER_ACCELERATED);
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
		if (selectOut(i, inPos)) return i;
	return nullptr;
}

// 0 - map, 1 - A, 2 - B, 3 - Ñ, 4 - Out, 5 - inE;
int Game::selectOut(IGameObject* chObj, Position selPos)
{
	int oX = chObj->getPos().x, oY = chObj->getPos().y;
	int mX = selPos.x, mY = selPos.y;
	if (mX > oX && mX < oX + 114 && mY > oY && mY < oY + 200)
	{
		if (mX > oX && mX < oX + 10 && mY > oY + 30 && mY < oY + 50) return 1;
		if (mX > oX && mX < oX + 10 && mY > oY + 90 && mY < oY + 110) return 2;
		if (mX > oX && mX < oX + 10 && mY > oY + 150 && mY < oY + 170) return 3;
		if (mX > oX + 104 && mX < oX + 114 && mY > oY + 90 && mY < oY + 110) return 4;
		return 5;
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

	if (EventGame->isButPressed(SDLK_0)) select_elem = 0;
	if (EventGame->isButPressed(SDLK_1)) select_elem = 1;
	if (EventGame->isButPressed(SDLK_2)) select_elem = 2;
	if (EventGame->isButPressed(SDLK_3)) select_elem = 3;
	if (EventGame->isButPressed(SDLK_4)) select_elem = 4;
	if (EventGame->isButPressed(SDLK_5)) select_elem = 5;
	if (EventGame->isButPressed(SDLK_6)) select_elem = 6;
	if (EventGame->isButPressed(SDLK_7)) select_elem = 7;
	if (EventGame->isButPressed(SDLK_8)) select_elem = 8;
	if (EventGame->isButPressed(SDLK_9)) select_elem = 9;

	if (EventGame->isButPressed(SDLK_w)) y += 10;
	if (EventGame->isButPressed(SDLK_s)) y -= 10;
	if (EventGame->isButPressed(SDLK_a)) x += 10;
	if (EventGame->isButPressed(SDLK_d)) x -= 10;
	

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
			if (!obj)
			{
				switch (select_elem)
				{
				case 0:
					vectorOfObjects.push_back(new Lamp(mousePos - Position(57, 100)));
					break;
				case 1:
					vectorOfObjects.push_back(new Switch(mousePos - Position(57, 100)));
					break;
				case 2:
					vectorOfObjects.push_back(new LogEAnd(mousePos - Position(57, 100)));
					break;
				case 3:
					vectorOfObjects.push_back(new LogENand(mousePos - Position(57, 100)));
					break;
				case 4:
					vectorOfObjects.push_back(new LogEOr(mousePos - Position(57, 100)));
					break;
				case 5:
					vectorOfObjects.push_back(new LogENor(mousePos - Position(57, 100)));
					break;
				case 6:
					vectorOfObjects.push_back(new LogEXor(mousePos - Position(57, 100)));
					break;
				case 7:
					vectorOfObjects.push_back(new LogEXnor(mousePos - Position(57, 100)));
					break;
				case 8:
					vectorOfObjects.push_back(new LogEInv(mousePos - Position(57, 100)));
					break;
				case 9:
					vectorOfObjects.push_back(new LogEBuf(mousePos - Position(57, 100)));
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
				case 3:
					outSelect = 1;
					connected = true;
					break;
				case 2:
				case 4:
					connected = true;
					break;
				case 5:
					if (dynamic_cast<Switch*>(obj))
					{
						if (mousePos.x > objPos.x + 30 && mousePos.x < objPos.x + 84 && mousePos.y > objPos.y + 50 && mousePos.y < objPos.y + 150)
						{
							sw = true;
							break;
						}
					}
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
		auto obj = getObjectFromPosition(mousePos);
		if (isMoved)
		{
			isMoved = false;
		}
		else if (connected)
		{
			if (obj)
			{
				Connection* con;
				switch (selectOut(obj, mousePos))
				{
				case 2:
				case 1:
					con = new Connection(obj, tmpObj, 0);
					vectorOfObjects.push_back(con);
					break;
				case 3:
					con = new Connection(obj, tmpObj, 1);
					vectorOfObjects.push_back(con);
					break;
				case 4:
					con = new Connection(tmpObj, obj, outSelect);
					vectorOfObjects.push_back(con);
					break;
				default:
					break;
				}
			}
			connected = false;


		}
		else if(sw)
		{
			if (dynamic_cast<Switch*>(obj))
			{
				dynamic_cast<Switch*>(obj)->Toggle();
				sw = false;
			}
		}
	}


	if (EventGame->isMouseButPressed(SDL_BUTTON_RIGHT))
	{
		auto obj = getObjectFromPosition(mousePos);
		if (obj)
		{
			static_cast<ILogElement*>(obj)->delConnection(selectOut(obj, mousePos));
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
	if (connected)
	{
		SDL_SetRenderDrawColor(win->getRenderer(), 0, 0, 0, 200);
		SDL_RenderDrawLine(win->getRenderer(), tmpObj->getPos().x, tmpObj->getPos().y,
			EventGame->getMousePosX(), EventGame->getMousePosY());
	}
	SDL_RenderPresent(win->getRenderer());
}

void Game::StopGame()
{
	run_game = false;
}

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

Position Game::getShiftPosition()
{
	return Position(x,y);
}
