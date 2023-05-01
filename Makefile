COMPILER=g++

all: clean debug run remove_header_binaries

clean: remove_header_binaries
	rm -f agenda.out

remove_header_binaries:
	rm -f heure.hpp.ghc date.hpp.ghc

compile: interface

run:
	./SCP

interface:
	$(COMPILER) interface.cpp -o SCP

debug:
	$(COMPILER) interface.cpp -o SCP -gdwarf -g

