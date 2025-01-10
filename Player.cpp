#include "Player.h"

namespace
{
	constexpr double playerSpeed{ 5. };
}


void Player::handleInput(olc::PixelGameEngine* pge, float fElapsedTime)
{
	for (const auto& binding : m_keys)
	{
		if (pge->GetKey(binding.key).bHeld)
		{
			m_pos += binding.dir * playerSpeed;
		}
	}
}