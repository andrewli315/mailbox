#include <stdio.h>
#include "mailbox.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <error.h>
int main(void)
{
	mailbox_t *client;
	int id,i;
	char usr[32];
	printf("input your user name : ");
	scanf("%s",usr);
	printf("input your id : ");
	scanf("%d",&id);

	client = mailbox_open(id);
	//if(client != NULL)
	
	printf("fd = %d\n",client->fd);
	printf("id = %d\n",client->id);
	return 0;

}
