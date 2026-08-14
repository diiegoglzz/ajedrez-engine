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

	std::cout << "\n¿Rey blanco en jaque? " << (isKingInCheck(board, true) ? "Si" : "No") << "\n";
	std::cout << "¿Rey negro en jaque? " << (isKingInCheck(board, false) ? "Si" : "No") << "\n";

	Move testMove;
	testMove.from = 12;
	testMove.to = 28;
	testMove.isCapture = false;
	testMove.piece = PAWN;

	Board afterMove = makeMove(board, testMove);
	std::cout << "\nTablero despues de mover peon e2-e4:\n";
	printBoard(afterMove);
	std::cout << "¿Turno de blancas ahora? " << (afterMove.whiteToMove ? "Si" : "No") << "\n";

	std::vector<Move> legalMoves = generateLegalMoves(board);
	std::cout << "\nTotal de movimientos LEGALES (tablero inicial, turno blancas): " << legalMoves.size() << "\n";

	std::cout << "\nPerft(1): " << perft(board, 1) << "\n";
	std::cout << "Perft(2): " << perft(board, 2) << "\n";
	std::cout << "Perft(3): " << perft(board, 3) << "\n";

	std::cout << "\nEvaluacion del tablero inicial: " << evaluateBoard(board) << "\n";

	std::cout << "\nMinimax profundidad 2 (tablero inicial): " << minimax(board, 2) << "\n";

	std::cout << "\nMinimax profundidad 3: " << minimax(board, 3) << "\n";
	std::cout << "AlphaBeta profundidad 3: " << alphaBeta(board, 3, INT_MIN, INT_MAX) << "\n";

	Move bestAB = findBestMove(board, 4);
	std::cout << "\nMejor jugada (alpha-beta, profundidad 4): de " << bestAB.from << " a " << bestAB.to << "\n";

	Board testBoard;
	initBoard(testBoard);

	// Vaciamos manualmente f1 y g1 (alfil y caballo blancos) para permitir enroque corto
	testBoard.whiteBishops &= ~(1ULL << 5);
	testBoard.whiteKnights &= ~(1ULL << 6);

	std::cout << "\nTablero con f1/g1 vacias:\n";
	printBoard(testBoard);

	std::vector<Move> legalMoves2 = generateLegalMoves(testBoard);
	std::cout << "\nMovimientos legales encontrados: " << legalMoves2.size() << "\n";

	bool foundCastling = false;
	for (const Move& m : legalMoves2) {
		if (m.from == 4 && m.to == 6) {
			foundCastling = true;
		}
	}
	std::cout << "¿Se genero el enroque corto blanco? " << (foundCastling ? "Si" : "No") << "\n";

	if (foundCastling) {
		Move castleMove;
		castleMove.from = 4;
		castleMove.to = 6;
		castleMove.isCapture = false;
		castleMove.piece = KING;

		Board afterCastle = makeMove(testBoard, castleMove);
		std::cout << "\nTablero despues del enroque:\n";
		printBoard(afterCastle);
	}

	// Posición: peón blanco en e5, peón negro avanza d7-d5 (doble), habilitando captura al paso
	Board epTest;
	initBoard(epTest);

	// Movemos manualmente el peon blanco de e2 a e5 (simulando que ya avanzo antes)
	epTest.whitePawns &= ~(1ULL << 12); // quita de e2
	epTest.whitePawns |= (1ULL << 36);  // pon en e5
	epTest.whiteToMove = false; // le toca a negras

	std::cout << "\nPosicion antes del avance doble negro:\n";
	printBoard(epTest);

	// Negras avanzan d7-d5 (doble), esto debe habilitar captura al paso
	Move blackDouble;
	blackDouble.from = 51; // d7
	blackDouble.to = 35;   // d5
	blackDouble.isCapture = false;
	blackDouble.piece = PAWN;
	blackDouble.isEnPassant = false;

	Board afterBlackDouble = makeMove(epTest, blackDouble);
	std::cout << "\nenPassantSquare tras d7-d5: " << afterBlackDouble.enPassantSquare << " (deberia ser 43, d6)\n";

	std::vector<Move> epMoves = generateLegalMoves(afterBlackDouble);
	bool foundEP = false;
	for (const Move& m : epMoves) {
		if (m.isEnPassant) foundEP = true;
	}
	std::cout << "¿Se genero la captura al paso? " << (foundEP ? "Si" : "No") << "\n";

	if (foundEP) {
		for (const Move& m : epMoves) {
			if (m.isEnPassant) {
				Board afterEP = makeMove(afterBlackDouble, m);
				std::cout << "\nTablero tras la captura al paso:\n";
				printBoard(afterEP);
			}
		}
	}

	Board promoTest;
	initBoard(promoTest);

	// Vaciamos el tablero casi entero y colocamos solo un peon blanco en a7, listo para promocionar
	promoTest.whitePawns = (1ULL << 48); // peon blanco en a7
	promoTest.blackPawns = 0ULL;
	promoTest.whiteKnights = 0ULL; promoTest.blackKnights = 0ULL;
	promoTest.whiteBishops = 0ULL; promoTest.blackBishops = 0ULL;
	promoTest.whiteRooks = 0ULL; promoTest.blackRooks = 0ULL;
	promoTest.whiteQueens = 0ULL; promoTest.blackQueens = 0ULL;
	promoTest.whiteKing = (1ULL << 4);   // rey blanco en e1
	promoTest.blackKing = (1ULL << 60);  // rey negro en e8
	promoTest.whiteToMove = true;
	promoTest.enPassantSquare = -1;
	promoTest.whiteCanCastleKingside = false;
	promoTest.whiteCanCastleQueenside = false;
	promoTest.blackCanCastleKingside = false;
	promoTest.blackCanCastleQueenside = false;

	std::cout << "\nPosicion antes de promocionar:\n";
	printBoard(promoTest);

	std::vector<Move> promoMoves = generateLegalMoves(promoTest);
	Move promoMove;
	bool found = false;
	for (const Move& m : promoMoves) {
		if (m.promotion == QUEEN) {
			promoMove = m;
			found = true;
		}
	}

	std::cout << "¿Se genero movimiento de promocion? " << (found ? "Si" : "No") << "\n";

	if (found) {
		Board afterPromo = makeMove(promoTest, promoMove);
		std::cout << "\nTablero despues de la promocion:\n";
		printBoard(afterPromo);
	}

	Board freshBoard;
	initBoard(freshBoard);

	std::cout << "\nPerft(4): " << perft(freshBoard, 4) << " (esperado: 197281)\n";

	return 0;
}
