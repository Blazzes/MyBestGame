#include "./src/Game.h"

int main(int argv, char** argc)
{
	int FrameRate = 60;
	std::cout << "start" << std::endl;

	while (SGame->isRunneble())
	{
		SGame->Update();
		SGame->Render();
		SDL_Delay(1000 / FrameRate);
	}
	std::cout << "Stop" << std::endl;
	return 0;
}