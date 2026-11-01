#pragma once
#include "types.h"

inline Bitboard KNIGHT_ATTACKS[64] = {};
inline Bitboard KING_ATTACKS[64] = {};
inline Bitboard PAWN_ATTACKS[2][64] = {};

[[nodiscard]] constexpr Bitboard knightAttacks(Square sq) noexcept
{
    Bitboard standing = {};
    Bitboard attacks = {};

    setBit(standing, sq);

    attacks |= (standing << 17) & NOT_A_FILE;
    attacks |= (standing << 15) & NOT_H_FILE;
    attacks |= (standing << 10) & NOT_AB_FILE;
    attacks |= (standing << 6) & NOT_GH_FILE;

    attacks |= (standing >> 17) & NOT_H_FILE;
    attacks |= (standing >> 15) & NOT_A_FILE;
    attacks |= (standing >> 10) & NOT_GH_FILE;
    attacks |= (standing >> 6) & NOT_AB_FILE;

    return attacks;
}

[[nodiscard]] constexpr Bitboard kingAttacks(Square sq) noexcept
{
    Bitboard standing = {};
    Bitboard attacks = {};

    setBit(standing, sq);

    attacks |= (standing << 9) & NOT_A_FILE;
    attacks |= (standing << 8);
    attacks |= (standing << 7) & NOT_H_FILE;
    attacks |= (standing << 1) & NOT_A_FILE;

    attacks |= (standing >> 9) & NOT_H_FILE;
    attacks |= (standing >> 8);
    attacks |= (standing >> 7) & NOT_A_FILE;
    attacks |= (standing >> 1) & NOT_H_FILE;

    return attacks;
}

[[nodiscard]] constexpr Bitboard pawnAttacks(Square sq, Color color) noexcept
{
    Bitboard standing = {};
    Bitboard attacks = {};

    setBit(standing, sq);

    if (color == WHITE)
    {
        attacks |= (standing << 9) & NOT_A_FILE;
        attacks |= (standing << 7) & NOT_H_FILE;
    }
    else
    {
        attacks |= (standing >> 9) & NOT_H_FILE;
        attacks |= (standing >> 7) & NOT_A_FILE;
    }

    return attacks;
}

[[nodiscard]] constexpr Bitboard slidingAttacks(const Square sq, const Bitboard occupancy, const int directions[4][2]) noexcept
{
    const int rank = rankOf(sq);
    const int file = fileOf(sq);
    Bitboard attacks = {};

    for (int i = 0; i < 4; i++)
    {
        const int dr = directions[i][0];
        const int df = directions[i][1];

        for (int r = rank + dr, f = file + df; 0 <= r && r < 8 && 0 <= f && f < 8; r += dr, f += df)
        {
            const Square target = makeSquare(f, r);
            setBit(attacks, target);

            if (getBit(occupancy, target)) {break;}
        }
    }
    return attacks;
}
[[nodiscard]] constexpr Bitboard rookAttacks(const Square sq, const Bitboard occupancy) noexcept
{
    return slidingAttacks(sq, occupancy, ROOK_DIRECTIONS);
}

[[nodiscard]] constexpr Bitboard bishopAttacks(const Square sq, const Bitboard occupancy) noexcept
{
    return slidingAttacks(sq, occupancy, BISHOP_DIRECTIONS);
}

[[nodiscard]] constexpr Bitboard queenAttacks(const Square sq, const Bitboard occupancy) noexcept
{
    return rookAttacks(sq, occupancy) | bishopAttacks(sq, occupancy);
}


inline void initAttacks() noexcept
{
    for (int i = 0; i < 64; i++)
    {
        const auto sq = static_cast<Square>(i);

        KNIGHT_ATTACKS[i] = knightAttacks(sq);
        KING_ATTACKS[i] = kingAttacks(sq);
        PAWN_ATTACKS[WHITE][i] = pawnAttacks(sq, WHITE);
        PAWN_ATTACKS[BLACK][i] = pawnAttacks(sq, BLACK);
    }
}

[[nodiscard]] inline Bitboard pieceAttacks(PieceType type, Square sq, const Bitboard occupancy) noexcept
{
    switch (type)
    {
        case KNIGHT:
            return KNIGHT_ATTACKS[sq];
        case BISHOP:
            return bishopAttacks(sq, occupancy);
        case ROOK:
            return rookAttacks(sq, occupancy);
        case QUEEN:
            return queenAttacks(sq, occupancy);
        case KING:
            return KING_ATTACKS[sq];
        default:
            return 0;
    }
}
