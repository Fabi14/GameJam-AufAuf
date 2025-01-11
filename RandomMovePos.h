#pragma once
#include <olcPixelGameEngine.h>

class RandomMovePos
{
public:
	void onUpdate(float fElapsedTime);

	olc::vd2d getPos()const
	{
		return pos;
	}

private:
	olc::vd2d pos{ static_cast<double>(std::rand() * 1920 / RAND_MAX),  static_cast<double>(std::rand() * 1080 / RAND_MAX) };
	olc::vd2d v{ olc::vd2d{static_cast<double>(std::rand()) * 2. / RAND_MAX - 1.,static_cast<double>(std::rand()) * 2. / RAND_MAX - 1.}.norm() };
	double speed{ 70. };
};

