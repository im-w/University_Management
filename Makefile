CXX = g++
CXXFLAGS = -std=c++11 -Wall -pedantic

BUILD_DIR = build
TEMPLATE_DIR = .template
OUT_EXE = myserver.out

ifeq ($(OS),Windows_NT)
	LDLIBS += -l Ws2_32
endif

# List of all source files
SRC_FILES = \
	utils/template_parser.cpp \
	utils/response.cpp \
	utils/request.cpp \
	utils/utilities.cpp \
	utils/strutils.cpp \
	server/server.cpp \
	server/route.cpp \
	src/handlers.cpp \
	src/main.cpp \
	src/Admin.cpp \
	src/CSVHandler.cpp \
	src/Professor.cpp \
	src/Program.cpp \
	src/Student.cpp \
	src/TimeRange.cpp \
	src/User.cpp \
	src/Constant.hpp

# Create a list of object files by replacing .cpp extension with .o
OBJ_FILES = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Main target
all: $(BUILD_DIR) $(OUT_EXE)

$(OUT_EXE): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: all clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) $(OUT_EXE) &> /dev/null
