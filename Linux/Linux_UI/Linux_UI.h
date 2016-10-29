#ifndef LINUX_UI_H
#define LINUX_UI_H

#define BUFFER_SIZE 128

#include <iostream>
#include <thread>
#include <ncurses.h>
#include "../../multi_platform/Interfaces/Thread_communication.h"
#include "../../multi_platform/Interfaces/UI.h"

enum Cor : int {COR_M_ENVIADA = 1, COR_M_RECEBIDA,  COR_ENVIANDO, COR_AVISO_INTERMEDIARIO, COR_AVISO_FINAL, COR_SEM_CONEXAO,
				COR_CONEXAO_OK, COR_TENTANDO_CONECTAR, COR_BORDAS, COR_M_SENDO_ESCRIRA, COR_COMANDO_SISTEMA };

class Linux_UI: public UI
{
private:
	void run();
	WINDOW* conversa;
	WINDOW* entrada;
	WINDOW* info;

	engine_to_UI* recebido;
	UI_engine_communication* engine_communication;

	void definir_cores();

public:
	Linux_UI(UI_engine_communication* engine_communication);
	~Linux_UI();
};

#endif