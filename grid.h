#pragma once

#include <array>

#define GRID_SIZE 8

enum class piece
{
	NONE = 0, WHITE , RED , DOUBLE_WHITE , DOUBLE_RED
};

class grid
{
public:
	grid();
	void set(int x, int y, piece p);
	piece get(int x, int y);
	
	void reset();

private:
	std::array<std::array<piece, GRID_SIZE>, GRID_SIZE> data;

};

