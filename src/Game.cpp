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

	if (EventGame->isButPressed(SDLK_w)) y -= 10;
	if (EventGame->isButPressed(SDLK_s)) y += 10;
	if (EventGame->isButPressed(SDLK_a)) x -= 10;
	if (EventGame->isButPressed(SDLK_d)) x += 10;

	if (EventGame->getMouseScrollUp()) { zoom -= 1; if (zoom < 1) zoom = 1; }
	if (EventGame->getMouseScrollDown()) { zoom += 1; if (zoom > 10) zoom = 10;}
	

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
					if (dynamic_cast<Switch*>(obj)) break;
					if (dynamic_cast<LogEBuf*>(obj)) break;
					if (dynamic_cast<LogEInv*>(obj)) break;
					outSelect = 0;
					connected = 1;
					break;
				case 3:
					if (dynamic_cast<Switch*>(obj)) break;
					if (dynamic_cast<LogEBuf*>(obj)) break;
					if (dynamic_cast<LogEInv*>(obj)) break;
					outSelect = 1;
					connected = 2;
					break;
				case 2:
				case 4:
					if (dynamic_cast<Lamp*>(obj)) break;
					connected = 3;
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
				case 1:
					if (dynamic_cast<Switch*>(obj)) break;
					if (dynamic_cast<LogEBuf*>(obj)) break;
					if (dynamic_cast<LogEInv*>(obj)) break;
				case 2:
					con = new Connection(obj, tmpObj, 0);
					vectorOfObjects.push_back(con);
					break;
				case 3:
					if (dynamic_cast<Switch*>(obj)) break;
					if (dynamic_cast<LogEBuf*>(obj)) break;
					if (dynamic_cast<LogEInv*>(obj)) break;
					con = new Connection(obj, tmpObj, 1);
					vectorOfObjects.push_back(con);
					break;
				case 4:
					if (dynamic_cast<Lamp*>(obj)) break;
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
	
	std::string mouse_pos = std::to_string(EventGame->getMousePosX()) + ":" + std::to_string(EventGame->getMousePosY());
	TEXT->PrintText(FONTS::Cosmic, mouse_pos.c_str(),
		{ 0,0,0,180 }, win->getWinPos().w - 150, 30, mouse_pos.size() * 10, 20);

	for (auto i : vectorOfObjects) i->Render();

	if (connected)
	{
		int y_ = 0;
		if (connected == 1) y_ = 40;
		if (connected == 2) y_ = 160;
		if (connected == 3) y_ = 100;
		SDL_SetRenderDrawColor(win->getRenderer(), 0, 0, 0, 200);
		SDL_RenderDrawLine(win->getRenderer(), 
			tmpObj->getPos().x + (connected == 3 ? 110:0) - x, tmpObj->getPos().y + y_ - y,
			EventGame->getMousePosX(), EventGame->getMousePosY());
	}

	for (int i = 0; i < quest.size(); i++)
	{
		TEXT->PrintText(FONTS::Cosmic,
			quest.at(i).c_str(),
			{ (Uint8)(select_elem == i ? 255 : 0),0,0,180 }, win->getWinPos().w - 150, 50 + i * 20, quest.at(i).size() * 10, 20);
	}

	TEXT->PrintText(FONTS::Cosmic, "WASD - move", { 0,0,0,180 }, win->getWinPos().w - 150, 50 + quest.size() * 20, 120, 20);

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

int Game::getZoom()
{
	return zoom;
}
