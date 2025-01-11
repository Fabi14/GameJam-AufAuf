#include "Player.h"
#include <numeric>
#include <ranges>
#include "Helper.h"

namespace
{
	constexpr double maxPlayerSpeed{ 500. };
	constexpr double maxPlayerBeschleunigung{ 500. };
}

std::optional<olc::vd2d> Player::handleInput(olc::PixelGameEngine* pge, float fElapsedTime)
{
	if (blockTime > 0.)
	{
		blockTime -= fElapsedTime;
		return std::nullopt;
	}
	if (m_input.isMoving())
	{
		m_speed = m_speed < maxPlayerSpeed ? m_speed + maxPlayerBeschleunigung * fElapsedTime : maxPlayerSpeed;
	}
	else
	{
		m_speed = 0;
	}

	olc::vd2d dir = m_input.getMoveDir();
	if (dir != olc::vd2d{ 0.,0. })
	{
		m_pos += dir.norm() * m_speed * fElapsedTime;
	}
	if (m_input.isActionButtonPressed())
	{
		return m_pos + calcCenter(m_imageCursor);
	}
	return std::nullopt;
}