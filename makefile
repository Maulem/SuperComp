# c++ files location
#cpp_file = $(wildcard ./*/*.cpp)
#cpp_file = $(wildcard *.cpp)

# output names
#file = $(cpp_file:.cpp=)

#all: $(file)


#cada: $(cpp_file)
#	g++ $< -Wall -o $@

SOURCES = $(wildcard ./*/*.cpp)
EXECS = $(SOURCES:%.cpp=%)
CFLAGS = -g Wall -O3

all: $(EXECS)