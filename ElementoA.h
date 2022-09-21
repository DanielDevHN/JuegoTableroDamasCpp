#ifndef ELEMENTO_A
#define ELEMENTO_A

#include "Elemento.h"
#include <string>
#include <vector>
using namespace std;

class ElementoA : public Elemento
{
	public:
		ElementoA();
		ElementoA(int x, int y);
		// devuelve los movimientos disponibles (movimientos de A hacia arriba)
		vector<int*> obtenerMovimientosValidos(int** map); 
		~ElementoA();
};


#endif