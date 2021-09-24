#pragma once

struct v2di
{
	v2di()
	{
		x = 0;
		y = 0;
	}
	v2di(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int x = 0;
	int y = 0;
};