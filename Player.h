#pragma once
#include "olcPixelGameEngine.h"
#include "Input.h"


class Player
{
public:
	Player(std::unique_ptr<IInput>&& keyBindings, olc::Pixel tint, const std::string& imagePath, olc::vd2d pos, const std::string& imageScoreBackgroundPath)
		: m_pInput{ std::move(keyBindings) },
		m_pos{pos},
		m_tint{tint}
	{
		m_imageCursor.Load(imagePath);
		m_imageScoreBackground.Load(imageScoreBackgroundPath);
	}
	std::optional<olc::vd2d> handleInput(olc::PixelGameEngine* pge, float fElapsedTime);

	void onDraw(olc::PixelGameEngine* pge) const;
	void drawPoints(olc::PixelGameEngine* pge, int index) const;

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

	olc::Pixel getColor() const
	{
		return m_tint;
	}

private:
	olc::Renderable m_imageCursor;
	olc::Renderable m_imageScoreBackground;

	olc::vd2d m_pos{100,100};
	olc::Pixel m_tint;
	std::unique_ptr<IInput> m_pInput;
	double m_speed{ 0 };
	bool m_isActive{ false };

	double blockTime{0.};

	int points{0};
};

