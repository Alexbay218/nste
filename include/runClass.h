#pragma once
#include "../include/configReader.h"
#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/toolbar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/filebox.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <array>

class runClass {
public:
	runClass();
	int loaded; //0: not loaded, 1: load files, 2: load ntmp
	nana::paint::font* defaultFont;
	nana::form fm;
	nana::textbox ed;
	nana::menubar mb;
	nana::filebox fb;
	void onResize();
};