#include "menu_render.h"
#include <string>
#include <vector>

class Option{
	public:
	std::string str;
	bool selected;
	Option(std::string str_param): str(str_param), selected(false) {}
};

class MenuRenderOptions: public MenuRender{
	public:
	void draw(const std::vector<Option>& options);
	void render(const std::string& title, const std::vector<Option>& options); 

	MenuRenderOptions(Terminal& term_param, int rows_size, int cols_size): MenuRender(term_param, rows_size, cols_size) {}
};
