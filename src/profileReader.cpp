#include "../include/profileReader.h"

profileReader::profileReader() {
}

bool profileReader::loadProfile(std::string currentPath, std::string extension) {
	std::string line = currentPath + "profile\\" + extension + ".ntheme";
	std::cout << "Opening " << extension << " profile: " << (currentPath + "profile\\" + extension + ".ntheme") << std::endl;
	std::fstream pfile(line, std::ios::in);
	if (pfile.is_open()) {
		while (std::getline(pfile,line)) {
			if (line.find(">") != std::string::npos && line.find("<") != std::string::npos) {
				loadProfile(currentPath, line.substr(line.find(">")+1, line.find("<")-line.find(">")));
			}
			if (line.find(":") != std::string::npos) {
				wordList.push_back(line.substr(0, line.find(":")));
				if (line.find(",") != std::string::npos) {
					colorList.push_back(colorFromHex(line.substr(line.find(":") + 1, line.find(",") - line.find(":")-1)));
					bColorList.push_back(colorFromHex(line.substr(line.find(",") + 1)));
				}
				else {
					colorList.push_back(colorFromHex(line.substr(line.find(":") + 1)));
					bColorList.push_back(nana::color(255,255,255));
				}
			}
		}
		return true;
	}
	return false;
}

nana::color profileReader::colorFromHex(std::string hex)  {
	hex = hex.substr(hex.find("#")+1);
	std::stringstream h;
	int r = 0;
	int g = 0;
	int b = 0;
	h << std::hex << hex.substr(0, 2);
	h >> r;
	h.clear();
	h << std::hex << hex.substr(2, 2);
	h >> g;
	h.clear();
	h << std::hex << hex.substr(4, 2);
	h >> b;
	h.clear();
	return nana::color(r,g,b);
}
