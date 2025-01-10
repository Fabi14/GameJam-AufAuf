#include "Player.h"
#include "olcPGEX_Sound.h"
#include "olcPixelGameEngine.h"

constexpr int gameW{ 1920 };
constexpr int gameH{ 1080 };

struct RandomMovePos
{
	void onUpdate(float fElapsedTime)
	{
		pos += v * fElapsedTime * speed;

		//change dir
		if (pos.x < 0 || pos.x > gameW)
		{
			v.x *= -1;
		}
		if (pos.y < 0 || pos.y > gameH)
		{
			v.y *= -1;
		}
	}

	olc::vd2d pos{ static_cast<double>(std::rand() * 1920 / RAND_MAX),  static_cast<double>(std::rand() * 1080 / RAND_MAX) };
	olc::vd2d v{olc::vd2d{static_cast<double>(std::rand())*2. / RAND_MAX-1.,static_cast<double>(std::rand())*2. / RAND_MAX-1.}.norm()};
	double speed{ 70. };
};

#pragma once
class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		// Name your application
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

private:
	void onDraw();

	olc::Renderable m_imageRoom;
	olc::Renderable m_imageSheep;
	olc::Renderable m_imageWecker;

	std::vector<RandomMovePos> m_vecSheepPos{200};
	RandomMovePos m_weckerPos;

	std::vector<Player> m_vecPlayer;
	std::optional<int> m_win{ std::nullopt };
};

