#include "board.h"
#include <iostream>

void initBoard(Board& board) {
    // Piezas blancas
    board.whitePawns = (1ULL << 8) | (1ULL << 9) | (1ULL << 10) | (1ULL << 11) |
        (1ULL << 12) | (1ULL << 13) | (1ULL << 14) | (1ULL << 15);
    board.whiteKnights = (1ULL << 1) | (1ULL << 6);
    board.whiteBishops = (1ULL << 2) | (1ULL << 5);
    board.whiteRooks = (1ULL << 0) | (1ULL << 7);
    board.whiteQueens = (1ULL << 3);
    board.whiteKing = (1ULL << 4);

    board.whiteToMove = true;

    board.blackPawns = (1ULL << 48) | (1ULL << 49) | (1ULL << 50) | (1ULL << 51) |
        (1ULL << 52) | (1ULL << 53) | (1ULL << 54) | (1ULL << 55);
    board.blackKnights = (1ULL << 57) | (1ULL << 62);
    board.blackBishops = (1ULL << 58) | (1ULL << 61);
    board.blackRooks = (1ULL << 56) | (1ULL << 63);
    board.blackQueens = (1ULL << 59);
    board.blackKing = (1ULL << 60);
}

bool getBit(uint64_t bitboard, int square) {
    return (bitboard >> square) & 1ULL;
}

void printBoard(const Board& board) {
    for (int rank = 7; rank >= 0; rank--) {          // fila 8 hacia fila 1
        for (int file = 0; file < 8; file++) {       // columna a hacia h
            int square = rank * 8 + file;
            char piece = '.';

            if (getBit(board.whitePawns, square)) piece = 'P';
            else if (getBit(board.whiteKnights, square)) piece = 'N';
            else if (getBit(board.whiteBishops, square)) piece = 'B';
            else if (getBit(board.whiteRooks, square)) piece = 'R';
            else if (getBit(board.whiteQueens, square)) piece = 'Q';
            else if (getBit(board.whiteKing, square)) piece = 'K';
            else if (getBit(board.blackPawns, square)) piece = 'p';
            else if (getBit(board.blackKnights, square)) piece = 'n';
            else if (getBit(board.blackBishops, square)) piece = 'b';
            else if (getBit(board.blackRooks, square)) piece = 'r';
            else if (getBit(board.blackQueens, square)) piece = 'q';
            else if (getBit(board.blackKing, square)) piece = 'k';

            std::cout << piece << ' ';
        }
        std::cout << '\n';
    }
}