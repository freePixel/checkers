#include "logic.h"

logic::logic()
{
	_grid = new grid();
	graph = new Graphics(_grid);
	_event = SDL_Event();
}
logic::~logic()
{
	delete graph;
	delete _grid;

}
void logic::run()
{
	while (is_running)
	{
		handle_event();
		handle_logic();
		handle_graphics();
		SDL_Delay(100);
	}
}


void logic::handle_event()
{
	evaluate_click = false;
	while (SDL_PollEvent(&_event) > 0)
	{
		switch (_event.type)
		{
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (_event.button.button)
			{
			case SDL_BUTTON_LEFT:
				v2di grid_click = { (int)(GRID_SIZE * (float)_event.motion.x / (graph->wx)) , (int)(GRID_SIZE * (float)_event.motion.y / (graph->wy)) };
				click[0] = { click[1].x , click[1].y };
				click[1] = grid_click;
				evaluate_click = true;
				break;
			}
		}
	}
}

void logic::play(v2di origin, v2di dest)
{
	std::vector<v2di> available = get_available_moves(origin.x , origin.y);
	for (int i = 0; i < available.size(); i++)
	{
		if (dest.x == available[i].x && dest.y == available[i].y)
		{
			if (dest.y == 0) _grid->set(dest.x, dest.y, piece::DOUBLE_RED);
			else {
				if(dest.y == 7) _grid->set(dest.x, dest.y, piece::DOUBLE_WHITE);
				else {
				_grid->set(dest.x, dest.y, _grid->get(origin.x, origin.y));
				}
			}
			_grid->set(origin.x, origin.y, piece::NONE);
			if (abs(dest.x - origin.x) >= 2)
			{
				_grid->set((origin.x + dest.x) / 2, (origin.y + dest.y) / 2, piece::NONE); //clear destroyed piece
			}
			
			turn_1 = !turn_1;
		}
	}
	selected = false;
	graph->set_highlight(std::vector<v2di>());
	std::cout << "unselected \n";
}

void logic::handle_logic()
{
	if (evaluate_click)
	{
		if (selected)
		{
			play(click[0],click[1]);
			
		}
		
		else {
			std::cout << "selected \n";
			std::vector<v2di> p = get_available_moves(click[1].x, click[1].y);
			graph->set_highlight(p);
			selected = true;
			if (p.size() == 0) selected = false;
		}
		
	}
}



void logic::handle_graphics()
{
	graph->draw();
}

std::vector<v2di> logic::get_available_moves(int x, int y) //return availables moves for a given position
{
	std::vector<v2di> available;
	switch (_grid->get(x, y))
	{
	case piece::RED:
		if (turn_1 == true)
		{
			if (x >= 1 && y >= 1) // left move
			{
				if (_grid->get(x - 1, y - 1) == piece::NONE) available.push_back({ x - 1,y - 1 });
				else {
					if (x >= 2 && y >= 2 && _grid->get(x - 2, y - 2) == piece::NONE && (_grid->get(x - 1, y - 1) == piece::WHITE || _grid->get(x - 1, y - 1) == piece::DOUBLE_WHITE))
					{
						available.push_back({x-2,y-2});
					}
				}
			}
			if (x <= 6 && y >= 1) //right move
			{
				if (_grid->get(x + 1, y - 1) == piece::NONE) available.push_back({ x + 1,y - 1 });
				else {
					if (x <= 5 && y >= 2 && _grid->get(x + 2, y - 2) == piece::NONE && (_grid->get(x + 1, y - 1) == piece::WHITE || _grid->get(x + 1, y - 1) == piece::DOUBLE_WHITE))
					{
						available.push_back({ x + 2,y - 2 });
					}
				}
			}
		}
		break;

	case piece::WHITE:
		if (turn_1 == false)
		{
			if (x >= 1 && y <= 6) // left move
			{
				if (_grid->get(x - 1, y + 1) == piece::NONE) available.push_back({ x - 1,y + 1 });
				else {
					if (x >= 2 && y <= 5  && _grid->get(x - 2, y + 2) == piece::NONE && (_grid->get(x - 1, y + 1) == piece::RED || _grid->get(x - 1, y + 1) == piece::DOUBLE_RED))
					{
						available.push_back({ x - 2,y + 2 });
					}
				}
			}
			if (x <= 6 && y <= 6) //right move
			{
				if (_grid->get(x + 1, y + 1) == piece::NONE) available.push_back({ x + 1,y + 1 });
				else {
					if (x <= 5 && y <= 5 && _grid->get(x + 2, y + 2) == piece::NONE && (_grid->get(x + 1, y + 1) == piece::RED || _grid->get(x + 1, y + 1) == piece::DOUBLE_RED))
					{
						available.push_back({ x + 2,y + 2 });
					}
				}
			}
		}
		break;
	}

	return available;
}
