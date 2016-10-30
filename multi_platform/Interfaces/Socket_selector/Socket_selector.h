#ifndef Socket_selector_H
#define Socket_selector_H

#include "../Thread_communication.h"
#ifdef __linux__ 
		#include "../../../Berkeley_socket/Berkeley_socket.h"
#elif _WIN32
		// TODO
#endif

class socket_selector{
public:
	static void novo_socket(socket_engine_communication* engine_communication);
};

#endif