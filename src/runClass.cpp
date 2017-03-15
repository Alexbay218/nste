#include "../include/runClass.h"

runClass::runClass() : ed(fm), mb(fm), fb(true) {
	defaultFont = new nana::paint::font("Consolas", 10, false, false, false, false);
	fm.typeface(*defaultFont);
	fm.caption("NSTE");
	fm.size(nana::size(600, 400));
	
	ed.multi_lines(true);
	ed.typeface(*defaultFont);
	ed.focus_behavior(nana::textbox::text_focus_behavior::none);
	ed.enable_caret();

	mb.typeface(*defaultFont);
	mb.push_back("File");
	mb.push_back("View");

	loaded = 0;
}

void runClass::onResize() {
	ed.move(nana::point(5, 30));
	ed.size(nana::size(fm.size().width - 10, fm.size().height - 35));
}

std::string runClass::loadFile(std::string filename) {
	targetFile = filename;
	if (targetFile.find(".ntmp") != std::string::npos) {
		targetFile = targetFile.substr(0, targetFile.find(".ntmp"));
	}
	std::cout << "Loading: " << targetFile << std::endl;
	std::fstream ntmpCheck(targetFile + ".ntmp");
	if (ntmpCheck.is_open()) {
		loaded = 2;
		ed.load(targetFile + ".ntmp");
		merged = filesContentEqual(targetFile, targetFile + ".ntmp");
		if (merged) {
			fm.caption("NSTE - " + targetFile);
		}
		else {
			fm.caption("NSTE - " + targetFile + " (Unmerged)");
		}
	}
	else {
		loaded = 1;
		ed.load(targetFile);
		merged = false;
		fm.caption("NSTE - " + targetFile + " (Unmerged)");
	}
	return targetFile;
}

bool runClass::filesContentEqual(std::string f1, std::string f2) {
	std::cout << "Comparing: " << f1 << " and " << f2 << std::endl;
	std::fstream fs1(f1, std::ios::in);
	std::fstream fs2(f2, std::ios::in);
	std::string currentLine1;
	std::string currentLine2;
	while (std::getline(fs1, currentLine1)) {
		std::getline(fs2, currentLine2);
		if (currentLine1 != currentLine2) {
			std::cout << "1: " << currentLine1 << " != " << currentLine2 << std::endl;
			return false;
		}
	}
	fs1.close();
	fs2.close();
	fs1.open(f1, std::ios::in);
	fs2.open(f2, std::ios::in);
	while(std::getline(fs2, currentLine2)) {
		std::getline(fs1, currentLine1);
		if (currentLine1 != currentLine2) {
			std::cout << "2: " << currentLine1 << " != " << currentLine2 << std::endl;
			return false;
		}
	}
	return true;
}