#include "mailbox.h"
#include <errno.h>
#include <error.h>

#define SHM_NAME "/__mailbox_"
#define CREATE 1
#define LEAVE 0

mailbox_t mailbox_open(int id)
{

	int fd;
	char name[32];	

	sprintf(name,"%s%d",SHM_NAME,id);
	fd = shm_open(name, O_RDWR | O_CREAT, 0777);
	if(fd == -1)
	{
		fprintf(stderr, "Open shared memory failed\n");
		return NULL;
	}
	return (void*)fd;
}
int mailbox_unlink(int id)
{
	char name[32];	
	sprintf(name,"%s%d",SHM_NAME,id);
	if(shm_unlink(name) == -1)
		return -1;
	return 0;

}
int mailbox_send(mailbox_t box, mail_t *mail)
{
	

}
int mailbox_recv(mailbox_t box, mail_t *mail)
{

}
int mailbox_check_empty(mailbox_t box)
{

}
int mailbox_check_full(mailbox_t box)
{

}
int mailbox_close(mailbox_t box)
{
	if(close(box) == -1)
		return -1;
	return 0;
}
