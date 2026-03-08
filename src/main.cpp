#include <string>
#include <vector>
#include "player.h"
#include "game.h"
#include "render.h"
#include "terms/term.h"
#include "menu/option_menu.h"
#include "menu/number_menu.h"

int main(){
	Terminal term;

	std::vector<std::string> lang = {"en", "es"};
	OptionMenu menu_lang(term, "Language", lang);

	int lang_selct = menu_lang.start();
	std::string lang_str;
	if (lang_selct == 0){
		lang_str = "en";
	} else {
		lang_str = "es";
	}

	std::vector<std::string> mode = {"time", "words"};
	OptionMenu menu_mode(term, "Mode", mode);
	int mode_select = menu_mode.start();
	char mode_str;
	
	int max;
	if (mode_select == 0){
		mode_str = 't';
		NumberMenu menu_max(term, "time", 5, 60);
		max = menu_max.start();
	} else {
		mode_str = 'w';
		NumberMenu menu_max(term, "Words", 5, 60);
		max = menu_max.start();
	}
	

	Player player(lang_str);
	Render render(term);

	Game game(player, render, term, mode_str, max);


	game.start();
	game.end();


    return 0;
}
