#ifndef LINUX_UI_H
#define LINUX_UI_H

#include <iostream>
#include <ncurses.h>
#include "../../multi_platform/Interfaces/Thread_communication.h"
#include "../../multi_platform/Interfaces/UI.h"

class Linux_UI: public UI
{
private:
	void run();
	engine_to_UI* recebido;
	UI_engine_communication* engine_communication;

public:
	Linux_UI(UI_engine_communication* engine_communication);
	~Linux_UI();
};

#endif