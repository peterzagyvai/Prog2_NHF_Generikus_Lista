# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++11 -Wall -DMEMTRACE

# Directories
SRC_DIR := Source
OBJ_DIR := Bin/Intermediates
BIN_DIR := Bin

# Executable name
EXEC := Generikus_Lista

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
SRCS += $(wildcard $(SRC_DIR)/*.hpp)

# Object files
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Build executable
$(BIN_DIR)/$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
