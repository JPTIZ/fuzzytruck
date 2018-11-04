CONTEST-DIR := contest

MAKE := make --no-print-directory

.PHONY: socket tools fuzzytruck

default: tools fuzzytruck
	@echo ":3"

fuzzytruck:
	@$(MAKE) -C src

tools: socket truck

run-server:
	@$(MAKE) -C $(CONTEST-DIR) run

socket:
	@$(MAKE) -C tools/socket
	@mkdir -p lib
	mv tools/socket/socket.a lib

truck:
	@echo "Euro-truck super composer...START!"
	@echo "Generating C++ file..."
	@java -jar tools/jFuzzyLogic.jar -c truck.fcl 2>/dev/null > truck.cpp
	@echo "Applying style and separating into .h..."
	@python tools/cppfixer.py truck.cpp fuzzytruck/truck
	@echo "Removing temporary files..."
	@rm truck.cpp
	@echo "Compiling to library..."
	@$(MAKE) -C fuzzytruck
	@mv fuzzytruck/truck.a lib
	@echo "Done."
