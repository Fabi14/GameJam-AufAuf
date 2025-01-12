#include "Input.h"
#include <numeric>
#include <ranges>

olc::vd2d Input::getMoveDir()
{
    return std::reduce(std::begin(m_keyBindings.move), std::end(m_keyBindings.move), olc::vd2d{ 0.,0. },
		[&](olc::vd2d dir, const auto& binding)
		{
			return dir + (m_pge->GetKey(binding.key).bHeld ? binding.dir : olc::vd2d{ 0., 0. });
		}
	);
}

bool Input::isActionButtonPressed()
{
    return m_pge->GetKey(m_keyBindings.action.key).bPressed;
}

bool Input::isMoving()
{
	return !std::ranges::none_of(m_keyBindings.move, [&](const auto& binding) {return m_pge->GetKey(binding.key).bHeld; });
}

olc::vd2d InputGamePad::getMoveDir()
{
	if (gamepad)
	{
		return gamepad->getAxis(olc::GPAxes::LX) * olc::vd2d{ 1.,0. }
		+ gamepad->getAxis(olc::GPAxes::LY) * olc::vd2d{ 0.,1. };
	}
	return olc::vd2d();
}

bool InputGamePad::isActionButtonPressed()
{
	if (gamepad == nullptr || !gamepad->stillConnected) {
		gamepad = olc::GamePad::selectWithButton(olc::GPButtons::FACE_R);
		return gamepad;
	}
	return gamepad->getButton(olc::GPButtons::FACE_R).bPressed;
}

bool InputGamePad::isMoving() 
{
	auto dir = getMoveDir();
	auto dir2 = dir * dir;
	return dir2.x > 0.0001 || dir2.y >0.0001;
}
