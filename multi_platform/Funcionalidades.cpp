#include <iostream>
#include <stdlib.h> //exit()
#include "Funcionalidades.h"

funcionalidades::funcionalidades(plataforma p)
{

	plataforma_ = p;
	if(plataforma_ == Linux)
	{
		enviado_ = false;
		recebido_ = false;
		lido_ = false;
	} 
	else if(plataforma_ == Windows)
	{
		enviado_ = false;
		recebido_ = false;
		lido_ = false;
	} 
	else if(plataforma_ == Android)
	{
		enviado_ = false;
		recebido_ = false;
		lido_ = false;
	}
	else
	{
		std::cout << "Plataforma invalida\n";
		exit(1);
	}
}