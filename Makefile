#compile the mailbox
CC = gcc
CFLAGS=
mail_client: mailbox.h mail_client.o
	$(CC)$(CFLAGS) mail_client.o mailbox.o -o mail_client
mail_client.o: mailbox.h mailbox.c mail_client.c
	$(CC)$(CFLAGS) -c mail_client.c -o mail_client.o
mailbox.o: mailbox.h mailbox.c
	$(CC)$(CFLAGS) -c mailbox.c -o mailbox.o
