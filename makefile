# gnuish Makefile

.PHONY: all clean

TARGET = sysinfo

# Check debug options

CFLAGS =-DGNU_SOURCE -Wall -finline-functions -fforce-addr -funroll-loops
LDFLAGS =-shared-libgcc -lX11

# Our compiler
CXX = gcc

# Build a list of source and object files
SRCS = $(wildcard src/*.c) $(wildcard src/*.cpp)
OBJS = $(subst src/,obj/,$(subst .c,.o,$(subst .cpp,.o,$(SRCS))))

# Default target: make dependancies then the lib
all: $(TARGET)

ifneq ($(wildcard obj/*.d),)
-include $(wildcard obj/*.d)
endif

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f obj/*.o obj/*.d
	rm -f $(TARGET)*

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@
