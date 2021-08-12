#include "./src/Game.h"

int main(int argv, char** argc)
{
	int FrameRate = 60;
	
	while (SGame->isRunneble())
	{
		SGame->Update();
		SGame->Render();
		SDL_Delay(1000 / FrameRate);
	}
	return 0;
}