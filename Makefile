# Define the compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -pedantic -Wno-gnu-statement-expression
LDFLAGS = -lsqlite3 -lcmocka -lSDL2

# Directories
INCLUDES = -Iheaders

# Files
# We use 'filter-out' to remove main.c from the test build
SRC = $(shell find src -name "*.c")
OBJ = $(SRC:.c=.o)
TEST_SRC = $(wildcard tests/*.c)
EXEC = taverner

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Test target: compiles src files (except main) and test files
test: $(filter-out src/main.o, $(OBJ))
	$(CC) $(CFLAGS) $(INCLUDES) $(filter-out src/main.o, $(OBJ)) $(TEST_SRC) -o test_runner $(LDFLAGS)
	./test_runner

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC) test_runner taverner.db
