#include "../include/compareHighlight.h"

compareHighlight::compareHighlight() {

}

void compareHighlight::highlight(nana::textbox* display, std::string l1, std::string l2) {
	display->set_highlight("Green", nana::color(0,0,0), nana::color(100, 255, 100));
	display->set_highlight("Red", nana::color(0, 0, 0), nana::color(255, 100, 100));
	auto refreshFiles = [&] {
		file1.close();
		file2.close();
		file1.open(l1, std::ios::in);
		file2.open(l2, std::ios::in);
	};

	std::string disp = "";
	std::string disp1 = "";
	std::string disp2 = "";
	std::string line1 = "";
	std::string line2 = "";
	
	refreshFiles();
	int maxLines = 0;
	if (file1.is_open()) {
		maxLines = 1;
		while (std::getline(file1, line1)) {
			maxLines++;
		}
	}
	int temp = 0;
	if (file2.is_open()) {
		temp = 1;
		while (std::getline(file2, line2)) {
			temp++;
		}
	}
	bool twoIsGreater = temp > maxLines;
	if (twoIsGreater) {
		maxLines = temp;
	}
	int maxTrueLines = maxLines;
	refreshFiles();
	while (std::getline(file1, line1)) {
		std::getline(file2, line2);
		if (line1.compare(line2) != 0) {
			maxLines++;
		}
	}
	int lineCount = 0;
	while (maxLines / pow(10, lineCount) >= 1) {
		lineCount++;
	}

	refreshFiles();

	int currentLine = 1;
	while (std::getline(file1, line1)) {
		int currentlineCount = 0;
		while (currentLine / pow(10, currentlineCount) >= 1) {
			currentlineCount++;
		}
		for (int i = 0; i < lineCount - currentlineCount; i++) {
			disp1 += " ";
		}
		disp1 += std::to_string(currentLine) + "|" + line1 + "\n";
		currentLine++;
	}

	refreshFiles();

	currentLine = 1;
	while (std::getline(file2, line2)) {
		int currentlineCount = 0;
		while (currentLine / pow(10, currentlineCount) >= 1) {
			currentlineCount++;
		}
		for (int i = 0; i < lineCount - currentlineCount; i++) {
			disp2 += " ";
		}
		disp2 += std::to_string(currentLine) + "|" + line2 + "\n";
		currentLine++;
	}
	currentLine = 1;
	bool hasMore1 = true;
	bool hasMore2 = true;
	while (currentLine < maxTrueLines) {
		hasMore1 = disp1.find("\n") != std::string::npos;
		hasMore2 = disp2.find("\n") != std::string::npos;
		if (hasMore1) {
			line1 = disp1.substr(0, disp1.find_first_of("\n"));
			disp1 = disp1.substr(disp1.find_first_of("\n") + 1);
		}
		if (hasMore2) {
			line2 = disp2.substr(0, disp2.find_first_of("\n"));
			disp2 = disp2.substr(disp2.find_first_of("\n") + 1);
		}
		if (line1.compare(line2) == 0) {
			disp += line1 + "\n";
		}
		else {
			if (hasMore1) {
				disp += line1 + "\n";
				display->set_keywords("Red", true, true, { line1 });
			}
			if (hasMore2) {
				disp += line2 + "\n";
				display->set_keywords("Green", true, true, { line2 });
			}
		}
		if (!hasMore1 && !hasMore2) {
			currentLine = maxTrueLines;
		}
		currentLine++;
	}
	display->select(true);
	display->del();
	display->append(disp, false);
	std::cout << disp1 << std::endl;
	std::cout << disp2 << std::endl;
	std::cout << disp;
}