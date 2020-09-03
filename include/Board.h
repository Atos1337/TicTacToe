#pragma once

#include <vector>

class Board final {
public:
	enum class State {
		GAME_IN_PROGRESS = 0,
		ZERO_WINNER = 1,
		CROSS_WINNER = 2,
		DRAW = 3
	};
	enum class Player {
		ZERO = 0,
		CROSS = 1,
		NONE = 2
	};
	enum class Cell {
		ZERO = 0,
		CROSS = 1,
		EMPTY = 2
	};
	Board();
	void move(int x, int y, Player player);
	bool can_move(int x, int y, Player player) const;
	Cell get_cell(int x, int y) const;
	State get_state() const;
	Player get_current_player() const;
	bool is_inside_field(int x, int y) const;
	static constexpr int FIELD_SIZE = 10;
	static constexpr int NEED_TO_WIN = 5;
private:
	std::vector<std::vector<Cell>> field;
	std::vector<std::pair<int, int>> directions = {
		{1, 0}, {0, 1}, {1, 1}, {1, -1}
	};
	State current_state = State::GAME_IN_PROGRESS;
	int not_empty_sq = 0;
	Player current_player = Player::ZERO;
	bool is_empty(int x, int y) const;
	void update_state(int x, int y, Player player);
	bool is_draw() const;
	bool is_winner(int x, int y, Player player) const;
	bool check_line(int x, int y, int dx, int dy, Player player) const;
};
