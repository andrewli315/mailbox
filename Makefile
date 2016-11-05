#compile the mailbox
CC = gcc
CFLAGS=
FLAGS=-lrt

mail_client mail_server:	mailbox.h mail_client.o mail_server.o
	$(CC)$(CFLAGS) mail_client.o mailbox.o -o mail_client $(FLAGS)
	$(CC)$(CFLAGS) mail_server.o mailbox.o -o mail_server $(FLAGS)
mail_client.o:	mailbox.h mailbox.o mail_client.c
		$(CC)$(CFLAGS) -c mail_client.c -o mail_client.o $(FLAGS)
mail_server.o:	mailbox.h mailbox.o mail_server.c
	$(CC)$(CFLAGS) -c mail_server.c -o mail_server.o $(FLAGS)
mailbox.o:	mailbox.h mailbox.c
	$(CC)$(CFLAGS) -c mailbox.c -o mailbox.o $(FLAGS)
clean:
	rm -rf *.o
