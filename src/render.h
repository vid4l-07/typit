#pragma once
#include <string>
#include "player.h"
#include "terms/term.h"

class Render{
	private:
	Terminal& term;
	int rows;
	int columns;
	int words_gen;

	public:
	int max_words;
	Render(Terminal& term_param): term(term_param),  words_gen(0) { term.get_center(rows, columns); }

	void center(int rows, int columns);
	void new_words(Player& player);
	void stats(int time, int wpm);
	void update(Player& player);
	void end(double time, int words, double wpm, double accuracy, int errors);
};
