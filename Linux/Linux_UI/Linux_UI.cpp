#include "Linux_UI.h"

using namespace std;

Linux_UI::Linux_UI() {}


Linux_UI::~Linux_UI()
{
	endwin();			/* End curses mode */
}

//Linux_UI::run(){
//	initscr();			/* Start curses mode */
//}