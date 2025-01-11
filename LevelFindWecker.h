#pragma once
#include "Level.h"
#include "RandomMovePos.h"
#include "Player.h"

class LevelFindWecker : public Level
{
public:
	LevelFindWecker(Game* pge) :Level{ pge } {}

	virtual bool OnUserCreate() override;
	virtual std::unique_ptr<Level> OnUserUpdate(float fElapsedTime) override;

private:
	void onDraw();

	
	olc::Renderable m_imageSheep;
	olc::Renderable m_imageWecker;

	std::vector<RandomMovePos> m_vecSheepPos;
	std::optional<RandomMovePos> m_weckerPos;

	std::optional<int> m_win{ std::nullopt };

	double timer{ 60. };

	int audioSamplehungrysheep{ -1 };
};

