#include "../include/runClass.h"
using namespace nana;

int main(int argc, char *argv[]) {
	runClass mainRun;

	mainRun.ed.move(point(5, 5));
	mainRun.ed.size(size(mainRun.fm.size().width - 10, mainRun.fm.size().height - 10));
	mainRun.fm.show();
	mainRun.fm.events().resizing([&]{mainRun.onResize();});
	mainRun.fm.events().resized([&]{mainRun.onResize();});
	exec();
}

runClass::runClass() : ed(fm) {
	defaultFont = new paint::font("Consolas", 12, false, false, false, false);
	fm.typeface(*defaultFont);
	fm.caption("NSTE");
	
	ed.multi_lines(true);
	ed.typeface(*defaultFont);
}

void runClass::onResize() {
	ed.move(point(5, 5));
	ed.size(size(fm.size().width - 10, fm.size().height - 10));
}