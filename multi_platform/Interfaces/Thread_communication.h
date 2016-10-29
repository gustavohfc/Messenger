#ifndef THREAD_COMMUNICATION_H
#define THREAD_COMMUNICATION_H

#include <string>
#include <queue>	// std::queue

// Tipos de request
enum UI_to_engine_request {};

enum engine_to_UI_request { ESCREVER_MENSAGEM_RECEBIDA, ATUALIZAR_MENSAGEM_ENTREGUE, ATUALIZAR_MENSAGEM_LIDA, ENCERRAR_UI };

enum engine_to_sockets_request {};

enum sockets_to_engine_request {};

// Tipos de mensagem entre threads
typedef struct UI_to_engine
{
	
} UI_to_engine;

class engine_to_UI
{
public:
	engine_to_UI();
	engine_to_UI(engine_to_UI_request type); // Request para ENCERRAR_UI
	engine_to_UI(engine_to_UI_request type, std::string mensagem); // Request para ESCREVER_MENSAGEM_RECEBIDA
	~engine_to_UI();

	engine_to_UI_request type;
	std::string* mensagem;
};

typedef struct engine_to_sockets
{
	// TODO
} engine_to_sockets;

typedef struct sockets_to_engine
{
	// TODO
} sockets_to_engine;



class UI_engine_communication
{
private:
	void* temp;
	std::queue<UI_to_engine*> to_engine;
	std::queue<engine_to_UI*> to_UI;

public:
	UI_engine_communication();
	bool theres_request_to_engine();
	bool theres_request_to_UI();
	void send_request_to_engine(UI_to_engine* request);
	void send_request_to_UI(engine_to_UI* request);
	UI_to_engine* request_to_engine();
	engine_to_UI* request_to_UI();
};

class sockets_communication
{
};


#endif