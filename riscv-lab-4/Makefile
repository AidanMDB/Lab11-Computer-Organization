CFLAGS = -O3

all: run

lab.o: lab.cc
	g++ $(CFLAGS) -c lab.cc -o lab.o

lab: lab.o
	g++ $(CFLAGS) autograder.o lab.o -o lab

run: lab
	./lab

debug:
	g++ -g -c lab.cc -o lab.o
	g++ -g autograder.o lab.o -o lab

clean:
	rm lab.o lab