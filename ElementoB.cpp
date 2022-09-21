#include "Elemento.h"
#include "ElementoB.h"
#include <string>
#include <vector>
#include <iostream>
#include "funciones.h"
#include <cstdlib>

using namespace std;

ElementoB::ElementoB()
{
}

ElementoB::ElementoB(int x, int y)
{

	posicion[0] = x;
	posicion[1] = y;

	equipo = 1;
}

vector<int *> ElementoB::obtenerMovimientosValidos(int **map)
{

	int **tablero = map;

	vector<int *> movimientoListado;
	// Usado para devolver multiples saltos
	vector<int *> listaSinTerminar;
	int cuadroActual[2];

	int contadorDeMovimientos = 0;

	int *listaTomada;
	listaTomada = new int[7];
	for (int i = 0; i < 7; i++)
	{
		listaTomada[i] = 0;
	}

	// Inicia en el origen
	// Vuelve a pasar por el vector inacabado, pasa por todos los movimientos
	listaSinTerminar.push_back(posicion);

	// Va a travez de los movimientos
	for (int j = 0; j < listaSinTerminar.size(); j++)
	{
		cuadroActual[0] = listaSinTerminar[j][0] - 1; // x
		cuadroActual[1] = listaSinTerminar[j][1] - 1; // y

		// -1 es izquierda, 1 es derecha
		int direction = -1;

		// Repetir para la izquierda y la derecha
		for (int i = 0; i < 2; i++)
		{

			// Comprueba las casillas inmediatas a la izquierda y a la derecha
			// También comprueba si la caja está vacía
			// si no ha saltado ya && el movimiento está en el tablero && el espacio está vacío
			if (j == 0 && estaLaCoordenadaEnTablero(cuadroActual[0], cuadroActual[1]) == true && tablero[cuadroActual[0]][cuadroActual[1]] == 0)
			{
				movimientoListado.push_back(new int[3]);
				movimientoListado[contadorDeMovimientos][0] = cuadroActual[0];
				movimientoListado[contadorDeMovimientos][1] = cuadroActual[1];

				// Ningún enemigo a eliminar
				movimientoListado[contadorDeMovimientos][2] = 0;

				contadorDeMovimientos++;
			}
			// se mueve en el tablero && hay un enemigo en esta casilla && un hueco detrás
			else if (estaLaCoordenadaEnTablero(cuadroActual[0] + direction, cuadroActual[1] - 1) == true && tablero[cuadroActual[0]][cuadroActual[1]] * equipo < 0 && tablero[cuadroActual[0] + direction][cuadroActual[1] - 1] == 0)
			{

				movimientoListado.push_back(new int[2]);
				// pone el movimiento en la lista de movimientos válidos
				movimientoListado[contadorDeMovimientos][0] = cuadroActual[0] + direction;
				movimientoListado[contadorDeMovimientos][1] = cuadroActual[1] - 1; // UP

				listaTomada[contadorDeMovimientos] = (tablero[cuadroActual[0]][cuadroActual[1]]);

				listaSinTerminar.push_back(movimientoListado[contadorDeMovimientos]);

				contadorDeMovimientos++;
			}
			// cambiar para comprobar el cuadrado derecho
			cuadroActual[0] += 2;

			// cambiar al lado derecho
			direction = 1;
		}
	}

	// Pone los ids de las piezas a eliminar al final de este vector
	movimientoListado.push_back(listaTomada);

	return movimientoListado;
}

ElementoB::~ElementoB()
{
}