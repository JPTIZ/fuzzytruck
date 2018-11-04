CXXSTD := c++17
OUTPUT := ../fuzzytruck-client

SOCKETLIB := ../lib/socket.a
TRUCKLIB  := ../lib/truck.a

default: client

%.o: %.cpp
	g++ -c $^ -std=$(CXXSTD)

$(SOCKETLIB):
	@make -C ../tools/socket

client: main.o $(SOCKETLIB) $(TRUCKLIB)
	g++ -o $(OUTPUT) $^ -std=$(CXXSTD)

clean:
	rm $(OUTPUT) *.o
