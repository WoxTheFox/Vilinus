#pragma once

#include "types.h"
#include "bitboard.h"

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
};