#pragma once
#include "olcPixelGameEngine.h"
#include "Input.h"


class Player
{
public:
	Player(const Input& keyBindings, olc::Pixel tint)
		: m_input{ keyBindings },
			m_tint{tint}
	{
		m_imageCursor.Load("assets\\Hand.png");
	}
	std::optional<olc::vd2d> handleInput(olc::PixelGameEngine* pge, float fElapsedTime);

	void onDraw(olc::PixelGameEngine* pge) const
	{
		pge->DrawDecal(m_pos, m_imageCursor.Decal(), {0.8f,0.8f}, m_tint);
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
};

