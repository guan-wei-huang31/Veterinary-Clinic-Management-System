# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -std=c11

# Directories
SRC_DIR = src
DATA_DIR = data
BIN_DIR = bin

# Target executable name and path
TARGET = $(BIN_DIR)/clinic_system

# Source and object files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/clinic.c $(SRC_DIR)/core.c
OBJS = $(SRCS:.c=.o)

# Header files
HDRS = $(SRC_DIR)/clinic.h $(SRC_DIR)/core.h

# Default target: Build the executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile source files into object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: Remove object files and the executable
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

# Run the program (optional target)
run: $(TARGET)
	./$(TARGET)

# Phony targets to avoid conflicts with filenames
.PHONY: clean run
