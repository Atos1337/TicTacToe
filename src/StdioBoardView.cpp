#include <cstdio>
#include <cstring>
#include <iostream>
#include <cassert>
#include "StdioBoardView.h"

StdioBoardView::StdioBoardView(Board& board, Mode argument) : View(board, argument) {}

Position StdioBoardView::read_valid_move() {
	if (mode != View::Mode::SILENT) {
		show_field();
	}
    std::string tmp;
    char space, none;
	bool is_correct_read = 0;
	while(!is_correct_read) {
		show_call();
		assert(std::cin.good());
		getline(std::cin, tmp);
		assert(std::cin.good());
		if (sscanf(tmp.c_str(), "%d%c%d%c", &current_position.y, &space, &current_position.x, &none) != 3 || space != ' ' || 
			(current_position != EXIT_CODE && !game.can_move(current_position.x, current_position.y, game.get_current_player()))) {
			check_output(printf("Bad move!\n"));
			continue;
		}
		is_correct_read = 1;
	}
	return current_position;	        
}

void StdioBoardView::show_field() const {
	check_output(printf("\n"));
	for (int j = 0; j < Board::FIELD_SIZE; j++) {
		for (int i = 0; i < Board::FIELD_SIZE; i++) {
			check_output(printf("%c", get_cell(i, j)));
		}
		check_output(printf("\n"));
	}
}

void StdioBoardView::show_result() const {
	show_field();
	switch(game.get_state()) {
		case Board::State::ZERO_WINNER:
			check_output(printf("%c wins!\n", 'O'));
			break;
		case Board::State::CROSS_WINNER:
			check_output(printf("%c wins!\n", 'X'));
			break;
		case Board::State::DRAW:
			check_output(printf("Draw.\n"));
			break;	
		case Board::State::GAME_IN_PROGRESS:
			break;	
	}
}

void StdioBoardView::show_call() const {
	assert(game.get_current_player() != Board::Player::NONE);
	switch(game.get_current_player()) {
		case Board::Player::ZERO:
			check_output(printf("%c move: ", 'O'));
			break;
		case Board::Player::CROSS:
			check_output(printf("%c move: ", 'X'));
			break;
		case Board::Player::NONE:
			break;		
	}
}
