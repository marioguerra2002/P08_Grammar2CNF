CC=g++
CFLAGS=-O0 -g -Wall
DEPS = alphabet.h chain.h symbol.h state.h grammar.h
OBJ = main.o

SRC = './src/'

compilar:
	g++ $(CFLAGS) $(SRC)*.cc -o P08_Grammar2CNF


%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
all: grammar2cnf

language: main.o
	g++ -o grammar2cnf main.cc alphabet.cc chain.cc symbol.cc state.cc grammar.cc

clean:
	rm -f *.o