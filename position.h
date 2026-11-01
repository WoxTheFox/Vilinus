#pragma once

#include <cctype>
#include <string>
#include <sstream>

#include "types.h"

[[nodiscard]] inline bool fenToFigure(char fen, Color& color, PieceType& pieceType) noexcept
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
    unsigned int moveCount = 1;
    unsigned int moveCount50Rule = 0;
    uint8_t castlingRights = 0;

    void updateOccupancy() noexcept
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

        std::istringstream ss(fen);

        std::string placing;
        std::string side;
        std::string castling;
        std::string passant;

        int rank = 7;
        int file = 0;

        ss >> placing >> side >> castling >> passant >> moveCount50Rule >> moveCount;

        for (const char place : placing)
        {
            if (place == '/') { rank--; file = 0; }
            else if (isdigit(place)) { file += place - '0'; }
            else
            {
                Color color;
                PieceType pieceType;

                if (fenToFigure(place, color, pieceType))
                {
                    setBit(pieces[color][pieceType], makeSquare(file, rank));
                    file++;
                }
            }
        }

        onMove = side == "w" ? WHITE : BLACK;

        for (const char castle : castling)
        {
            switch (castle)
            {
                case 'K':
                    castlingRights |= SHORT_WHITE;
                    break;
                case 'Q':
                    castlingRights |= LONG_WHITE;
                    break;
                case 'k':
                    castlingRights |= SHORT_BLACK;
                    break;
                case 'q':
                    castlingRights |= LONG_BLACK;
                    break;
                default: ;
            }
        }

        if (passant != "-")
        {
            const int col = passant[0] - 'a';
            const int row = passant[1] - '1';

            enPassant = makeSquare(col, row);
        }

        updateOccupancy();
    }
};