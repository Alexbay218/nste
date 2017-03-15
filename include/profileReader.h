#pragma once
#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/filesystem/filesystem.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

class profileReader {
public:
	std::vector<nana::color> colorList;
	std::vector<nana::color> bColorList;
	std::vector<std::string> wordList;
	
	bool hasProfile;
	profileReader();
	bool loadProfile(std::string currentPath, std::string extension);
	nana::color colorFromHex(std::string hex);
};

