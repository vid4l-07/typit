#pragma once
#ifdef _WIN32
#include <windows.h>
enum Key{
	KEY_MIN = 0,
	KEY_UP = 72,
	KEY_DOWN = 80,
	KEY_RIGHT = 77,
	KEY_LEFT = 75,
	KEY_BACKSPACE = 8,
	ENTER = 13
};
#else
#include <termios.h>
enum Key{
	KEY_MIN = 32,
	KEY_UP = 65,
	KEY_DOWN = 66,
	KEY_RIGHT = 67,
	KEY_LEFT = 68,
	KEY_BACKSPACE = 127,
	ENTER = 10
};
#endif
#undef min
#undef max


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
