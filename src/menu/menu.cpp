#include "menu.h"

int Menu::start(){
	term.clear();
	bool runing = true;
	render();

	while (runing){
		char c = term.read_char();
		runing = handle_input(c);
		render();
	}

	end();
	return get_value();
}

void Menu::end(){
	term.clear();
}
