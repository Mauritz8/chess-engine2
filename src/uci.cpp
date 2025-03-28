#include "uci.hpp"

#include <algorithm>
#include <cmath>
#include <fmt/core.h>
#include <numeric>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <vector>

#include "board.hpp"
#include "defs.hpp"
#include "fen.hpp"
#include "move.hpp"
#include "search/command.hpp"
#include "search/search_defs.hpp"
#include "utils.hpp"

namespace uci {

const int MOVE_OVERHEAD = 50;

std::string get_fen(const std::vector<std::string> &words) {
  if (words.at(1) == "startpos") {
    return STARTING_POSITION_FEN;
  }

  auto join = [](std::string str1, std::string str2) {
    return fmt::format("{} {}", str1, str2);
  };
  auto moves_it = std::find(words.begin(), words.end(), "moves");
  std::string fen =
      std::accumulate(words.begin() + 2, moves_it, std::string(""), join);
  return fen.substr(1);
}

bool make_move(const std::string &move_uci, std::unique_ptr<Board> &board) {
  const Color player = board->get_player_to_move();
  const std::vector<Move> pseudo_legal_moves =
      board->get_pseudo_legal_moves(ALL);
  for (const Move &move : pseudo_legal_moves) {
    if (move.to_uci_notation() == move_uci) {
      board->make(move);
      if (board->is_in_check(player)) {
        board->undo();
        return false;
      }
      return true;
    }
  }
  return false;
}

Command get_go_command(const std::vector<std::string> &words) {
  if (words.size() < 3) {
    return Command::go_infinite();
  }

  std::string name = words.at(1);
  std::string value = words.at(2);
  if (name == "depth") {
    int depth = std::stoi(value);
    return Command::go_depth(depth);
  }
  if (name == "movetime") {
    int movetime = std::stoi(value);
    return Command::go_move_time(movetime);
  }
  if (name == "perft") {
    int depth = std::stoi(value);
    return Command::go_perft(depth);
  }


  int wtime = 0;
  int btime = 0;
  int winc = 0;
  int binc = 0;
  int moves_to_go = 0;
  for (int i = 1; i < words.size() - 1; i += 2) {
    std::string name = words.at(i);
    std::string value = words.at(i + 1);
    if (name == "wtime") {
      wtime = std::stoi(value);
    } else if (name == "btime") {
      btime = std::stoi(value);
    } else if (name == "winc") {
      winc = std::stoi(value);
    } else if (name == "binc") {
      binc = std::stoi(value);
    } else if (name == "movestogo") {
      moves_to_go = std::stoi(value);
    }
  }

  if (wtime != 0 && btime != 0) {
    return Command::go_game_time(wtime, btime, winc, binc, moves_to_go);
  }
  return Command::go_infinite();
}

void process(const std::string &input, int write_descriptor) {

  const std::vector<std::string> words = str_split(input, ' ');

  const bool is_position = words.size() >= 2 && words.at(0) == "position" &&
                           (words.at(1) == "startpos" || words.at(1) == "fen");
  if (input == "uci") {
    fmt::println("id name {} {}\nid author {}\nuciok\n", NAME, VERSION, AUTHOR);
  } else if (input == "isready") {
    fmt::println("readyok\n");
  } else if (is_position) {
    const std::string fen = get_fen(words);
    try {
      std::unique_ptr<Board> board = fen::get_position(fen);
      auto moves_it = std::find(words.begin(), words.end(), "moves");
      if (moves_it != words.end()) {
        std::for_each(
            moves_it + 1, words.end(),
            [&](const std::string &move_uci) { make_move(move_uci, board); });
      }
    } catch (const std::invalid_argument &e) {
      fmt::println(e.what());
    }
  } else if (words.at(0) == "go") {
    Command command = get_go_command(words);
    fmt::println("command = {}", (int) command.type);
    write(write_descriptor, &command, sizeof(command));
  } else if (input == "quit") {
    exit(0);
  } else {
    fmt::println("invalid input: {}", input);
  }
}

std::string show(const SearchSummary &ss) {
  const int ply = CHECKMATE - std::abs(ss.score);
  const int mate_in_x = std::ceil(ply / 2.0);
  const int sign = ss.score > 0 ? 1 : -1;
  const std::string score = std::abs(ss.score) > CHECKMATE_THRESHOLD
                                ? fmt::format("mate {}", sign * mate_in_x)
                                : fmt::format("cp {}", ss.score);

  const long long nps = ss.nodes * 1000 / (ss.time == 0 ? 1 : ss.time);
  const std::string pv =
      std::accumulate(ss.pv.begin(), ss.pv.end(), std::string(""),
                      [](std::string acc, const Move &m) {
                        return fmt::format("{} {}", acc, m.to_uci_notation());
                      });

  return fmt::format("info depth {} seldepth {} multipv 1 score {} nodes {} "
                     "nps {} time {} pv{}",
                     ss.depth, ss.seldepth, score, ss.nodes, nps, ss.time, pv);
}

std::string bestmove(const Move &move) {
  return fmt::format("bestmove {}", move.to_uci_notation());
}
} // namespace uci
