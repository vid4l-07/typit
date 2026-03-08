#pragma once
#include <string>
#include <vector>
#include "../terms/term.h"

class Menu{
	protected:
	Terminal& term;

	public:
	std::string title;
	virtual bool handle_input(char c) = 0;
	virtual void render() = 0;
	virtual int get_value() = 0;
	void end();
	int start();

	Menu(std::string title_param, Terminal& term_param): title(title_param), 
	term(term_param){}
};
