#ifndef ELEMENTO_B
#define ELEMENTO_B

#include "Elemento.h"
#include <string>
#include <vector>
using namespace std;

class ElementoB : public Elemento
{
public:
	ElementoB();
	ElementoB(int x, int y);
	// devuelve los movimientos disponibles (movimientos de B hacia arriba)
	vector<int *> obtenerMovimientosValidos(int **map);
	~ElementoB();
};

#endif