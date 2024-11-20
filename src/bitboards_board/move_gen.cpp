#include "bitboards_board.hpp"
#include "bitboards_board/bits.hpp"
#include "defs.hpp"
#include "move.hpp"
#include "utils.hpp"
#include <sys/types.h>

u_int64_t BitboardsBoard::get_castling_check_not_allowed_bb(int start,
                                                   bool kingside) const {
  u_int64_t bb = bbs.squares.at(start);
  return bb |= kingside ? bbs.squares.at(start + 1) | bbs.squares.at(start + 2)
    : bbs.squares.at(start - 1) | bbs.squares.at(start - 2);
}

u_int64_t
BitboardsBoard::get_castling_pieces_not_allowed_bb(int start,
                                                   bool kingside) const {
  return kingside ? bbs.squares.at(start + 1) | bbs.squares.at(start + 2)
                  : bbs.squares.at(start - 1) | bbs.squares.at(start - 2) |
                        bbs.squares.at(start - 3);
}

u_int64_t BitboardsBoard::gen_castling_moves_bb(int start) const {
  u_int64_t castling = 0;

  int king_initial = pos_data.player_to_move == WHITE ? 60 : 4;
  if (start != king_initial) {
    return castling;
  }

  Castling castling_rights =
      pos_data.castling_rights.at(pos_data.player_to_move);

  u_int64_t attacked_bb =
      castling_rights.kingside || castling_rights.queenside
          ? get_attacking_bb(get_opposite_color(pos_data.player_to_move))
          : 0;

  u_int64_t pieces_bb = 0;
  for (int piece = 0; piece < 6; piece++) {
    if ((PieceType) piece != KING) {
      pieces_bb |=
        bb_pieces.at(pos_data.player_to_move).at(piece);
    }
  }
  for (int piece = 0; piece < 6; piece++) {
    pieces_bb |=
        bb_pieces.at(get_opposite_color(pos_data.player_to_move)).at(piece);
  }

  if (castling_rights.kingside) {
    u_int64_t no_check_bb = get_castling_check_not_allowed_bb(start, true);
    u_int64_t no_pieces_bb = get_castling_pieces_not_allowed_bb(start, true);
    if (((no_check_bb & attacked_bb) | (no_pieces_bb & pieces_bb)) == 0) {
      castling |= bbs.squares.at(start + 2);
    }
  }

  if (castling_rights.queenside) {
    u_int64_t no_check_bb = get_castling_check_not_allowed_bb(start, false);
    u_int64_t no_pieces_bb = get_castling_pieces_not_allowed_bb(start, false);
    if (((no_check_bb & attacked_bb) | (no_pieces_bb & pieces_bb)) == 0) {
      castling |= bbs.squares.at(start - 2);
    }
  }

  return castling;
}

std::vector<Move> BitboardsBoard::gen_king_moves(int start) const {
  std::vector<Move> moves;

  u_int64_t normal = bbs.king_moves[start];
  for (int i = 0; i < 6; i++) {
    normal &= ~bb_pieces[pos_data.player_to_move][i];
  }


  std::optional<int> end_pos = bits::popLSB(normal);
  while (end_pos.has_value()) {
    Move move = Move(start, end_pos.value());
    moves.push_back(move);
    end_pos = bits::popLSB(normal);
  }

  u_int64_t castling = gen_castling_moves_bb(start);
  end_pos = bits::popLSB(castling);
  while (end_pos.has_value()) {
    Move move = Move(start, end_pos.value());
    move.move_type = CASTLING;
    moves.push_back(move);
    end_pos = bits::popLSB(castling);
  }
  return moves;
}

std::vector<Move> BitboardsBoard::gen_knight_moves(int start) const {
  std::vector<Move> moves;

  u_int64_t knight_moves = bbs.knight_moves[start];
  for (int i = 0; i < 6; i++) {
    knight_moves &= ~bb_pieces[pos_data.player_to_move][i];
  }

  std::optional<int> end_pos = bits::popLSB(knight_moves);
  while (end_pos.has_value()) {
    Move move = Move(start, end_pos.value());
    moves.push_back(move);
    end_pos = bits::popLSB(knight_moves);
  }
  return moves;
}

