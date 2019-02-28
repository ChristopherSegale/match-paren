BIN=mp
CC=gcc
CFLAGS=-std=c89 -c -Wall -pedantic

all: mp

mp: $(BIN).o
	$(CC) $(BIN).o -o $(BIN)

$(BIN).o:
	$(CC) $(CFLAGS) $(BIN).c

clean:
	$(RM) $(BIN).o $(BIN)
