SRC = $(wildcard src/*.c)
SRC += $(wildcard deps/*.c)
OBJ = $(SRC:.c=.o)
PREFIX=/usr/local
BIN = zero-histo
LIB = /usr/local/lib
CFLAGS = -L$(LIB) -lzmq

release: test zero-histo
	@:

zero-histo: $(SRC) test.c
	@echo $^
	@$(CC) $^ -std=c99 -lm -I deps -o release/$@ $(CFLAGS)

clean:
	@rm -f $(BIN) $(OBJ)
	@rm -rf release/*

build-test: $(SRC)
	@$(CC) $^ test.c -std=c99 -lm -I deps -o test $(CFLAGS)

test: build-test
	@./test server & ./test && exit

.PHONY: clean test.c test