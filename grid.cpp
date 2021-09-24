#include "grid.h"

grid::grid()
{
	reset();
}

void grid::set(int x, int y, piece p)
{
	data[y][x] = p;
}

piece grid::get(int x, int y)
{
	return data[y][x];
}

void grid::reset()
{
	for (int y = 0; y < GRID_SIZE; y++)
	{
		data[y].fill(piece::NONE);
	}
	data[0][1] = piece::WHITE; data[0][3] = piece::WHITE; data[0][5] = piece::WHITE; data[0][7] = piece::WHITE;
	data[1][0] = piece::WHITE; data[1][2] = piece::WHITE; data[1][4] = piece::WHITE; data[1][6] = piece::WHITE;
	data[2][1] = piece::WHITE; data[2][3] = piece::WHITE; data[2][5] = piece::WHITE; data[2][7] = piece::WHITE;

	data[5][0] = piece::RED; data[5][2] = piece::RED; data[5][4] = piece::RED; data[5][6] = piece::RED;
	data[6][1] = piece::RED; data[6][3] = piece::RED; data[6][5] = piece::RED; data[6][7] = piece::RED;
	data[7][0] = piece::RED; data[7][2] = piece::RED; data[7][4] = piece::RED; data[7][6] = piece::RED;
}