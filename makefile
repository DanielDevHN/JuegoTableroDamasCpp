main: funciones.cpp Tablero.cpp Elemento.cpp main.cpp ElementoB.cpp ElementoA.cpp
	g++ -c funciones.cpp
	g++ -c Tablero.cpp 
	g++ -c Elemento.cpp
	g++ -c ElementoB.cpp
	g++ -c ElementoA.cpp
	g++ -c main.cpp
	g++ -o JuegoDeDamas main.o funciones.o Elemento.o Tablero.o ElementoB.o ElementoA.o
	./JuegoDeDamas