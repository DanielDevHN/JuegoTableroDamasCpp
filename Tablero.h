#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "Elemento.h"
using namespace std;

class Tablero
{
public:
	// En el constructor se crean elementos, se les asigna la posición
	Tablero();

	// Guarda un array de los elementos
	vector<Elemento *> listaDeElementos;
	//  Guarda un segundo arreglo del tablero y los índices de los elementos
	int **arrayTablero;

	// Jugador A o Jugador B
	int turno;

	int limite;

	static const int JUGADOR_A = 1;
	static const int JUGADOR_B = 2;

	int numeroDePiezas;
	bool esJuagoGanado;

	// Agrega un elemento tipo puntero en tablero
	void agregarElemento(Elemento *new_piece);

	// Crea los elementos en la posiciones estándar del juego de damas y los añade al tablero
	void inicializar();

	// devuelve los movimientos disponibles
	int validarPosicion(int x, int y);

	// Recorre cada elemento del tablero y actualiza los elementos en el tablero
	void actualizarTablero();

	// Renderiza el tablero
	void mostrar();

	// Pasa al siguiente turno
	void siguienteTurno();

	// Termina el juego y felicita al ganador
	void ganar(int player);

	// Actualmente no hace nada ya que se manejan mediante código la eliminación de los objetos
	~Tablero();
};

#endif