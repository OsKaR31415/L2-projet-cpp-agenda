
all: clean heure agenda run

heure:
	g++ heure.cpp -o heure.out

date:
	g++ date.cpp -o date.out

agenda:
	g++ agenda.cpp -o agenda.out

clean:
	rm -f heure.out date.out agenda.out

run:
	./agenda.out

