#pragma once
#include <SDL.h>
#include <map>
#include "./GameObjects/IGameObject.h"

#define EventGame SEvent::instance()

class SEvent
{
public:
	static SEvent* instance();
	void Update();
	bool isButPressed(SDL_KeyCode button);
	bool isMouseButPressed(int button);
	int getMousePosX();
	int getMousePosY();
	Position getPos();
	bool getMouseScrollUp();
	bool getMouseScrollDown();
private:
	SDL_Event e;
	SEvent() {}
	std::map<int, bool> buttonBuffer;
	std::map<int, bool> mouseBuffer;
	int MouseX = 0, MouseY = 0;
	double mouseScrollY = 0;
};

