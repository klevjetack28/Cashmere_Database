CC = gcc
CFLAGS = -Wall -Wextra -g -Ilib
LDFLAGS = -lsqlite3

SRC = src/network.c src/packet.c src/db_tables.c src/database.c src/0xca75.c src/payload.c src/misc.c src/seed.c

all: c s

c: src/client.c $(SRC)
	$(CC) $(CFLAGS) src/client.c $(SRC) -o client/c $(LDFLAGS)

s: src/server.c $(SRC)
	$(CC) $(CFLAGS) src/server.c $(SRC) -o server/s $(LDFLAGS)

clean:
	rm -f client/c server/s
