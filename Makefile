# Define the compiler to use
CC = clang

# Define compiler flags for warnings and other checks
CFLAGS = -Wall -Wextra -pedantic -Wno-gnu-statement-expression

# Define linker flags
LDFLAGS = -lsqlite3 -lcmocka

# List all source files in the project
SRC = src/main.c src/sql/colour/colour.c

# Define object files based on the source files (for each .c file, create a .o file)
OBJ = $(SRC:.c=.o)

# Define the name of the final executable
EXEC = taverner

# Default target to build the project when 'make' is run with no arguments
# This is the first target and will build the executable
all: $(EXEC)

# Rule to create the executable file from the object files
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Rule to compile .c files into .o object files
%.o: %.c
	$(CC) $(CFLAGS) -Iheaders -c $< -o $@

# Clean up generated files like object files, executables, binaries
clean:
	rm -f $(OBJ) $(EXEC) taverner.db

# Run the compiled program (after it's built)
run: $(EXEC)
	./$(EXEC)


# I'll figure out how to test once internet is back up

# Unit tests target for test_file.c and colour-related test files
#test: tests/test_test_file.c src/test_file.o src/sql/colour/colour.o
#	$(CC) $(CFLAGS) -Iheaders -Itests src/test_file.o tests/test_test_file.c src/sql/colour/colour.o -o test_file_test $(LDFLAGS)

# Run the unit tests
#test_run: test
#	./test_file_test
