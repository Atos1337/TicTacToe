#include "Controller.h"
#include <ncurses.h>

Controller::Controller(View& view, Board& board) : view(view), game(board) {}

void Controller::Run_game() {
	Position p;
	while(game.get_state() == Board::State::GAME_IN_PROGRESS) {
		p = view.read_valid_move();
		if (p == view.EXIT_CODE)
			return;	
		game.move(p.x, p.y, game.get_current_player());
	}
	view.show_result();
}