#include "Tablero.h"
#include "Elemento.h"
#include "ElementoB.h"
#include "ElementoA.h"
#include <string>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <vector>
#include "funciones.h"

using namespace std;

Tablero::Tablero()
{
	// Este iterador crea todos los elementos y los pone dentro del array
	int i;

	limite = 24;

	arrayTablero = new int *[8];
	for (i = 0; i < 8; i++)
	{
		arrayTablero[i] = new int[8];
	}

	turno = 1;
	numeroDePiezas = 0;
	cout << "Tablero inicializado" << endl;
	esJuagoGanado = false;
}

void Tablero::agregarElemento(Elemento *elemento)
{
	if (numeroDePiezas < limite)
	{
		// Crea un nuevo elemento y lo agrega a la lista
		listaDeElementos.push_back(elemento);

		numeroDePiezas++;
	}
}

void Tablero::actualizarTablero()
{
	int i, j, elementoX, elementoY;

	// Limpiar el tablero y renderizarlo

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			arrayTablero[i][j] = 0;
		}
	}

	// Itera las piezas y les pone el id en la coordenada de del tablero

	for (i = 0; i < listaDeElementos.size(); i++)
	{
		if (listaDeElementos[i] != NULL)
		{
			elementoX = listaDeElementos.at(i)->posicion[0];
			elementoY = listaDeElementos.at(i)->posicion[1];
			arrayTablero[elementoX][elementoY] = listaDeElementos.at(i)->id * listaDeElementos.at(i)->equipo;
		}
	}

	// Valida si el jugador A gana

	for (i = 0; i < 8; i++)
	{
		if (arrayTablero[i][0] > 0)
		{
			ganar(JUGADOR_A);
		}
	}

	// Valida si el jugador B gana

	for (i = 0; i < 8; i++)
	{
		if (arrayTablero[i][7] < 0)
		{
			ganar(JUGADOR_B);
		}
	}
}

void Tablero::inicializar()
{

	cout << "Cargando..." << endl;
	actualizarTablero();

	// Creando los elementos del tablero
	Elemento **ptrPieza;
	ptrPieza = new Elemento *[24];

	// Crea los elementos para el jugador A
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == 1)
			{
				ptrPieza[i + j] = new ElementoA(2 * j, i);
			}
			else
			{
				ptrPieza[i + j] = new ElementoA(2 * j + 1, i);
			}
			agregarElemento(ptrPieza[i + j]);
		}
	}
	cout << "Elementos del jugador 'A' colocados." << endl;

	// Crea todos los elementos para el jugador B
	for (int i = 5; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == 6)
			{
				ptrPieza[i + j] = new ElementoB(2 * j + 1, i);
			}
			else
			{
				ptrPieza[i + j] = new ElementoB(2 * j, i);
			}
			agregarElemento(ptrPieza[i + j]);
		}
	}
	cout << "Elementos del jugador 'B' colocados." << endl;

	actualizarTablero();
	cout << "¡El tablero está listo!" << endl;
}

// Retorna el índice como pocición
int Tablero::validarPosicion(int x, int y)
{
	return arrayTablero[x][y];
}

void Tablero::mostrar()
{
	//  Recorre el tablero, imprime carácteres ASCII, en función del número del array

	int i, j, x, caracter;

	string codigosASCII[4] = {
		" ", // Cuadro negro,
		"█", // Cuadro blanco
		"o", // Jugador A
		"●"	 // Jugador B
	};

	const int CUADRO_NEGRO_INDICE = 0;
	const int CUADRO_BLANCO_INDICE = 1;
	const int JUGADOR_A_INDICE = 2;
	const int JUGADOR_B_INDICE = 3;

	cout << "Jugador A: " << codigosASCII[JUGADOR_A_INDICE] << endl;
	cout << "Jugador B: " << codigosASCII[JUGADOR_B_INDICE] << endl << endl;

	string headers[8] = {"A", "B", "C", "D", "E", "F", "G", "H"};

	cout << "  ";

	// Mostrando las columnas
	for (i = 0; i < 8; i++)
	{
		cout << " " << headers[i] << " ";
	}

	cout << endl;

	//  Eje Y
	for (i = 0; i < 8; i++)
	{
		// Enumerando las filas
		cout << i + 1 << " ";

		// Eje X
		for (j = 0; j < 24; j++)
		{
			x = floor(j / 3);

			if (arrayTablero[x][i] == 0 || (j - 1) % 3 != 0)
			{
				if ((i + x) % 2 == 0)
				{
					// Cuadros blancos
					cout << codigosASCII[CUADRO_BLANCO_INDICE];
				}
				else
				{
					// Cuadros negros
					cout << codigosASCII[CUADRO_NEGRO_INDICE];
				}
			}
			// Si actualmente se dibuja el centro de un cuadrado negro, valida el los jugadores (elementos)
			else if ((j - 1) % 3 == 0)
			{
				if (arrayTablero[x][i] < 0)
				{
					// Elemento blanco
					cout << codigosASCII[JUGADOR_B_INDICE];
				}
				else
				{
					// Elemento negro
					cout << codigosASCII[JUGADOR_A_INDICE];
				}
			}
		}
		cout << "|" << endl;
	}

	cout << "  ";
	// Pintando una linea debajo del tablero
	for (i = 0; i < 24; i++)
	{
		cout << "‾";
	}
	cout << endl;
}

