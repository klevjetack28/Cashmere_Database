CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -g -O0 -Ilib
LDFLAGS = -lsqlite3

SAN_FLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer

ALL_SRC = $(wildcard src/*.c)
SRC = $(filter-out src/client.c src/server.c, $(ALL_SRC))

TEST_SRC = tests/test_main.c $(wildcard tests/src/*.c)

.PHONY: all c s t test \
        debug-test debug-client debug-server \
        memcheck-test memcheck-client memcheck-server \
        sanitize-test sanitize-client sanitize-server \
        clean

all: c s

# Normal builds

c:
	$(CC) $(CFLAGS) src/client.c $(SRC) \
		-o client/c $(LDFLAGS)

s:
	$(CC) $(CFLAGS) src/server.c $(SRC) \
		-o server/s $(LDFLAGS)

t:
	$(CC) $(CFLAGS) -Itests/lib $(TEST_SRC) $(SRC) \
		-o tests/t $(LDFLAGS)

test: t
	./tests/t

# GDB

debug-test: t
	gdb ./tests/t

debug-client: c
	gdb ./client/c

debug-server: s
	gdb ./server/s

# Valgrind

memcheck-test: t
	cd ./tests/ && valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         --track-origins=yes \
	         ./t

memcheck-client: c
	cd ./client/ && valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         --track-origins=yes \
	         ./c

memcheck-server: s
	cd ./server/ && valgrind --leak-check=full \
	         --show-leak-kinds=all \
	         --track-origins=yes \
	         ./s

# Sanitizers

sanitize-test:
	$(CC) $(CFLAGS) $(SAN_FLAGS) -Itests/lib \
		$(TEST_SRC) $(SRC) \
		-o tests/t-sanitize $(LDFLAGS)
	./tests/t-sanitize

sanitize-client:
	$(CC) $(CFLAGS) $(SAN_FLAGS) \
		src/client.c $(SRC) \
		-o client/c-sanitize $(LDFLAGS)

sanitize-server:
	$(CC) $(CFLAGS) $(SAN_FLAGS) \
		src/server.c $(SRC) \
		-o server/s-sanitize $(LDFLAGS)

clean:
	rm -f client/c \
	      server/s \
	      tests/t \
	      client/c-sanitize \
	      server/s-sanitize \
	      tests/t-sanitize
