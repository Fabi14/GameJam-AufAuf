#pragma once
#include <olcPixelGameEngine.h>

class Game;

class Level 
{
public:
	Level(Game* pge) :m_pge{ pge } {}

	virtual bool OnUserCreate();
	virtual void onLoad();
	virtual std::unique_ptr<Level> OnUserUpdate(float fElapsedTime);

protected:
	Game* m_pge;
};