void Tablero::siguienteTurno()
{
	string eleccionUsuario;
	int x = -1, y = -1, indiceActual;
	bool esValidaLaEleccion = false;
	vector<int *> movimientosValidos;

	if (turno > 0)
	{
		cout << "--- Turno del Jugador 'A' ---" << endl
			 << endl;
	}
	else
	{
		cout << "--- Turno del Jugador 'B' ---" << endl
			 << endl;
	}

	// Asegurarse de que el elemento escogido es válido, saldrá de aquí hasta haber validado.
	while (esValidaLaEleccion == false)
	{
		cout << "¿A cuál elemento te gustaría mover?" << endl;
		cout << "(ejemplo de lo que debes ingresar: 'D5')" << endl
			 << endl;
		cout << ">> ";
		cin >> eleccionUsuario;

		// Validar si X & Y están en el tablero

		if (eleccionUsuario.length() >= 2)
		{
			// Coordenada en eje X
			x = eleccionUsuario.at(0) - 65;

			// Coordenada en eje Y
			y = eleccionUsuario.at(1) - 49;
		}

		// Se comprueba que la posición esté en el rango del array
		if (estaLaCoordenadaEnTablero(x, y))
		{

			// Esta comprobación consiste en que el elemento tiene el mismo signo que el turno (se selecciona la pieza del color correcto)

			if (validarPosicion(x, y) * turno > 0)
			{
				indiceActual = validarPosicion(x, y);

				indiceActual = abs(indiceActual) - 1;

				// Obtiene los movimientos validos del elemento
				movimientosValidos = listaDeElementos[indiceActual]->obtenerMovimientosValidos(arrayTablero);

				// Por lo menos un movimiento es válido
				if (movimientosValidos.size() > 1)
				{
					esValidaLaEleccion = true;
				}
			}
		}
		if (esValidaLaEleccion == false)
		{
			cout << endl
				 << "*x*x*x*x*x*x*x* Movimiento inválido *x*x*x*x*x*x*x*" << endl
				 << endl;
		}
	}

	// Resetear coordenadas
	x = -1;
	y = -1;

	esValidaLaEleccion = false;

	// Obtener hacia dónde se va mover
	while (esValidaLaEleccion == false)
	{
		cout << endl
			 << "¿Hacia dónde quieres moverte?" << endl
			 << endl;
		cout << ">> ";
		cin >> eleccionUsuario;

		if (eleccionUsuario.length() >= 2)
		{
			// Coordenada en eje X
			x = eleccionUsuario.at(0) - 65;

			// Coordenada en eje Y
			y = eleccionUsuario.at(1) - 49;
		}

		for (int i = 0; i < movimientosValidos.size() - 1; i++)
		{
			if (movimientosValidos[i][0] == x && movimientosValidos[i][1] == y)
			{
				esValidaLaEleccion = true;
			}
		}
		if (esValidaLaEleccion == false)
		{
			cout << endl
				 << "*x*x*x*x*x*x*x* Movimiento inválido *x*x*x*x*x*x*x*" << endl
				 << endl;
		}
	}

	// Elimina los elementos seteando su puntero en nulo, para que la lista de elementos permanezca en orden
	for (int i = 0; i < 7; i++)
	{
		// Si no son 0
		if (movimientosValidos[movimientosValidos.size() - 1][i] != 0)
		{
			int indiceElemento = abs(movimientosValidos[movimientosValidos.size() - 1][i]) - 1;
			listaDeElementos[indiceElemento] = NULL;
		}
	}

	// Mover elemento
	listaDeElementos[indiceActual]->mover(x, y);

	// Dar participación al siguiente jugador
	turno = turno * (-1);

	actualizarTablero();

	// Borrando los punteros válidos del movimiento
	for (int i = 0; i < movimientosValidos.size() - 1; i++)
	{
		delete movimientosValidos[i];
	}
}

void Tablero::ganar(int jugador)
{
	switch (jugador)
	{
	case JUGADOR_A:
		cout << endl
			 << endl
			 << endl
			 << "*******************************" << endl
			 << "*******************************" << endl
			 << "¡¡El jugador 'A' es el gandor!!" << endl
			 << "*******************************" << endl
			 << "*******************************" << endl
			 << endl
			 << endl
			 << endl;
		break;
	case JUGADOR_B:
		cout << endl
			 << endl
			 << endl
			 << "*******************************" << endl
			 << "*******************************" << endl
			 << "¡¡El jugador 'B' es el gandor!!" << endl
			 << "*******************************" << endl
			 << "*******************************" << endl
			 << endl
			 << endl
			 << endl;
		break;
	default:
		break;
	}

	esJuagoGanado = true;
}

Tablero::~Tablero() {}