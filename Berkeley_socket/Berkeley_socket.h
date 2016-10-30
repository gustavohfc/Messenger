#ifndef BERKELEY_SOCKET_H
#define BERKELEY_SOCKET_H

#include <iostream>
#include <thread>
#include "../multi_platform/Interfaces/Thread_communication.h"


class berkeley_socket
{
private:
	socket_engine_communication* engine_communication;

public:
	berkeley_socket(socket_engine_communication* engine_communication);
	~berkeley_socket();
};

#endif