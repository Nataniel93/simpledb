CC = gcc

CFLAGS  = -O3
CFLAGS += -Wall -Wextra -Werror -pendantic
CFLAGS += -std=c11

BIN = main
LIBS = -lpthread

all:
	$(CC) main.c src/cli/commands.c src/cli/utils.c src/crud/operacoes.c src/leituraJson.c src/tabelaHash.c -o $(BIN) $(LIBS)

clean:
	rm -f main