#if defined(_WIN32) || defined(WIN32) || defined(__MINGW32__) || defined(__BORLANDC__)
#define OS_WIN
#endif

#include "../include/scriptReader.h"

scriptReader::scriptReader() {
}

void scriptReader::loadScript(std::string path) {
	scriptList.clear();
	std::string line = path + "list.nScript";
	std::cout << "Opening script list from: " << line << std::endl;
	std::fstream sfile(line, std::ios::in);
	if (sfile.is_open()) {
		while (std::getline(sfile, line)) {
			script temp;
			temp.menuName = line.substr(0, line.find_first_of(":"));
			temp.options = line.substr(line.find_first_of(":") + 1, line.find_last_of(":") - line.find_first_of(":") - 1);
			temp.path = line.substr(line.find_last_of(":") + 1);
			scriptList.push_back(temp);
		}
	}
	else {
		std::cout << "Error opening script list at: " << line << std::endl;
	}
}

void scriptReader::runScript(std::string name, std::string currentPath, std::string currentFilePath) {
	bool isWindows = true;
#ifdef OS_WIN
	isWindows = true;
#else
	isWindows =  false;
#endif
	unsigned int i = 0;
	while (i < scriptList.size()) {
		if (scriptList[i].menuName.compare(name) == 0) {
			std::string c = scriptList[i].path;
			if (scriptList[i].options.at(1) == 'R') {
				c = currentPath + c;
			}
			if (scriptList[i].options.at(2) == 'F') {
				c = c + " " + currentFilePath;
			}
			if (scriptList[i].options.at(0) == 'W') {
				c = "start " + c;
			}
			else {
				c = c + " &";
			}
			if ((scriptList[i].options.at(0) == 'W') == isWindows) {
				std::cout << "Running: " << c << std::endl;
				system(c.c_str());
			}
		}
		i++;
	}
}