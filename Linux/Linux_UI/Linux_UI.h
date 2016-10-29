#ifndef LINUX_UI_H
#define LINUX_UI_H

#include <iostream>
#include <ncurses.h>
#include "../../multi_platform/Interfaces/UI.h"

class Linux_UI: public UI
{
private:

public:
	Linux_UI();
	~Linux_UI();
    void ler_mensagem();
    void escrever_mensagem();
};

#endif