#pragma once
#include <cstdint>
#include <vector>

// Máscaras que representan "todas las columnas menos esta"
const uint64_t NOT_A_FILE = 0xFEFEFEFEFEFEFEFEULL;
const uint64_t NOT_H_FILE = 0x7F7F7F7F7F7F7F7FULL;
const uint64_t NOT_AB_FILE = 0xFCFCFCFCFCFCFCFCULL;
const uint64_t NOT_GH_FILE = 0x3F3F3F3F3F3F3F3FULL;

struct Board {
    uint64_t whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens, whiteKing;
    uint64_t blackPawns, blackKnights, blackBishops, blackRooks, blackQueens, blackKing;
    bool whiteToMove;
};

struct Move {
    int from;
    int to;
    bool isCapture;
};

// Índices de casillas: a1 = 0, b1 = 1, ..., h1 = 7, a2 = 8, ..., h8 = 63
void initBoard(Board& board);
bool getBit(uint64_t bitboard, int square);
void printBoard(const Board& board);
void printBitBoard(uint64_t bitboard);

uint64_t knightAttacks(int square);
uint64_t kingAttacks(int square);
uint64_t rookAttacks(int square, uint64_t occupied);
uint64_t bishopAttacks(int square, uint64_t occupied);
uint64_t queenAttacks(int square, uint64_t occupied);
uint64_t pawnAttacks(int square, bool isWhite);
uint64_t pawnMoves(int square, bool isWhite, uint64_t occupied);

uint64_t getAllPieces(const Board& board);
uint64_t getAllWhites(const Board& board);
uint64_t getAllBlacks(const Board& board);

void generateKnightMoves(const Board& board, std::vector<Move>& moves);
void generateKingMoves(const Board& board, std::vector<Move>& moves);