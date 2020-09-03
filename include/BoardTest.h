#pragma once

#include "Test.h"
#include "Board.h"

class BoardTest final : public Test {
private:
	void test_game_in_progress() const;
	void test_zero_wins_vertical() const;
	void test_cross_wins_diagonal() const;
	void test_cross_wins_gorisontal() const;
	void test_zero_wins_diagonal() const;
	void test_full_board_draw() const;
	void test_move1() const;
	void test_move2() const;
	void test_move3() const;
	void test_move4() const;
	void test_get_cell1() const;
	void test_get_cell2() const;
	void test_get_cell3() const;
	void test_get_player_on_start() const;
	void test_get_player_after_first_move() const;
	void test_get_player_after_second_move() const;
	void test_get_player_on_end() const;
	void test_is_inside1() const;
	void test_is_inside2() const;
	void test_is_inside3() const;
	void test_is_inside4() const;
public:
	void Run_all_tests() const override;	
};
