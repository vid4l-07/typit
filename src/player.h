#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

struct FormatedChar{
	char c;
	bool format;
};

class Player{
	public:
	std::string org_str;
	std::string rest_str;
	std::vector<FormatedChar> player_input;
	int errors;

	Player(const std::string& str): org_str(str), rest_str(str), errors(0) {}

	void type(char c, bool correct);
	void backspace(int index);
};

#endif
