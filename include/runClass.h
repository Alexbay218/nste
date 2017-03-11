#pragma once
#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/toolbar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/filesystem/filesystem.hpp>
#include <string>
#include <vector>

class runClass {
public:
	runClass();
	nana::paint::font* defaultFont;
	nana::form fm;
	nana::textbox ed;
	void onResize();
};