#ifndef MAILBBOX
#define MAILBOX

#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<std/shm.h>
#include<std/types.h>

#define SIZE_OF_SHORT_STRING 64
#define SIZE_OF_LONG_STRING 128
typedef void *mailbox_t;
typedef struct __MAIL{
	int form;
	int type;
	char sstr[SIZE_OF_SHORT_STRING];
	char lstr[SIZE_OF_LONG_STRING];
}mail_t;
//declare API finctions
mailbox_t mailbox_open(int id);
int mailbox_unlink(int id);
int mailbox_send(mailbox_t box, mail_t *mail);
int mailbox_recv(mailbox_t box, mail_t *mail);
int mailbox_check_empty(mailbox_t box);
int mailbox_check_full(mailbox_t box);
int mailbox_close(mailbox_t box);

#endif