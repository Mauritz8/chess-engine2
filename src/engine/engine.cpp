#include "engine.hpp"
#include "engine/command.hpp"
#include "engine/search.hpp"
#include "engine/search_defs.hpp"
#include "engine/time_management.hpp"
#include <memory>
#include <unistd.h>

namespace engine {
SearchParams get_search_params(Command &command, Color player_to_move) {
  SearchParams params = SearchParams();
  switch (command.type) {
  case GoInfinite:
    params.search_mode = SearchMode::INFINITE;
    break;
  case GoDepth:
    params.search_mode = SearchMode::DEPTH;
    params.depth = command.arg.integer;
    break;
  case GoMoveTime:
    params.search_mode = SearchMode::MOVE_TIME;
    params.allocated_time = command.arg.integer;
    break;
  case GoGameTime:
    params.search_mode = SearchMode::MOVE_TIME;
    params.allocated_time =
        calc_allocated_time(player_to_move, command.arg.game_time.wtime,
                            command.arg.game_time.btime);
    break;
  case GoPerft:
    // todo
    break;
  }
  return params;
}

void run(int read_descriptor) {
  std::unique_ptr<Board> board = Board::get_starting_position();
  Command command;
  while (true) {
    read(read_descriptor, &command, sizeof(command));

    SearchParams params =
        get_search_params(command, board->get_player_to_move());
    Search search = Search(board, params);
    search.iterative_deepening_search();
  }
}

}; // namespace engine
