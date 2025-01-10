#include "Game.h"

int main()
{
	Game demo;
	if (demo.Construct(1920, 1080, 1, 1,true))
		demo.Start();
	return 0;
}