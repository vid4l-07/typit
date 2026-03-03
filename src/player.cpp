#include <string>
#include <vector>
#include "player.h"

void Player::type(char c, bool correct){
	FormatedChar typedchar;
	typedchar.c = c;
	
	if (correct){
		typedchar.format = true;
	} else{
		typedchar.format = false;
		errors ++;
	}

	player_input.push_back(typedchar);
	rest_str.erase(0,1);
}

void Player::backspace(int index){
	player_input.pop_back();
	rest_str.insert(rest_str.begin(), org_str[index]);
}
