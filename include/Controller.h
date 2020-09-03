#pragma once

#include "Board.h"
#include "StdioBoardView.h"
#include "NcursesBoardView.h"
#include <ncurses.h>

class Controller final{
public:	
	Controller(View& view, Board& board);
	void Run_game();	
private:
	View& view;
	Board& game;
}; 