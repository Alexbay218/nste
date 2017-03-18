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

class compareHighlight {
public:
	compareHighlight();
	std::fstream file1; //being compare from
	std::fstream file2; //being compared to (highlighting is happening on here)
	nana::textbox display;

	std::vector<int> lines;
	nana::textbox* highlight(std::string l1,std::string l2);
};