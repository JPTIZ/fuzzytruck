#-----------------------------------------------------------------------------
# Config
#-----------------------------------------------------------------------------

CONTEST-DIR := contest
TRUCK-FCL   := fcl/truck.fcl

MAKE := make --no-print-directory

#-----------------------------------------------------------------------------
# Rules
#-----------------------------------------------------------------------------
.PHONY: socket tools fuzzytruck report

default: tools fuzzytruck report
	@echo ":3"

#-----------------------------------------------------------------------------
# Tooling
#-----------------------------------------------------------------------------

fuzzytruck:
	@$(MAKE) -C src

tools: socket truck

socket:
	@$(MAKE) -C tools/socket
	@mkdir -p lib
	mv tools/socket/socket.a lib

truck:
	@echo "Euro-truck super composer...START!"
	@echo "Generating FCL file..."
	python tools/fclconverter.py $(TRUCK-FCL)
	@echo "Generating C++ file from FCL..."
	java -jar tools/jFuzzyLogic.jar -c $(TRUCK-FCL) > truck.cpp
	@echo "Applying style and separating into .h..."
	python tools/cppfixer.py truck.cpp fuzzytruck/truck
	@echo "Removing temporary files..."
	rm truck.cpp
	@echo "Compiling to library..."
	@$(MAKE) -C fuzzytruck
	mv fuzzytruck/truck.a lib
	@echo "Done."

#-----------------------------------------------------------------------------
# Operations
#-----------------------------------------------------------------------------

run-client: tools fuzzytruck
	@./fuzzytruck-client localhost ${PORT}

run-server:
	@$(MAKE) -C $(CONTEST-DIR) run

show-chart:
	javac -cp tools/jFuzzyLogic.jar tools/Charter.java
	java -cp tools:tools/jFuzzyLogic.jar Charter ${FILE} ${FUNCTIONBLOCK}

#-----------------------------------------------------------------------------
# Other
#-----------------------------------------------------------------------------

report:
	@$(MAKE) -C report
