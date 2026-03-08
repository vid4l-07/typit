#include <iostream>
#include <vector>
#include <string>
#include "menu_render_options.h"

void MenuRenderOptions::draw(const std::vector<Option>& options){
	int padding_top = rows * 0.2;
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
	int options_start_row = title_line + padding_top;
	int space = (col_size - (padding_col * 2)) / (number_options + 1);

	options_start_col += padding_col;
	move_cursor(options_start_row, options_start_col);

	for (int i = 0; i < options.size(); i++){
		if (i >= 4){
			options_start_row += 5;
			options_start_col = start_col + padding_col;
		}
		options_start_col += space;

		move_cursor(options_start_row, options_start_col - (options[i].str.size() / 2));

		if (options[i].selected){
			std::cout << "\033[7m" << options[i].str << "\033[0m";
		} else {
			std::cout << options[i].str;
		}
	}
}

void MenuRenderOptions::render(const std::string& title, const std::vector<Option>& options){
	draw_border();
	draw_title(title);
	draw(options);
}

