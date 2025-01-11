#pragma once
#include <olcPixelGameEngine.h>

class RandomMovePos
{
public:
	RandomMovePos(olc::vd2d size) : m_size{ size } {}

	void onUpdate(float fElapsedTime);

	olc::vd2d getPos()const
	{
		return pos;
	}
	olc::vd2d getDir()const
	{
		return v;
	}

private:
	olc::vd2d pos{ static_cast<double>(std::rand() * 1920 / RAND_MAX),  static_cast<double>(std::rand() * 1080 / RAND_MAX) };
	olc::vd2d v{ olc::vd2d{static_cast<double>(std::rand()) * 2. / RAND_MAX - 1.,static_cast<double>(std::rand()) * 2. / RAND_MAX - 1.}.norm() };
	double speed{ 70. };

	olc::vd2d m_size;
};

 