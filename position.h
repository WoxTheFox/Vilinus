#pragma once

#include <cctype>
#include <string>

#include "types.h"
#include "bitboard.h"


inline bool fenToFigure(char fen, Color& color, PieceType& pieceType)
{
    if (isupper(fen)) {color = WHITE;}
    else {color = BLACK;}

    switch (tolower(fen))
    {
        case 'p':
            pieceType = PAWN;
            return true;
        case 'n':
            pieceType = KNIGHT;
            return true;
        case 'b':
            pieceType = BISHOP;
            return true;
        case 'r':
            pieceType = ROOK;
            return true;
        case 'q':
            pieceType = QUEEN;
            return true;
        case 'k':
            pieceType = KING;
            return true;
        default:
            return false;
    }
}

struct Position
{
    Bitboard pieces[2][6] = {};
    Bitboard occupancy[3] = {};
    Color onMove = WHITE;
    Square enPassant = NO_SQUARE;
    int moveCount = 1;
    int moveCount50Rule = 0;
    uint8_t castlingRights = 0;

    void updateOccupancy()
    {
        occupancy[WHITE] = 0;
        occupancy[BLACK] = 0;

        for (int i = 0; i < 6; i++)
        {
            occupancy[WHITE] |= pieces[WHITE][i];
            occupancy[BLACK] |= pieces[BLACK][i];
        }
        occupancy[BOTH] = occupancy[WHITE] | occupancy[BLACK];

    }
    
    void loadFen(const std::string& fen)
    {
        *this = Position{};

        int rank = 7;
        int file = 0;
        for (char fenChar : fen)
        {
            if (fenChar == ' ') { break; }
            else if (fenChar == '/') { rank--; file = 0; }
            else if (isdigit(fenChar)) { file += fenChar - '0'; }
            else
            {
                Color color;
                PieceType pieceType;

                if (fenToFigure(fenChar, color, pieceType))
                {
                    setBit(pieces[color][pieceType], makeSquare(file, rank));
                    file++;
                }
            }

        }
        updateOccupancy();
    }
};