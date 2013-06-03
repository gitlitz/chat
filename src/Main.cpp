/*
 * Main.cpp
 *
 *  Created on: 2 αιεπ 2013
 *      Author: yuval
 */
#include <stdio.h>
#include "Server.h"
#include <iostream>

void server();
void client();
int main(int argc, char* argv[])
{
	char who;
	puts("Do you want to be a server (s) or a client (c) ?");
	who=getchar();
	if(who=='s')
		server();
	else
		client();
	return 0;
}
void server() {
	Server s;
	getchar();
	getchar();
	getchar();

}

void client()
{
	sf::IpAddress server("127.0.0.1");

	// Create a socket for communicating with the server
	sf::TcpSocket socket;

	// Connect to the server
	if (socket.connect(server, Server::PORT) != sf::Socket::Done)
	{
		puts("connection failed");
		return;
	}
	std::cout << "Connected to server " << server << std::endl;

	// Receive a message from the server
	// Send an answer to the server
	char c[128];
	while (strcmp(c,"q")!=0)
	{
		fgets(c,sizeof(c),stdin);
		if (socket.send(&c, sizeof(c)) != sf::Socket::Done)
		{
			puts("failed to send msg");
			return;
		}
	}
}
