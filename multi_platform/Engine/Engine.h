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

public:
	engine();
};

#endif