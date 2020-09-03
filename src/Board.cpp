#include "Board.h"
#include <cassert>
#include <vector>

static constexpr Board::Player next_player(Board::Player player) {
	assert(player != Board::Player::NONE);
	switch(player) {
		case Board::Player::ZERO:
			return Board::Player::CROSS;
		case Board::Player::CROSS:
			return Board::Player::ZERO;
		default:
			return Board::Player::NONE;
	}
}

static constexpr Board::Cell Player_to_Cell(Board::Player player) {
	assert(player != Board::Player::NONE);
	switch(player) {
		case Board::Player::ZERO:
			return Board::Cell::ZERO;
		case Board::Player::CROSS:
			return Board::Cell::CROSS;
		default:
			return Board::Cell::EMPTY;		
	}
}

Board::Board() : field(FIELD_SIZE, std::vector<Cell>(FIELD_SIZE, Cell::EMPTY)) {}

Board::Cell Board::get_cell(int x, int y) const {
	return field[y][x];
}

bool Board::is_empty(int x, int y) const {
	assert(is_inside_field(x, y));
	return field[y][x] == Cell::EMPTY;
}

bool Board::is_inside_field(int x, int y) const {
    return x >= 0 && x < FIELD_SIZE && y >= 0 && y < FIELD_SIZE;
}    

bool Board::can_move(int x, int y, Player player) const {
	assert(player != Board::Player::NONE);
	return current_state == State::GAME_IN_PROGRESS && player == current_player && is_inside_field(x, y) && is_empty(x, y);
}

void Board::move(int x, int y, Player player) {
	assert(can_move(x, y, player));
	field[y][x] = Player_to_Cell(player);
	not_empty_sq++;
	update_state(x, y, player);
	current_player = next_player(current_player);
}

bool Board::check_line(int x, int y, int dx, int dy, Player player) const {
	int count = 0;
	int i = x + dx;
	int j = y + dy;
	while(is_inside_field(i, j) && field[j][i] == (Cell)player) {
		count++;
		i += dx;
		j += dy;
	}
	i = x - dx;
	j = y - dy;
	while(is_inside_field(i, j) && field[j][i] == (Cell)player) {
		count++;
		i -= dx;
		j -= dy;
	}
	return (count + (field[y][x] == Player_to_Cell(player))) >= NEED_TO_WIN;
}

Board::Player Board::get_current_player() const {
	if (get_state() == Board::State::GAME_IN_PROGRESS) {
		return current_player;
	}
	return Board::Player::NONE;	
}

bool Board::is_winner(int x, int y, Player player) const {
	bool is_win = false;
	for (int i = 0; i < 4; i++) {
		is_win |= check_line(x, y, directions[i].first, directions[i].second, player);
	}
	return is_win;
}

bool Board::is_draw() const {
	return not_empty_sq == FIELD_SIZE * FIELD_SIZE;
}

void Board::update_state(int x, int y, Player player) {
	if (is_winner(x, y, player)) {
		switch(player) {
			case Player::ZERO:
				current_state = State::ZERO_WINNER;
				break;
			case Player::CROSS:
				current_state = State::CROSS_WINNER;
				break;
			default:
				break;		
		}
		return;
	}
	if (is_draw())
		current_state = State::DRAW;
}

Board::State Board::get_state() const {
	return current_state;
}
