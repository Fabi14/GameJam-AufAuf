#include "RandomMovePos.h"
#include "GameSettings.h"

void RandomMovePos::onUpdate(float fElapsedTime)
{
	pos += v * fElapsedTime * speed;

	//change dir
	if (pos.x < 0 || pos.x > GameSettings::gameW)
	{
		v.x *= -1;
	}
	if (pos.y < 0 || pos.y > GameSettings::gameH)
	{
		v.y *= -1;
	}
}
