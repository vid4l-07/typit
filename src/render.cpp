#include <iostream>
#include <string>
#include "render.h"

void Render::center(int rows, int columns){
	std::cout << "\033[" << rows << ";" << columns << "H";
}

void Render::new_words(Player& player){
	while (player.rest_str.size() < columns - 10 && words_gen < max_words){
		player.gen_word();
		words_gen ++;
	}
	if (player.player_input.size() >= columns - 5){
		player.del_char();
	}
}

void Render::stats(int time, int wpm){
	center(rows - rows / 2, columns - columns / 3);
	std::cout << time;
	center(rows - rows / 2, columns + columns / 3);
	std::cout << "wpm: " << wpm;
}

void Render::update(Player& player){
	center(rows, columns);
	new_words(player);
	std::string copy_str = player.rest_str;

	if (!player.rest_str.empty()) {
		std::cout << "\033[7m" << player.rest_str.front() << "\033[0m" << player.rest_str.substr(1);
	}
	center(rows, columns - player.player_input.size());
	
	std::string format_str;
	for (const auto& i:player.player_input){
		std::string s(1,i.c);

		if (i.format){
			format_str += "\033[32m" + s + "\033[0m";
		} else{
			format_str += "\033[31m" + s + "\033[0m";
		}
	}
	std::cout << format_str;
	center(rows, columns + player.rest_str.size());
	std::cout << "\033[K";  // clear right of the words
	center(rows, columns - player.player_input.size() - 1);
	std::cout << "\033[1K";  // clear left of the words
	center(rows, columns);
}

void Render::end(double time, int words, double wpm, double accuracy, int errors){
	std::string result;
	center(rows, columns - 9);
	std::cout << "Time: " << time << " s\n";
	center(rows + 1, columns -9);
	std::cout << "Words: " << words << "\n";
	center(rows + 2, columns -9);
	std::cout << "WPM: " << wpm << " \n";
	center(rows + 3, columns -9);
	std::cout << "Accuracy: " << accuracy << " %\n";
	center(rows + 4, columns -9);
	std::cout << "Errors: " << errors << " errores\n";
}
