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

	bool m_canStart{ false };
};

