#if defined(_WIN32) || defined(WIN32) || defined(__MINGW32__) || defined(__BORLANDC__)
#define OS_WIN
#endif

#include "../include/runClass.h"
#include "../include/scriptReader.h"
#include "../include/compareHighlight.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <array>

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/textbox.hpp>

int main(int argc, char *argv[]) {
	runClass mainRun;
	profileReader mainProfile;
	scriptReader mainScript;
	compareHighlight mainPreview;

	std::cout << "Arguments: " << argc << std::endl;
	std::string path = argv[0];
	path = path.substr(0, path.find_last_of("nste"));
	std::cout << "Path: " << path << std::endl;
	std::string currentFile;
	if (argc > 1) {
		currentFile = mainRun.loadFile(argv[1]);
	}
	std::string currentThemeFilePath = path + "profile\\default.ntheme";

	mainRun.onResize();
	auto profileRead = [&](std::string themeFilePath) {
		std::cout << "Opening profile for " << currentFile << std::endl;
		if (currentFile.find(".") != std::string::npos) {
			mainProfile.loadProfile(path, currentFile.substr(currentFile.find_last_of(".") + 1));
			for (unsigned int i = 0; i < mainProfile.wordList.size(); i++) {
				std::cout << "Highlight for: " << mainProfile.wordList[i] << std::endl;
				mainRun.ed.set_highlight(mainProfile.wordList[i], mainProfile.colorList[i], mainProfile.bColorList[i]);
				mainRun.ed.set_keywords(mainProfile.wordList[i], false, true, { mainProfile.wordList[i] });
			}
		}
		else {
			std::cout << "No profiles for  " << currentFile << std::endl;
		}
		mainProfile.loadProfile(themeFilePath);
		mainProfile.loadTheme(&mainRun.fm, &mainRun.mb, &mainRun.ed, &mainRun.ln);
	};
	auto loadScriptMenu = [&] {
		mainRun.mb.at(2).clear();
		mainScript.loadScript(path + "script\\");
		unsigned int i = 0;
		while (i < mainScript.scriptList.size()) {
			auto temp = [&](nana::menu::item_proxy& ip) {
				int index = ip.index();
				std::cout << "Running Script" << std::endl;
				mainScript.runScript(mainScript.scriptList[index].menuName, path + "script\\", currentFile);
			};
			mainRun.mb.at(2).append(mainScript.scriptList[i].menuName, temp);
			i++;
		}
	};
	auto refresh = [&] {
		if (mainRun.loaded > 0) {
			mainRun.ed.store(currentFile + ".ntmp");
		}
		else {
			mainRun.ed.load(currentFile);
		}
		loadScriptMenu();
		profileRead(currentThemeFilePath);
		mainRun.ed.enable_caret();
		mainRun.fm.activate();
		mainRun.ed.focus();
		mainRun.mb.focus();
		mainRun.ed.focus();
	};
	auto open = [&] {
		mainRun.fb.init_path(path);
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
				refresh();
			}
		}
	};
	auto openTheme = [&] {
		mainRun.fb.init_path(path);
		if (mainRun.fb()) {
			currentThemeFilePath = mainRun.fb.file();
			refresh();
		}
	};
	auto create = [&] {
		mainRun.fb.init_path(path);
		if (mainRun.fb()) {
			mainRun.ed.store(mainRun.fb.file());
			currentFile = mainRun.loadFile(mainRun.fb.file());
			refresh();
		}
	};
	auto merge = [&]() {
		if (mainRun.loaded > 0) {
			mainRun.ed.store(currentFile);
			mainRun.merged = true;
			mainRun.ed.edited_reset();
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
	};
	auto revert = [&] {
		mainRun.ed.load(currentFile);
		mainRun.ed.store(currentFile + ".ntmp");
		currentFile = mainRun.loadFile(currentFile);
		refresh();
	};
	auto preview = [&] {
		if (mainRun.loaded > 0) {
			std::cout << "Previewing " << currentFile << std::endl;
			nana::form pv(mainRun.fm, nana::size(600, 300), nana::appearance());

			pv.caption(currentFile);
			nana::textbox pvtb(pv);
			pvtb.editable(false);
			pvtb.focus_behavior(nana::textbox::text_focus_behavior::none);
			pvtb.typeface(*mainRun.defaultFont);
			pvtb.load(currentFile);
			pvtb.move(nana::point(5, 5));
			mainPreview.highlight(&pvtb, currentFile, currentFile + ".ntmp");
			auto r = [&] {pvtb.size(nana::size(pv.size().width - 10, pv.size().height - 10)); };
			pv.events().resized(r);
			pv.events().resizing(r);
			r();
			pv.show();
			pv.modality();
			std::cout << "Done with preview" << std::endl;
			refresh();
		}
		else {
			nana::msgbox mb(mainRun.fm, "Cannot Preview!");
			mb.icon(nana::msgbox::icon_error) << "Please create file first!";
			mb.show();
		}
	};
	auto push = [&](const nana::arg_keyboard& arg) {
		std::cout << arg.key << std::endl;
		if (!arg.ctrl && mainRun.loaded > 0) {
			std::cout << "Pushing" << std::endl;
			mainRun.ed.store(currentFile + ".ntmp");
			if (mainRun.loaded == 2) {
				mainRun.merged = mainRun.ed.edited();
			}
			else {
				mainRun.merged = true;
			}
			if (mainRun.merged) {
				mainRun.fm.caption("NSTE - " + currentFile);
			}
			else {
				mainRun.fm.caption("NSTE - " + currentFile + " (Unmerged)");
			}
		}
		if (arg.key == 83 && arg.ctrl) {
			if (mainRun.loaded > 0) {
				merge();
			}
			else {
				create();
			}
		}
		if (arg.key == 79 && arg.ctrl) {
			open();
		}
		if (arg.key == 82 && arg.ctrl) {
			refresh();
		}
		if (arg.key == 87 && arg.ctrl) {
			preview();
		}
	};

	mainRun.mb.at(0).append("Open", [&](nana::menu::item_proxy &) {open(); });
	mainRun.mb.at(0).append("Create", [&](nana::menu::item_proxy &) {create(); });
	mainRun.mb.at(0).append("Merge", [&](nana::menu::item_proxy &) {merge(); });
	mainRun.mb.at(0).append("Revert", [&](nana::menu::item_proxy &) {revert(); });
	mainRun.mb.at(1).append("Refresh", [&](nana::menu::item_proxy &) {refresh(); });
	mainRun.mb.at(1).append("Preview", [&](nana::menu::item_proxy &) {preview(); });
	mainRun.mb.at(1).append("Choose Theme", [&](nana::menu::item_proxy &) {openTheme(); });

	mainRun.ed.events().key_release(push);
	mainRun.fm.events().resizing([&] {mainRun.onResize(); });
	mainRun.fm.events().resized([&] {mainRun.onResize(); });
	mainRun.fm.events().unload([&](const nana::arg_unload& arg) {
		if (!mainRun.merged && mainRun.loaded > 0) {
			nana::msgbox emb(mainRun.fm, "Unmerged Changes", nana::msgbox::yes_no_cancel);
			emb.icon(nana::msgbox::icon_warning) << "Do you want to merge changes?\n";
			nana::msgbox::pick_t r = emb.show();
			if (r == nana::msgbox::pick_yes) {
				mainRun.ed.store(currentFile);
				mainRun.running = false;
			}
			else if (r == nana::msgbox::pick_cancel) {
				arg.cancel = true;
			}
			else {
				arg.cancel = false;
				mainRun.running = false;
			}
		}
	});
	refresh();
	mainRun.fm.show();
	mainRun.ed.focus();
	nana::exec();
}