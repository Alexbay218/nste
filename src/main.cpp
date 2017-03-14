#include "../include/runClass.h"
#include <iostream>

int main(int argc, char *argv[]) {
	runClass mainRun;

	std::cout << "Arguments: " << argc << std::endl;
	int ac = argc;
	std::string path = argv[0];
	path = path.substr(0, path.find("nste.exe"));
	std::cout << "Path: " << path << std::endl;
	std::string targetFile;
	if (argc > 1) {
		targetFile = argv[1];
		if (targetFile.find(".ntmp") != std::string::npos) {
			targetFile = targetFile.substr(0, targetFile.find(".ntmp"));
		}
		mainRun.fm.caption("NSTE - " + targetFile);
		std::cout << "Loading: " << targetFile << std::endl;
		std::fstream ntmpCheck(targetFile + ".ntmp");
		if (ntmpCheck.is_open()) {
			mainRun.loaded = 2;
			mainRun.ed.load(targetFile + ".ntmp");
		}
		else {
			mainRun.loaded = 1;
			mainRun.ed.load(targetFile);
		}
	}
	mainRun.onResize(); 
	mainRun.mb.at(0).append("Open", [&](nana::menu::item_proxy &) {
		if (mainRun.loaded > 0) {
			if (mainRun.fb()) {
				std::string c = path + "nste.exe " + mainRun.fb.file();
				system(c.c_str());
			}
		}
		else {
			if (mainRun.fb()) {
				targetFile = mainRun.fb.file();
				if (targetFile.find(".ntmp") != std::string::npos) {
					targetFile = targetFile.substr(0, targetFile.find(".ntmp"));
				}
				mainRun.fm.caption("NSTE - " + targetFile);
				std::cout << "Loading: " << targetFile << std::endl;
				std::fstream ntmpCheck(targetFile + ".ntmp");
				if (ntmpCheck.is_open()) {
					mainRun.loaded = 2;
					mainRun.ed.load(targetFile + ".ntmp");
				}
				else {
					mainRun.loaded = 1;
					mainRun.ed.load(targetFile);
				}
			}
		}
	});
	mainRun.mb.at(0).append("Create", [&](nana::menu::item_proxy &) {
		if (mainRun.fb()) {
			mainRun.ed.store(mainRun.fb.file());
		}
	});
	mainRun.mb.at(0).append("Merge", [&](nana::menu::item_proxy &) {
		if (mainRun.loaded > 0) {
			mainRun.ed.store(targetFile);
		}
	});
	mainRun.fm.show();
	mainRun.fm.events().resizing([&] {mainRun.onResize(); });
	mainRun.fm.events().resized([&] {mainRun.onResize(); });
	mainRun.ed.events().key_press([&] {
		if (mainRun.loaded > 0) {
			std::cout << "Saving" << std::endl;
			mainRun.ed.store(targetFile + ".ntmp"); 
		}
	});
	nana::exec();
}

runClass::runClass() : ed(fm), mb(fm), fb(true) {
	defaultFont = new nana::paint::font("Consolas", 10, false, false, false, false);
	fm.typeface(*defaultFont);
	fm.caption("NSTE");
	fm.size(nana::size(600, 400));
	
	ed.multi_lines(true);
	ed.typeface(*defaultFont);

	mb.typeface(*defaultFont);
	mb.push_back("File");

	loaded = 0;
}

void runClass::onResize() {
	ed.move(nana::point(5, 30));
	ed.size(nana::size(fm.size().width - 10, fm.size().height - 35));
}