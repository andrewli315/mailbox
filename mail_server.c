#include "mailbox.h"
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <sys/mman.h>

#define NONECOLOR "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;36m"
#define PURPLE "\033[0;35m"
#define LIGHT_PURPLE "\033[1;35m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"

mailbox *client[10];
mailbox *chatroom[3][10];
int client_count=0;
int chatroom_count =0;

int searchClient(int id);
unsigned int check(mail_t *mail);
int searchChatroom(int room,int id);
int main(void)
{
	int id = 0;
	int j;
	
	int n;
	int from,from_for_check;
	int pm_id,chat_num;
	char str[] = "server";
	char esc[10];
	char ID[3];
	mail_t *mail;
	mail = (mail_t*)malloc(sizeof(mail_t));

	mailbox* server;
	
	//init mailbox


	server = (mailbox*)mailbox_open(id);
/*
	fcntl(0,F_SETFL,fcntl(0,F_GETFL)|O_NONBLOCK);//STDIN
	fcntl(1,F_SETFL,fcntl(1,F_GETFL)|O_NONBLOCK);//STDOUT
*/
	
	printf( RED "Server is on\n" WHITE);
	while(1)
	{
//		printf(BROWN);
		memset(mail,0,sizeof(mail_t));
		off_t ptr_cur = lseek(server->fd, 0,SEEK_CUR);
		off_t ptr_end = lseek(server->fd, 0,SEEK_END);
		
		//read(0,&esc,sizeof(esc));
	    lseek(server->fd,ptr_cur,SEEK_SET);

		
		if(ptr_cur < ptr_end)
		{
		    mailbox_recv(server,mail);
	   
			if(mail->type == 0)
			{
				int t;
				printf("JOIN from id    : %d\n",mail->from );
				client[client_count] = (mailbox*)mailbox_open(mail->from);
				strcpy(client[client_count]->name,mail->sstr);
				for(t =0;t<64;t++)
				{
					client[client_count]->checksum ^= mail->sstr[t];
				}
				mailbox_send(client[client_count], mail);
				//printf("client_id is    : %d\n",client[i]->id);
				//printf("client_fd is    : %d\n",client[i]->fd);
				memset(mail,0,sizeof(mail_t));
				client_count++;

			}
			else if(mail->type == 1)
			{
				printf(LIGHT_CYAN);
				printf("id is           : %d\n",mail->from);
				printf("type is         : %d\n", mail->type);
				printf("receive mail    : %s\n",mail->sstr);
				printf("mail content    : %s\n", mail->lstr);
				printf(WHITE);
				from = mail->from;
				//get the info of whom send msg
				from = searchClient(from);
				if(check(mail) == client[from]->checksum)
				{
					strcpy(mail->sstr,client[from]->name);
					mail->from = 0;
					//broadcast the msg
					for(j=0;j<client_count;j++)
					{			
						//printf("name = %s\n",client[j]->name );
						mailbox_send(client[j], mail);
					}
				}
				else
				{
					ptr_end -= sizeof(mail_t);
				}
				memset(mail->lstr,0,SIZE_OF_LONG_STRING);
			}
			else if(mail->type == 2)
			{
				from = mail->from;
				from = searchClient(from);
				strcpy(mail->sstr,client[from]->name);
				strcpy(mail->lstr,"leave");
				mail->from = 0;
				//printf("%s leave\n",client[from]->name );
				//broadcast the msg
				for(j=0;j<client_count;j++)
				{			
					if(j != from)
					{
						//printf("name = %s\n",client[j]->name );
						mailbox_send(client[j], mail);
					}
				}
				//free(client[from]);
				for(j=0;j<client_count-1;j++)
				{
					if(j < from)
						continue;
					else if(j >= from )
					{
						memcpy(client[j],client[j+1],sizeof(mailbox));

					}
				}
				memset(mail->lstr,0,SIZE_OF_LONG_STRING);
				client_count--;
			}
			else if(mail->type == 3)
			{
				memset(mail->lstr,'\0',SIZE_OF_LONG_STRING);
				from = mail->from;
				for(j=0;j<client_count;j++)
				{
					strcat(mail->lstr,"\nid = ");
					sprintf(ID,"%d",client[j]->id);
					strcat(mail->lstr,ID);
					strcat(mail->lstr," name = ");
					strcat(mail->lstr,client[j]->name);
					strcat(mail->lstr,"\n");
				}
				from = searchClient(from);
				if(from !=- 1)
					mailbox_send(client[from],mail);
				memset(mail->lstr,0,SIZE_OF_LONG_STRING);
			}
			else if(mail->type /10 == 4)
			{
				pm_id = mail->type %10;
				mail->type /= 10;
				pm_id = searchClient(pm_id);
				if(pm_id != -1)
				{
					mail->from = 0;
					mailbox_send(client[pm_id],mail);
				}
				else if(pm_id == -1)
				{
					
					pm_id = searchClient(mail->from);
					strcpy(mail->lstr,"no such client");
					mail->from = 0;
					memset(mail->sstr,'\0',SIZE_OF_SHORT_STRING);
					mailbox_send(client[pm_id],mail);
				}
				memset(mail->lstr,0,SIZE_OF_LONG_STRING);
			}
			else if(mail->type/10 == 5)
			{
				chat_num = mail->type%10;
				from = mail->from;
				mail->type /= 10;
				if (chat_num >= 3 )
				{
					mail->type = 5;
					strcpy(mail->lstr,"no such chatroom number");
					mail->from = 0;
					memset(mail->sstr,'\0',SIZE_OF_SHORT_STRING);
					from = searchClient(from);
					mailbox_send(client[from],mail);
				}
				else 
				{
					chatroom[chat_num][chatroom_count] = (mailbox*)mailbox_open(mail->from);
					strcpy(chatroom[chat_num][chatroom_count]->name,mail->sstr);
					printf("%s\n", chatroom[chat_num][chatroom_count]->name);
					chatroom_count++;
					mail->from = 0;
					strcpy(mail->lstr,mail->sstr);
					strcat(mail->lstr," JOIN");
					from = searchChatroom(chat_num,from);
					strcpy(mail->sstr,chatroom[chat_num][from]->name);
					for(j=0;j<chatroom_count;j++)
					{	
						mailbox_send(chatroom[chat_num][j], mail);
					}
				}
				memset(mail->lstr,0,SIZE_OF_LONG_STRING);
			}
			else if(mail->type/10 == 6)
			{
				from = mail->from;
				chat_num = mail->type%10;
				mail->from = 0;
				from = searchChatroom(chat_num,from);
				strcpy(mail->sstr,chatroom[chat_num][from]->name);
				for(j=0;j<chatroom_count;j++)
				{			
					mailbox_send(chatroom[chat_num][j], mail);
				}
			}
			else if(mail->type/10 == 7)
			{
				from = mail->from;
				chat_num = mail->type%10;

				if(chat_num >= 3 )
				{
					mail->type = 7;
					strcpy(mail->lstr,"no such chatroom number");
					mail->from = 0;
					memset(mail->sstr,'\0',SIZE_OF_SHORT_STRING);
					from = searchClient(from);
					mailbox_send(client[from],mail);
				}
				else 
				{
					from = searchChatroom(chat_num,from);
					if(from != -1)	
					{
						strcpy(mail->sstr,chatroom[chat_num][from]->name);
						strcpy(mail->lstr,"leave");
						mail->from = 0;
						//printf("%s leave\n",client[from]->name );
						//broadcast the msg
						for(j=0;j<chatroom_count;j++)
						{			
							if(j != from)
							{
								//printf("name = %s\n",client[j]->name );
								mailbox_send(chatroom[chat_num][j], mail);
							}
						}
						//free(client[from]);
						for(j=0;j<chatroom_count-1;j++)
						{
							if(j < from)
								continue;
							else if(j >= from )
							{
								memcpy(chatroom[chat_num][j],chatroom[chat_num][j+1],sizeof(mailbox));

							}
						}
						memset(mail->lstr,0,SIZE_OF_LONG_STRING);
						chatroom_count--;
					}
					else
					{
						mail->type = 7;
						strcpy(mail->lstr,"you have not join the chatroom");
						mail->from = 0;
						memset(mail->sstr,'\0',SIZE_OF_SHORT_STRING);
						from = searchClient(from);
						mailbox_send(client[from],mail);
					}
				}
			}
		}
		else
			continue;

	}
}
int searchClient(int id)
{
	//search the target client
	int j;
	for(j =0;j<client_count;j++)
	{
		if(id == client[j]->id)
			return j;
		else
			continue;
	}
	return -1;

}
int searchChatroom(int room,int id)
{
	int j;
	for(j =0;j<chatroom_count;j++)
	{
		if(id == chatroom[room][j]->id)
			return j;
		else
			continue;
	}
	return -1;
	
}
unsigned int check(mail_t *mail)
{
	unsigned int x;
	int i;
	x^= mail->from;
	for(i=0;i<64;i++)
	{
		x ^= mail->sstr[i];
	}
	return x;


}