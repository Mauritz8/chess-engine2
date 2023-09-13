#ifndef BOARD_H
#define BOARD_H

#include "square.h"
#include <array>
#include <optional>
#include <string>
#include <vector>

class Board {
    private:
        std::vector<std::vector<Square>> squares;
        Color player_to_move;

        void setup_pieces(int row, std::vector<Piece_type> order, Color color);
        void setup_pawns(int row, Color color);
        int place_pieces(const std::string fen_piece_placement_field);
        int set_player_to_move(const std::string fen_active_color_field);

    public:
        Board() {}

        static Board get_empty_board();
        static Board get_starting_position();
        static Board get_position_from_fen(std::string fen);
        

        const Square& get_square(int x, int y) const { 
            return squares.at(y).at(x); 
        }
        Square& get_square(int x, int y) { 
            return squares.at(y).at(x); 
        }

        void set_square(int x, int y, const std::optional<Piece> piece) {
            Square& square = squares.at(y).at(x); 
            square.set_piece(piece);
        }

        Color get_player_to_move() const { 
            return player_to_move; 
        }
        void set_player_to_move(Color player_to_move) { 
            this->player_to_move = player_to_move; 
        }

        void show_board() const;
};

#endif
