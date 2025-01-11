#pragma once
#include "olcPixelGameEngine.h"
#include "Input.h"


class Player
{
public:
	Player(const Input& keyBindings, olc::Pixel tint, std::string imagePath)
		: m_input{ keyBindings },
			m_tint{tint}
	{
		m_imageCursor.Load(imagePath);
	}
	std::optional<olc::vd2d> handleInput(olc::PixelGameEngine* pge, float fElapsedTime);

	void onDraw(olc::PixelGameEngine* pge) const
	{
		if (blockTime > 0.)
		{
			pge->DrawDecal(m_pos, m_imageCursor.Decal(), { 1.f, 1.f }, olc::DARK_GREY );
			return;
		}

		pge->DrawDecal(m_pos, m_imageCursor.Decal(), {1.f,1.f});
	}

	olc::Pixel getColor()
	{
		return m_tint;
	}

	void block()
	{
		blockTime = 1.;
	}

private:
	olc::Renderable m_imageCursor;
	olc::vd2d m_pos{100,100};
	olc::Pixel m_tint;
	Input m_input;
	double m_speed{ 0 };

	double blockTime{0.};
};

