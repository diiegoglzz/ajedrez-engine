#include <iostream>
#include "board.h"
#include <windows.h>;


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	
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

	std::cout << "\nCapturas del peon blanco desde e4 (indice 28):\n";
	printBitBoard(pawnAttacks(28, true));

	std::cout << "\nCapturas del peon negro desde e5 (indice 36):\n";
	printBitBoard(pawnAttacks(36, false));

	std::cout << "\nMovimientos del peon blanco desde e2 (indice 12), tablero inicial:\n";
	printBitBoard(pawnMoves(12, true, occupied));

	std::cout << "\nMovimientos del peon negro desde e7 (indice 52), tablero inicial:\n";
	printBitBoard(pawnMoves(52, false, occupied));

	std::vector<Move> moves;
	generateKnightMoves(board, moves);

	std::cout << "\nMovimientos de caballo generados (tablero inicial, turno blancas):\n";
	for (const Move& m : moves) {
		std::cout << "De " << m.from << " a " << m.to << (m.isCapture ? " (captura)" : "") << "\n";
	}

	std::vector<Move> kingMoves;
	generateKingMoves(board, kingMoves);

	std::cout << "\nMovimientos del rey generados (tablero inicial, turno blancas):\n";
	for (const Move& m : kingMoves) {
		std::cout << "De " << m.from << " a " << m.to << (m.isCapture ? " (captura)" : "") << "\n";
	}

	std::vector<Move> rookMoves, bishopMoves, queenMoves;
	generateRookMoves(board, rookMoves);
	generateBishopMoves(board, bishopMoves);
	generateQueenMoves(board, queenMoves);

	std::cout << "\nMovimientos de torre generados: " << rookMoves.size() << "\n";
	std::cout << "\nMovimientos de alfil generados: " << bishopMoves.size() << "\n";
	std::cout << "\nMovimientos de dama generados: " << queenMoves.size() << "\n";

	std::vector<Move> pawnMovesList;
	generatePawnMoves(board, pawnMovesList);

	std::cout << "\nMovimientos de peon generados: " << pawnMovesList.size() << "\n";

	std::vector<Move> allMoves = generateAllMoves(board);
	std::cout << "\nTotal de movimientos generados (tablero inicial, turno blancas): " << allMoves.size() << "\n";

	std::cout << "\n¿e4 esta atacada por blancas? " << (isSquareAttacked(board, 28, true) ? "Si" : "No") << "\n";
	std::cout << "¿e5 esta atacada por blancas? " << (isSquareAttacked(board, 36, true) ? "Si" : "No") << "\n";
	std::cout << "¿e5 esta atacada por negras? " << (isSquareAttacked(board, 36, false) ? "Si" : "No") << "\n";

	return 0;
}
