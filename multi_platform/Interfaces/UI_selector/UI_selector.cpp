#include "UI_selector.h"

void UI_selector::nova_interface(UI_engine_communication* engine_communication)
{
	#ifdef __linux__ 
		delete new Linux_UI(engine_communication);
	#elif _WIN32
		// TODO
	#endif
}