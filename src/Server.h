/*
 * Server.h
 *
 *  Created on: 27 במאי 2013
 *      Author: yuval
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <pthread.h>
#include <SFML/Network.hpp>
#include <map>
using namespace std;
using namespace sf;

struct Client{
	TcpSocket* socket;
	pthread_t recvThread;
};
typedef struct{
	TcpListener listener;
	bool isListening;
	vector<struct Client> clients;
}ListenThreadArgs;
void *ListenThread(void* listenThreadArgs);
void *RecvThread(void* socket);
void SendMsg(char *c);
class Server {
public:
	static const unsigned short PORT = 5000;
	Server();
	virtual ~Server();
	void StopListening();

private:
	ListenThreadArgs listenArgs;
	pthread_t listen;

};

#endif /* SERVER_H_ */
