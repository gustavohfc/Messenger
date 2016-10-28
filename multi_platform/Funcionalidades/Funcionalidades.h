#ifndef Funcionalidades_H
#define Funcionalidades_H

enum plataforma {Linux, Windows, Android};

class funcionalidades
{
private:
	// Funcionalidades disponiveis
	plataforma plataforma_;
	bool enviado_;
	bool recebido_;
	bool lido_;

public:
	int enviado() const { return enviado_; }
	int recebido() const { return recebido_; }
	int lido() const { return lido_; }

	// Define o contrutor de acordo com a plataforma
	#ifdef __linux__ 
		funcionalidades(plataforma p = Linux);
	#elif _WIN32
		funcionalidades(plataforma p = Windows);
	#endif
};

#endif