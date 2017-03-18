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

class scriptReader {
public:
	struct script {
		std::string menuName;
		/*
		options:
		1st char: W or L (windows or linux)
		2nd char: R or A (relative or absolute path)
		3rd char: F or N (current file path or none)
		*/
		std::string options;
		std::string path;
	};
	std::vector<script> scriptList;
	scriptReader();

	void loadScript(std::string path);
	void runScript(std::string name, std::string currentPath, std::string currentFilePath);
};