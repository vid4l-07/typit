#include <random>
#include <string>
#include <unistd.h>
#include "player.h"
#include "words_es.h" // all_words array
#include "words_en.h"

void Player::type(char c, bool correct){
	FormatedChar typedchar;
	typedchar.c = c;
	
	if (correct){
		typedchar.format = true;
	} else{
		typedchar.format = false;
		errors ++;
	}

	index ++;
	player_input.push_back(typedchar);
	rest_str.erase(0,1);

	if (consecutive_dels > 0){
		consecutive_dels --;
	}
}

void Player::backspace(){
	if (!player_input.empty() && consecutive_dels < 5){
		index --;
		player_input.pop_back();
		rest_str.insert(rest_str.begin(), org_str[index]);
		consecutive_dels ++;
	}
}

bool Player::key_pressed() {
    timeval tv; 
	tv.tv_sec = 0;
	tv.tv_usec = 5000;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
	int ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

    if (ret == -1)
		return false;
    return FD_ISSET(STDIN_FILENO, &fds);
}

void Player::gen_word(bool first){
	const std::array<std::string_view, 1000>* all_words = nullptr;
	if (len == "es") {
		all_words = &all_words_es;
	}else{
		all_words = &all_words_en;
	} 

    std::uniform_int_distribution<> dis(0, (*all_words).size() - 1);

    int indice_aleatorio = dis(gen);
	std::string word;

	if (first){
		word = (*all_words)[indice_aleatorio];
	} else{
		word = " " + std::string((*all_words)[indice_aleatorio]);
	}
	rest_str.append(word);
	org_str.append(word);
}

void Player::del_char(){
	player_input.erase(player_input.begin());
}
