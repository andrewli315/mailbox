#include "mailbox.h"
#include <stdarg.h>
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
	char usr[32];
	int length;
	mailbox* server_box;
	mail_t mail,get;
	printf(CYAN "input your user name : " WHITE);
	scanf("%s",usr);
	printf(CYAN "input your id : " WHITE);
	scanf("%d",&id);
	
	mailbox* box = (mailbox*)mailbox_open(id);
	server_box = (mailbox*)mailbox_open(0);
	memcpy(mail.sstr,usr,sizeof(usr));

	fcntl(0,F_SETFL,fcntl(0,F_GETFL)|O_NONBLOCK);//STDIN
	fcntl(1,F_SETFL,fcntl(1,F_GETFL)|O_NONBLOCK);//STDOUT

	while(strcmp("leave",mail.lstr)!=0)
	{
		//non blocking input 
		n = read(0,mail.lstr,SIZE_OF_LONG_STRING);
		//non blocking receive from server
		m = mailbox_recv(server_box, &get);
		
		length = strlen(mail.lstr);
		mail.lstr[length-1] = '\0';
		
		if(n > 0)
		{
			mailbox_send(box,&mail);
			//write(server_box->fd,&mail,sizeof(mail_t));
		}
		else if(n < 0 && m>0)
		{
			printf(BROWN);
			printf("GET mail : %s\n",get.lstr);
			printf(WHITE);
			
		}
		/*else if (m<0 || n<0 )
		{
			printf(RED "Error\n" WHITE);
			break;
		}*/
		sleep(1);
	}
	mailbox_unlink(id);
	return 0;

}
