#pragma once
#include <string>
#include <vector>
#include <random>

struct FormatedChar{
	char c;
	bool format;
};

class Player{
	private:
    std::mt19937 gen;
	public:
	std::string org_str;
	std::string rest_str;
	std::vector<FormatedChar> player_input;
	int words_typed;
	int errors;
	int index;
	int consecutive_dels;
	std::string len; // en english, es spanish

	Player(std::string lenguage): len(lenguage), gen(std::random_device{}()), errors(0), words_typed(0), index(0), consecutive_dels(0) {
		gen_word(true);
	}

	void type(char c, bool correct);
	void backspace();
	bool key_pressed();
	void count_words();
	void gen_word(bool first = false);
	void del_char();
};
