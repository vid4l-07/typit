#include <chrono>
#include "render.h"
#include "player.h"
#include "Game.h"

void Game::set_start_time(){
	inicio = std::chrono::high_resolution_clock::now();
}
double Game::get_time() const{
	auto fin = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tiempo = fin - inicio;
	return tiempo.count();
}

void Game::start() {
	render.enable_raw_mode();
	render.clear();
	if (mode == 'w'){
		render.max_words = 15;
		render.update(player);
		main_loop_words();
	} else {
		render.max_words = 999999;
		render.update(player);
		main_loop_time();
	}
}

void Game::end() {
	render.disable_raw_mode();
	double accuracy = (double(player.org_str.size()) - player.errors) / double(player.org_str.size()) * 100;
	std::cout << "\n\n";
	if (mode == 'w'){
		std::cout << "Tiempo: " << duration << " segundos\n";
	} else {
		std::cout << "Palabras: " << player.words << "\n";
	}
	std::cout << "Precision: " << accuracy << " %\n";
	std::cout << "Errores: " << player.errors << " errores\n";
}

void Game::main_loop_words(){
	int index = 0;

	set_start_time();
	while (index < player.org_str.size()) {
		char c = getchar();

		if (c < 32) continue;
		if (c == 127){
			if (index > 0){
				index --;
				player.backspace(index);
			}

		} else if (c == player.rest_str[0]){
			player.type(c, true);
			index ++;

		} else{
			player.type(c, false);
			index ++;

		}
		render.update(player);
	}
	duration = get_time();
}

void Game::main_loop_time(){
	int index = 0;

	set_start_time();
	while (get_time() < 10) {
		char c = getchar();

		if (c < 32) continue;
		if (c == 127){
			if (index > 0){
				index --;
				player.backspace(index);
			}

		} else if (c == player.rest_str[0]){
			player.type(c, true);
			index ++;

		} else{
			player.type(c, false);
			index ++;

		}
		render.update(player);
	}
	duration = get_time();
}
