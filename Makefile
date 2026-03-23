# Define the compiler to use
CC = clang

# Define compiler flags for warnings and other checks
CFLAGS = -Wall -Wextra -pedantic -Wno-gnu-statement-expression

# Define linker flags (empty for now, but can be extended later)
LDFLAGS = -lcmocka  # Link to CMocka library for testing

# List all source files in the project
SRC = src/test_file.c src/main.c

# Define object files based on the source files (for each .c file, create a .o file)
OBJ = $(SRC:.c=.o)

# Define the name of the final executable
EXEC = taverner

# Default target to build the project when 'make' is run with no arguments
# This is the first target and will build the executable
all: $(EXEC)

# Rule to create the executable file from the object files
# $(EXEC) is the target, $(OBJ) are the dependencies (object files)
# The compiler is invoked to link the object files into an executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Rule to compile .c files into .o object files
# For each .c file, compile it into a corresponding .o file
# The '-Iheaders' flag is used to include the 'headers' directory for header files
%.o: %.c
	$(CC) $(CFLAGS) -Iheaders -c $< -o $@

# Clean up generated files like object files, the executable, and the test binary
# This is useful for cleaning up the directory before a fresh build
clean:
	rm -f $(OBJ) $(EXEC) test_file_test  # Explicitly remove the test binary too

# Run the compiled program (after it's built)
# This target ensures that the executable is run
run: $(EXEC)
	./$(EXEC)

# Unit tests target for test_file.c
# This will compile the unit tests along with the necessary object files
test: tests/test_test_file.c src/test_file.o
	$(CC) $(CFLAGS) -Iheaders -Itests src/test_file.o tests/test_test_file.c -o test_file_test $(LDFLAGS)

# Run the unit tests
# This will execute the unit test binary after it is built
test_run: test
	./test_file_test
