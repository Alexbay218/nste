#pragma once
#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/filebox.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class profileReader {
public:
	std::vector<nana::color> colorList;
	std::vector<nana::color> bColorList;
	std::vector<nana::color> themeColorList;
	std::vector<std::string> wordList;
	
	//bool hasProfile;
	profileReader();

	bool loadProfile(std::string currentPath, std::string extension);
	bool loadProfile(std::string currentPath);
	void loadTheme(nana::form* fm, nana::menubar* mb, nana::textbox* ed);
	nana::color colorFromHex(std::string hex);
};