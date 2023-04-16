
all: clean heure agenda

heure:
	g++ heure.cpp -o heure

date:
	g++ date.cpp -o date

agenda:
	g++ agenda.cpp -o agenda

clean:
	rm -f heure date agenda

