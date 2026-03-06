#pragma once
#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#endif

enum Key{
	KEY_UP = 65,
	KEY_DOWN = 66,
	KEY_RIGHT = 67,
    KEY_LEFT = 68,
    KEY_BACKSPACE = 127,
};

class Terminal { 
	private:

#ifdef _WIN32
	void* hIn;
	void* hOut;
	unsigned long oldInMode;
	unsigned long oldOutMode;
#else
	termios oldt;
#endif
	public:

	Terminal();

	~Terminal();

	bool key_pressed();

	char read_char();

	void clear();

	void get_center(int& rows, int& columns);
};
