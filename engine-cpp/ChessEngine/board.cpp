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
    board.whiteCanCastleKingside = true;
    board.whiteCanCastleQueenside = true;
    board.blackCanCastleKingside = true;
    board.blackCanCastleQueenside = true;

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

uint64_t bishopAttacks(int square, uint64_t occupied) {
    uint64_t attacks = 0ULL;
    int currentSquare;
    
    currentSquare = square + 9;
    while (currentSquare <= 63) {
        attacks |= (1ULL << currentSquare);
        if (occupied & (1ULL << currentSquare)) break;
        if (currentSquare % 8 == 7) break;
        currentSquare += 9;
    }

    currentSquare = square - 9;
    while (currentSquare >= 0) {
        attacks |= (1ULL << currentSquare);
        if (occupied & (1ULL << currentSquare)) break;
        if (currentSquare % 8 == 0) break;
        currentSquare -= 9;
    }

    currentSquare = square + 7;
    while (currentSquare <= 63) {
        attacks |= (1ULL << currentSquare);
        if (occupied & (1ULL << currentSquare)) break;
        if (currentSquare % 8 == 0) break;
        currentSquare += 7;
    }

    currentSquare = square - 7;
    while (currentSquare >= 0) {
        attacks |= (1ULL << currentSquare);
        if (occupied & (1ULL << currentSquare)) break;
        if (currentSquare % 8 == 7) break;
        currentSquare -= 7;
    }

    return attacks;
}

uint64_t queenAttacks(int square, uint64_t occupied) {
    return rookAttacks(square, occupied) | bishopAttacks(square, occupied);
}

uint64_t pawnAttacks(int square, bool isWhite) {
    uint64_t pawn = 1ULL << square;
    uint64_t attacks = 0ULL;

    if (isWhite) {
        attacks |= (pawn << 9) & NOT_A_FILE;
        attacks |= (pawn << 7) & NOT_H_FILE;
    }
    else {
        attacks |= (pawn >> 7) & NOT_A_FILE;
        attacks |= (pawn >> 9) & NOT_H_FILE;
    }

    return attacks;
}

