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

	return 0;
}
