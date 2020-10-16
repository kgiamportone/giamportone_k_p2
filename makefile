FLAGS = -g -Wall -Werror -std=c++14
RUNNAME = program2
.PHONY: program2 clean run

program2: Minheap.o
	g++ $(FLAGS) Minheap.o -o program2

Minheap.o: Minheap.cpp
	g++ -c $(FLAGS) Minheap.cpp -o Minheap.o

run: program2
	./$(RUNNAME)

clean:
	rm *.o $(RUNNAME)

memcheck: program2
	valgrind --leak-check=yes ./$(RUNNAME)
