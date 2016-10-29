#include "Linux_UI.h"

using namespace std;

Linux_UI::Linux_UI(UI_engine_communication* engine_communication)
{
	this->engine_communication = engine_communication;
	initscr();	/* Start curses mode */
	start_color();
	this->definir_cores();
	cbreak();
	noecho();
	//nodelay(stdscr, TRUE); // non-blocking getchar

	// Cria as janelas
	entrada = newwin(3, 132, 40, 0);
	wattrset(entrada, COLOR_PAIR(COR_BORDAS));
	box(entrada, 0 , 0);
	mvwaddch(entrada, 1, 1, ' ');
	wrefresh(entrada);
	nodelay(entrada, TRUE); // non-blocking getchar

	conversa = newwin(38, 132, 2, 0);
	wattrset(conversa, COLOR_PAIR(COR_BORDAS));
	box(conversa, 0 , 0);	
	scrollok(conversa, TRUE);
	wrefresh(conversa);

	info = newwin(2, 132, 0, 0);
	wrefresh(info);


	this->run();
}


Linux_UI::~Linux_UI()
{
	delwin(entrada);
	delwin(conversa);
	delwin(info);
	endwin();	/* End curses mode */
}

void Linux_UI::run()
{
	char input_temp_char;
	char input_temp[BUFFER_SIZE];
	unsigned input_location = 0;
	unsigned linha_atual = 0;
	UI_to_engine* request;

	while(true)
	{
		// Verifica se tem algum request da engine
		if((recebido = engine_communication->request_to_UI()) != NULL)
		{
			if(recebido->type == ENCERRAR_UI)
			{
				delete recebido;
				return;
			}
			else if(recebido->type == ESCREVER_MENSAGEM_RECEBIDA)
			{
				wattrset(conversa, COLOR_PAIR(COR_BORDAS));
				wborder(conversa, ' ', ' ', ' ',' ',' ',' ',' ',' ');
				scroll(conversa); // Sobe a conversa uma linha
				box(conversa, 0 , 0);

				wattrset(conversa, COLOR_PAIR(COR_M_RECEBIDA));
				mvwprintw(conversa, 36, 1, recebido->mensagem->c_str());
				linha_atual++;
				wrefresh(conversa);
				delete recebido;
			}
		}

		// Verifica se tem entrada do teclado
		if((input_temp_char = wgetch(entrada)) != ERR)
		{
			if(input_temp_char == 27) // Tecla ESC
			{
				engine_communication->send_request_to_engine(new UI_to_engine(UI_ENCERRADA));
				return;
			}
			else if(input_temp_char == 127) // Tecla BACK
			{
				if(input_location > 0)
				{
					wattrset(entrada, COLOR_PAIR(COR_BORDAS));
					wborder(entrada, ' ', ' ', ' ',' ',' ',' ',' ',' ');
					int mvwdelch(entrada, 1, input_location--);
					box(entrada, 0 , 0);
					wrefresh(entrada);
				}
			}
			else if(input_temp_char == '\n') // Tecla ENTER
			{
				input_temp[input_location] = '\0';
				// Limpa entrada
				for(; input_location > 0; mvwaddch(entrada, 1, input_location--, ' '));
				wrefresh(entrada);

				// Preparar request
				if(input_temp[0] == ':') // Verifica se eh comando para o sistema
					request = new UI_to_engine(COMANDO_SISTEMA, string(input_temp));
				else
					request = new UI_to_engine(ENVIAR_MENSAGEM, string(input_temp), linha_atual);

				// Escreve a mensagem na conversa, deve ser feito antes de enviar para a engine pois sua thread pode deletar o objeto
				wattrset(conversa, COLOR_PAIR(COR_BORDAS));
				wborder(conversa, ' ', ' ', ' ',' ',' ',' ',' ',' ');
				scroll(conversa); // Sobe a conversa uma linha
				box(conversa, 0 , 0);
				if(input_temp[0] == ':') // Verifica se eh comando para o sistema
				{
					wattrset(conversa, COLOR_PAIR(COR_COMANDO_SISTEMA));
					mvwprintw(conversa, 36, 1, "To system > %s", request->mensagem->c_str());

				}
				else
				{
					wattrset(conversa, COLOR_PAIR(COR_M_ENVIADA));
					mvwprintw(conversa, 36, 1, "%2d:%2d:%2d > %s", request->horario->tm_hour, request->horario->tm_min, request->horario->tm_sec, request->mensagem->c_str());
					wattrset(conversa, COLOR_PAIR(COR_ENVIANDO)); // Escrever Enviando...
					mvwprintw(conversa, 36, 120, "Enviando...");
				}
				linha_atual++;
				wrefresh(conversa);

				delete request; //**********temp

				// Envia a mensagem para o controle
				//engine_communication->send_request_to_engine(new UI_to_engine());
			}
			else
			{
				input_temp[input_location++] = input_temp_char;
				box(entrada, 0 , 0);
				mvwaddch(entrada, 1, input_location, input_temp_char);
				wrefresh(entrada);
			}
		}
	}

	return;
}


void Linux_UI::definir_cores()
{
	init_pair(COR_M_ENVIADA, COLOR_BLUE, COLOR_BLACK);
	init_pair(COR_M_RECEBIDA, COLOR_GREEN, COLOR_BLACK);
	init_pair(COR_ENVIANDO, COLOR_RED, COLOR_BLACK); // Aviso de Enviando...
	init_pair(COR_AVISO_INTERMEDIARIO, COLOR_WHITE, COLOR_BLACK); // Usado quando possui a funcionalidade de mensagem lida, esse aviso eh usado quando a mensagem eh entregue
	init_pair(COR_AVISO_FINAL, COLOR_GREEN, COLOR_BLACK);
	init_pair(COR_SEM_CONEXAO, COLOR_RED, COLOR_BLACK);
	init_pair(COR_TENTANDO_CONECTAR, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COR_CONEXAO_OK, COLOR_GREEN, COLOR_BLACK);
	init_pair(COR_BORDAS, COLOR_GREEN, COLOR_BLACK);
	init_pair(COR_M_SENDO_ESCRIRA, COLOR_GREEN, COLOR_BLACK);
	init_pair(COR_COMANDO_SISTEMA, COLOR_BLACK, COLOR_MAGENTA);
}