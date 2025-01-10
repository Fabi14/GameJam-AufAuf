#pragma once
#include "olcPixelGameEngine.h"

struct KeyBinding
{
	olc::Key key;
	olc::vd2d dir;
};

const std::array<KeyBinding, 4> KeyBinding_WASD
{
	KeyBinding{olc::Key::W,olc::vd2d{0.,-1.}},
	KeyBinding{olc::Key::S,olc::vd2d{0.,1.}},
	KeyBinding{olc::Key::A,olc::vd2d{-1.,0.}},
	KeyBinding{olc::Key::D,olc::vd2d{1.,0.}}
};

const std::array<KeyBinding, 4> KeyBinding_Arrows
{
	KeyBinding{olc::Key::UP,{0.,-1.}},
	KeyBinding{olc::Key::DOWN,{0.,1.}},
	KeyBinding{olc::Key::LEFT,{-1.,0.}},
	KeyBinding{olc::Key::RIGHT,{1.,0.}}
};

class Player
{
public:
	Player(const std::array<KeyBinding, 4>& keyBindings, olc::Pixel tint) 
		:	m_keys{ keyBindings },
			m_tint{tint}
	{
		m_imageCursor.Load("assets\\Hand.png");
	}
	void handleInput(olc::PixelGameEngine* pge, float fElapsedTime);

	void onDraw(olc::PixelGameEngine* pge) const
	{
		pge->DrawDecal(m_pos, m_imageCursor.Decal(), {0.8f,0.8f}, m_tint);
	}

private:
	olc::Renderable m_imageCursor;
	olc::vd2d m_pos;
	olc::Pixel m_tint;
	std::array<KeyBinding, 4> m_keys{ KeyBinding_Arrows };
};

