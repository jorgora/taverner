# taverner makefile

# compiler
CC = clang

# compiler flags
CFLAGS = -Wall -Wextra -pedantic -Wno-gnu-statement-expression

# linker flags
LDFLAGS = -lsqlite3 -lcmocka -lSDL2

# header files
INCLUDES = -Iheaders

# list all .c files in src
SRC = $(shell find src -name "*.c")

# for each .c file, create a .o object file
OBJ = $(SRC:.c=.o)

# list all .c files in tests
TEST_SRC = $(wildcard tests/*.c)

TEST_OBJ = $(TEST_SRC:.c=)

# name of executable
EXEC = taverner

# default target to build project when "make" is run with no args
all: $(EXEC)

# rule to create executable file from object files
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

test: $(TEST_OBJ)
	@for t in $(TEST_OBJ); do ./$$t || exit 1; done

# Test target: compiles src files (except main) and test files
# pattern rule
tests/test_%: tests/test_%.c $(filter-out src/main.o, $(OBJ))
	$(CC) $(CFLAGS) $(INCLUDES) $^ -lcmocka $(LDFLAGS) -o $@

# rule to compile .c files into .o object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# remove objects and executables
clean:
	rm -f $(OBJ) $(TEST_OBJ) $(EXEC) taverner.db
