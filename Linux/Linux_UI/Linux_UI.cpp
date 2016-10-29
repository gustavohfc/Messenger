#include "Linux_UI.h"

using namespace std;

Linux_UI::Linux_UI(UI_engine_communication* engine_communication)
{
	this->engine_communication = engine_communication;
	initscr();	/* Start curses mode */
	getch();
	this->run();
}


Linux_UI::~Linux_UI()
{
	endwin();	/* End curses mode */
}

void Linux_UI::run(){

	while(true)
	{
		if(engine_communication->theres_request_to_UI())
		{
			recebido = engine_communication->request_to_UI();
			if(recebido->type == ENCERRAR_UI)
				return;
			printw(recebido->mensagem->c_str());
			printw("\n");
			refresh();
		}
	}

	return;
}