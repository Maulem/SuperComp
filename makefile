# c++ files location
cpp_file = $(wildcard ./*/*.cpp)
#cpp_file = $(wildcard *.cpp)

# output names
file = $(cpp_file:.cpp=)

all: $(file)

$(file): $(cpp_file)
	g++ -Wall $< -o $@