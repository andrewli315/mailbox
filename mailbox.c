#include "mailbox.h"

#define SHM_NAME "/__mailbox_"
#define CREATE 1
#define LEAVE 0

mailbox_t* mailbox_open(int id)
{

	int fd;
	unsigned *addr;
	char name[32];	
	char usr[32];

	sprintf(name,"%s%d",SHM_NAME,id);
	fd = shm_open(name, O_RDWR | O_CREAT, 0777);
	mailbox_t *new;
	new->fd = fd;
	new->id = id;
	new->status = CREATE;
	if(fd == -1)
	{
		fprintf(stderr, "Open shared memory failed : %s\n", 
			stderror(errno));
		return NULL;
	}
	if(ftruncate(fd,sizeof(mailbox_t)) == -1)
	{
		fprintf(stderr, "ftruncate failed : %s\n", 
			stderror(errno));
		return NULL;
	}
	return new;
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
	box.status = LEAVE;
	if(close(box.fd) == -1)
		return -1;
	return 0;
}