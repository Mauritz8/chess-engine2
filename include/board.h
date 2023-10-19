#ifndef BOARD_H
#define BOARD_H

#include "square.h"
#include <array>
#include <memory>
#include <optional>
#include <string>
#include <vector>

struct Pos {
    int x;
    int y;
};
bool operator==(const Pos& pos1, const Pos& pos2);

struct Castling {
    bool kingside;
    bool queenside;
};

struct GameState {
    Color player_to_move;
    std::optional<Pos> en_passant_square;
    std::array<Castling, 2> castling_rights;
    std::array<std::vector<std::shared_ptr<Piece>>, 2> pieces;
};

class Board {
    public:
        GameState game_state;
        std::vector<GameState> history;

        Board() {}
        Board(const Board& board);

        static Board get_empty_board();
        static Board get_starting_position();
        static Board get_position_from_fen(std::string fen);
        
        const Square& get_square(int x, int y) const;
        Square& get_square(int x, int y);
        void set_square(int x, int y, std::shared_ptr<Piece> piece);

        void show() const;
        void switch_player_to_move();
        void remove_piece(std::shared_ptr<Piece> piece);

    private:
        std::vector<std::vector<Square>> squares;

        void place_pieces(const std::string& fen_piece_placement_field);
        void set_player_to_move(const std::string& fen_active_color_field);
        void set_castling_rights(const std::string& fen_castling_field);
        void set_en_passant_square(const std::string& fen_en_passant_field);
};

#endif
