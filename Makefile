
all: clean compile run clean

clean:
	rm -f heure.hpp.ghc date.hpp.ghc agenda.out

compile: heure date agenda

run:
	./agenda.out

heure:
	g++ heure.hpp

date:
	g++ date.hpp

agenda:
	g++ agenda.cpp -o agenda.out

