#ifndef Engine_H
#define Engine_H

#include "../Interfaces/Thread_communication.h"
#include "../Interfaces/UI.h"
#include "../Interfaces/UI_selector/UI_selector.h"
#include <thread>         // std::thread
#include <algorithm>    // std::find
#include <string>
#include <list>

enum status { CONEXAO_OK, TENTANDO_CONECTAR, SEM_CONEXAO};

typedef struct message_info {
	message_info(unsigned id)
	{
		message_id = id;
		tempo = 0;
	}
	unsigned message_id;
	unsigned tempo;
} message_info;

class engine
{
private:
	UI_engine_communication* UI_communication;
	UI_to_engine* request_from_UI;
	engine_to_UI* request_to_UI;
	engine_to_sockets* request_from_sockets;
	sockets_to_engine* request_to_sockets;
	bool encerrar = false; // Define se as threads auxiliades devem acabar

	// timeout_control variaveis
	std::list<message_info*> timeout_control_list;
	std::list<unsigned> enviadas_id;
	std::list<unsigned> timedout_id;
	std::list<unsigned> entregue_id;
	std::list<unsigned> received_connection_test_id;
	bool send_connection_test = false;
	unsigned send_connection_test_id;
	bool connection_status_alterado = false;
	status connection_status = SEM_CONEXAO;
	unsigned time_limit = 10; // Em segundos


	void timeout_control();

public:
	engine();
};

#endif