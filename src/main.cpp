#include <termios.h>
#include "player.h"
#include "game.h"
#include "render.h"

int main(){
    termios oldt;
	Player player;
	Render render(oldt);
	
	char mode;
	std::cout << "Modo: ";
	std::cin >> mode;

	Game game(player, render, mode);

	game.start();
    game.end();

    return 0;
}
