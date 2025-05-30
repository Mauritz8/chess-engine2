#include "board/board.hpp"
#include "defs.hpp"
#include "evaluation/evaluation.hpp"
#include "fen.hpp"
#include "move.hpp"
#include <gtest/gtest.h>

TEST(MoveTests, KnightMoveTest) {
  Board board = Board::get_starting_position();

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start = g1;
  int end = f3;
  Move move(start, end);
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), KNIGHT);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(start).has_value());
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), KNIGHT);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 1);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  int white_psqt_new = white_psqt -
                       get_psqt_score(KNIGHT, start, WHITE, false, false) +
                       get_psqt_score(KNIGHT, end, WHITE, false, false);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), KNIGHT);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, BishopMoveTest) {
  Board board = fen::get_position(
      "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start = e2;
  int end = c4;
  Move move(start, end);
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), BISHOP);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(start).has_value());
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), BISHOP);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 1);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  int white_psqt_new = white_psqt -
                       get_psqt_score(BISHOP, start, WHITE, false, false) +
                       get_psqt_score(BISHOP, end, WHITE, false, false);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), BISHOP);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, RookMoveTest) {
  Board board = fen::get_position(
      "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start = a1;
  int end = d1;
  Move move(start, end);
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), ROOK);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(start).has_value());
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), ROOK);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 1);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  int white_psqt_new = white_psqt -
                       get_psqt_score(ROOK, start, WHITE, false, false) +
                       get_psqt_score(ROOK, end, WHITE, false, false);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), ROOK);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, QueenMoveTest) {
  Board board = fen::get_position(
      "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start = f3;
  int end = f4;
  Move move(start, end);
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), QUEEN);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(start).has_value());
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), QUEEN);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 1);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  int white_psqt_new = white_psqt -
                       get_psqt_score(QUEEN, start, WHITE, false, false) +
                       get_psqt_score(QUEEN, end, WHITE, false, false);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), QUEEN);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, CaptureMoveTest) {
  Board board = fen::get_position(
      "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start = e5;
  int end = g6;
  Move move(start, end);
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), KNIGHT);
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), PAWN);

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(start).has_value());
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), KNIGHT);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_TRUE(board.get_captured_piece().has_value());
  EXPECT_EQ(board.get_captured_piece().value(), Piece(PAWN, BLACK, end));

  EXPECT_EQ(board.get_material(BLACK), black_material - PAWN_VALUE);
  EXPECT_EQ(board.get_psqt(BLACK),
            black_psqt - get_psqt_score(PAWN, end, BLACK, false, false));
  EXPECT_EQ(board.get_material(WHITE), white_material);
  int white_psqt_new = white_psqt -
                       get_psqt_score(KNIGHT, start, WHITE, false, false) +
                       get_psqt_score(KNIGHT, end, WHITE, false, false);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), KNIGHT);
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), PAWN);

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, KingMoveTest) {
  Board board = fen::get_position(
      "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start = e1;
  int end = f1;
  Move move(start, end);
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), KING);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(start).has_value());
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), KING);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 1);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  int white_psqt_new = white_psqt -
                       get_psqt_score(KING, start, WHITE, false, false) +
                       get_psqt_score(KING, end, WHITE, false, false);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), KING);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, CastlingKingsideTest) {
  Board board = fen::get_position(
      "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int king_start = e1;
  int king_end = g1;
  int rook_start = h1;
  int rook_end = f1;
  Move move(king_start, king_end, CASTLING);
  EXPECT_TRUE(board.get_piece_type(king_start).has_value());
  EXPECT_EQ(board.get_piece_type(king_start).value(), KING);
  EXPECT_FALSE(board.get_piece_type(king_end).has_value());
  EXPECT_TRUE(board.get_piece_type(rook_start).has_value());
  EXPECT_EQ(board.get_piece_type(rook_start).value(), ROOK);
  EXPECT_FALSE(board.get_piece_type(rook_end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(king_start).has_value());
  EXPECT_TRUE(board.get_piece_type(king_end).has_value());
  EXPECT_EQ(board.get_piece_type(king_end).value(), KING);
  EXPECT_FALSE(board.get_piece_type(rook_start).has_value());
  EXPECT_TRUE(board.get_piece_type(rook_end).has_value());
  EXPECT_EQ(board.get_piece_type(rook_end).value(), ROOK);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 1);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  int white_psqt_new = white_psqt -
                       get_psqt_score(KING, king_start, WHITE, false, false) +
                       get_psqt_score(KING, king_end, WHITE, false, false) -
                       get_psqt_score(ROOK, rook_start, WHITE, false, false) +
                       get_psqt_score(ROOK, rook_end, WHITE, false, false);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(king_start).has_value());
  EXPECT_EQ(board.get_piece_type(king_start).value(), KING);
  EXPECT_FALSE(board.get_piece_type(king_end).has_value());
  EXPECT_TRUE(board.get_piece_type(rook_start).has_value());
  EXPECT_EQ(board.get_piece_type(rook_start).value(), ROOK);
  EXPECT_FALSE(board.get_piece_type(rook_end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, CastlingQueensideTest) {
  Board board = fen::get_position(
      "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int king_start = e1;
  int king_end = c1;
  int rook_start = a1;
  int rook_end = d1;
  Move move(king_start, king_end, CASTLING);
  EXPECT_TRUE(board.get_piece_type(king_start).has_value());
  EXPECT_EQ(board.get_piece_type(king_start).value(), KING);
  EXPECT_FALSE(board.get_piece_type(king_end).has_value());
  EXPECT_TRUE(board.get_piece_type(rook_start).has_value());
  EXPECT_EQ(board.get_piece_type(rook_start).value(), ROOK);
  EXPECT_FALSE(board.get_piece_type(rook_end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(king_start).has_value());
  EXPECT_TRUE(board.get_piece_type(king_end).has_value());
  EXPECT_EQ(board.get_piece_type(king_end).value(), KING);
  EXPECT_FALSE(board.get_piece_type(rook_start).has_value());
  EXPECT_TRUE(board.get_piece_type(rook_end).has_value());
  EXPECT_EQ(board.get_piece_type(rook_end).value(), ROOK);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 1);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  int white_psqt_new = white_psqt -
                       get_psqt_score(KING, king_start, WHITE, false, false) +
                       get_psqt_score(KING, king_end, WHITE, false, false) -
                       get_psqt_score(ROOK, rook_start, WHITE, false, false) +
                       get_psqt_score(ROOK, rook_end, WHITE, false, false);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(king_start).has_value());
  EXPECT_EQ(board.get_piece_type(king_start).value(), KING);
  EXPECT_FALSE(board.get_piece_type(king_end).has_value());
  EXPECT_TRUE(board.get_piece_type(rook_start).has_value());
  EXPECT_EQ(board.get_piece_type(rook_start).value(), ROOK);
  EXPECT_FALSE(board.get_piece_type(rook_end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, PawnMoveOneSquareTest) {
  Board board = Board::get_starting_position();

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start = e2;
  int end = e3;
  Move move(start, end);
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), PAWN);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(start).has_value());
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), PAWN);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  int white_psqt_new = white_psqt -
                       get_psqt_score(PAWN, start, WHITE, false, false) +
                       get_psqt_score(PAWN, end, WHITE, false, false);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), PAWN);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, PawnMoveTwoSquaresTest) {
  Board board = Board::get_starting_position();

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start = d2;
  int end = d4;
  Move move(start, end, PAWN_TWO_SQUARES_FORWARD);
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), PAWN);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(start).has_value());
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), PAWN);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_TRUE(board.get_en_passant_square().has_value());
  EXPECT_EQ(board.get_en_passant_square().value(), d3);
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  int white_psqt_new = white_psqt -
                       get_psqt_score(PAWN, start, WHITE, false, false) +
                       get_psqt_score(PAWN, end, WHITE, false, false);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), PAWN);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, PawnCaptureMoveTest) {
  Board board = fen::get_position("2k5/8/4p3/3P4/8/2K5/8/8 b - - 0 1");

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start = e6;
  int end = d5;
  Move move(start, end);
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), PAWN);
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), PAWN);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(start).has_value());
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), PAWN);

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 2);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_TRUE(board.get_captured_piece().has_value());
  EXPECT_EQ(board.get_captured_piece().value(), Piece(PAWN, WHITE, end));

  EXPECT_EQ(board.get_material(WHITE), white_material - PAWN_VALUE);
  EXPECT_EQ(board.get_psqt(WHITE),
            white_psqt - get_psqt_score(PAWN, end, WHITE, false, false));
  EXPECT_EQ(board.get_material(BLACK), black_material);
  int black_psqt_new = black_psqt -
                       get_psqt_score(PAWN, start, BLACK, false, false) +
                       get_psqt_score(PAWN, end, BLACK, false, false);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), PAWN);
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), PAWN);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, EnPassantTest) {
  Board board = fen::get_position("2k5/4p3/8/3P4/8/2K5/8/8 b - - 0 1");

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start1 = e7;
  int end1 = e5;
  Move move1(start1, end1, PAWN_TWO_SQUARES_FORWARD);
  EXPECT_TRUE(board.get_piece_type(start1).has_value());
  EXPECT_EQ(board.get_piece_type(start1).value(), PAWN);
  EXPECT_FALSE(board.get_piece_type(end1).has_value());

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move1);
  EXPECT_FALSE(board.get_piece_type(start1).has_value());
  EXPECT_TRUE(board.get_piece_type(end1).has_value());
  EXPECT_EQ(board.get_piece_type(end1).value(), PAWN);

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 2);
  EXPECT_TRUE(board.get_en_passant_square().has_value());
  EXPECT_EQ(board.get_en_passant_square().value(), e6);
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
  EXPECT_EQ(board.get_material(BLACK), black_material);
  int black_psqt_new = black_psqt -
                       get_psqt_score(PAWN, start1, BLACK, false, false) +
                       get_psqt_score(PAWN, end1, BLACK, false, false);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt_new);

  int start2 = d5;
  int end2 = d6;
  Move move2(start2, end2, EN_PASSANT);
  EXPECT_TRUE(board.get_piece_type(start2).has_value());
  EXPECT_EQ(board.get_piece_type(start2).value(), PAWN);
  EXPECT_FALSE(board.get_piece_type(end2).has_value());

  board.make(move2);
  EXPECT_FALSE(board.get_piece_type(start2).has_value());
  EXPECT_TRUE(board.get_piece_type(end2).has_value());
  EXPECT_EQ(board.get_piece_type(end2).value(), PAWN);
  EXPECT_FALSE(board.get_piece_type(end1).has_value());

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 2);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_TRUE(board.get_captured_piece().has_value());
  EXPECT_EQ(board.get_captured_piece().value(), Piece(PAWN, BLACK, end1));

  EXPECT_EQ(board.get_material(BLACK), black_material - PAWN_VALUE);
  EXPECT_EQ(board.get_psqt(BLACK),
            black_psqt - get_psqt_score(PAWN, start1, BLACK, false, false));
  EXPECT_EQ(board.get_material(WHITE), white_material);
  int white_psqt_new = white_psqt -
                       get_psqt_score(PAWN, start2, WHITE, false, false) +
                       get_psqt_score(PAWN, end2, WHITE, false, false);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start2).has_value());
  EXPECT_EQ(board.get_piece_type(start2).value(), PAWN);
  EXPECT_FALSE(board.get_piece_type(end2).has_value());
  EXPECT_TRUE(board.get_piece_type(end1).has_value());
  EXPECT_EQ(board.get_piece_type(end1).value(), PAWN);

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 2);
  EXPECT_TRUE(board.get_en_passant_square().has_value());
  EXPECT_EQ(board.get_en_passant_square().value(), e6);
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt_new);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start1).has_value());
  EXPECT_EQ(board.get_piece_type(start1).value(), PAWN);
  EXPECT_FALSE(board.get_piece_type(end1).has_value());

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, PromotionMoveTest) {
  Board board = fen::get_position("8/8/8/4k3/8/8/6p1/3K1N2 b - - 0 1");

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start = g2;
  int end = g1;
  PieceType promotion_piece = QUEEN;
  Move move(start, end, promotion_piece);
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), PAWN);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(start).has_value());
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), promotion_piece);

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 2);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
  EXPECT_EQ(board.get_material(BLACK),
            black_material - PAWN_VALUE + get_piece_value(promotion_piece));
  int black_psqt_new =
      black_psqt - get_psqt_score(PAWN, start, BLACK, false, false) +
      get_psqt_score(promotion_piece, end, BLACK, false, false);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), PAWN);
  EXPECT_FALSE(board.get_piece_type(end).has_value());

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}

