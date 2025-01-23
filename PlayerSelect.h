#pragma once
#include "Level.h"
#include "Player.h"

class PlayerSelect : public Level
{
public:
	PlayerSelect(Game* pge) : Level{ pge } {}

	virtual bool OnUserCreate() override;
	virtual std::unique_ptr<Level> OnUserUpdate(float fElapsedTime) override;

private:
	olc::Renderable m_imageInputWASD;
	olc::Renderable m_imageInputArrows;
	olc::Renderable m_imageInputController;

	bool m_canStart{ false };
};

