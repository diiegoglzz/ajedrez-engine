#include <iostream>
#include "board.h"

int main()
{
	Board board;
	initBoard(board);
	printBoard(board);

	std::cout << "\nAtaques del caballo desde d4 (indice 27):\n";
	printBitBoard(knightAttacks(27));

	std::cout << "\nAtaques del caballo desde a1 (indice 0):\n";
	printBitBoard(knightAttacks(0));

	std::cout << "\nAtaques del rey desde d4 (indice 27):\n";
	printBitBoard(kingAttacks(27));

	std::cout << "\nAtaques del rey desde a1 (indice 0):\n";
	printBitBoard(kingAttacks(0));

	uint64_t occupied = getAllPieces(board);

	std::cout << "\nOcupacion total del tablero:\n";
	printBitBoard(occupied);

	std::cout << "\nAtaques de la torre desde a1 (indice 0), tablero inicial:\n";
	printBitBoard(rookAttacks(0, occupied));

	std::cout << "\nAtaques de la torre desde d4 (indice 27), tablero inicial:\n";
	printBitBoard(rookAttacks(27, occupied));

	std::cout << "\nAtaques del alfil desde c1 (indice 2), tablero inicial:\n";
	printBitBoard(bishopAttacks(2, occupied));

	std::cout << "\nAtaques del alfil desde d4 (indice 27), tablero inicial:\n";
	printBitBoard(bishopAttacks(27, occupied));

	std::cout << "\nAtaques de la dama desde d4 (indice 27), tablero inicial:\n";
	printBitBoard(queenAttacks(27, occupied));

	return 0;
}
