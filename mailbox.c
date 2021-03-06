#include "mailbox.h"
#include <errno.h>
#include <error.h>

#define SHM_NAME "/__mailbox_"


mailbox_t mailbox_open(int id)
{

	int fd;
	char name[32];	
	mailbox* box = (mailbox*)malloc(sizeof(mailbox));
	sprintf(name,"%s%d",SHM_NAME,id);
	box->id = id;
	box->fd = shm_open(name, O_RDWR | O_CREAT, 0777);
	box->checksum ^= id;
	//if open the shared mem failed
	if(fd == -1)
	{
		fprintf(stderr, "Open shared memory failed\n");
		return NULL;
	}
	return (mailbox*)box;
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
	int n=0;
	if(mailbox_check_full(box) == 0)
		write(((mailbox*)box)->fd,mail,sizeof(mail_t));
	else
	{
		mailbox_unlink(((mailbox*)box)->id);
		mailbox_open(((mailbox*)box)->id);
	}
	return 0;
}
int mailbox_recv(mailbox_t box, mail_t *mail)
{
	int n=0;
	if(mailbox_check_empty(box) == 0)
		n = read(((mailbox*)box)->fd,mail,sizeof(mail_t));
	else
		return -1;
	return n;

}
int mailbox_check_empty(mailbox_t box)
{
	off_t ptr_cur = lseek(((mailbox*)box)->fd, 0,SEEK_CUR);
	off_t ptr_set = lseek(((mailbox*)box)->fd, 0,SEEK_SET);
	off_t ptr_end = lseek(((mailbox*)box)->fd, 0,SEEK_END);
	
	lseek(((mailbox*)box)->fd,ptr_cur,SEEK_SET);
	if(ptr_end == ptr_set)
		return 1;
	else
		return 0;
}
int mailbox_check_full(mailbox_t box)
{
	off_t ptr_end = lseek(((mailbox*)box)->fd, 0,SEEK_END);
	if(ptr_end > 20*sizeof(mail_t))
		return 1;
	return 0;

}
int mailbox_close(mailbox_t box)
{
	if(close(((mailbox*)box)->fd) == -1)
		return -1;
	return 0;
}
