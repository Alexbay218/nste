#pragma once
#include "../include/profileReader.h"
#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/toolbar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/filebox.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <array>

class runClass {
public:
	runClass();
	int loaded; //0: not loaded, 1: load files, 2: load ntmp
	std::string targetFile;
	bool merged;
	nana::paint::font* defaultFont;
	nana::form fm;
	nana::textbox ed;
	nana::menubar mb;
	nana::filebox fb;
	void onResize();
	std::string loadFile(std::string filename);
	bool filesContentEqual(std::string f1, std::string f2);
};