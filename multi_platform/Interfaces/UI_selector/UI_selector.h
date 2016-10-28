#ifndef UI_selector_H
#define UI_selector_H

#include "../UI.h"
#ifdef __linux__ 
		#include "../../../Linux/Linux_UI/Linux_UI.h"
#elif _WIN32
		// TODO
#endif

class UI_selector{
public:
	static UI* nova_interface();
};

#endif