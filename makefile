CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -g -O0 -Ilib
LDFLAGS = -lsqlite3

SRC = src/network.c \
      src/packet.c \
      src/db_tables.c \
      src/db_core.c \
      src/db_filters.c \
      src/0xca75.c \
      src/payload.c \
      src/misc.c \
      src/seed.c \
      src/db_print.c

TEST_SRC = tests/test_main.c $(wildcard tests/src/*.c)

.PHONY: all c s t test debug memcheck sanitize clean

all: c s

c: src/client.c $(SRC)
	$(CC) $(CFLAGS) src/client.c $(SRC) -o client/c $(LDFLAGS)

s: src/server.c $(SRC)
	$(CC) $(CFLAGS) src/server.c $(SRC) -o server/s $(LDFLAGS)

t: $(TEST_SRC) $(SRC)
	$(CC) $(CFLAGS) -Itests/lib $(TEST_SRC) $(SRC) \
		-o tests/t $(LDFLAGS)

test: t
	./tests/t

debug: t
	gdb ./tests/t

memcheck: t
	valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         --track-origins=yes \
	         ./tests/t

sanitize:
	$(CC) $(CFLAGS) -Itests/lib \
		-fsanitize=address,undefined \
		-fno-omit-frame-pointer \
		$(TEST_SRC) $(SRC) \
		-o tests/t-sanitize $(LDFLAGS)
	./tests/t-sanitize

clean:
	rm -f client/c server/s tests/t tests/t-sanitize
