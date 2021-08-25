#include "SEvent.h"
#include "Game.h"

SEvent* SEvent::instance()
{
    static SEvent* st_event = new SEvent();
    return st_event;
}

void SEvent::Update()
{
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT) { SGame->StopGame(); }
        if (e.type == SDL_KEYDOWN) { buttonBuffer.insert_or_assign(e.key.keysym.sym, true); }
        if (e.type == SDL_KEYUP) { buttonBuffer.insert_or_assign(e.key.keysym.sym, false); }
        if (e.type == SDL_MOUSEBUTTONDOWN) { mouseBuffer.insert_or_assign(e.button.button, true); }
        if (e.type == SDL_MOUSEBUTTONUP) { mouseBuffer.insert_or_assign(e.button.button, false); }
        if (e.type == SDL_MOUSEWHEEL) { mouseScrollY = e.wheel.y; }
    }
    SDL_GetMouseState(&MouseX, &MouseY);
}

bool SEvent::isButPressed(SDL_KeyCode button)
{
    if (buttonBuffer.find(button) != buttonBuffer.end())
        return buttonBuffer[button];
    buttonBuffer.insert({ button, false });
    return false;
}

bool SEvent::isMouseButPressed(int button)
{
    if (mouseBuffer.find(button) != mouseBuffer.end())
        return mouseBuffer[button];
    mouseBuffer.insert({ button, false });
    return false;
}

int SEvent::getMousePosX()
{
    return MouseX + SGame->getShiftPosition().x;
}

int SEvent::getMousePosY()
{
    return MouseY + SGame->getShiftPosition().y;
}

Position SEvent::getPos()
{
    return Position(MouseX, MouseY) + SGame->getShiftPosition();
}

bool SEvent::getMouseScrollUp()
{
    return mouseScrollY > 0 ? true : false;
}

bool SEvent::getMouseScrollDown()
{
    return mouseScrollY < 0 ? true : false;
}
