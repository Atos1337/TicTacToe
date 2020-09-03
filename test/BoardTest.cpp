#include "BoardTest.h"
#include "Board.h"

void BoardTest::test_game_in_progress() const {
	Board b;
	b.move(0, 0, Board::Player::ZERO);
	b.move(1, 0, Board::Player::CROSS);
	b.move(0, 1, Board::Player::ZERO);
	b.move(1, 1, Board::Player::CROSS);
	DO_CHECK(b.get_state() == Board::State::GAME_IN_PROGRESS);
}

void BoardTest::test_zero_wins_vertical() const {
	Board b;
	b.move(0, 0, Board::Player::ZERO);
	b.move(1, 1, Board::Player::CROSS);
	b.move(1, 0, Board::Player::ZERO);
	b.move(1, 2, Board::Player::CROSS);
	b.move(2, 0, Board::Player::ZERO);
	b.move(1, 3, Board::Player::CROSS);
	b.move(3, 0, Board::Player::ZERO);
	b.move(1, 4, Board::Player::CROSS);
	b.move(4, 0, Board::Player::ZERO);
	DO_CHECK(b.get_state() == Board::State::ZERO_WINNER);
} 

void BoardTest::test_cross_wins_diagonal() const {
	Board b;
	b.move(9, 1, Board::Player::ZERO);
	b.move(0, 0, Board::Player::CROSS);
	b.move(0, 2, Board::Player::ZERO);
	b.move(1, 1, Board::Player::CROSS);
	b.move(0, 3, Board::Player::ZERO);
	b.move(2, 2, Board::Player::CROSS);
	b.move(0, 4, Board::Player::ZERO);
	b.move(3, 3, Board::Player::CROSS);
	b.move(0, 5, Board::Player::ZERO);
	b.move(4, 4, Board::Player::CROSS);
	DO_CHECK(b.get_state() == Board::State::CROSS_WINNER);
} 

void BoardTest::test_cross_wins_gorisontal() const {
	Board b;
	b.move(1, 9, Board::Player::ZERO);
	b.move(0, 0, Board::Player::CROSS);
	b.move(1, 2, Board::Player::ZERO);
	b.move(0, 1, Board::Player::CROSS);
	b.move(1, 3, Board::Player::ZERO);
	b.move(0, 2, Board::Player::CROSS);
	b.move(1, 4, Board::Player::ZERO);
	b.move(0, 3, Board::Player::CROSS);
	b.move(1, 5, Board::Player::ZERO);
	b.move(0, 4, Board::Player::CROSS);
	DO_CHECK(b.get_state() == Board::State::CROSS_WINNER);
} 

void BoardTest::test_zero_wins_diagonal() const {
	Board b;
	b.move(5, 5, Board::Player::ZERO);
	b.move(0, 3, Board::Player::CROSS);
	b.move(6, 4, Board::Player::ZERO);
	b.move(0, 4, Board::Player::CROSS);
	b.move(7, 3, Board::Player::ZERO);
	b.move(0, 5, Board::Player::CROSS);
	b.move(8, 2, Board::Player::ZERO);
	b.move(0, 6, Board::Player::CROSS);
	b.move(9, 1, Board::Player::ZERO);
	DO_CHECK(b.get_state() == Board::State::ZERO_WINNER);
} 

void BoardTest::test_full_board_draw() const {
	Board b;
	for (int k = 0; k < 5; k++) {
		for (int i = k * 2; i < 2 * (k + 1); i++) {
			for (int j = k % 2; j < 10; j += 2) {
				b.move(i, j, b.get_current_player());
				if (!(k % 2)) {
					b.move(i, j + 1, b.get_current_player());
				} else {
					b.move(i, j - 1, b.get_current_player());
				}	
			}
		}
	}
	DO_CHECK(b.get_state() == Board::State::DRAW);
} 

void BoardTest::test_move1() const {
	Board b;
	b.move(0, 0, Board::Player::ZERO);
	DO_CHECK(!b.can_move(0, 0, Board::Player::ZERO));
}

void BoardTest::test_move2() const {
	Board b;
	b.move(0, 0, Board::Player::ZERO);
	DO_CHECK(b.can_move(0, 1, Board::Player::CROSS));
}

void BoardTest::test_move3() const {
	Board b;
	b.move(9, 5, Board::Player::ZERO);
	DO_CHECK(!b.can_move(0, 9, Board::Player::ZERO));
}

void BoardTest::test_move4() const {
	Board b;
	b.move(5, 5, Board::Player::ZERO);
	b.move(6, 4, Board::Player::CROSS);
	b.move(7, 3, Board::Player::ZERO);
	b.move(8, 2, Board::Player::CROSS);
	b.move(9, 1, Board::Player::ZERO);
	DO_CHECK(!b.can_move(1, 1, Board::Player::ZERO));
}

void BoardTest::test_get_cell1() const {
	Board b;
	DO_CHECK(b.get_cell(0, 0) == Board::Cell::EMPTY);
}

void BoardTest::test_get_cell2() const {
	Board b;
	b.move(1, 0, Board::Player::ZERO);
	DO_CHECK(b.get_cell(1, 0) == Board::Cell::ZERO);
}

void BoardTest::test_get_cell3() const {
	Board b;
	b.move(7, 9, Board::Player::ZERO);
	DO_CHECK(b.get_cell(7, 9) == Board::Cell::ZERO);
}

void BoardTest::test_get_player_on_start() const {
	Board b;
	DO_CHECK(b.get_current_player() == Board::Player::ZERO);
}

void BoardTest::test_get_player_after_first_move() const {
	Board b;
	b.move(7, 9, Board::Player::ZERO);
	DO_CHECK(b.get_current_player() == Board::Player::CROSS);
}

void BoardTest::test_get_player_after_second_move() const {
	Board b;
	b.move(7, 9, Board::Player::ZERO);
	b.move(6, 3, Board::Player::CROSS);
	DO_CHECK(b.get_current_player() == Board::Player::ZERO);
}

void BoardTest::test_get_player_on_end() const {
	Board b;
	for (int k = 0; k < 5; k++) {
		for (int i = k * 2; i < 2 * (k + 1); i++) {
			for (int j = k % 2; j < 10; j += 2) {
				b.move(i, j, b.get_current_player());
				if (!(k % 2)) {
					b.move(i, j + 1, b.get_current_player());
				} else {
					b.move(i, j - 1, b.get_current_player());
				}	
			}
		}
	}
	DO_CHECK(b.get_current_player() == Board::Player::NONE);
}

void BoardTest::test_is_inside1() const {
	Board b;
	DO_CHECK(b.is_inside_field(0, 0));
}

void BoardTest::test_is_inside2() const {
	Board b;
	DO_CHECK(!b.is_inside_field(10, 10));
}

void BoardTest::test_is_inside3() const {
	Board b;
	DO_CHECK(!b.is_inside_field(-100, -100));
}

void BoardTest::test_is_inside4() const {
	Board b;
	DO_CHECK(b.is_inside_field(5, 5));
}

void BoardTest::Run_all_tests() const {
	test_game_in_progress();
	test_zero_wins_vertical();
	test_cross_wins_diagonal();
	test_cross_wins_gorisontal();
	test_zero_wins_diagonal();
	test_full_board_draw();
	test_move1();
	test_move2();
	test_move3();
	test_move4();
	test_get_cell1();
	test_get_cell2();
	test_get_cell3();
	test_get_player_on_start();
	test_get_player_after_first_move();
	test_get_player_after_second_move();
	test_get_player_on_end();
	test_is_inside1();
	test_is_inside2();
	test_is_inside3();
	test_is_inside4();
}
