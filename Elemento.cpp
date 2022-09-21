#include "Elemento.h"
#include "funciones.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int Elemento::idActual = 1;

Elemento::Elemento()
{
	posicion[0] = 0;
	posicion[1] = 0;
	equipo = 1;
	id = idActual++;
}

// Creación personalizada del elemento
Elemento::Elemento(int x, int y, int player)
{

	posicion[0] = x;
	posicion[1] = y;

	// -1 = blanco, 1 = negro
	equipo = player;
	id = idActual++;
}

int *Elemento::obtenerPosicion()
{
	return posicion;
}

//  función virtual pura (se va a sobreescribir), devuelve un vector lleno de movimientos disponibles
vector<int *> Elemento::obtenerMovimientosValidos(int **map) {}

void Elemento::mover(int x, int y)
{
	posicion[0] = x;
	posicion[1] = y;
}

Elemento::~Elemento()
{
}