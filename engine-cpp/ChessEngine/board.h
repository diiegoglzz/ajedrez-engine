#pragma once
#include <cstdint>

// Máscaras que representan "todas las columnas menos esta"
const uint64_t NOT_A_FILE = 0xFEFEFEFEFEFEFEFEULL; // excluye columna a
const uint64_t NOT_H_FILE = 0x7F7F7F7F7F7F7F7FULL; // excluye columna h
const uint64_t NOT_AB_FILE = 0xFCFCFCFCFCFCFCFCULL; // excluye columnas a y b
const uint64_t NOT_GH_FILE = 0x3F3F3F3F3F3F3F3FULL; // excluye columnas g y h

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
uint64_t knightAttacks(int square);
void printBitBoard(uint64_t bitboard);