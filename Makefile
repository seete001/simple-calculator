CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -Iinclude

# =========================
# Main calculator program
# =========================

SRC = src/main.c \
      src/calculator.c \
      src/lexer.c \
      src/parser.c \
      src/ast.c \
      src/evaluator.c

OBJ = $(SRC:src/%.c=obj/%.o)

TARGET = bin/calculator


# =========================
# Tests
# =========================

TEST_SRC = tests/test_evaluator.c

TEST_OBJ = $(TEST_SRC:tests/%.c=obj/tests/%.o)

TEST_SUPPORT = obj/evaluator.o \
               obj/ast.o

TEST_TARGET = bin/test_evaluator


# =========================
# Default target
# =========================

all: $(TARGET)


# =========================
# Build calculator
# =========================

$(TARGET): $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)


# Compile source files
obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@


# =========================
# Build tests
# =========================

$(TEST_TARGET): $(TEST_OBJ) $(TEST_SUPPORT)
	mkdir -p bin
	$(CC) $(CFLAGS) $(TEST_OBJ) $(TEST_SUPPORT) -o $(TEST_TARGET)


# Compile test files
obj/tests/%.o: tests/%.c
	mkdir -p obj/tests
	$(CC) $(CFLAGS) -c $< -o $@


# Compile source files used by tests
obj/evaluator.o: src/evaluator.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@


obj/ast.o: src/ast.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@


# =========================
# Run tests
# =========================

test: $(TEST_TARGET)
	./$(TEST_TARGET)


# =========================
# Run calculator
# =========================

run: $(TARGET)
	./$(TARGET)


# =========================
# Cleanup
# =========================

clean:
	rm -rf obj bin


# =========================
# Prevent name conflicts
# =========================

.PHONY: all test run clean
