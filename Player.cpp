#include "Player.h"
#include <numeric>
#include <ranges>
#include "Helper.h"
#include "GameSettings.h"

namespace
{
	constexpr double maxPlayerSpeed{ 1000. };
	constexpr double maxPlayerBeschleunigung{ 500. };
}

std::optional<olc::vd2d> Player::handleInput(olc::PixelGameEngine* pge, float fElapsedTime)
{
	if (m_isActive)
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
			m_pos.x = m_pos.x < 0 ? 0 : m_pos.x;
			m_pos.x = m_pos.x > GameSettings::gameW ? GameSettings::gameW : m_pos.x;
			m_pos.y = m_pos.y < 0 ? 0 : m_pos.y;
			m_pos.y = m_pos.y > GameSettings::gameH ? GameSettings::gameH : m_pos.y;
		}
	}
	if (m_input.isActionButtonPressed())
	{
		return m_pos;
	}
	return std::nullopt;
}

void Player::onDraw(olc::PixelGameEngine* pge) const
{
	if (blockTime > 0.)
	{
		pge->DrawDecal(m_pos- calcCenter(m_imageCursor), m_imageCursor.Decal(), { 1.f, 1.f }, olc::DARK_GREY);
		return;
	}
	pge->DrawDecal(m_pos- calcCenter(m_imageCursor), m_imageCursor.Decal(), { 1.f,1.f }, m_isActive ? olc::WHITE : olc::BLACK);
}
