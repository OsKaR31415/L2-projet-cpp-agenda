COMPILER=g++

all: clean compile run remove_header_binaries

clean: remove_header_binaries
	rm -f agenda.out

remove_header_binaries:
	rm -f heure.hpp.ghc date.hpp.ghc

compile: heure date agenda

run:
	./agenda.out

heure:
	$(COMPILER) heure.hpp

date:
	$(COMPILER) date.hpp

agenda:
	$(COMPILER) agenda.cpp -o agenda.out