uint64_t pawnMoves(int square, bool isWhite, uint64_t occupied) {
    uint64_t moves = 0ULL;

    if (isWhite) {
        int oneStep = square + 8;
        if (!(occupied & (1ULL << oneStep))) {
            moves |= (1ULL << oneStep);
            // avance doble: ¿cómo comprobarías que square está en la fila 2?
            if (square >= 8 && square <= 15) {
                int twoStep = square + 16;
                if (!(occupied & (1ULL << twoStep))) {
                    moves |= (1ULL << twoStep);
                }
            }
        }
    }
    else {
        int oneStep = square - 8;
        if (!(occupied & (1ULL << oneStep))) {
            moves |= (1ULL << oneStep);
            if (square >= 48 && square <= 55) {
                int twoStep = square - 16;
                if (!(occupied & (1ULL << twoStep))) {
                    moves |= (1ULL << twoStep);
                }
            }
        }
    }

    return moves;
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

uint64_t getAllWhites(const Board& board) {
    return board.whitePawns | board.whiteKnights | board.whiteBishops | board.whiteRooks | board.whiteQueens | board.whiteKing;
}

uint64_t getAllBlacks(const Board& board) {
    return board.blackPawns | board.blackKnights | board.blackBishops | board.blackRooks | board.blackQueens | board.blackKing;
}

void generateKnightMoves(const Board& board, std::vector<Move>& moves) {
    uint64_t knights = board.whiteToMove ? board.whiteKnights : board.blackKnights;
    uint64_t ownPieces = board.whiteToMove ? getAllWhites(board) : getAllBlacks(board);
    uint64_t enemyPieces = board.whiteToMove ? getAllBlacks(board) : getAllWhites(board);

    while (knights) {
        unsigned long fromSquare;
        _BitScanForward64(&fromSquare, knights);

        uint64_t attacks = knightAttacks(fromSquare) & ~ownPieces;

        while (attacks) {
            unsigned long toSquare;
            _BitScanForward64(&toSquare, attacks);

            Move m;
            m.from = fromSquare;
            m.to = toSquare;
            m.isCapture = getBit(enemyPieces, toSquare);
            m.piece = KNIGHT;
            moves.push_back(m);

            attacks &= (attacks - 1);
        }

        knights &= (knights - 1);
    }
}

void generateKingMoves(const Board& board, std::vector<Move>& moves) {
    uint64_t king = board.whiteToMove ? board.whiteKing : board.blackKing;
    uint64_t ownPieces = board.whiteToMove ? getAllWhites(board) : getAllBlacks(board);
    uint64_t enemyPieces = board.whiteToMove ? getAllBlacks(board) : getAllWhites(board);

    while (king) {
        unsigned long fromSquare;
        _BitScanForward64(&fromSquare, king);

        uint64_t attacks =  kingAttacks(fromSquare) & ~ownPieces;

        while (attacks) {
            unsigned long toSquare;
            _BitScanForward64(&toSquare, attacks);

            Move m;
            m.from = fromSquare;
            m.to = toSquare;
            m.isCapture = getBit(enemyPieces, toSquare);
            m.piece = KING;
            moves.push_back(m);

            attacks &= (attacks - 1);
        }

        king &= (king - 1);
    }
}

void generateRookMoves(const Board& board, std::vector<Move>& moves) {
    uint64_t rooks = board.whiteToMove ? board.whiteRooks : board.blackRooks;
    uint64_t ownPieces = board.whiteToMove ? getAllWhites(board) : getAllBlacks(board);
    uint64_t enemyPieces = board.whiteToMove ? getAllBlacks(board) : getAllWhites(board);
    uint64_t occupied = getAllPieces(board);

    while (rooks) {
        unsigned long fromSquare;
        _BitScanForward64(&fromSquare, rooks);

        uint64_t attacks = rookAttacks(fromSquare, occupied) & ~ownPieces;

        while (attacks) {
            unsigned long toSquare;
            _BitScanForward64(&toSquare, attacks);

            Move m;
            m.from = fromSquare;
            m.to = toSquare;
            m.isCapture = getBit(enemyPieces, toSquare);
            m.piece = ROOK;
            moves.push_back(m);

            attacks &= (attacks - 1);
        }

        rooks &= (rooks - 1);
    }
}

void generateBishopMoves(const Board& board, std::vector<Move>& moves) {
    uint64_t bishops = board.whiteToMove ? board.whiteBishops : board.blackBishops;
    uint64_t ownPieces = board.whiteToMove ? getAllWhites(board) : getAllBlacks(board);
    uint64_t enemyPieces = board.whiteToMove ? getAllBlacks(board) : getAllWhites(board);
    uint64_t occupied = getAllPieces(board);

    while (bishops) {
        unsigned long fromSquare;
        _BitScanForward64(&fromSquare, bishops);

        uint64_t attacks = bishopAttacks(fromSquare, occupied) & ~ownPieces;

        while (attacks) {
            unsigned long toSquare;
            _BitScanForward64(&toSquare, attacks);

            Move m;
            m.from = fromSquare;
            m.to = toSquare;
            m.isCapture = getBit(enemyPieces, toSquare);
            m.piece = BISHOP;
            moves.push_back(m);

            attacks &= (attacks - 1);
        }

        bishops &= (bishops - 1);
    }
}

void generateQueenMoves(const Board& board, std::vector<Move>& moves) {
    uint64_t queens = board.whiteToMove ? board.whiteQueens : board.blackQueens;
    uint64_t ownPieces = board.whiteToMove ? getAllWhites(board) : getAllBlacks(board);
    uint64_t enemyPieces = board.whiteToMove ? getAllBlacks(board) : getAllWhites(board);
    uint64_t occupied = getAllPieces(board);

    while (queens) {
        unsigned long fromSquare;
        _BitScanForward64(&fromSquare, queens);

        uint64_t attacks = queenAttacks(fromSquare, occupied) & ~ownPieces;

        while (attacks) {
            unsigned long toSquare;
            _BitScanForward64(&toSquare, attacks);

            Move m;
            m.from = fromSquare;
            m.to = toSquare;
            m.isCapture = getBit(enemyPieces, toSquare);
            m.piece = QUEEN;
            moves.push_back(m);

            attacks &= (attacks - 1);
        }

        queens &= (queens - 1);
    }
}

void generatePawnMoves(const Board& board, std::vector<Move>& moves) {
    uint64_t pawns = board.whiteToMove ? board.whitePawns : board.blackPawns;
    uint64_t enemyPieces = board.whiteToMove ? getAllBlacks(board) : getAllWhites(board);
    uint64_t occupied = getAllPieces(board);

    while (pawns) {
        unsigned long fromSquare;
        _BitScanForward64(&fromSquare, pawns);

        // Avances (simple + doble)
        uint64_t advances = pawnMoves(fromSquare, board.whiteToMove, occupied);
        while (advances) {
            unsigned long toSquare;
            _BitScanForward64(&toSquare, advances);
            Move m;
            m.from = fromSquare;
            m.to = toSquare;
            m.isCapture = false; // un avance nunca es captura
            m.piece = PAWN;
            moves.push_back(m);
            advances &= (advances - 1);
        }

        // Capturas diagonales
        uint64_t captures = pawnAttacks(fromSquare, board.whiteToMove) & enemyPieces;
        while (captures) {
            unsigned long toSquare;
            _BitScanForward64(&toSquare, captures);
            Move m;
            m.from = fromSquare;
            m.to = toSquare;
            m.isCapture = true; // aquí ya sabemos que siempre es captura
            m.piece = PAWN;
            moves.push_back(m);
            captures &= (captures - 1);
        }

        pawns &= (pawns - 1);
    }
}

std::vector<Move> generateAllMoves(const Board& board) {
    std::vector<Move> moves;

    generateKnightMoves(board, moves);
    generateKingMoves(board, moves);
    generateRookMoves(board, moves);
    generateBishopMoves(board, moves);
    generateQueenMoves(board, moves);
    generatePawnMoves(board, moves);
    generateCastlingMoves(board, moves);

    return moves;
}

bool isSquareAttacked(const Board& board, int square, bool byWhite) {
    uint64_t occupied = getAllPieces(board);

    // Caballo
    uint64_t knights = byWhite ? board.whiteKnights : board.blackKnights;
    if (knightAttacks(square) & knights) return true;

    // Rey
    uint64_t king = byWhite ? board.whiteKing : board.blackKing;
    if (kingAttacks(square) & king) return true;

    // Peón (color invertido, como acabas de deducir)
    uint64_t pawns = byWhite ? board.whitePawns : board.blackPawns;
    if (pawnAttacks(square, !byWhite) & pawns) return true;

    // Torre / Dama (movimiento recto)
    uint64_t rooksQueens = byWhite ? (board.whiteRooks | board.whiteQueens) : (board.blackRooks | board.blackQueens);
    if (rookAttacks(square, occupied) & rooksQueens) return true;

    // Alfil / Dama (movimiento diagonal)
    uint64_t bishopsQueens = byWhite ? (board.whiteBishops | board.whiteQueens) : (board.blackBishops | board.blackQueens);
    if (bishopAttacks(square, occupied) & bishopsQueens) return true;

    return false;
}

bool isKingInCheck(const Board& board, bool whiteKing) {
    uint64_t king = whiteKing ? board.whiteKing : board.blackKing;

    unsigned long kingSquare;
    _BitScanForward64(&kingSquare, king);

    return isSquareAttacked(board, kingSquare, !whiteKing);
}

Board makeMove(const Board& board, const Move& m) {
    Board newBoard = board;

    uint64_t fromBit = 1ULL << m.from;
    uint64_t toBit = 1ULL << m.to;

    // Mover la pieza en su bitboard correspondiente
    switch (m.piece) {
    case PAWN:
        if (newBoard.whiteToMove) { newBoard.whitePawns &= ~fromBit; newBoard.whitePawns |= toBit; }
        else { newBoard.blackPawns &= ~fromBit; newBoard.blackPawns |= toBit; }
        break;
    case KNIGHT:
        if (newBoard.whiteToMove) { newBoard.whiteKnights &= ~fromBit; newBoard.whiteKnights |= toBit; }
        else { newBoard.blackKnights &= ~fromBit; newBoard.blackKnights |= toBit; }
        break;
    case BISHOP:
        if (newBoard.whiteToMove) { newBoard.whiteBishops &= ~fromBit; newBoard.whiteBishops |= toBit; }
        else { newBoard.blackBishops &= ~fromBit; newBoard.blackBishops |= toBit; }
        break;
    case ROOK:
        if (newBoard.whiteToMove) { newBoard.whiteRooks &= ~fromBit; newBoard.whiteRooks |= toBit; 
        if (m.from == 0) { newBoard.whiteCanCastleQueenside = false; } 
        if (m.from == 7) { newBoard.whiteCanCastleKingside = false; } 
        }
        else { newBoard.blackRooks &= ~fromBit; newBoard.blackRooks |= toBit; 
        if (m.from == 56) { newBoard.blackCanCastleQueenside = false; } 
        if (m.from == 63) { newBoard.blackCanCastleKingside = false; }
        }
        break;
    case QUEEN:
        if (newBoard.whiteToMove) { newBoard.whiteQueens &= ~fromBit; newBoard.whiteQueens |= toBit; }
        else { newBoard.blackQueens &= ~fromBit; newBoard.blackQueens |= toBit; }
        break;
    case KING:
        if (newBoard.whiteToMove) { 
            newBoard.whiteKing &= ~fromBit; newBoard.whiteKing |= toBit; 
            newBoard.whiteCanCastleKingside = false; newBoard.whiteCanCastleQueenside = false; 
        
            // Enroque corto
            if (m.from == 4 && m.to == 6){
                newBoard.whiteRooks &= ~(1ULL << 7);  // quita torre de h1
                newBoard.whiteRooks |= (1ULL << 5);   // pone la torre en f1
            }
            // Enroque largo
            if (m.from == 4 && m.to == 2) {
                newBoard.whiteRooks &= ~(1ULL << 0);  // quita torre de a1
                newBoard.whiteRooks |= (1ULL << 3);   // pone la torre en d1
            }
        
        }
        else { 
            newBoard.blackKing &= ~fromBit; newBoard.blackKing |= toBit; 
            newBoard.blackCanCastleKingside = false; newBoard.blackCanCastleQueenside = false;

            // Enroque corto
            if (m.from == 60 && m.to == 62) {
                newBoard.blackRooks &= ~(1ULL << 63);
                newBoard.blackRooks |= (1ULL << 61);
            }
            // Enroque largo
            if (m.from == 60 && m.to == 58) {
                newBoard.blackRooks &= ~(1ULL << 56);
                newBoard.blackRooks |= (1ULL << 59);
            }
        }
        break;
    }

    // Manejar captura: quitar la pieza rival de la casilla 'to'
    if (m.isCapture) {
        if (newBoard.whiteToMove) {
            // el rival es negro, apaga el bit 'to' en los 6 bitboards negros
            newBoard.blackPawns &= ~toBit;
            newBoard.blackKnights &= ~toBit;
            newBoard.blackBishops &= ~toBit;
            newBoard.blackRooks &= ~toBit;
            newBoard.blackQueens &= ~toBit;
            newBoard.blackKing &= ~toBit;

            // NUEVO: si capturaste la torre negra en su casilla original, pierde el enroque de ese lado
            if (m.to == 56) { newBoard.blackCanCastleQueenside = false; }
            if (m.to == 63) { newBoard.blackCanCastleKingside = false; }
        }
        else {
            newBoard.whitePawns &= ~toBit;
            newBoard.whiteKnights &= ~toBit;
            newBoard.whiteBishops &= ~toBit;
            newBoard.whiteRooks &= ~toBit;
            newBoard.whiteQueens &= ~toBit;
            newBoard.whiteKing &= ~toBit;

            if (m.to == 0) { newBoard.whiteCanCastleQueenside = false; }
            if (m.to == 7) { newBoard.whiteCanCastleKingside = false; }
        }
    }

    newBoard.whiteToMove = !newBoard.whiteToMove;


    return newBoard;
}

std::vector<Move> generateLegalMoves(const Board& board) {
    std::vector<Move> pseudoLegal = generateAllMoves(board);
    std::vector<Move> legal;

    for (const Move& m : pseudoLegal) {
        Board afterMove = makeMove(board, m);
        if (!isKingInCheck(afterMove,!afterMove.whiteToMove)) {
            legal.push_back(m);
        }
    }

    return legal;
}

// Tests para probar casos triviales
uint64_t perft(const Board& board, int depth) {
    if (depth == 0) {
        return 1;
    }

    std::vector<Move> legalMoves = generateLegalMoves(board);
    uint64_t count = 0;

    for (const Move& m : legalMoves) {
        
         Board afterMove = makeMove(board, m);
         count += perft(afterMove, depth - 1);
        
        /* Board afterMove = makeMove(board, m); — igual que ya hiciste antes en main.cpp para probar el 
        peón e2-e4, aquí aplicas el movimiento m sobre el tablero actual, y guardas el resultado en afterMove.
        - count += perft(afterMove, depth - 1); — aquí está la parte nueva: en vez de sumar 1, le preguntas a la
        propia función perft cuántas posiciones hay desde esta nueva posición, pero con un nivel menos de profundidad. 
        Esa llamada, a su vez, hará lo mismo (generará movimientos legales de afterMove, y por cada uno llamará
        de nuevo a perft con depth - 2), hasta que depth llegue a 0 — momento en el que el caso base (return 1;) 
        para la recursión y empieza a "sumar hacia atrás" todos los resultados */
    }

    return count;
}

int countBits(uint64_t bitBoard) {
    int count = 0;

    while (bitBoard) {
        count++;
        bitBoard &= (bitBoard - 1);
    }

    return count;
}

int evaluateBoard(const Board& board) {
    int whiteMaterial = countBits(board.whitePawns) * 1
        + countBits(board.whiteKnights) * 3
        + countBits(board.whiteBishops) * 3
        + countBits(board.whiteRooks) * 5
        + countBits(board.whiteQueens) * 9;

    int blackMaterial = countBits(board.blackPawns) * 1
        + countBits(board.blackKnights) * 3
        + countBits(board.blackBishops) * 3
        + countBits(board.blackRooks) * 5
        + countBits(board.blackQueens) * 9;

    return whiteMaterial - blackMaterial;
}

int minimax(const Board& board, int depth) {
    if (depth == 0) {
        return evaluateBoard(board);
    }

    std::vector<Move> legalMoves = generateLegalMoves(board);

    if (board.whiteToMove) {
        // Blancas MAXIMIZA: busca la jugada con mayor evaluación posible
        int best = INT_MIN;
        for (const Move& m : legalMoves) {
            Board afterMove = makeMove(board, m);
            int eval = minimax(afterMove, depth - 1);
            if (eval > best) {
                best = eval;
            }
        }
        return best;
    }
    else {
        // Negras MINIMIZA: busca la jugada con menor evaluación posible
        int best = INT_MAX;
        for (const Move& m : legalMoves) {
            Board afterMove = makeMove(board, m);
            int eval = minimax(afterMove, depth - 1);
            if (eval < best) {
                best = eval;
            }
        }
        return best;
    }
}

Move findBestMove(const Board& board, int depth) {
    std::vector<Move> legalMoves = generateLegalMoves(board);
    Move bestMove = legalMoves[0]; // por defecto, la primera, luego se sustituye

    if (board.whiteToMove) {
        int best = INT_MIN;
        for (const Move& m : legalMoves) {
            Board afterMove = makeMove(board, m);
            int eval = alphaBeta(afterMove, depth - 1, INT_MIN, INT_MAX);
            if (eval > best) {
                best = eval;
                bestMove = m;
            }
        }
    }
    else {
        int best = INT_MAX;
        for (const Move& m : legalMoves) {
            Board afterMove = makeMove(board, m);
            int eval = alphaBeta(afterMove, depth - 1, INT_MIN, INT_MAX);
            if (eval < best) {
                best = eval;
                bestMove = m;
            }
        }
    }

    return bestMove;
}

int alphaBeta(const Board& board, int depth, int alpha, int beta) {
    if (depth == 0) {
        return evaluateBoard(board);
    }

    std::vector<Move> legalMoves = generateLegalMoves(board);

    if (board.whiteToMove) {
        int best = INT_MIN;
        for (const Move& m : legalMoves) {
            Board afterMove = makeMove(board, m);
            int eval = alphaBeta(afterMove, depth - 1, alpha, beta);
            if (eval > best) {
                best = eval;
            }
            if (best > alpha) {
                alpha = best; // actualizamos "lo mejor que blancas tiene garantizado"
            }
            if (alpha >= beta) {
                break; // esta rama ya no puede mejorar el resultado, cortamos
            }
        }
        return best;
    }

    else {
        int best = INT_MAX;
        for (const Move& m : legalMoves) {
            Board afterMove = makeMove(board, m);
            int eval = alphaBeta(afterMove, depth - 1, alpha, beta);
            if (eval < best) {
                best = eval;
            }
            if (best < beta) {
                beta = best;
            }
            if (alpha >= beta) {
                break;
            }
        }
        return best;
    }
}

void generateCastlingMoves(const Board& board, std::vector<Move>& moves) {
    uint64_t occupied = getAllPieces(board);

    if (board.whiteToMove) {
        // Enroque corto blanco
        if (board.whiteCanCastleKingside) {
            bool squaresEmpty = !getBit(occupied, 5) && !getBit(occupied, 6);
            bool notInCheck = !isKingInCheck(board, true);
            bool pathSafe = !isSquareAttacked(board, 5, false) && !isSquareAttacked(board, 6, false);

            if (squaresEmpty && notInCheck && pathSafe) {
                Move m;
                m.from = 4;
                m.to = 6;
                m.isCapture = false;
                m.piece = KING;
                moves.push_back(m);
            }
        }

        // Enroque largo blanco
        if (board.whiteCanCastleQueenside) {
            bool squaresEmpty = !getBit(occupied, 1) && !getBit(occupied, 2) && !getBit(occupied, 3);
            bool notInCheck = !isKingInCheck(board, true);
            bool pathSafe = !isSquareAttacked(board, 2, false) && !isSquareAttacked(board, 3, false);

            if (squaresEmpty && notInCheck && pathSafe) {
                Move m;
                m.from = 4;
                m.to = 2;
                m.isCapture = false;
                m.piece = KING;
                moves.push_back(m);
            }
        }
    }
    // Turno de negras 
    else {
        if (board.blackCanCastleKingside) {
            bool squaresEmpty = !getBit(occupied, 61) && !getBit(occupied, 62);
            bool notInCheck = !isKingInCheck(board, false);
            bool pathSafe = !isSquareAttacked(board, 61, true) && !isSquareAttacked(board, 62, true);

            if (squaresEmpty && notInCheck && pathSafe) {
                Move m;
                m.from = 60;
                m.to = 62;
                m.isCapture = false;
                m.piece = KING;
                moves.push_back(m);
            }
        }

        if (board.blackCanCastleQueenside) {
            bool squaresEmpty = !getBit(occupied, 57) && !getBit(occupied, 58) && !getBit(occupied, 59);
            bool notInCheck = !isKingInCheck(board, false);
            bool pathSafe = !isSquareAttacked(board, 58, true) && !isSquareAttacked(board, 59, true);

            if (squaresEmpty && notInCheck && pathSafe) {
                Move m;
                m.from = 60;
                m.to = 58;
                m.isCapture = false;
                m.piece = KING;
                moves.push_back(m);
            }
        }
    }
}