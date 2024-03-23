# Compiler settings - Can be customized.
CC = g++
CFLAGS = -I ../NDI_SDK/include
LDFLAGS = -L ../NDI_SDK/lib/x86_64-linux-gnu
LIBS = -lndi -pthread
# Target executable name
TARGET = ndisf
# Source files
SOURCES = main.cpp
# Object files
OBJECTS = $(SOURCES:.cpp=.o)
# Rule to make everything.
all: $(TARGET)
# Rule to remake everything. Does not include clean.
rebuild: clean all
# Rule to make the target.
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(TARGET) $(LIBS)
# Rule to compile source files into object files.
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
# Rule to clean files.
clean:
	rm -f $(TARGET) $(OBJECTS)
# Dependency rules for non-file targets
.PHONY: all rebuild clean