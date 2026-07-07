CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -pthread -Iinclude

SRC = src/main.c \
	  src/lexer.c \
	  src/parser.c \
	  src/ast.c \
	  src/evaluator.c

OBJ = $(SRC:src/%.c=obj/%.o)

TARGET = bin/calculator

$(TARGET): $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf obj bin 

.PHONY: clean run
