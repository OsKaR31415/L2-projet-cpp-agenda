COMPILER=g++

all: clean compile run remove_header_binaries

clean: remove_header_binaries
	rm -f SCP

remove_header_binaries:
	rm -f *.gch *.out *.o


compile: interface


interface:
	$(COMPILER) interface.cpp -o SCP


run:
	./SCP
