#include "NcursesBoardView.h"
#include <cassert>
#include <ncurses.h>

NcursesBoardView::NcursesBoardView(Board& board, Mode argument) : View(board, argument) {
	initscr();
	start_color();
	curs_set(0);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
	keypad(stdscr, true);
	noecho();
	halfdelay(1);
}

NcursesBoardView::~NcursesBoardView() {
	endwin();
}

Position NcursesBoardView::read_valid_move() {
	while(true) {
		clear();
		show_call();
		refresh();	
		int ch = getch();
		switch(ch) {
			case ERR:
				break;
			case (int)(' '):
				if(game.can_move(current_position.x, current_position.y, game.get_current_player()))
					return current_position;
				break;
			case KEY_DOWN:
				change_current_position(0, 1);
				break;
			case KEY_LEFT:
				change_current_position(-1, 0);
				break;
			case KEY_UP:
				change_current_position(0, -1);
				break;
			case KEY_RIGHT:
				change_current_position(1, 0);
				break;
			case int('x'):
				return EXIT_CODE;						
		}
	}	
}

void NcursesBoardView::change_current_position(int x, int y) {
	int& x0 = current_position.x;
	int& y0 = current_position.y;
	if (game.is_inside_field(x + x0, y + y0)) {
		x0 += x;
		y0 += y;
	}
}

void NcursesBoardView::show_position() const {
	int x = current_position.x;
	int y = current_position.y;
	switch(game.get_cell(x, y)) {
		case Board::Cell::EMPTY:
			check_output(addch('_' | A_BLINK | A_STANDOUT | COLOR_PAIR(2)));
			break;
		default:
			check_output(addch(get_cell(x, y) | A_BLINK | COLOR_PAIR(1)));
			break;	
	}
}

void NcursesBoardView::show_field() const {
	clear();
	for (int j = 0; j < Board::FIELD_SIZE; j++) {
		for (int i = 0; i < Board::FIELD_SIZE; i++) {
			if (i == current_position.x && j == current_position.y) {
				show_position();
			} else {
				check_output(addch(get_cell(i, j)));
			}	
		}
		check_output(printw("\n"));
	}
	refresh();
}

void NcursesBoardView::show_result() const {
	clear();
	show_field();
	switch(game.get_state()) {
		case Board::State::ZERO_WINNER:
			check_output(printw("%c wins!\n", 'O'));
			break;
		case Board::State::CROSS_WINNER:
			check_output(printw("%c wins!\n", 'X'));
			break;
		case Board::State::DRAW:
			check_output(printw("Draw.\n"));
			break;	
		case Board::State::GAME_IN_PROGRESS:
			break;	
	}
	check_output(printw("Press 'x' to exit.\n"));
	refresh();
	while(getch() != 'x');
}

void NcursesBoardView::show_call() const {
	clear();
	show_field();
	assert(game.get_current_player() != Board::Player::NONE);
	switch(game.get_current_player()) {
		case Board::Player::ZERO:
			check_output(printw("%c move: ", 'O'));
			break;
		case Board::Player::CROSS:
			check_output(printw("%c move: ", 'X'));
			break;
		case Board::Player::NONE:
			break;		
	}
	refresh();
}
