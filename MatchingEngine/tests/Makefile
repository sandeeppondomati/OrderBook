CC := g++

RM := rm -rf

CFLAGS  := -g -Wall -std=c++17

SRCS := $(wildcard *.cpp)
INCLUDES := *.hpp
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

# the build target executable:
TARGET = matchingEngineTest

all: $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp 
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS)
