#include <functional>
#include <iostream>
#include <limits.h>
#include <memory>
#include <optional>
#include <vector>

#include "board.h"
#include "engine/engine.h"
#include "game_state.h"
#include "move.h"
#include "piece.h"
#include "pieces/bishop.h"
#include "pieces/king.h"
#include "pieces/knight.h"
#include "pieces/pawn.h"
#include "pieces/queen.h"
#include "pieces/rook.h"


static PieceCounts get_piece_counts(const Board& board, Color color) {
    PieceCounts piece_counts = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            const std::shared_ptr<Piece>& piece = board.get_square(j, i).get_piece();
            if (!piece || piece->get_color() != color) {
                continue;
            }

            if (dynamic_cast<King*>(piece.get()) != nullptr) {
                piece_counts.kings++; 
            }  else if (dynamic_cast<Queen*>(piece.get()) != nullptr) {
                piece_counts.queens++;
            }  else if (dynamic_cast<Rook*>(piece.get()) != nullptr) {
                piece_counts.rooks++;
            }  else if (dynamic_cast<Bishop*>(piece.get()) != nullptr) {
                piece_counts.bishops++;
            }  else if (dynamic_cast<Knight*>(piece.get()) != nullptr) {
                piece_counts.knights++;
            }  else if (dynamic_cast<Pawn*>(piece.get()) != nullptr) {
                piece_counts.pawns++;
            }
        }
    }
    return piece_counts;
}

static int get_material_score(const Board& board) {
    const PieceCounts player_piece_counts = get_piece_counts(board, board.get_player_to_move());

    const Color opponent_color = get_opposite_color(board.get_player_to_move());
    const PieceCounts opponent_piece_counts = get_piece_counts(board, opponent_color);

    return KING_SCORE * (player_piece_counts.kings - opponent_piece_counts.kings) +
           QUEEN_SCORE * (player_piece_counts.queens - opponent_piece_counts.queens) +
           ROOK_SCORE * (player_piece_counts.rooks - opponent_piece_counts.rooks) +
           BISHOP_SCORE * (player_piece_counts.bishops - opponent_piece_counts.bishops) +
           KNIGHT_SCORE * (player_piece_counts.knights - opponent_piece_counts.knights) +
           PAWN_SCORE * (player_piece_counts.pawns - opponent_piece_counts.pawns);
}

static int get_piece_square_tables_values(const Board& board) {
    const Color player_to_move = board.get_player_to_move();
    const Color opponent = get_opposite_color(board.get_player_to_move());
    const auto white_pieces = get_all_pieces(WHITE, board);
    const auto black_pieces = get_all_pieces(BLACK, board);

    int white_score = 0;
    for (const std::shared_ptr<Piece> piece : white_pieces) {
        int value = piece->get_piece_square_table().at(piece->get_y()).at(piece->get_x()); 
        white_score += value;
    }
    int black_score = 0;
    for (const std::shared_ptr<Piece> piece : black_pieces) {
        int value = piece->get_piece_square_table().at(7 - piece->get_y()).at(piece->get_x()); 
        black_score += value;
    }

    if (board.get_player_to_move() == WHITE) {
        return white_score - black_score;
    }
    return black_score - white_score;
}

static double evaluate(const Board& board) {
    const int material_score = get_material_score(board);
    const double piece_square_tables_score = 0.01 * get_piece_square_tables_values(board);
    const double score = material_score + piece_square_tables_score;
    return score;
}

static double nega_max(int depth, Board& board, std::vector<Move>& move_history) {
    if (depth == 0) {
        return evaluate(board);
    }
    double max = INT_MIN;
    std::vector<Move> legal_moves = get_all_legal_moves(board, move_history);
    for (int i = 0; i < legal_moves.size(); i++) {
        Move move = legal_moves.at(i);
        move.make_appropriate(board, move_history);
        const double score = -nega_max(depth - 1, board, move_history);
        move.undo_appropriate(board, move_history);
        if (score > max) {
            max = score;
        }
    }
    return max;
}

Move get_best_move(int depth, const Board& board, const std::vector<Move>& move_history) {
    Board board_copy = board;
    std::vector<Move> move_history_copy = move_history;

    double max = INT_MIN;
    const std::vector<Move> legal_moves = get_all_legal_moves(board_copy, move_history_copy);
    const Move* best_move = nullptr;
    for (int i = 0; i < legal_moves.size(); i++) {
        Move move = legal_moves.at(i);
        move.make_appropriate(board_copy, move_history_copy);
        const double score = -nega_max(depth - 1, board_copy, move_history_copy);
        move.undo_appropriate(board_copy, move_history_copy);
        if (score > max) {
            max = score;
            best_move = &legal_moves.at(i);
        }
    }
    return *best_move;
}


int perft(int depth, Board board, std::vector<Move> move_history) {
    if (depth == 0) {
        return 1;
    }

    int nodes = 0;
    const std::vector<Move> move_list = get_all_legal_moves(board, move_history);
    for (int i = 0; i < move_list.size(); i++) {
        Move move = move_list.at(i);
        move.make_appropriate(board, move_history);
        nodes += perft(depth - 1, board, move_history);    
        move.undo_appropriate(board, move_history);
    }
    return nodes;
}

void divide(int depth, Board board, std::vector<Move> move_history) {
    std::cout << "";
    int nodes_searched = 0;
    const std::vector<Move> move_list = get_all_legal_moves(board, move_history);
    for (int i = 0; i < move_list.size(); i++) {
        Move move = move_list.at(i);
        move.make_appropriate(board, move_history);
        const int nodes = perft(depth - 1, board, move_history);
        nodes_searched += nodes;
        std::cout << move.to_uci_notation() << ": " << nodes << "\n";
        move.undo_appropriate(board, move_history);
    }
    std::cout << "\nNodes searched: " << nodes_searched << "\n";
}