std::vector<Move> BitboardsBoard::gen_pawn_moves(int start) const {
  std::vector<Move> moves;

  u_int64_t pawn = bbs.squares.at(start);
  u_int64_t move_one = bbs.pawn_moves_one.at(pos_data.player_to_move).at(start);
  u_int64_t move_two = bbs.pawn_moves_two.at(pos_data.player_to_move).at(start);
  for (int color = 0; color < 2; color++) {
    for (int piece = 0; piece < 6; piece++) {
      u_int64_t bb_piece = bb_pieces.at(color).at(piece);
      u_int64_t bb_piece_one_rank_forward =
          pos_data.player_to_move == WHITE ? bb_piece >> 8 : bb_piece << 8;
      move_one &= ~bb_piece;
      move_two &= ~(bb_piece | (bb_piece_one_rank_forward));
    }
  }

  u_int64_t captures = bbs.pawn_captures.at(pos_data.player_to_move).at(start);
  u_int64_t bb_opponent = 0;
  for (int piece = 0; piece < 6; piece++) {
    u_int64_t bb_piece_team = bb_pieces.at(pos_data.player_to_move).at(piece);
    u_int64_t bb_piece_opponent =
        bb_pieces.at(get_opposite_color(pos_data.player_to_move)).at(piece);
    bb_opponent |= bb_piece_opponent;
    captures &= ~bb_piece_team;
  }
  u_int64_t normal_captures = captures & bb_opponent;

  u_int64_t en_passant_captures = pos_data.en_passant_square.has_value()
    ? captures & bbs.squares.at(pos_data.en_passant_square.value())
    : 0;

  u_int64_t bb_end = move_one | normal_captures;
  std::optional<int> end_pos = bits::popLSB(bb_end);
  while (end_pos.has_value()) {
    if (end_pos.value() < 8 || end_pos.value() > 55) {
      std::array<PieceType, 4> promotion_pieces = {
          QUEEN,
          ROOK,
          BISHOP,
          KNIGHT,
      };
      for (PieceType p : promotion_pieces) {
        Move move = Move(start, end_pos.value());
        move.move_type = PROMOTION;
        move.promotion_piece = p;
        moves.push_back(move);
      }
    } else {
      Move move = Move(start, end_pos.value());
      moves.push_back(move);
    }
    end_pos = bits::popLSB(bb_end);
  }

  end_pos = bits::popLSB(move_two);
  while (end_pos.has_value()) {
    Move move = Move(start, end_pos.value());
    move.move_type = PAWN_TWO_SQUARES_FORWARD;
    moves.push_back(move);
    end_pos = bits::popLSB(move_two);
  }

  end_pos = bits::popLSB(en_passant_captures);
  while (end_pos.has_value()) {
    Move move = Move(start, end_pos.value());
    move.move_type = EN_PASSANT;
    moves.push_back(move);
    end_pos = bits::popLSB(en_passant_captures);
  }

  return moves;
}

bool BitboardsBoard::piece_on_square(u_int64_t pos_bb, Color color) const {
  for (int piece = 0; piece < 6; piece++) {
    if ((pos_bb & ~bb_pieces.at(color).at(piece)) == 0) {
      return true;
    }
  }
  return false;
}

u_int64_t BitboardsBoard::gen_sliding_moves(int start,
                                                    Direction direction,
                                                    Color color) const {
  u_int64_t moves_bb = 0;
  u_int64_t pos_bb = bbs.squares[start];

  auto stop = [&]() {
    switch (direction) {
      case UP:
        return (pos_bb & ~bbs.rank_1) == 0;
      case DOWN:
        return (pos_bb & ~bbs.rank_8) == 0;
      case LEFT:
        return (pos_bb & ~bbs.a_file) == 0;
      case RIGHT:
        return (pos_bb & ~bbs.h_file) == 0;
      case UP_LEFT:
        return (pos_bb & ~(bbs.a_file | bbs.rank_1)) == 0;
      case UP_RIGHT:
        return (pos_bb & ~(bbs.h_file | bbs.rank_1)) == 0;
      case DOWN_LEFT:
        return (pos_bb & ~(bbs.a_file | bbs.rank_8)) == 0;
      case DOWN_RIGHT:
        return (pos_bb & ~(bbs.h_file | bbs.rank_8)) == 0;
    }
  };

  auto go_next_pos = [&]() {
    switch (direction) {
      case UP:
        pos_bb >>= 8;
        break;
      case DOWN:
        pos_bb <<= 8;
        break;
      case LEFT:
        pos_bb >>= 1;
        break;
      case RIGHT:
        pos_bb <<= 1;
        break;
      case UP_LEFT:
        pos_bb >>= 9;
        break;
      case UP_RIGHT:
        pos_bb >>= 7;
        break;
      case DOWN_LEFT:
        pos_bb <<= 7;
        break;
      case DOWN_RIGHT:
        pos_bb <<= 9;
        break;
    }
  };

  while (!stop()) {
    go_next_pos();
    if (piece_on_square(pos_bb, color)) {
      break;
    }

    moves_bb |= pos_bb;

    if (piece_on_square(pos_bb, get_opposite_color(color))) {
      break;
    }
  }

  return moves_bb;
}

