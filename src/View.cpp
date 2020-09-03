#include "View.h"
#include <cassert>

void check_output(int return_code) {
	if (return_code < 0) {
		throw 1;
	}
}

View::View(Board& board, Mode argument) : game(board), mode(argument) {}

View::~View() {}

char View::get_cell(int x, int y) const {
	switch(game.get_cell(x, y)) {
		case Board::Cell::ZERO:
			return 'O';
		case Board::Cell::CROSS:
			return 'X';	
		case Board::Cell::EMPTY:
			return '.';			
	}
	return 0;
}
