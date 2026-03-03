#include <string>
#include <vector>
#include "player.h"

void Player::type(char c, bool correct){
	std::string format_ch;
	std::string s(1,c);
	if (correct){
		format_ch = "\033[32m";
	} else{
		format_ch = "\033[31m";
		errors ++;
	}

	player_input.push_back(format_ch + s + "\033[0m");
	rest_str.erase(0,1);
}

void Player::backspace(int index){
	player_input.pop_back();
	rest_str.insert(rest_str.begin(), org_str[index]);
}

std::string Player::dump_input() const{
	std::string format;
	for (const auto& i : player_input){
		format += i;
	}
	return format;
}
