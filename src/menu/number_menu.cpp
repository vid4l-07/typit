#include "number_menu.h"

bool NumberMenu::handle_input(char c) {
	if (c == ENTER){
		return false;
	}
	if (c == KEY_UP){
		if (value < max_value)
			value++;
	}
	else if (c == KEY_DOWN){
		if (value > min_value)
			value--;
	}
	return true;
}

int NumberMenu::get_value() {
	return value;
}

void NumberMenu::render(){
	menu_render.render(title, value);
}
