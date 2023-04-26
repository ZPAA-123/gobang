#pragma once
#include "ALL.h"

typedef struct iplist
{
	int key;
	int count = 0;
	char ip[20];
}iplist;

int MINkey(iplist* ip);
int WB_net(pieces(&game));
int BB_net(pieces(&game));
int open_server(SOCKET& socketServer, SOCKET& socketClient);
int open_client(SOCKET& socketServer, SOCKET& socketClient);
void client_start(pieces& gamemod1, SOCKET& socketServer, SOCKET& socketClient);
void server_start(pieces& gamemod1, SOCKET& socketServer, SOCKET& socketClient);
