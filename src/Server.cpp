/*
 * Server.cpp
 *
 *  Created on: 27 במאי 2013
 *      Author: yuval
 */

#include "Server.h"
#include <SFML/Network.hpp>
#include <stdio.h>
#include <pthread.h>
Server::Server() {
	if (listenArgs.listener.listen(PORT) != sf::Socket::Done)
	{
		printf("failed listening to port:%d \n",PORT);
		exit(-1);
	}
	puts("listening");
	listenArgs.isListening=true;
	pthread_create(&listen,NULL,ListenThread,&listenArgs);
}

Server::~Server() {
	for(auto i:listenArgs.clients)
	{
		pthread_cancel(i.recvThread);
		delete i.socket;
	}
}

void* ListenThread(void* listenThreadArgs) {
	ListenThreadArgs* args=(ListenThreadArgs*)listenThreadArgs;
	while(args->isListening)
	{
		TcpSocket* socket=new TcpSocket();
		if(args->listener.accept(*socket) != Socket::Done)
		{
			puts("failed to accept client");
			return 0;
		}
		printf("connected %s\n",socket->getRemoteAddress().toString().c_str());
		pthread_t recv;
		pthread_create(&recv,NULL,RecvThread,socket);
		struct Client client;
		client.recvThread=recv;
		client.socket=socket;
		args->clients.push_back(client);
	}
	return 0;
}

void* RecvThread(void* socket) {
	TcpSocket* s=(TcpSocket*)socket;
	char in[128];
	std::size_t received;
	while(true)
	{
		if (s->receive(in, sizeof(in), received) != sf::Socket::Done)
		{
			puts("failed to recv msg");
			return 0;
		}
		in[received]='\0';
		printf("recv:%s\n",in);
	}
	return 0;
}

void Server::StopListening() {
	listenArgs.isListening=false;
}

void SendMsg(const char *c,vector<struct Client> &clients) {
	for(auto i:clients)
		i.socket->send(c,sizeof(c));
}
