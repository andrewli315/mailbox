#ifndef MAILBBOX
#define MAILBOX

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <error.h>

#define SIZE_OF_SHORT_STRING 64
#define SIZE_OF_LONG_STRING 128
#define JOIN 0
#define BROADCAST 1
#define PRIVATE 2
#define LEAVE 3

typedef struct __MAIL{
	int from;	// the id of client
	int type;	// the type client want to let server know
	char sstr[SIZE_OF_SHORT_STRING];	// name of client
	char lstr[SIZE_OF_LONG_STRING];		// content
}mail_t;
typedef struct __MAILBOX_T
{
	int id;
	int fd;
	char* name;
	
}mailbox;
typedef void *mailbox_t;
//declare API finctions
mailbox_t mailbox_open(int id);
int mailbox_unlink(int id);
int mailbox_send(mailbox_t box, mail_t *mail);
int mailbox_recv(mailbox_t box, mail_t *mail);
int mailbox_check_empty(mailbox_t box);
int mailbox_check_full(mailbox_t box);
int mailbox_close(mailbox_t box);

#endif
