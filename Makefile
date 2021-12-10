CC = gcc

INCLUDEDIR = "headers"
CFLAGS  = -O3
CFLAGS += -I $(INCLUDEDIR)

BIN = main
LIBS = -lpthread -ljson-c

all:
	$(CC) $(CFLAGS) main.c src/cli/commands.c src/cli/utils.c src/crud/operacoes.c src/tabelahash.c src/leiturajson.c -o $(BIN) $(LIBS)

clean:
	rm -f main