#ifndef BOARD_H
#define BOARD_H

#include "square.h"
#include <array>
#include <optional>
#include <string>
#include <vector>

struct Pos {
    int x;
    int y;
};

struct Castling {
    bool kingside;
    bool queenside;
};

struct GameState {
    Color player_to_move;
    std::optional<Pos> en_passant_square;
    std::array<Castling, 2> castling_rights;
};

class Board {
    public:
        GameState game_state;
        std::vector<GameState> history;

        Board() {}

        static Board get_empty_board();
        static Board get_starting_position();
        static Board get_position_from_fen(std::string fen);
        
        const Square& get_square(int x, int y) const;
        Square& get_square(int x, int y);
        void set_square(int x, int y, std::shared_ptr<Piece> piece);

        void show() const;
        void switch_player_to_move();

    private:
        std::vector<std::vector<Square>> squares;

        void place_pieces(const std::string& fen_piece_placement_field);
        void set_player_to_move(const std::string& fen_active_color_field);
        void set_castling_rights(const std::string& fen_castling_field);
};

#endif
