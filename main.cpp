#include <iostream>
#include "Tablero.h"
#include "Elemento.h"
#include "ElementoB.h"
#include <string>

using namespace std;

int main(void)
{

	Tablero juego;

	// Inicializa los elementos en su posición por defecto
	juego.inicializar();

	// Actualiza el tablero
	juego.actualizarTablero();

	// Se itera hasta que el juego finaliza
	while (juego.esJuagoGanado == false)
	{
		juego.mostrar();
		juego.siguienteTurno();
	}

	for (int i = 0; i < juego.listaDeElementos.size() - 1; i++)
	{
		// Limpia la memoria dinámicamente
		if (juego.listaDeElementos[i] != NULL)
		{
			delete juego.listaDeElementos[i];
		}
	}
	
	return 0;
}