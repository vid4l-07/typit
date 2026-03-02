#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <chrono>
#include <vector>
#include <sys/ioctl.h>

struct Player{
	std::string org_str;
	std::string rest_str;
	std::vector<std::string> player_input;

	Player(const std::string& str): org_str(str), rest_str(str) {}
	void type(char c, bool correct){
		std::string format_ch;
		std::string s(1,c);
		if (correct){
			format_ch = "\033[32m";
		} else{
			format_ch = "\033[31m";
		}

		player_input.push_back(format_ch + s + "\033[0m");
		rest_str.erase(0,1);
	}

	void backspace(int index){
		player_input.pop_back();
		rest_str.insert(rest_str.begin(), org_str[index]);
	}

	std::string dump_imput(){
		std::string format;
		for (const auto i : player_input){
			format += i;
		}
		return format;
	}
};

struct Game{
	Player player;
	termios oldt;
	int filas;
	int columnas;

	Game(Player& player0, termios& org): player(player0), oldt(org) {}

	void enableRawMode() {
		termios newt;
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	}

	void disableRawMode() {
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}

	void clear(){
		std::cout << "\033[2J";
	}

	void obtenerCentro() {
		struct winsize w;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
		filas = w.ws_row / 2;
		columnas = w.ws_col / 2;
	}

	void centrar(int filas, int columnas){
		std::cout << "\033[" << filas << ";" << columnas << "H";
	}


	void update(){
		obtenerCentro();
		clear();
		centrar(filas, columnas);
		std::cout << player.rest_str; 
		centrar(filas, columnas - player.player_input.size());
		std::cout << player.dump_imput();
		centrar(filas, columnas);
	}
};


int main() {
    termios oldt;

	Player player("Escribe esto");

	Game game(player, oldt);

	game.enableRawMode();

	game.update();

    auto inicio = std::chrono::high_resolution_clock::now();

	int index = 0;

    while (index < game.player.org_str.size()) {
        char c = getchar();

		if (c < 32) continue;
		if (c == 127){
			if (index > 0){
				index --;
				game.player.backspace(index);
			}

		} else if (c == player.rest_str[index]){
			game.player.type(c, true);
			index ++;

		} else{
			game.player.type(c, false);
			index ++;
			
		}
		game.update();

        std::cout.flush();
    }

    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempo = fin - inicio;

    game.disableRawMode();

    std::cout << "\n\nTiempo: " << tiempo.count() << " segundos\n";

    return 0;
}
