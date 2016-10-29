#include "Engine.h"


#include <chrono>



using namespace std;

engine::engine()
{
	UI_communication = new UI_engine_communication;
	thread interface_thread (&UI_selector::nova_interface, UI_communication);

	UI_communication->send_request_to_UI(new engine_to_UI(ESCREVER_MENSAGEM_RECEBIDA, string("a")));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		UI_communication->send_request_to_UI(new engine_to_UI(ESCREVER_MENSAGEM_RECEBIDA, string("b")));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		UI_communication->send_request_to_UI(new engine_to_UI(ESCREVER_MENSAGEM_RECEBIDA, string("c")));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		UI_communication->send_request_to_UI(new engine_to_UI(ESCREVER_MENSAGEM_RECEBIDA, string("d")));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		UI_communication->send_request_to_UI(new engine_to_UI(ESCREVER_MENSAGEM_RECEBIDA, string("e")));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		UI_communication->send_request_to_UI(new engine_to_UI(ENCERRAR_UI));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	interface_thread.join();
}

