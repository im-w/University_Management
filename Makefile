CXX = g++
CXXFLAGS = -std=c++20 -Wall
TARGET = utms.out
SRCDIR = src
BUILDDIR = build

# Get all source files
SRCS := $(wildcard $(SRCDIR)/*.cpp)

# Generate object file names
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile each source file into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -f $(BUILDDIR)/*.o $(TARGET)
