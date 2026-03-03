#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <chrono>
#include "player.h"
#include "render.h"

class Game{
	private:
	Player player;
	Render render;
	std::chrono::time_point<std::chrono::high_resolution_clock> inicio;
	void main_loop();

	public:
	double duration;

	Game(Player& player_param, Render render_param): player(player_param), render(render_param) {}

	void start();
	void end();
	void set_start_time();
	double get_time() const;
};

#endif
