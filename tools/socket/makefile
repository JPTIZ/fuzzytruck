CXXSTD := c++17
TEST   := socket-test
OUTPUT := socket.a

all: lib

lib: socket.o
	@echo "Creating lib..."
	@ar rvs $(OUTPUT) $^

%.o: %.cpp
	g++ -c $^ -std=$(CXXSTD)

test: socket.o test.o
	g++ -o $(TEST) $^ -std=$(CXXSTD)

clean:
	rm $(OUTPUT) *.o
