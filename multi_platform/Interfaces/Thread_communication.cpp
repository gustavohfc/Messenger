#include "Thread_communication.h"


/************************************* UI_to_engine *************************************/
UI_to_engine::UI_to_engine()
{
	throw "Argumento invalido";
}

UI_to_engine::~UI_to_engine()
{
	delete mensagem;
}

UI_to_engine::UI_to_engine(UI_to_engine_request type)
{
	if(type != UI_ENCERRADA)
		throw "Argumento invalido";

	this->type = type;
}

UI_to_engine::UI_to_engine(UI_to_engine_request type, std::string mensagem)
{
	if(type != COMANDO_SISTEMA)
		throw "Argumento invalido";

	this->type = type;
	this->mensagem = new std::string(mensagem);
}

UI_to_engine::UI_to_engine(UI_to_engine_request type, std::string mensagem, unsigned message_id)
{
	if(type != ENVIAR_MENSAGEM)
		throw "Argumento invalido";

	time_t rawtime;

	this->type = type;
	this->mensagem = new std::string(mensagem);
	time (&rawtime);
	this->horario = localtime (&rawtime);
	this->message_id = message_id;
}


/************************************* engine_to_UI *************************************/
engine_to_UI::engine_to_UI()
{
	throw "Argumento invalido";
}

engine_to_UI::~engine_to_UI()
{
	delete mensagem;
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


/************************************* engine_to_sockets *************************************/


/************************************* sockets_to_engine *************************************/


/************************************* UI_engine_communication *************************************/
UI_engine_communication::UI_engine_communication(){}

UI_engine_communication::~UI_engine_communication()
{
	// Deleta as listas de pedidos
	while(!to_engine.empty())
	{
		delete to_engine.front();
		to_engine.pop();
	}

	while(!to_UI.empty())
	{
		delete to_UI.front();
		to_UI.pop();
	}

}

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
	if(to_engine.empty())
		return NULL;
	temp = to_engine.front();
	to_engine.pop();
	return (UI_to_engine*) temp;
}

engine_to_UI* UI_engine_communication::request_to_UI()
{
	if(to_UI.empty())
		return NULL;
	temp = to_UI.front();
	to_UI.pop();
	return (engine_to_UI*) temp;
}

/************************************* sockets_communication *************************************/