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

uint64_t knightAttacks(int square) {
    uint64_t knight = 1ULL << square;
    uint64_t attacks = 0ULL;

    attacks |= (knight << 17) & NOT_A_FILE;
    attacks |= (knight << 15) & NOT_H_FILE;
    attacks |= (knight << 10) & NOT_AB_FILE;
    attacks |= (knight << 6) & NOT_GH_FILE;

    attacks |= (knight >> 17) & NOT_H_FILE;
    attacks |= (knight >> 15) & NOT_A_FILE;
    attacks |= (knight >> 10) & NOT_GH_FILE;
    attacks |= (knight >> 6) & NOT_AB_FILE;

    return attacks;
}

uint64_t kingAttacks(int square) {
    uint64_t king = 1ULL << square;
    uint64_t attacks = 0ULL;

    attacks |= (king << 8);
    attacks |= (king >> 8);
    attacks |= (king << 1) & NOT_A_FILE;
    attacks |= (king << 9) & NOT_A_FILE;
    attacks |= (king >> 7) & NOT_A_FILE;
    attacks |= (king >> 1) & NOT_H_FILE;
    attacks |= (king >> 9) & NOT_H_FILE;
    attacks |= (king << 7) & NOT_H_FILE;

    return attacks;
}

uint64_t rookAttacks(int square, uint64_t occupied) {
    uint64_t attacks = 0ULL;
    int currentSquare;

    // Dirección: arriba (+8)
    currentSquare = square + 8;
    while (currentSquare <= 63) {
        attacks |= (1ULL << currentSquare);
        if (occupied & (1ULL << currentSquare)) break;  // chocamos con algo, paramos
        currentSquare += 8;
    }

    // Direccion abajo (-8)
    currentSquare = square - 8;
    while(currentSquare >= 0) {
        attacks |= (1ULL << currentSquare);
        if (occupied & (1ULL << currentSquare)) break;
        currentSquare -= 8;
    }

    int rank = square / 8;
    
    // Derecha (+1)
    currentSquare = square + 1;
    while (currentSquare <= 63 && currentSquare / 8 == rank) {
        attacks |= (1ULL << currentSquare);
        if (occupied & (1ULL << currentSquare)) break;
        currentSquare += 1;
    }

    // Izquierda (-1)
    currentSquare = square - 1;
    while (currentSquare >= 0 && currentSquare / 8 == rank) {
        attacks |= (1ULL << currentSquare);
        if (occupied & (1ULL << currentSquare)) break;
        currentSquare -=1;
    }

    return attacks;
}

void printBitBoard(uint64_t bitboard) {
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            std::cout << (getBit(bitboard, square) ? '1' : '.') << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n'; // línea en blanco al final, para separar prints distintos
}

uint64_t getAllPieces(const Board& board) {
    return board.whitePawns | board.whiteKnights | board.whiteBishops | board.whiteRooks | board.whiteQueens | board.whiteKing |
        board.blackPawns | board.blackKnights | board.blackBishops | board.blackRooks | board.blackQueens | board.blackKing;
}