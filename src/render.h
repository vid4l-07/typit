#pragma once
#include <termios.h>
#include <string>
#include "player.h"

class Render{
	private:
	int filas;
	int columnas;
	int words_gen;

	public:
	int max_words;
	Render():  words_gen(0) { get_center(); }

	void get_center();
	void center(int filas, int columnas);
	void clear();
	void new_words(Player& player);
	void stats(int time, int wpm);
	void update(Player& player);
};
