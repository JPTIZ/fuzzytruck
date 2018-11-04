CXXSTD := c++17
OUTPUT := truck.a

all: truck

%.o: %.cpp
	g++ -c $^ -std=$(CXXSTD)

truck: truck.o
	@ar rvs $(OUTPUT) $^
