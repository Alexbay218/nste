#pragma once
#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/menu.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/filebox.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>

class compareHighlight {
public:
	compareHighlight();
	std::fstream file1; //being compare from
	std::fstream file2; //being compared to (highlighting is happening on here)

	std::vector<int> lines;
	void highlight(nana::textbox* display, std::string l1,std::string l2);
};