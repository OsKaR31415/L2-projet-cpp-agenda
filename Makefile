
all: clean compile run remove_header_binaries

clean: remove_header_binaries
	rm -f agenda.out

remove_header_binaries:
	rm -f heure.hpp.ghc date.hpp.ghc

compile: heure date agenda

run:
	./agenda.out

heure:
	g++ heure.hpp

date:
	g++ date.hpp

agenda:
	g++ agenda.cpp -o agenda.out

