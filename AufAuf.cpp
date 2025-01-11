#include "Game.h"
#include "GameSettings.h"

int main()
{
	Game demo;
	if (demo.Construct(GameSettings::gameW, GameSettings::gameH, 1, 1,true))
		demo.Start();
	return 0;
}