#pragma once

#include "Board.h"
#include "View.h"

class NcursesBoardView final : public View{
public:
	NcursesBoardView(Board& board, Mode argument);
	~NcursesBoardView() override;
	void show_field() const override;
	void show_result() const override;
	void show_call() const override;
	Position read_valid_move() override;
private:
	void change_current_position(int x, int y);
	void show_position() const;
};