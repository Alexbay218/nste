#include "../include/profileReader.h"

profileReader::profileReader() {
	themeColorList.push_back(colorFromHex("#999999")); //fmbgcolor
	themeColorList.push_back(colorFromHex("#000000")); //fmfgcolor
	themeColorList.push_back(colorFromHex("#d9d9d9")); //mbbgcolor
	themeColorList.push_back(colorFromHex("#ffffff")); //mbfgcolor
	themeColorList.push_back(colorFromHex("#ffffff")); //edbgcolor
	themeColorList.push_back(colorFromHex("#000000")); //edfgcolor
	themeColorList.push_back(colorFromHex("#0000ff")); //lnfgcolor
	themeColorList.push_back(colorFromHex("#0099ff")); //edsbgcolor
	themeColorList.push_back(colorFromHex("#ffffff")); //edsfgcolor
}

void profileReader::loadTheme(nana::form* fm, nana::menubar* mb, nana::textbox* ed, nana::label* ln) {
	int i = themeColorList.size();
	while (i < 9) {
		themeColorList.push_back(colorFromHex("#000000"));
		i++;
	}
	fm->bgcolor(themeColorList[0]);
	fm->fgcolor(themeColorList[1]);
	mb->bgcolor(themeColorList[2]);
	mb->fgcolor(themeColorList[3]);
	ed->bgcolor(themeColorList[4]);
	ed->fgcolor(themeColorList[5]);
	ed->scheme().selection = themeColorList[7];
	ed->scheme().selection_text = themeColorList[8];
	ln->bgcolor(themeColorList[4]);
	ln->fgcolor(themeColorList[6]);
}

bool profileReader::loadProfile(std::string currentPath, std::string extension) {
	std::string line = currentPath + "profile\\" + extension + ".ntheme";
	std::cout << "Opening " << extension << " profile: " << (currentPath + "profile\\" + extension + ".ntheme") << std::endl;
	std::fstream pfile(line, std::ios::in);
	if (pfile.is_open()) {
		while (std::getline(pfile,line)) {
			if (line.find(">") != std::string::npos && line.find("<") != std::string::npos) {
				loadProfile(currentPath, line.substr(line.find(">")+1, line.find("<")-line.find(">")-1));
			}
			if (line.find(":") != std::string::npos) {
				wordList.push_back(line.substr(0, line.find(":")));
				if (line.find(",") != std::string::npos) {
					colorList.push_back(colorFromHex(line.substr(line.find(":") + 1, line.find(",") - line.find(":")-1)));
					bColorList.push_back(colorFromHex(line.substr(line.find(",") + 1)));
				}
				else {
					colorList.push_back(colorFromHex(line.substr(line.find(":") + 1)));
					bColorList.push_back(themeColorList[4]);
				}
			}
		}
		return true;
	}
	return false;
}

bool profileReader::loadProfile(std::string currentPath) {
	std::string line = currentPath;
	std::cout << "Opening theme profile: " << currentPath << std::endl;
	std::fstream pfile(line, std::ios::in);
	std::vector<nana::color> temp;
	if (pfile.is_open()) {
		int i = 0;
		while (std::getline(pfile, line)) {
			if (line.find(":") != std::string::npos) {
				temp.push_back(colorFromHex(line.substr(line.find(":") + 1)));
			}
		}
		themeColorList = temp;
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