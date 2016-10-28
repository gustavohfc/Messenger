#ifndef UI_H
#define UI_H

// Define a interface de I/O basica
class UI
{
public:
    UI(){}
    virtual ~UI(){}
    virtual void ler_mensagem() = 0;
    virtual void escrever_mensagem() = 0;
};

#endif