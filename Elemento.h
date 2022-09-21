#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <string>
#include <vector>
using namespace std;

class Elemento
{
public:
	Elemento();
	Elemento(int x, int y, int jugador);
	static int idActual;

	// -1 = A, 1 = B
	int equipo;

	// Guarda la posición como un puntero de coordenadas
	int *posicion = new int[2];

	// Guarda el índice
	int id;

	// Retorna la posición de la pieza
	int *obtenerPosicion();

	// Retorna los movimientos válidos
	virtual vector<int *> obtenerMovimientosValidos(int **map);

	// Mueve un elemento
	void mover(int x, int y);

	~Elemento();
};

#endif