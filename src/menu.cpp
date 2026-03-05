#include <string>
#include <vector>
#include "term.h"

class Option{
	public:
	std::string str;
	bool selected;
	Option(std::string str_param): str(str_param), selected(false) {}
};

class Menu_render {
	private:
	Terminal& term;
	int rows;
	int columns;
	int title_row;
	int title_line;
	int row_size;
	int col_size;
	std::string border;
	void gen_border();
	void draw_border();
	void draw_title(const std::string& title);
	void draw_options(const std::vector<Option>& options);
	void center(int rows, int columns);

	public:
	int start_col;
	int start_row;
	int end_col;
	int end_row;
	void clear();
	void render(const std::string& title, const std::vector<Option>& options);
	Menu_render(Terminal& term_param): term(term_param){
		term.get_center(rows, columns);
		start_col = columns - columns / 2;
		start_row = rows - rows / 2;
		end_col = columns + columns / 2;
		end_row = rows + rows / 2;
		row_size = end_row - start_row;
		col_size = end_col - start_col;
		title_row = start_row + 2;
		title_line = title_row + 2;
		gen_border();
	}
};

void Menu_render::center(int rows, int columns){
	std::cout << "\033[" << rows << ";" << columns << "H";
}

void Menu_render::clear(){
	std::cout << "\033[2J";
	std::cout << "\033[?25l"; // hide cursor
}

void Menu_render::draw_options(const std::vector<Option>& options){
	int padding_top = 8;
	int padding_col = 5;
	int padding_row = 5;

	int number_options = options.size();

	if (number_options > 8){
		return;
	}else if (number_options > 4){
		number_options = 4;
		padding_top = (row_size) / 3;
	}

	int options_start_col = start_col;
	int options_start_row = title_row + padding_top;
	int space = (col_size - (padding_col * 2)) / (number_options + 1);

	options_start_col += padding_col;
	center(options_start_row, options_start_col);

	int index = 0;
	for (int i = 0; i < options.size(); i++){
		if (index >= 4){
			options_start_row += 5;
			options_start_col = start_col + padding_col;
		}
		options_start_col += space;

		center(options_start_row, options_start_col - (options.at(index).str.size() / 2));

		if (options.at(index).selected){
			std::cout << "\033[7m" << options.at(index).str << "\033[0m";
		} else {
			std::cout << options.at(index).str;
		}
		index ++;
	}
}

void Menu_render::draw_title(const std::string& title){
	int center_col = columns - (title.size() / 2);
	center(title_row, center_col);
	std::cout << title;
	center(title_line, start_col + 2);
	for (int i = start_col; i < end_col - 2; i++){
		std::cout << "─";
	}
	std::cout << "\n";
}

void Menu_render::draw_border(){
	center(start_row, 0);
	std::cout << border;
}

void Menu_render::gen_border(){
	std::string horizontal = "─";
	std::string vertical = "│";
	std::string top_right = "┐";
	std::string top_left = "┌";
	std::string bottom_left = "└";
	std::string bottom_right = "┘\n";

	center(start_row, 0);
	for (int i = start_row; i < end_row; i++ ){
		for (int j = 0; j < end_col; j++ ){
			if (i == start_row && j == start_col)
				border += top_left;

			else if (i == start_row && j == end_col - 1)
				border += top_right;

			else if (i == end_row - 1 && j == start_col)
				border += bottom_left;

			else if (i == end_row - 1 && j == end_col - 1)
				border += bottom_right;

			else if ((i == start_row || i == end_row - 1) && j > start_col)
				border += horizontal;

			else if (j == start_col || j == end_col - 1)
				border += vertical;

			else
				border += " ";
		}
		border += "\n";
	}
}

void Menu_render::render(const std::string& title, const std::vector<Option>& options){
	clear();
	draw_border();
	draw_title(title);
	draw_options(options);
}

class Menu{
	private:
	void select(bool direction);
	int current_selection;
	Terminal& term;
	Menu_render menu_render;

	public:
	std::string title;
	std::vector<Option> options;
	bool handle_input(char c);
	int start();
	void end();

	Menu(std::string& title_param, std::vector<std::string>& options_param, Terminal& term_param): title(title_param), 
	term(term_param), menu_render(Menu_render(term)), current_selection(0){

		for (const std::string& i:options_param){
			Option o(i);
			options.push_back(o);
		}
		options.at(0).selected = true;
	}
};

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
	std::cout << "\033[?25h"; // show cursor
}
