#pragma once
#include <olcPixelGameEngine.h>

inline olc::vd2d calcCenter(const olc::Renderable& renderable)
{
	if (renderable.Sprite())
	{
		return { renderable.Sprite()->width / 2., renderable.Sprite()->height / 2. };
	}
	return {};
}
