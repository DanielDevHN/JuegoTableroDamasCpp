#include "funciones.h"

bool estaLaCoordenadaEnTablero(int x, int y)
{
	if (x > -1 && x < 8 && y > -1 && y < 8)
	{
		return true;
	}
	else
	{
		return false;
	}
}
