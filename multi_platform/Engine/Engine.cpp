#include "Engine.h"


#include <chrono>

using namespace std;


engine::engine()
{
	UI_communication = new UI_engine_communication;
	thread interface_thread (&UI_selector::nova_interface, UI_communication);
	thread timeout_control_thread (&engine::timeout_control, this);

	while(true)
	{
		if((request_from_UI = UI_communication->request_to_engine()) != NULL)
		{
			if(request_from_UI->type == UI_ENCERRADA)
			{
				delete request_from_UI;
				break;
			}
			else if(request_from_UI->type == ENVIAR_MENSAGEM)
			{

			}
			else if(request_from_UI->type == COMANDO_SISTEMA)
			{

			}
		}

		UI_communication->send_request_to_UI(new engine_to_UI(ESCREVER_MENSAGEM_RECEBIDA, std::string("Mensagem")));
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}


	interface_thread.join();
	timeout_control_thread.join();

	delete UI_communication;
}




void engine::timeout_control()
{
	// As listas auxiliares sao utilizadas para evitar problemas e concorrencia entre as threads
	std::list<message_info*> timeout_control_list_delete;
	std::list<unsigned> entregue_id_del_flag; // IDs que serao deletados na proxima iteracao

	unsigned iterations_per_second = 2;
	unsigned time_delay = (1000) / iterations_per_second; // Em microsegundos
	unsigned n_iteracoes_max;

	unsigned n_iteracoes_entre_testes = 10 * iterations_per_second;
	unsigned iteracoes_desde_teste = 0;
	unsigned last_connection_test_id = 0;

	while(!encerrar)
	{
		n_iteracoes_max = time_limit * iterations_per_second;

		for (std::list<message_info*>::iterator t_c=timeout_control_list.begin(); t_c != timeout_control_list.end(); ++t_c)
		{
			if(entregue_id.empty())
			{
				if ((*t_c)->tempo > n_iteracoes_max)
				{
					timedout_id.push_back((*t_c)->message_id); // Insere o ID na lista de timeout
					timeout_control_list_delete.push_back(*t_c); // Marca o ID para ser deletado da timeout_control_list
				}
				else
				{
					(*t_c)->tempo++;
				}
			}
			else
			{
				for (std::list<unsigned>::iterator id=entregue_id.begin(); id != entregue_id.end(); ++id)
				{
					if((*t_c)->message_id == (*id))
					{
						// Se a mensagem foi entregue com sucesso, deleta o ID da mensagem da lista timeout_control_list e entregue_id
						// e vai para FOR_EXIT
						entregue_id.remove(*id);
						timeout_control_list_delete.push_back(*t_c); // Marca o ID para ser deletado da timeout_control_list
						goto id_OK;
					}
				}
				for (std::list<unsigned>::iterator id=entregue_id_del_flag.begin(); id != entregue_id_del_flag.end(); ++id)
				{
					if((*t_c)->message_id == (*id))
					{
						// Se a mensagem foi entregue com sucesso, deleta o ID da mensagem da lista timeout_control_list e entregue_id_del_flag
						// e vai para FOR_EXIT
						entregue_id_del_flag.remove(*id);
						timeout_control_list_delete.push_back(*t_c); // Marca o ID para ser deletado da timeout_control_list
						goto id_OK;
					}
				}
				if((*t_c)->tempo > n_iteracoes_max)
				{
					timedout_id.push_back((*t_c)->message_id); // Insere o ID na lista de timeout
					timeout_control_list_delete.push_back(*t_c); // Marca o ID para ser deletado da timeout_control_list
				}
				else
				{
					(*t_c)->tempo++;
				}

id_OK:			continue;
			}
		}

		// Verifica se ainda tem algum id em entregue_id, se tiver pode ter sido erro de concorrencia e entao eh armazenado em entregue_id_del_flag
		entregue_id_del_flag.clear();
		while(!entregue_id.empty())
		{
			entregue_id_del_flag.push_back(entregue_id.front());
			entregue_id.pop_front();
		}

		// Insere as novas mensagens enviadas
		while(!enviadas_id.empty())
		{
			timeout_control_list.push_back(new message_info(enviadas_id.front()));
			enviadas_id.pop_front();
		}

		// Testa a conexao
		if(iteracoes_desde_teste >= n_iteracoes_entre_testes)
		{
			while(!received_connection_test_id.empty())
			{
				if(received_connection_test_id.front() == last_connection_test_id)
				{
					if(connection_status != CONEXAO_OK)
					{
						connection_status_alterado = true;
						connection_status = CONEXAO_OK;
					}
				}
				else
				{
					if(connection_status == CONEXAO_OK)
					{
						connection_status_alterado = true;
						connection_status = TENTANDO_CONECTAR;
					}
					else if(connection_status == TENTANDO_CONECTAR)
					{
						connection_status_alterado = true;
						connection_status = SEM_CONEXAO;
					}
				}
			}
		}
		else
		{
			iteracoes_desde_teste++;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(time_delay));
	}// Fim do while(!encerrar)
}