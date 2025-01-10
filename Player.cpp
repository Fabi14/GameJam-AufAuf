#include "Player.h"
#include <numeric>
#include <ranges>

namespace
{
	constexpr double maxPlayerSpeed{ 500. };
	constexpr double maxPlayerBeschleunigung{ 500. };
}


std::optional<olc::vd2d> Player::handleInput(olc::PixelGameEngine* pge, float fElapsedTime)
{
	if (std::ranges::none_of(m_keys, [&](const auto& binding) {return pge->GetKey(binding.key).bHeld;}))
	{
		m_speed = 0;
	}
	else
	{
		m_speed = m_speed < maxPlayerSpeed ? m_speed + maxPlayerBeschleunigung * fElapsedTime : maxPlayerSpeed;
	}

	olc::vd2d dir = std::reduce(std::begin(m_keys), std::end(m_keys), olc::vd2d{ 0.,0. },
		[&](olc::vd2d dir, const auto& binding)
		{
			return dir + (pge->GetKey(binding.key).bHeld ? binding.dir : olc::vd2d{ 0., 0. });
		}
	);
	if (dir != olc::vd2d{ 0.,0. })
	{
		m_pos += dir.norm() * m_speed * fElapsedTime;
	}
	if (pge->GetKey(m_keys.back().key).bPressed)
	{
		return m_pos;
	}
	return std::nullopt;
}