cc=g++
FLAGS=-I
DEPS=langxun.h

main: main.o langxun.o $(DEPS)
	$(cc) -o main main.o langxun.o $(FLAGS).

main2: main2.o langxun.o $(DEPS) 
	$(cc) -o main2 main2.o langxun.o $(FLAGS).


%.o:%.cpp $(DEPS) 
	$(cc) -c -o $@  $< $(FLAGS).


test:testMain.o langxun.o
	$(cc) -o test testMain.o langxun.o

run1: main main2 test
	echo /dev/null > debug; ./test main main2


run2: main main2 test
	echo /dev/null > debug; ./test main2 main

.PHONY: clean debug

clean:
	rm -f *.o debug
debug: 
	g++ main.cpp langxun.cpp -g; gdb a.out


