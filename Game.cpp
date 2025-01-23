#include "Game.h"
#include "olcPGEX_Gamepad/olcPGEX_Gamepad.h"
#include "Helper.h"
#include "extensions/olcPGEX_Sound.h"

bool Game::OnUserCreate()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	m_imageRoom.Load("assets\\BedroomColor1.png");

	olc::GamePad::init();
	m_currentLevel->OnUserCreate();

	olc::SOUND::InitialiseAudio();
	

	return true;
}

bool Game::OnUserUpdate(float fElapsedTime) 
{
	if (GetKey(olc::ESCAPE).bPressed)
	{
		olc::SOUND::DestroyAudio();
		return false;
	}

	if (auto nextLevel = m_currentLevel->OnUserUpdate(fElapsedTime))
	{
		m_currentLevel = std::move(nextLevel);
	}

	if (gamepad == nullptr || !gamepad->stillConnected) {
		DrawString(10, 10, "Press the select button on a gamepad!");
		gamepad = olc::GamePad::selectWithButton(olc::GPButtons::FACE_R);
		return true;
	}

	if (!gamepad->getButton(olc::GPButtons::FACE_D).bHeld) {
		FillRect(10, 10, 30, 10, olc::WHITE * gamepad->getAxis(olc::GPAxes::TL));
		DrawRect(10, 10, 30, 10, olc::RED);
		return true;
	}
	else {
		FillRect(10, 10, 30, 10, olc::WHITE * gamepad->getAxis(olc::GPAxes::TL));
		DrawRect(10, 10, 30, 10, olc::BLUE);
		return true;
	}


	return true;
}

