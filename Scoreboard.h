#pragma once
#include "Level.h"


struct Score
{
	int points;
	olc::Pixel color;
};

class Scoreboard : public Level
{
public:
	Scoreboard(Game* pge) :Level{ pge } {}

	void addPoints(const std::vector<Score>& points);
	virtual bool OnUserCreate() override;
	virtual std::unique_ptr<Level> OnUserUpdate(float fElapsedTime) override;
};

