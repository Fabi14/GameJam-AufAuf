#pragma once
#include <array>
#include <olcPixelGameEngine.h>

struct KeyBinding
{
	olc::Key key;
	olc::vd2d dir;
};

const std::array KeyBinding_WASD
{
	KeyBinding{olc::Key::W,olc::vd2d{0.,-1.}},
	KeyBinding{olc::Key::S,olc::vd2d{0.,1.}},
	KeyBinding{olc::Key::A,olc::vd2d{-1.,0.}},
	KeyBinding{olc::Key::D,olc::vd2d{1.,0.}},
	KeyBinding{olc::Key::E,olc::vd2d{0.,0.}}
};

const std::array KeyBinding_Arrows
{
	KeyBinding{olc::Key::UP,{0.,-1.}},
	KeyBinding{olc::Key::DOWN,{0.,1.}},
	KeyBinding{olc::Key::LEFT,{-1.,0.}},
	KeyBinding{olc::Key::RIGHT,{1.,0.}},
	KeyBinding{olc::Key::CTRL,olc::vd2d{0.,0.}}
};
