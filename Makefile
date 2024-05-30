# Compiler
CC := g++
# Compiler flags
CFLAGS := -std=c++11 -Wall -Wextra

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
# Main object file
MAIN_OBJ := $(BUILD_DIR)/main.o

# Output binary
OUTPUT := utms.out

# Target: all (default)
all: $(OUTPUT)

# Rule to create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Rule to compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile main.cpp into main object file
$(MAIN_OBJ): main.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files and create the output binary
$(OUTPUT): $(OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Target: clean
clean:
	rm -rf $(BUILD_DIR) $(OUTPUT)

# Phony targets
.PHONY: all clean
