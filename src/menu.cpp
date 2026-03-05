#include "menu.h"

void Menu::select(bool direction){
	if (direction){
		if (current_selection < options.size() - 1){
			options.at(current_selection).selected = false;
			current_selection ++;
			options.at(current_selection).selected = true;
		}
	} else {
		if (current_selection > 0){
			options.at(current_selection).selected = false;
			current_selection --;
			options.at(current_selection).selected = true;
		}
	}
}

bool Menu::handle_input(char c){
	if (c == '\n'){
		return false;
	}
	if (c == 27) {
		term.read_char();
		char dir = term.read_char();

		if (dir == KEY_RIGHT) {
			select(true);
		} 
		else if (dir == KEY_LEFT) {
			select(false);
		}
	}
	return true;
}


int Menu::start(){
	bool runing = true;
	menu_render.render(title, options);
	while (runing){
		char c = term.read_char();
		runing = handle_input(c);
		menu_render.render(title, options);
	}
	end();
	return current_selection;
}

void Menu::end(){
	menu_render.clear();
}
