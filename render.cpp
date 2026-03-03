#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string>
#include "render.h"

void Render::clear(){
	std::cout << "\033[2J";
}

void Render::get_center() {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	filas = w.ws_row / 2;
	columnas = w.ws_col / 2;
}

void Render::center(int filas, int columnas){
	std::cout << "\033[" << filas << ";" << columnas << "H";
}

void Render::update(const Player& player){
	get_center();
	clear();
	center(filas, columnas);
	std::cout << player.rest_str; 
	center(filas, columnas - player.player_input.size());
	std::cout << player.dump_input();
	center(filas, columnas);
}

void Render::enable_raw_mode() {
	termios newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void Render::disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
