#pragma once
#include <bit>
#include <cstdint>

using Bitboard = uint64_t;
enum Color {WHITE, BLACK};
enum PieceType {PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING};
constexpr Bitboard RANK_1 = 0xFFULL;
constexpr Bitboard RANK_2 = RANK_1 << 8;
constexpr Bitboard RANK_3 = RANK_1 << 16;
constexpr Bitboard RANK_4 = RANK_1 << 24;
constexpr Bitboard RANK_5 = RANK_1 << 32;
constexpr Bitboard RANK_6 = RANK_1 << 40;
constexpr Bitboard RANK_7 = RANK_1 << 48;
constexpr Bitboard RANK_8 = RANK_1 << 56;

constexpr Bitboard FILE_A = 0x0101010101010101ULL;
constexpr Bitboard FILE_B = FILE_A << 1;
constexpr Bitboard FILE_C = FILE_A << 2;
constexpr Bitboard FILE_D = FILE_A << 3;
constexpr Bitboard FILE_E = FILE_A << 4;
constexpr Bitboard FILE_F = FILE_A << 5;
constexpr Bitboard FILE_G = FILE_A << 6;
constexpr Bitboard FILE_H = FILE_A << 7;

static_assert(RANK_8 == 0xFF00000000000000ULL);
static_assert(FILE_H == 0x8080808080808080ULL, "FILE_H jest niepoprawnie zdefiniowanie");

enum Square
{   A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    NO_SQUARE
};

constexpr Square makeSquare(int file, int rank) { return Square(rank * 8 + file); }

constexpr void setBit(Bitboard& bb, Square sq) { bb |= 1ULL << sq; }

constexpr bool getBit(Bitboard bb, Square sq) { return bb & (1ULL << sq); }

constexpr void popBit(Bitboard& bb, Square sq) { bb &= ~(1ULL << sq); }

constexpr int popCount(Bitboard bb) { return std::popcount(bb); }

constexpr Square lsb(Bitboard bb) { return Square(std::countr_zero(bb)); }

constexpr Square popLsb(Bitboard& bb)
{
    Square sq = lsb(bb);
    bb &= bb - 1;
    return sq;
}





