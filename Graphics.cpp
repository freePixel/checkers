#include "Graphics.h"

Graphics::Graphics(grid* g)
{
	this->_grid = g;
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("checkers", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wx, wy, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	load_textures();
}

Graphics::~Graphics()
{
	//dealocate textures
	for (auto const& x : texture_map)
	{
		SDL_DestroyTexture(x.second);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Graphics::draw()
{
	SDL_RenderClear(renderer);

	draw_board();
	draw_highlight();
	draw_pieces();

	SDL_RenderPresent(renderer);
}

void Graphics::draw_highlight()
{
	float w = (float)wx / GRID_SIZE;
	float h = (float)wy / GRID_SIZE;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	for (int i = 0; i < highlight.size(); i++)
	{
		const SDL_FRect* square = new SDL_FRect{ w * highlight[i].x,w * highlight[i].y,w,h };
		SDL_RenderFillRectF(renderer, square);
		delete square;

	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Graphics::set_highlight(std::vector<v2di> points)
{
	highlight = points;
}

void Graphics::draw_board()
{
	float w = (float)wx / GRID_SIZE;
	float h = (float)wy / GRID_SIZE;
	for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			const SDL_FRect* square = new SDL_FRect{ w*x,w*y,w,h};
			
			if ((x + y) % 2 == 0) SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			else {
				SDL_SetRenderDrawColor(renderer, 0, 30, 2, 255);
			}
			SDL_RenderFillRectF(renderer, square);
			delete square;
		}
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Graphics::draw_pieces()
{
	float w = (float)wx / GRID_SIZE;
	float h = (float)wy / GRID_SIZE;
	for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			if (_grid->get(x, y) != piece::NONE)
			{
				const SDL_FRect* square = new SDL_FRect{ w * x,w * y,w,h };
				SDL_RenderCopyF(renderer, texture_map[_grid->get(x, y)], NULL, square);
				delete square;
			}
		}
	}
}


SDL_Texture* Graphics::load_texture(const char* src_path)
{
	std::cout << "Loading texture: " << src_path << "\n";
	SDL_Surface* surface = IMG_Load(src_path);
	if (surface != nullptr)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
		SDL_FreeSurface(surface);
		if(texture == nullptr) std::cout << "Error:" << SDL_GetError() << "\n";
		return texture;
		
	}
	else {
		std::cout << "Error:" << SDL_GetError() << "\n";
		return nullptr;
	}
}

void Graphics::load_textures()
{
	texture_map[piece::WHITE] = load_texture("textures/white.png");
	texture_map[piece::DOUBLE_WHITE] = load_texture("textures/d_white.png");
	texture_map[piece::RED] = load_texture("textures/red.png");
	texture_map[piece::DOUBLE_RED] = load_texture("textures/d_red.png");
}
