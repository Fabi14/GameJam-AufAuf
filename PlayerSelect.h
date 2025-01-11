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
	bool m_canStart{ false };
};

