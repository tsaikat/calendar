cal: main.o interface.o
	g++ -std=c++17 -Wall -pedantic -g main.o interface.o -o cal

main.o: main.cpp
	g++ -std=c++17 -Wall -pedantic -g main.cpp -o main

interface.o: interface.cpp
	g++ -std=c++17 -Wall -pedantic -g interface.cpp -o interface

clean:
	rm *.o cal