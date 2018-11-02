CONTEST := fuzzyTruckContest

.PHONY: client

MAKE := make --no-print-directory

default:
	@echo ":3"

server:
	java -cp ${CONTEST}/bin:${CONTEST}/lib/forms.jar Server

client:
	@$(MAKE) -C client

truck:
	@echo "Euro-truck super composer...START!"
	@java -jar jFuzzyLogic.jar -c tip.fcl 2>/dev/null > tip.cpp
