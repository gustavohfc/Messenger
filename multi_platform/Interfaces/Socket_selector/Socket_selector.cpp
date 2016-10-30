#include "Socket_selector.h"

void socket_selector::novo_socket(socket_engine_communication* engine_communication)
{
	#ifdef __linux__ 
		delete new berkeley_socket(engine_communication);
	#elif _WIN32
		// TODO
	#endif
}