u_int64_t BitboardsBoard::gen_sliding_moves_directions(
    int start, std::vector<Direction> directions, Color color) const {
  u_int64_t moves_bb = 0;
  for (Direction direction : directions) {
    moves_bb |= gen_sliding_moves(start, direction, color);
  }
  return moves_bb;
}

u_int64_t BitboardsBoard::gen_rook_moves(int start, Color color) const {
  const std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
  return gen_sliding_moves_directions(start, directions, color);
}

u_int64_t BitboardsBoard::gen_bishop_moves(int start, Color color) const {
  const std::vector<Direction> directions = {UP_LEFT, UP_RIGHT, DOWN_LEFT,
                                         DOWN_RIGHT};
  return gen_sliding_moves_directions(start, directions, color);
}

u_int64_t BitboardsBoard::gen_queen_moves(int start, Color color) const {
  return gen_rook_moves(start, color) | gen_bishop_moves(start, color);
}

std::vector<Move>
BitboardsBoard::sliding_moves_bb_to_moves(int start, u_int64_t moves_bb) const {
  std::vector<Move> moves;
  std::optional<int> end_pos = bits::popLSB(moves_bb);
  while (end_pos.has_value()) {
    Move move = Move(start, end_pos.value());
    moves.push_back(move);
    end_pos = bits::popLSB(moves_bb);
  }
  return moves;
}

std::vector<Move> BitboardsBoard::gen_moves_piece(PieceType piece, int start) const {
  switch (piece) {
    case KING:
      return gen_king_moves(start);
    case KNIGHT:
      return gen_knight_moves(start);
    case PAWN:
      return gen_pawn_moves(start);
    case ROOK:
      return sliding_moves_bb_to_moves(
          start, gen_rook_moves(start, pos_data.player_to_move));
    case BISHOP:
      return sliding_moves_bb_to_moves(
          start, gen_bishop_moves(start, pos_data.player_to_move));
    case QUEEN:
      return sliding_moves_bb_to_moves(
          start, gen_queen_moves(start, pos_data.player_to_move));
  }
}

std::vector<Move> BitboardsBoard::gen_all_moves_piece(PieceType piece) const {
  std::vector<Move> moves;

  u_int64_t bb_piece = bb_pieces[pos_data.player_to_move][piece];
  std::optional<int> start_pos = bits::popLSB(bb_piece);
  while (start_pos.has_value()) {
    std::vector<Move> pos_moves = gen_moves_piece(piece, start_pos.value());
    moves.insert(moves.end(), pos_moves.begin(), pos_moves.end()); 
    start_pos = bits::popLSB(bb_piece);
  }
  return moves;
}

std::vector<Move>
BitboardsBoard::get_pseudo_legal_moves(MoveCategory move_category) const {
  std::vector<Move> moves;
  for (int piece = 0; piece < 6; piece++) {
    std::vector<Move> piece_moves = gen_all_moves_piece((PieceType) piece);
    moves.insert(moves.end(), piece_moves.begin(), piece_moves.end());
  }
  return moves;
}

u_int64_t BitboardsBoard::get_attacking_bb(Color color) const {
  u_int64_t attacking_bb = 0;

  std::array<PieceType, 3> non_sliding_pieces = {KING, PAWN, KNIGHT};
  for (PieceType piece : non_sliding_pieces) {
    std::array<u_int64_t, 64> piece_attacking_bb =
        piece == KING   ? bbs.king_moves
        : piece == PAWN ? bbs.pawn_captures.at(color)
                        : bbs.knight_moves;
    u_int64_t bb_piece = bb_pieces.at(color).at(piece);
    std::optional<int> start_pos = bits::popLSB(bb_piece);
    while (start_pos.has_value()) {
      attacking_bb |= piece_attacking_bb.at(start_pos.value());
      start_pos = bits::popLSB(bb_piece);
    }
  }

  std::array<PieceType, 3> sliding_pieces = {BISHOP, ROOK, QUEEN};
  for (PieceType piece : sliding_pieces) {
    u_int64_t bb_piece = bb_pieces.at(color).at(piece);
    std::optional<int> start_pos = bits::popLSB(bb_piece);
    while (start_pos.has_value()) {
      attacking_bb |=
          piece == BISHOP ? gen_bishop_moves(start_pos.value(), color)
          : piece == ROOK ? gen_rook_moves(start_pos.value(), color)
                          : gen_queen_moves(start_pos.value(), color);

      start_pos = bits::popLSB(bb_piece);
    }
  }
  return attacking_bb;
}

bool BitboardsBoard::is_in_check(Color color) const {
  u_int64_t attacked_bb = get_attacking_bb(get_opposite_color(color));
  return (bb_pieces.at(color).at(KING) & attacked_bb) != 0;
}
