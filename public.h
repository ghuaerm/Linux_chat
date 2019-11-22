#ifndef PUBLIC_H_
#define PUBLIC_H_

#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"sys/socket.h"
#include"sys/types.h"
#include"arpa/inet.h"
#include"netinet/in.h"
#include"unistd.h"
#include"pthread.h"


#define  MAX_CLIENT 3
#define  NAME_LEN   20
#define  MSG_LEN    100
#define  PORT       12345

#define LOGIN   1
#define EXIT    2
#define PUBLIC  3
#define PRIVATE 4
#define OK      5
#define ERROR   -6


typedef struct ClientList
{
	char name[NAME_LEN];
	int socketFd;
}CLIENTLIST;

typedef struct Message
{
	char fromUser[NAME_LEN];
    int  fromUserLocate;
	int  type;
	int  sendUserLocate;
	char message[MSG_LEN];
	CLIENTLIST clientList[MAX_CLIENT];
}MESSAGE;


CLIENTLIST  clientList[MAX_CLIENT];


#endif
