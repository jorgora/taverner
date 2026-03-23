# define compiler
CC = clang

# define compiler flags
CFLAGS = -Wall -Wextra -pedantic -Wno-gnu-statement-expression

# define linker flags
LDFLAGS = 

# list all source files
SRC = src/test_file.c src/main.c

# pattern rule (for each .c make a .o)
OBJ = $(SRC:.c=.o)

# define name of final executable
EXEC = taverner

# Default target to build the project (make with no arguments)
all: $(EXEC)

# Rule to create the executable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Rule to compile .c files into .o object files
%.o: %.c
	$(CC) $(CFLAGS) -Iheaders -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJ) $(EXEC)

# Run the program
run: $(EXEC)
	./$(EXEC)
