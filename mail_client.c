#include "mailbox.h"
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

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
	int id,i;
	int m =0;
	int n=0;
	char buf[130];
	char usr[32];
	int length;
	int type;
	int flag=1;
	mailbox* server_box;
	mail_t *mail,*get;
	mail_t *mail_join;
	mail = (mail_t*)malloc(sizeof(mail_t));
	mail_join = (mail_t*)malloc(sizeof(mail_t));
	get = (mail_t*)malloc(sizeof(mail_t));

	//set up client info
	printf(CYAN "input your user name : " WHITE);
	scanf("%s",usr);
	getchar();
	printf(CYAN "input your id : " WHITE);
	scanf("%d",&id);
	getchar();

	mailbox* box = (mailbox*)mailbox_open(id);
	server_box = (mailbox*)mailbox_open(0);
	memcpy(mail->sstr,usr,sizeof(usr));
	mail->from = id;
	
	//make a JOIN mail
	mail_join->from = id;
	mail_join->type = 0;
	memcpy(mail_join->sstr,usr,sizeof(usr));
	memset(mail_join->lstr,0,sizeof(mail_join->lstr));
	lseek(server_box->fd,0,SEEK_END);
	mailbox_send(server_box,mail_join);
	
	
	
	fcntl(0,F_SETFL,fcntl(0,F_GETFL)|O_NONBLOCK);//STDIN
	fcntl(1,F_SETFL,fcntl(1,F_GETFL)|O_NONBLOCK);//STDOUT

	fcntl(box->fd,F_SETFL,fcntl(0,F_GETFL)|O_NONBLOCK);//STDIN
	fcntl(server_box->fd,F_SETFL,fcntl(1,F_GETFL)|O_NONBLOCK);//STDOUT

	
	printf("choose 1)BROADCAST or 2)LEAVE 3)LIST 4(id))PRIVATE 5)JOIN_Chatroom and then input the content after a space \n");
	printf("6)Chat in Chatroom 7)LEAVE Chartroom\n");
	printf(LIGHT_GREEN "for example : 1 hello world\n");
	printf("for example : 4(id) message\n");
	printf("There are 3 chatroom, 0,1,2, the amount limit is 10\n");
	printf("for example : 5(chatroom number) message\n");
	printf(WHITE);
	while(1)
	{
		printf(WHITE);		
		//non blocking input 
		//using read to implement the nonblock io
		//cut the string 
		//judge the type and 
		n = read(0,buf,sizeof(buf));
		length = strlen(buf);
		buf[length-1] = '\0';
		//non blocking receive from server
		m = mailbox_recv(box, get);		

		if(n > 0)
		{
			sscanf(buf,"%d %s",&type,mail->lstr);
			if(type == 1)
			{
				mail->type = type;
				mailbox_send(server_box,mail);
				printf("choose 1)BROADCAST or 2)LEAVE 3)LIST 4(id))PRIVATE 5)JOIN_Chatroom and then input the content after a space \n");
				printf("6)Chat in Chatroom 7)LEAVE Chartroom\n");
				n = -1;
				memset(mail->lstr,'\0',SIZE_OF_LONG_STRING);
			}
			else if(type == 2)
			{
				mail->from = id;
				mail->type = 2;
				mailbox_send(server_box,mail);
				sleep(2);
				flag = 0;
				continue;
			}
			else if(type == 3)
			{
				mail->from = id;
				mail->type = 3;
				memset(mail->lstr,'\0',SIZE_OF_LONG_STRING);
				mailbox_send(server_box,mail);
				printf("choose 1)BROADCAST or 2)LEAVE 3)LIST 4(id))PRIVATE 5)JOIN_Chatroom and then input the content after a space \n");
				printf("6)Chat in Chatroom 7)LEAVE Chartroom\n");
			}
			else if(type /10 == 4)
			{
				mail->type = type;
				mailbox_send(server_box,mail);
				printf("choose 1)BROADCAST or 2)LEAVE 3)LIST 4(id))PRIVATE 5)JOIN_Chatroom and then input the content after a space \n");
				printf("6)Chat in Chatroom 7)LEAVE Chartroom\n");
			}
			else if(type/10 == 5)
			{
				mail->type = type;
				mailbox_send(server_box,mail);
				printf("choose 1)BROADCAST or 2)LEAVE 3)LIST 4(id))PRIVATE 5)JOIN_Chatroom and then input the content after a space \n");
				printf("6)Chat in Chatroom 7)LEAVE Chartroom\n");
			}
			else if(type/10 == 6)
			{
				mail->type = type;
				mailbox_send(server_box,mail);
				printf("choose 1)BROADCAST or 2)LEAVE 3)LIST 4(id))PRIVATE 5)JOIN_Chatroom and then input the content after a space \n");
				printf("6)Chat in Chatroom 7)LEAVE Chartroom\n");
			}
			else if(type/10 == 7)
			{
				mail->type = type;
				mailbox_send(server_box,mail);
				printf("choose 1)BROADCAST or 2)LEAVE 3)LIST 4(id))PRIVATE 5)JOIN_Chatroom and then input the content after a space \n");
				printf("6)Chat in Chatroom 7)LEAVE Chartroom\n");
			}
		}
			
		if( m > 0 )
		{
			printf(BROWN);
			printf("GET mail\n");
			printf("from      : %s\n",get->sstr);
			printf("id        : %d\n",get->from);
			printf("type      : %d\n",get->type);
			printf("content   : %s\n",get->lstr);
			printf(WHITE);
			printf("choose 1)BROADCAST or 2)LEAVE 3)LIST 4(id))PRIVATE 5)JOIN_Chatroom and then input the content after a space \n");
			printf("6)Chat in Chatroom 7)LEAVE Chartroom\n");
		}
		if(flag == 0)
			break;
		sleep(1);
	}
	free(mail);
	mailbox_unlink(id);
	return 0;

}
