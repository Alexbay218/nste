#include "../include/runClass.h"

runClass::runClass() : ed(fm), ln(fm), mb(fm), fb(true), refresher() {
	defaultFont = new nana::paint::font("Consolas", 10, false, false, false, false);
	fm.typeface(*defaultFont);
	fm.caption("NSTE");
	fm.size(nana::size(600, 400));
	
	ed.multi_lines(true);
	ed.typeface(*defaultFont);
	ed.focus_behavior(nana::textbox::text_focus_behavior::none);
	ed.borderless(true);
	ed.scheme().activated = nana::color(0, 0, 0, 0);
	ed.enable_caret();

	ln.typeface(*defaultFont);
	ln.borderless(true);
	ln.text_align(nana::align::right);
	ln.scheme().activated = nana::color(0, 0, 0, 0);

	mb.typeface(*defaultFont);
	mb.push_back("File");
	mb.push_back("View");
	mb.push_back("Scripts");
	loaded = 0;
	running = true;

	refresher = std::thread([&] {
		while (running) {
			lnRefresh();
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	});
	refresher.detach();
}

void runClass::onResize() {
	ln.move(nana::point(3, 30));
	ed.move(nana::point(35, 30));
	ln.size(nana::size(30, fm.size().height - 35));
	ed.size(nana::size(fm.size().width - 40, fm.size().height - 35));
	lnRefresh();
}

void runClass::lnRefresh() {
	lineNum.clear();
	int i = ed.text_position()[0].y;
	while (i <= ed.text_position().back().y) {
		lineNum += std::to_string(i+1) + "\n";
		i++;
	}
	ln.caption(lineNum);
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
		merged = true;
		fm.caption("NSTE - " + targetFile);
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