CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

build:
	$(CC) main.c -o main $(CFLAGS) $(LIBS)

run:
	./main
