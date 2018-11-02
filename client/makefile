CXXSTD := c++17
OUTPUT := supersender

%.o: %.cpp
	g++ -c $^ -std=$(CXXSTD)

all: client.o test.o
	g++ -o ../$(OUTPUT) $^ -std=$(CXXSTD)
