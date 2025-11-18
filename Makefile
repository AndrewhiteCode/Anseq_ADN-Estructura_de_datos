# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11

# Source files and target
SRC = main.c trie.c sequence.c
OBJ = $(SRC:.c=.o)
EXEC = bio

# Directory for documentation (optional)
DOXYGEN_DIR = docs
DOXYGEN_CMD = doxygen

# Default target: compile the program
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Rule to compile .c files into .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run Doxygen to generate documentation (HTML by default)
doxygen:
	$(DOXYGEN_CMD) Doxyfile

# Clean all object files and the executable
clean:
	rm -f $(OBJ) $(EXEC)

# Clean generated documentation (optional)
clean-docs:
	rm -rf $(DOXYGEN_DIR)

# Phony targets to avoid conflicts with filenames
.PHONY: all doxygen clean clean-docs
