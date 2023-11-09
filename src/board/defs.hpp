#include <array>

#include "move.hpp"
#include "piece.hpp"


struct Castling {
    bool kingside;
    bool queenside;
};

struct GameState {
    Color player_to_move;
    std::array<Castling, 2> castling_rights;
    std::optional<int> en_passant_square;
    int halfmove_clock;
    int fullmove_number;
    std::array<int, 2> material;
    std::array<int, 2> psqt;
    std::optional<Piece> captured_piece;
    Move next_move;
};
