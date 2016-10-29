#ifndef UI_selector_H
#define UI_selector_H

#include "../UI.h"
#include "../Thread_communication.h"
#ifdef __linux__ 
		#include "../../../Linux/Linux_UI/Linux_UI.h"
#elif _WIN32
		// TODO
#endif

class UI_selector{
public:
	static void nova_interface(UI_engine_communication* engine_communication);
};

#endif