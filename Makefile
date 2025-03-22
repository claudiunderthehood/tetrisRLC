CC      = gcc
CFLAGS  = -Iinclude -Wall -Wextra -std=c99
LDFLAGS = -lm

SRCS    = $(wildcard src/*.c)
TARGET  = tetris

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)