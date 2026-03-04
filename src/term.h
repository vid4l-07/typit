#pragma once
#include <termios.h>
#include <unistd.h>
#include <iostream>

class Terminal {
	termios oldt;
	public:
	Terminal() {
		termios newt;
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		std::cout << "\033[?25l"; // hide cursor
	}

	~Terminal() {
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		std::cout << "\033[?25h"; // show cursor
	}
};
