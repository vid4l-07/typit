#include "menu.h"
#include "render/menu_render_options.h"
#include <string>

class OptionMenu: public Menu{
	private:
	std::vector<Option> options;
	int current_selection;
	void select(bool direction);
	MenuRenderOptions menu_render;

	public:
	bool handle_input(char c) override;
	void render() override;
	int get_value() override;


	OptionMenu(Terminal& term_param, std::string title, std::vector<std::string>& options_param, int rows_size = 0, int cols_size = 0):
		Menu(title, term_param), menu_render(term_param, rows_size, cols_size){

		if (options_param.size() > 0){
			current_selection = 0;
			for (const std::string& i:options_param){
				Option o(i);
				options.push_back(o);
			}
			options.at(0).selected = true;
		}

	}
};
