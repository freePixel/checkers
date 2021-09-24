#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "grid.h"
#include <iostream>
#include <string>
#include <map>
#include "vector2d.h"
#include <vector>

class Graphics
{
public:
	Graphics(grid* g);
	~Graphics();
	static const int wx = 600;
	static const int wy = 600;

	void draw();
	
	void set_highlight(std::vector<v2di> points);
	

private:
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;

	std::vector<v2di> highlight;

	std::map<piece, SDL_Texture*> texture_map;
		
	grid* _grid = nullptr;

	v2di click = { -1,-1 };

	void draw_board();
	void draw_pieces();
	void draw_highlight();



	SDL_Texture* load_texture(const char* src_path);

	void load_textures();
};


