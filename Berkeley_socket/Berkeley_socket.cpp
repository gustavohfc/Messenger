#include "Berkeley_socket.h"

using namespace std;

berkeley_socket::berkeley_socket(socket_engine_communication* engine_communication)
{
	this->engine_communication = engine_communication;
}


berkeley_socket::~berkeley_socket()
{

}