TEST(MoveTests, PromotionCaptureMoveTest) {
  Board board = fen::get_position("8/8/8/4k3/8/8/6p1/3K1N2 b - - 0 1");

  int white_material = board.get_material(WHITE);
  int white_psqt = board.get_psqt(WHITE);
  int black_material = board.get_material(BLACK);
  int black_psqt = board.get_psqt(BLACK);

  int start = g2;
  int end = f1;
  PieceType promotion_piece = QUEEN;
  Move move(start, end, promotion_piece);
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), PAWN);
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), KNIGHT);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  board.make(move);
  EXPECT_FALSE(board.get_piece_type(start).has_value());
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), promotion_piece);

  EXPECT_EQ(board.get_player_to_move(), WHITE);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 2);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_TRUE(board.get_captured_piece().has_value());
  EXPECT_EQ(board.get_captured_piece().value(), Piece(KNIGHT, WHITE, end));

  EXPECT_EQ(board.get_material(WHITE), white_material - KNIGHT_VALUE);
  EXPECT_EQ(board.get_psqt(WHITE),
            white_psqt - get_psqt_score(KNIGHT, end, WHITE, false, false));
  EXPECT_EQ(board.get_material(BLACK),
            black_material - PAWN_VALUE + get_piece_value(promotion_piece));
  int black_psqt_new =
      black_psqt - get_psqt_score(PAWN, start, BLACK, false, false) +
      get_psqt_score(promotion_piece, end, BLACK, false, false);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt_new);

  board.undo();
  EXPECT_TRUE(board.get_piece_type(start).has_value());
  EXPECT_EQ(board.get_piece_type(start).value(), PAWN);
  EXPECT_TRUE(board.get_piece_type(end).has_value());
  EXPECT_EQ(board.get_piece_type(end).value(), KNIGHT);

  EXPECT_EQ(board.get_player_to_move(), BLACK);
  EXPECT_EQ(board.get_halfmove_clock(), 0);
  EXPECT_EQ(board.get_fullmove_number(), 1);
  EXPECT_FALSE(board.get_en_passant_square().has_value());
  EXPECT_FALSE(board.get_captured_piece().has_value());

  EXPECT_EQ(board.get_material(BLACK), black_material);
  EXPECT_EQ(board.get_psqt(BLACK), black_psqt);
  EXPECT_EQ(board.get_material(WHITE), white_material);
  EXPECT_EQ(board.get_psqt(WHITE), white_psqt);
}
