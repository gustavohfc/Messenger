#include "Engine.h"


#include <chrono>

using namespace std;


engine::engine()
{
	UI_communication = new UI_engine_communication;
	thread interface_thread (&UI_selector::nova_interface, UI_communication);

	while(true)
	{
		if((request_from_UI = UI_communication->request_to_engine()) != NULL)
		{
			if(request_from_UI->type == UI_ENCERRADA)
			{
				delete request_from_UI;
				break;
			}
		}

		UI_communication->send_request_to_UI(new engine_to_UI(ESCREVER_MENSAGEM_RECEBIDA, std::string("Mensagem")));
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}


	interface_thread.join();

	delete UI_communication;
}

