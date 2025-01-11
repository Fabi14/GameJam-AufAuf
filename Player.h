#pragma once
#include "olcPixelGameEngine.h"
#include "Input.h"


class Player
{
public:
	Player(const Input& keyBindings, olc::Pixel tint, std::string imagePath, olc::vd2d pos)
		: m_input{ keyBindings },
		m_pos{pos},
		m_tint{tint}
	{
		m_imageCursor.Load(imagePath);
	}
	std::optional<olc::vd2d> handleInput(olc::PixelGameEngine* pge, float fElapsedTime);

	void onDraw(olc::PixelGameEngine* pge) const;

	void setActive()
	{
		m_isActive = true;
	}

	bool isActive() const
	{
		return m_isActive;
	}

	void block()
	{
		blockTime = 1.;
	}

	void addPoint()
	{
		points++;
	}

	int getPoints() const
	{
		return points;
	}

	olc::Pixel getColor()
	{
		return m_tint;
	}

private:
	olc::Renderable m_imageCursor;
	olc::vd2d m_pos{100,100};
	olc::Pixel m_tint;
	Input m_input;
	double m_speed{ 0 };
	bool m_isActive{ false };

	double blockTime{0.};

	int points{0};
};

