#include "Thread_communication.h"


/************************************* UI_to_engine *************************************/


/************************************* engine_to_UI *************************************/
engine_to_UI::engine_to_UI()
{
	throw "Argumento invalido";
}

engine_to_UI::engine_to_UI(engine_to_UI_request type)
{
	if(type != ENCERRAR_UI)
		throw "Argumento invalido";
	this->type = type;
}

engine_to_UI::engine_to_UI(engine_to_UI_request type, std::string mensagem)
{
	if(type != ESCREVER_MENSAGEM_RECEBIDA)
		throw "Argumento invalido";
	this->type = type;
	this->mensagem = new std::string(mensagem);
}

engine_to_UI::~engine_to_UI()
{

}

/************************************* engine_to_sockets *************************************/


/************************************* sockets_to_engine *************************************/


/************************************* UI_engine_communication *************************************/
UI_engine_communication::UI_engine_communication(){}

bool UI_engine_communication::theres_request_to_engine()
{
	return !to_engine.empty();
}

bool UI_engine_communication::theres_request_to_UI()
{
	return !to_UI.empty();
}

void UI_engine_communication::send_request_to_engine(UI_to_engine* request)
{
	to_engine.push(request);
}

void UI_engine_communication::send_request_to_UI(engine_to_UI* request)
{
	to_UI.push(request);
}

UI_to_engine* UI_engine_communication::request_to_engine()
{
	temp = to_engine.front();
	to_engine.pop();
	return (UI_to_engine*) temp;
}

engine_to_UI* UI_engine_communication::request_to_UI()
{
	temp = to_UI.front();
	to_UI.pop();
	return (engine_to_UI*) temp;
}

/************************************* sockets_communication *************************************/