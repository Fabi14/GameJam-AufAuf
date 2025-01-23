#include "LevelFindWecker.h"
#include "Helper.h"
#include "Game.h"
#include <ranges>
#include "Scoreboard.h"
#include "GameSettings.h"

bool LevelFindWecker::OnUserCreate()
{

	m_imageSheep.Load("assets\\Sheep1.png");
	m_imageWecker.Load("assets\\Wecker1.png");
	m_imageFindTheAlarm.Load("assets\\Textbox.png");
	m_imageTimer.Load("assets\\TimeBox.png");

	std::generate_n(std::back_inserter(m_vecSheepPos), 100, [&]() {return RandomMovePos{ m_imageSheep.Sprite()->Size() }; });
	m_weckerPos = RandomMovePos{ m_imageWecker.Sprite()->Size() };

	audioSamplehungrysheep = olc::SOUND::LoadAudioSample("assets\\hungrysheep-61124.wav");
	audioSampleArlarmClock = olc::SOUND::LoadAudioSample("assets\\monoalarm.wav");
	//audioSampleTimer = olc::SOUND::LoadAudioSample("assets\\kitchen-timer.wav");
	StartSheepSounds();
    return true;
}

std::unique_ptr<Level> LevelFindWecker::OnUserUpdate(float fElapsedTime)
{
	onDraw();
	if (m_win)
	{
		return nullptr;
	}
	timer -= fElapsedTime;
	//if (timer < 10.)
	//{
	//	olc::SOUND::PlaySample(audioSampleTimer);
	//}
	if (timer < 0.)
	{
		auto scoreBoard = std::make_unique<Scoreboard>(m_pge);
		scoreBoard->OnUserCreate();

		using namespace std::views;
		scoreBoard->addPoints(m_pge->m_vecPlayer 
			| transform([](const auto& p) {return Score{ p->getPoints(), p->getColor() }; }) 
			| std::ranges::to<std::vector>());
		StopSheepStartAlarmSound();
		return scoreBoard;
	}


	for (auto& sheepPos : m_vecSheepPos)
	{
		sheepPos.onUpdate(fElapsedTime);
	}
	m_weckerPos->onUpdate(fElapsedTime);

	for (int i = 0; i < m_pge->m_vecPlayer.size(); ++i)
	{
		auto pos = m_pge->m_vecPlayer[i]->handleInput(m_pge, fElapsedTime);
		if (pos)
		{
			auto min = m_weckerPos->getPos() - 0.5 * olc::vd2d{ static_cast<double>(m_imageWecker.Sprite()->width),static_cast<double>(m_imageWecker.Sprite()->height) };
			auto max = m_weckerPos->getPos() + 0.5 * olc::vd2d{ static_cast<double>(m_imageWecker.Sprite()->width),static_cast<double>(m_imageWecker.Sprite()->height) };
			if (pos->x > min.x && pos->x < max.x && pos->y > min.y && pos->y < max.y)
			{
				timer += 5;
				m_win = i;
				m_pge->m_vecPlayer[i]->addPoint();
			}
			else
			{
				m_pge->m_vecPlayer[i]->block();
			}
		} 
	}

    return nullptr;
}

void LevelFindWecker::onDraw()
{
	m_pge->Clear(olc::BLACK);
	m_pge->DrawDecal(olc::vd2d{ 0.,0. }, m_pge->m_imageRoom.Decal());

	auto offset = calcCenter(m_imageWecker);
	m_pge->DrawDecal(m_weckerPos->getPos() - offset, m_imageWecker.Decal());

	if (!m_win)
	{
		auto offset = calcCenter(m_imageSheep);
		for (const auto& sheepPos : m_vecSheepPos)
		{
			olc::vf2d scale = sheepPos.getDir().x < 0 ? olc::vf2d{ -1.f,1.f } : olc::vf2d{ 1.f, 1.f };
			m_pge->DrawDecal(sheepPos.getPos() - offset, m_imageSheep.Decal(), scale);
		}
		StartSheepSounds();
	
		m_pge->DrawDecal({ 0.f, 0.f }, m_imageFindTheAlarm.Decal());
		//m_pge->DrawStringDecal(olc::vd2d{ 700.,900. }, "Find the alarm clock!", olc::DARK_GREY, { 5.f,5.f });
	}
	for (const auto& [i,player] : std::views::enumerate(m_pge->m_vecPlayer))
	{
		player->onDraw(m_pge);
		player->drawPoints(m_pge, i);
	}

	if (m_win)
	{
		StopSheepStartAlarmSound();
		m_pge->DrawStringDecal({ 800.,300. }, "WIN", m_pge->m_vecPlayer[*m_win]->getColor(), {20.,20.});

		m_pge->DrawStringDecal(olc::vd2d{ 900.,1000. }, "SPACE", olc::DARK_GREY, { 5.f,5.f });

		if (m_pge->GetKey(olc::SPACE).bPressed)
		{
			m_win = std::nullopt;
			m_weckerPos = RandomMovePos{ m_imageWecker.Sprite()->Size() };
			std::generate_n(std::back_inserter(m_vecSheepPos), 20, [&]() {return RandomMovePos{ m_imageSheep.Sprite()->Size() }; });
		}
	}
	m_pge->DrawDecal(olc::vf2d{ 1120.f,0.f }, m_imageTimer.Decal());
	m_pge->DrawStringDecal(olc::vf2d{ 1300.f,100.f-20.f }, std::to_string(timer), olc::BLACK, {6.f,6.f});
}

void LevelFindWecker::StopSheepStartAlarmSound()
{
	if(isSheepAudioRunning)
	{
		olc::SOUND::PlaySample(audioSampleArlarmClock, false);
		olc::SOUND::StopSample(audioSamplehungrysheep);

		isSheepAudioRunning = false;
	}
}

void LevelFindWecker::StartSheepSounds()
{
	if (!isSheepAudioRunning)
	{
		olc::SOUND::PlaySample(audioSamplehungrysheep, true);
		isSheepAudioRunning = true;
	}
}
