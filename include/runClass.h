#pragma once
#include "../include/profileReader.h"
#include <nana/gui.hpp>
#include <nana/any.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/filebox.hpp>
#include <thread>
#include <chrono>   
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <array>

class runClass {
public:
	runClass();

	bool merged;
	bool running;
	int loaded; //0: not loaded, 1: load files, 2: load ntmp
	std::string targetFile;
	std::string lineNum;
	std::thread refresher; //ln refresher
	nana::paint::font* defaultFont;

	nana::form fm;
	nana::textbox ed;
	nana::label ln;
	nana::menubar mb;
	nana::filebox fb;

	void onResize();
	void lnRefresh();
	std::string loadFile(std::string filename);
	bool filesContentEqual(std::string f1, std::string f2);
};