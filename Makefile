
all: clean compile run

clean:
	rm -f heure.out date.out agenda.out

compile: heure date agenda

run:
	./agenda.out

heure:
	g++ -c heure.cpp -o heure.out

date:
	g++ -c date.cpp -o date.out

agenda:
	g++ agenda.cpp -o agenda.out

