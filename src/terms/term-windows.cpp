#include <windows.h>
#include <iostream>
#include <conio.h>
#include "term.h"

Terminal::Terminal() {
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// guardar modos actuales
	GetConsoleMode(hIn, &oldInMode);
	GetConsoleMode(hOut, &oldOutMode);

	// desactivar echo y line input (equivalente a ICANON | ECHO)
	DWORD newInMode = oldInMode;
	newInMode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
	newInMode |= ENABLE_PROCESSED_INPUT;

	SetConsoleMode(hIn, newInMode);

	// activar soporte ANSI
	DWORD newOutMode = oldOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, newOutMode);

	std::cout << "\033[?25l"; // hide cursor
}

Terminal::~Terminal() {
	SetConsoleMode(hIn, oldInMode);
	SetConsoleMode(hOut, oldOutMode);

	std::cout << "\033[?25h"; // show cursor
}

bool Terminal::key_pressed(){
	return _kbhit();
}

char Terminal::read_char(){
	return _getch();
}

void Terminal::clear(){
	std::cout << "\033[2J";
}

void Terminal::get_center(int& rows, int& columns){
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hOut, &csbi);

	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	rows = height / 2;
	columns = width / 2;
}
