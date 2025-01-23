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

	void StopSheepStartAlarmSound();

	void StartSheepSounds();

	
	olc::Renderable m_imageSheep;
	olc::Renderable m_imageWecker;

	olc::Renderable m_imageFindTheAlarm;
	olc::Renderable m_imageTimer;

	std::vector<RandomMovePos> m_vecSheepPos;
	std::optional<RandomMovePos> m_weckerPos;

	std::optional<int> m_win{ std::nullopt };

	double timer{ 60. };

	int audioSamplehungrysheep{ -1 };
	bool isSheepAudioRunning{ false };

	int audioSampleArlarmClock{ -1 };

	//int audioSampleTimer{ -1 };
};

