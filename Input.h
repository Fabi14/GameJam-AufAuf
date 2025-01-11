#pragma once
#include <array>
#include <variant>
#include <olcPixelGameEngine.h>

struct KeyBindingMove
{
	olc::Key key;
	olc::vd2d dir;
};

struct KeyBindingAction
{
	olc::Key key;
	//Action
};

struct KeyBinding
{
	std::array<KeyBindingMove, 4> move;
	KeyBindingAction action;
};

const KeyBinding KeyBinding_WASD
{
	KeyBindingMove{olc::Key::W,olc::vd2d{0.,-1.}},
	KeyBindingMove{olc::Key::S,olc::vd2d{0.,1.}},
	KeyBindingMove{olc::Key::A,olc::vd2d{-1.,0.}},
	KeyBindingMove{olc::Key::D,olc::vd2d{1.,0.}},
	KeyBindingAction{olc::Key::E}
};

const KeyBinding KeyBinding_Arrows
{
	KeyBindingMove{olc::Key::UP,{0.,-1.}},
	KeyBindingMove{olc::Key::DOWN,{0.,1.}},
	KeyBindingMove{olc::Key::LEFT,{-1.,0.}},
	KeyBindingMove{olc::Key::RIGHT,{1.,0.}},
	KeyBindingAction{olc::Key::NP0}
};


class Input
{
public:
	Input(KeyBinding keyBindings, olc::PixelGameEngine* pge) :m_keyBindings{ keyBindings }, m_pge{pge} {};

	olc::vd2d getMoveDir();
	bool isActionButtonPressed();
	bool isMoving();

private:
	KeyBinding m_keyBindings;
	olc::PixelGameEngine* m_pge;
};

class InputGamePad
{
public:
	InputGamePad(olc::PixelGameEngine* pge) : m_pge{ pge } {};

	olc::vd2d getMoveDir();
	bool isActionButtonPressed();
	bool isMoving();

private:
	olc::PixelGameEngine* m_pge;
};