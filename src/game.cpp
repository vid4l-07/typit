#include <chrono>
#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include "render.h"
#include "player.h"
#include "Game.h"
#include "term.h"

void Game::set_start_time(){
	inicio = std::chrono::high_resolution_clock::now();
}
double Game::get_time() const{
	auto fin = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tiempo = fin - inicio;
	return tiempo.count();
}

void Game::start() {
	Terminal term;
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
	render.clear();
	double accuracy = (double(player.org_str.size()) - player.errors) / double(player.org_str.size()) * 100;
	std::cout << "\n\n";
	std::cout << "Tiempo: " << duration << " segundos\n";
	std::cout << "Palabras: " << player.words_typed << "\n";
	std::cout << "WPM: " << get_wpm() << " \n";
	std::cout << "Precision: " << accuracy << " %\n";
	std::cout << "Errores: " << player.errors << " errores\n";
}

double Game::get_wpm(){
	return player.words_typed / (get_time() / 60);
}

bool Game::key_pressed() {
    timeval tv; 
	tv.tv_sec = 0;
	tv.tv_usec = 5000;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    // select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
	int ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

    if (ret == -1)
		return false;
    return FD_ISSET(STDIN_FILENO, &fds);
}

void Game::handle_input(char c){
	if (c < 32) return;
	if (c == ' ') player.words_typed ++;

	if (c == 127){
		player.backspace();
	} else if (c == player.rest_str[0]){
		player.type(c, true);
	} else{
		player.type(c, false);
	}
}

void Game::main_loop_words(){
	set_start_time();
	while (player.index < player.org_str.size()) {
		if (key_pressed()){
			char c = getchar();
			handle_input(c);
			render.update(player);
		}
		render.stats(get_time(), get_wpm());
	}
	duration = get_time();
}

void Game::main_loop_time(){
	int index = 0;
	set_start_time();
	while (duration < 10) {
		duration = get_time();
		if (key_pressed()){
			char c = getchar();
			handle_input(c);
			render.update(player);
		}
		render.stats(10 - get_time(), get_wpm());
	}
}
