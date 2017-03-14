#pragma once
#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/filesystem/filesystem.hpp>
#include <string>

class configReader {
public:
	configReader(std::string configFile);
	void loadProfile(std::string profileFile);
};

