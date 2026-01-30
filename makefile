CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
LIBS = -lraylib -lm -lpthread -ldl -lrt -lX11

SRC_DIR = src
BIN_DIR = bin
TARGET = $(BIN_DIR)/coulomb

SRC = $(SRC_DIR)/main.c

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build
build: $(BIN_DIR)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)

# Run
run: build
	$(TARGET)
