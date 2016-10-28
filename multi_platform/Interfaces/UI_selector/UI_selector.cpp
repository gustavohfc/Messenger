#include "UI_selector.h"

UI* UI_selector::nova_interface()
{
	UI* interface;

	#ifdef __linux__ 
		interface = new Linux_UI();
	#elif _WIN32
		// TODO
	#endif

	return interface;
}