#include <nana/gui.hpp>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/toolbar.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/filesystem/filesystem.hpp>
#include <string>
#include <vector>
using namespace nana;

/*
void onResize() {
	ed.move(point(5, 5));
	ed.size(size(fm.size().width - 5, fm.size().height - 5));
}
*/
void onResize(textbox ed, form fm) {
	ed.move(point(5, 5));
	ed.size(size(fm.size().width - 5, fm.size().height - 5));
}

int main() {
	form fm;
	textbox ed(fm);

	paint::font defaultFont("Consolas", 12, false, false, false, false);
	fm.typeface(defaultFont);
	fm.caption("NSTE");

	ed.move(point(5,5));
	ed.size(size(fm.size().width-10,fm.size().height-10));
	ed.multi_lines(true);
	ed.typeface(defaultFont);
	fm.show();
	
	//fm.events().resizing(onResize(ed,fm);
	exec();
}