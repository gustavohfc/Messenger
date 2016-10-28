#ifndef LINUX_UI_H
#define LINUX_UI_H

#include "../../multi_platform/Interfaces/UI.h"

class Linux_UI: public UI
{
public:
    void ler_mensagem();
    void escrever_mensagem();
};

#endif