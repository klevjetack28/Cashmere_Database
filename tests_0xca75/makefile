CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
INCLUDES = -I../lib -Ilib

TARGET = t

SOURCES = \
	../src/0xca75.c \
	../src/bitmask.c \
	test_0xca75.c \
	src/test_bitmask.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all test clean
