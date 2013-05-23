SRC = $(wildcard src/*.c)
SRC += $(wildcard deps/*.c)
OBJ = $(SRC:.c=.o)
PREFIX=/usr/local
BIN = zero-histo
LIB = /usr/local/lib
CFLAGS = -L$(LIB) -lzmq

release: zero-histo
	@:

zero-histo: $(SRC) test.c
	@echo $^
	@$(CC) $^ -std=c99 -lm -I deps -o release/$@ $(CFLAGS)

install: $(BIN)
	@install $(BIN) $(PREFIX)/bin

uninstall:
	@rm $(PREFIX)/bin/$(BIN)

clean:
	@rm -f $(BIN) $(OBJ)
	@rm -rf release/*

test: $(SRC)
	@$(CC) $^ test.c -std=c99 -lm -I deps -o test $(CFLAGS)
	@./test server & ./test

.PHONY: clean install uninstall test.c test