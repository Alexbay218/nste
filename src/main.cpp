#if defined(_WIN32) || defined(WIN32) || defined(__MINGW32__) || defined(__BORLANDC__)
#define OS_WIN
#endif

#include "../include/runClass.h"
#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/toolbar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/filebox.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <array>

int main(int argc, char *argv[]) {
	runClass mainRun;
	profileReader mainProfile;

	std::cout << "Arguments: " << argc << std::endl;
	int ac = argc;
	std::string path = argv[0];
	path = path.substr(0, path.find("nste.exe"));
	std::cout << "Path: " << path << std::endl;
	std::string currentFile;
	if (argc > 1) {
		currentFile = mainRun.loadFile(argv[1]);
	}
	mainRun.onResize(); 
	mainRun.mb.at(0).append("Open", [&](nana::menu::item_proxy &) {
		if (mainRun.loaded > 0) {
			if (mainRun.fb()) {
				std::string c = argv[0];
#ifdef OS_WIN
				c = "start " + c + " " + mainRun.fb.file();
#else
				c = c + " " + mainRun.fb.file() + " &";
#endif
				std::cout << "Running: " << c;
				system(c.c_str());
			}
		}
		else {
			if (mainRun.fb()) {
				currentFile = mainRun.loadFile(mainRun.fb.file());
				if (currentFile.find(".") != std::string::npos) {
					mainProfile.loadProfile(path, currentFile.substr(currentFile.find_last_of(".") + 1));
					for (int i = 0; i < mainProfile.wordList.size(); i++) {
						std::cout << "Highlight for: " << mainProfile.wordList[i] << std::endl;
						mainRun.ed.set_highlight(mainProfile.wordList[i], mainProfile.colorList[i], mainProfile.bColorList[i]);
						mainRun.ed.set_keywords(mainProfile.wordList[i], false, true, { mainProfile.wordList[i] });
					}
				}
				else {
					std::cout << "Profile was not loaded! " << std::endl;
				}
			}
		}
	});
	mainRun.mb.at(0).append("Create", [&](nana::menu::item_proxy &) {
		if (mainRun.fb()) {
			mainRun.ed.store(mainRun.fb.file());
			currentFile = mainRun.loadFile(mainRun.fb.file());
			if (currentFile.find(".") != std::string::npos) {
				mainProfile.loadProfile(path, currentFile.substr(currentFile.find_last_of(".") + 1));
				for (int i = 0; i < mainProfile.wordList.size(); i++) {
					std::cout << "Highlight for: " << mainProfile.wordList[i] << std::endl;
					mainRun.ed.set_highlight(mainProfile.wordList[i], mainProfile.colorList[i], mainProfile.bColorList[i]);
					mainRun.ed.set_keywords(mainProfile.wordList[i], false, true, { mainProfile.wordList[i] });
				}
			}
			else {
				std::cout << "Profile was not loaded! " << std::endl;
			}
		}
	});
	mainRun.mb.at(0).append("Merge", [&](nana::menu::item_proxy &) {
		if (mainRun.loaded > 0) {
			mainRun.ed.store(currentFile);
			mainRun.merged = true;
			if (mainRun.merged) {
				mainRun.fm.caption("NSTE - " + currentFile);
			}
			else {
				mainRun.fm.caption("NSTE - " + currentFile + " (Unmerged)");
			}
		}
		else {
			nana::msgbox mb(mainRun.fm, "Cannot Merge!");
			mb.icon(nana::msgbox::icon_error) << "Please create file first!";
			mb.show();
		}
	});
	mainRun.mb.at(0).append("Revert", [&](nana::menu::item_proxy &) {
		mainRun.ed.load(currentFile);
		mainRun.ed.store(currentFile+".ntmp");
		currentFile = mainRun.loadFile(currentFile);
		if (currentFile.find(".") != std::string::npos) {
			mainProfile.loadProfile(path, currentFile.substr(currentFile.find_last_of(".") + 1));
			for (int i = 0; i < mainProfile.wordList.size(); i++) {
				std::cout << "Highlight for: " << mainProfile.wordList[i] << std::endl;
				mainRun.ed.set_highlight(mainProfile.wordList[i], mainProfile.colorList[i], mainProfile.bColorList[i]);
				mainRun.ed.set_keywords(mainProfile.wordList[i], false, true, { mainProfile.wordList[i] });
			}
		}
	});
	mainRun.ed.events().key_release([&] {
		if (mainRun.loaded > 0) {
			std::cout << "Saving" << std::endl;
			mainRun.ed.store(currentFile + ".ntmp");
			mainRun.merged = false;
			if (mainRun.merged) {
				mainRun.fm.caption("NSTE - " + currentFile);
			}
			else {
				mainRun.fm.caption("NSTE - " + currentFile + " (Unmerged)");
			}
		}
	});
	//Profile Reading
	if (currentFile.find(".") != std::string::npos) {
		mainProfile.loadProfile(path, currentFile.substr(currentFile.find_last_of(".")+1));
		for (int i = 0; i < mainProfile.wordList.size(); i++) {
			std::cout << "Highlight for: " << mainProfile.wordList[i] << std::endl;
			mainRun.ed.set_highlight(mainProfile.wordList[i], mainProfile.colorList[i], mainProfile.bColorList[i]);
			mainRun.ed.set_keywords(mainProfile.wordList[i], false, true, { mainProfile.wordList[i] });
		}
	}
	else {
		std::cout << "Profile was not loaded! " << std::endl;
	}
	mainRun.fm.events().resizing([&] {mainRun.onResize(); });
	mainRun.fm.events().resized([&] {mainRun.onResize(); });
	mainRun.fm.events().unload([&](const nana::arg_unload& arg) {
		if (!mainRun.merged) {
			nana::msgbox emb(mainRun.fm, "Unmerged Changes", nana::msgbox::yes_no_cancel);
			emb.icon(nana::msgbox::icon_warning) << "Do you want to merge changes?\n";
			nana::msgbox::pick_t r = emb.show();
			if (r == nana::msgbox::pick_yes) {
				mainRun.ed.store(currentFile);
			}
			else if (r == nana::msgbox::pick_cancel) {
				arg.cancel = true;
			}
			else {
				arg.cancel = false;
			}
		}
	});
	mainRun.fm.show();
	mainRun.ed.focus();
	nana::exec();
}