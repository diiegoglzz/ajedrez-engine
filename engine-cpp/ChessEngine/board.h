#pragma once
#include <cstdint>

struct Board {
    // Bitboards por pieza y color
    // Piezas blancas
    uint64_t whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens, whiteKing;

    // Piezas negras
    uint64_t blackPawns, blackKnights, blackBishops, blackRooks, blackQueens, blackKing;

    bool whiteToMove;
    // más adelante: derechos de enroque, casilla al paso, contador de medio-movimientos
};

// Índices de casillas: a1 = 0, b1 = 1, ..., h1 = 7, a2 = 8, ..., h8 = 63
void initBoard(Board& board);
bool getBit(uint64_t bitboard, int square);
void printBoard(const Board& board);