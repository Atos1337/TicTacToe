#pragma once

#include "Board.h"

void check_output(int return_code);

struct Position{
	int x;
	int y;
	bool operator==(const Position& other) {
		return x == other.x && y == other.y;
	}
	bool operator!=(const Position& other) {
		return !(*this == other);
	}
};

class View{
public:
	enum class Mode{
		DEFAULT = 0,
		SILENT = 1
	};
	View(Board& board, Mode argument);
	virtual ~View();
	virtual void show_field() const = 0;
	virtual void show_result() const = 0;
	virtual void show_call() const = 0;
	virtual Position read_valid_move() = 0;
	static constexpr Position EXIT_CODE = {-1, -1};
protected:
	Board& game;
	char get_cell(int x, int y) const;
	Position current_position = {0, 0};
	Mode mode;
}; 
