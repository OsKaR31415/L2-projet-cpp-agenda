
all: clean compile run

clean:
	rm -f heure.out date.out agenda.out

compile: heure date agenda

run:
	./agenda.out

heure:
	g++ heure.h -o heure.out

date:
	g++ date.h -o date.out

agenda:
	g++ agenda.cpp -o agenda.out

