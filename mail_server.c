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


int main(void)
{
	int id = 0;
	int j;
	int i=0;
	int n;
	int from;
	char str[] = "server";
	char esc[10];
	mail_t *mail;
	mail = (mail_t*)malloc(sizeof(mail_t));

	mailbox* server;
	mailbox *client[10];
	server = (mailbox*)mailbox_open(id);
/*
	fcntl(0,F_SETFL,fcntl(0,F_GETFL)|O_NONBLOCK);//STDIN
	fcntl(1,F_SETFL,fcntl(1,F_GETFL)|O_NONBLOCK);//STDOUT
*/
	
	printf( RED "Server is on\n" WHITE);
	while(strcmp("leave",esc) !=0)
	{
//		printf(BROWN);
		memset(mail,0,sizeof(mail_t));
		off_t ptr_cur = lseek(server->fd, 0,SEEK_CUR);
		off_t ptr_end = lseek(server->fd, 0,SEEK_END);
		
	
	    lseek(server->fd,ptr_cur,SEEK_SET);

		
		if(ptr_cur < ptr_end)
		{
		    mailbox_recv(server,mail);
			if(mail->type == 0)
			{
				client[i] = (mailbox*)mailbox_open(mail->from);
				strcpy(client[i]->name,mail->sstr);
				mailbox_send(client[i], mail);
				printf("client_id is    : %d\n",client[i]->id);
				printf("id is           : %d\n",mail->from);
				printf("type is         : %d\n", mail->type);
				printf("receive mail    : %s\n",mail->sstr);
				printf("mail content    : %s\n", mail->lstr);
				i++;
			}
			else if(mail->type == 1)
			{
				printf("id is           : %d\n",mail->from);
				printf("type is         : %d\n", mail->type);
				printf("receive mail    : %s\n",mail->sstr);
				printf("mail content    : %s\n", mail->lstr);
			
				from = mail->from;
				for(j=0;j<i;j++)
				{
					mail->from = 0;
					//strcpy(mail->sstr,client[from]->name);
					//mailbox_send(client[i]->fd, mail);
				}
			}
		}
		else
			continue;

	}
	
	
	
	
}
