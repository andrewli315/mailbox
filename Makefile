#compile the mailbox
CC = gcc
CFLAGS=
FLAGS=-lrt
mail_client:	mailbox.h mail_client.o
	$(CC)$(CFLAGS) mail_client.o mailbox.o -o mail_client $(FLAGS)
mail_client.o:	mailbox.h mailbox.o mail_client.c
	$(CC)$(CFLAGS) -c mail_client.c -o mail_client.o $(FLAGS)
mailbox.o:	mailbox.h mailbox.c
	$(CC)$(CFLAGS) -c mailbox.c -o mailbox.o $(FLAGS)
clean:
	rm -rf *.o
