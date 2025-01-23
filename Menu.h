#pragma once
#include "Level.h"

class Game;

class Menu : public Level
{
public:
	Menu(Game* pge) :Level{ pge } {}

	virtual bool OnUserCreate() override;
	virtual std::unique_ptr<Level> OnUserUpdate(float fElapsedTime) override;

private:
	olc::Renderable m_imageTitle;
	olc::Renderable m_imageCredits;
};

