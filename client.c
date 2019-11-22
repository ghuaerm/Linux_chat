#include"public.h"

pthread_t tid1;
char g_name[NAME_LEN];
int  g_locate;
int  g_total;

void flush(){ char c; do{c=getc(stdin);}while(c!='\n'&&c!=EOF);};
int CheckExist()
{

	int i;
	for(i=0;i<MAX_CLIENT;i++)
	{

		if(!strcmp(g_name,clientList[i].name))
			break;
	}

	if(i<MAX_CLIENT)
	{
		printf("this name: %s is already exist!!\n",g_name);
		return 1;
	}
	else
		return 0;
}
void  ShowList()
{
int i;
g_total=0;
                 printf("\t _____________________________ \n");
                 printf("\t|         CLIENT LIST         |\n");
                 printf("\t|_____________________________|\n");
			     printf("\t|\e[4m  sort   |      name         \e[24m|\n ");
                // printf("\t|_________|___________________|\n");
  for(i=0;i<MAX_CLIENT;i++)
  {

    	if(clientList[i].socketFd!=0)
    	{
	       if(i==g_locate)
		   {
			     printf("\t|\e[4;31m *%-4d   |  %-10s       \e[0m|\n",++g_total,clientList[i].name);
                 //printf("\t|_________|___________________|\n");
		   }
		   else
		   {
		         printf("\t|\e[4m   %-4d  |  %-10s       \e[24m|\n",++g_total,clientList[i].name);
             //    printf("\t|_________|___________________|\n");
		   }
    	}
   }

                 printf("\t|\e[4m                Total:%-3d    \e[24m|\n",g_total);
}
int MakeTempList(int *tmp)
{
int i,n=0;
  for(i=0;i<MAX_CLIENT;i++)
  {
	 if(clientList[i].socketFd!=0)
     {	tmp[n]=i; n++; }
  }
    ShowList();

	int select;
	printf("please select the user \n");
	if(1!=scanf("%d",&select))
	{
		flush();
		printf("bad select \n");
		return -1;
	}
	if(select<=g_total)    
	{
		if(tmp[select-1]==g_locate)
		{
			printf("\e[33m#SYSTEM:YOU CAN NOT SELECT YOURSELF\e[0m\n");
			return -1;
		}
		else
			return tmp[select-1];
	}
	else
	{
		printf("bad select \n");
		return -1;
	}

}
void *RecvMsg(void *fd)
{

	int sockfd=*(int *)fd;
	MESSAGE msg;
    
	while(1)
	{
		bzero(&msg,sizeof(msg)); msg.type=ERROR;
		read(sockfd,&msg,sizeof(msg));
		
		if(msg.type==ERROR)
			break;
		switch(msg.type)
		{

         case LOGIN:
			 if(msg.fromUserLocate==g_locate)
			 printf("\e[34m######  > loing succeed\e[0m\n");
			 else
			 printf("\e[33m#LOGIN  > From:%-10s Msg:%s\e[0m\n",msg.fromUser,msg.message);
			 break;
		 case EXIT:
			 printf("\e[33m#EXIT   > From:%-10s Msg:%s\e[0m\n",clientList[msg.fromUserLocate].name,msg.message);
			 break;
		 case PUBLIC:
			 printf("\e[32m#PUBLIC > From:%-10s Msg:%s\e[0m\n",msg.fromUser,msg.message);
			 break;
		 case PRIVATE:
			 printf("\e[31m#PRIVATE> From:%-10s Msg:%s\e[0m\n",msg.fromUser,msg.message);
			 break;
		 default:break;
		
		}
		memcpy(&clientList,&msg.clientList,sizeof(clientList));

	}
	
	printf("server is breakdown \n");
	exit(1);

}

void SendMsg(int fd)
{
 	
	MESSAGE msg;
    msg.type=LOGIN;
	msg.fromUserLocate=g_locate;
	strcpy(msg.fromUser,g_name);
	strcpy(msg.message,g_name);
    write(fd,&msg,sizeof(msg));

	int tmp[MAX_CLIENT];
	int  key;
	while(1)
	{  

        printf(" 1 public  2 private 3 EXIT 4 client list\n");
	   if(1!= scanf("%d",&key))
	   {
		   key=0;
	       flush();
	   }
		bzero(&msg,sizeof(msg));
	    strcpy(msg.fromUser,g_name);
        msg.fromUserLocate=g_locate;
		switch(key)
		{

           case 1:
               msg.type=PUBLIC;
			   printf("\npublic: please input content \n");
	            flush();
			   fgets(msg.message,sizeof(msg.message),stdin);
			   msg.message[strlen(msg.message)-1]='\0';
               write(fd,&msg,sizeof(msg));
			   break;
		   case 2:
			   bzero(tmp,sizeof(tmp));
			   msg.type=PRIVATE;
			   if(-1!=(msg.sendUserLocate=MakeTempList(tmp)))
			   { 
				printf("\nprivate: please input content \n");
	            flush();
			    fgets(msg.message,sizeof(msg.message),stdin);
			    msg.message[strlen(msg.message)-1]='\0';
                write(fd,&msg,sizeof(msg));
			   }
			   break;
		   case 3:
			   printf("EXIT \n");
               msg.type=EXIT;
			   strcpy(msg.message,"bye-bye");
               write(fd,&msg,sizeof(msg));
			   break;
		   case 4:
			   ShowList();
			   break;
		   default:
			   printf("bad select  \n");
               msg.type=0;
			   break;
		}
	    if(msg.type==EXIT)
		{
			break;
		}
	}
   pthread_cancel(tid1);


}
int main()
{
    int fd;
	char ip[20]="127.0.0.1";
	//printf("please input the ip \n");scanf("%s",ip);
	struct sockaddr_in addr;
	addr.sin_port=htons(PORT);
	addr.sin_family=AF_INET;
  	addr.sin_addr.s_addr=inet_addr(ip);
   
	if(-1==(fd=socket(AF_INET,SOCK_STREAM,0)))
	{
		perror("socket error");
		exit(1);
	}
   
	if(-1==(connect(fd,(struct sockaddr*)&addr,sizeof(struct sockaddr))))
	{
		perror("connect error");
		exit(2);
	}

   MESSAGE msg;

   read(fd,&msg,sizeof(msg));
   
   if(msg.type==EXIT)
   {
	   printf("service refuse connect \n");
	   exit(1);
   }
   else
   {

	memcpy(&clientList,&msg.clientList,sizeof(clientList));
   g_locate=msg.fromUserLocate;
   pthread_create(&tid1,NULL,RecvMsg,(void *)&fd);
   do{
   printf("please input your name\n");scanf("%s",g_name);
     }while(CheckExist());
   SendMsg(fd);
   
   pthread_join(tid1,NULL);
   }
	return 0;
}
