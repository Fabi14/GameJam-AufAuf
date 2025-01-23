#pragma once
#include "Level.h"
#include <vector>

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

private:
	olc::Renderable m_win;
	std::vector<std::pair<olc::Pixel, olc::Renderable>> m_mapWinner;
	std::vector<Score> scores;
};

