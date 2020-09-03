#pragma once

#include "Board.h"
#include "View.h"

class StdioBoardView final : public View{
public:
	StdioBoardView(Board &board, Mode argument);
	void show_field() const override;
	void show_result() const override;
	void show_call() const override;
	Position read_valid_move() override;
};
