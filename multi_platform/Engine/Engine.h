#ifndef Engine_H
#define Engine_H

#include "../Interfaces/Thread_communication.h"
#include "../Interfaces/UI.h"
#include "../Interfaces/UI_selector/UI_selector.h"
#include <thread>         // std::thread
#include <string>


class engine
{
private:
	UI_engine_communication* UI_communication;
	UI_to_engine* request_from_UI;
	engine_to_UI* request_to_UI;
	engine_to_sockets* request_from_sockets;
	sockets_to_engine* request_to_sockets;

public:
	engine();
};

#endif