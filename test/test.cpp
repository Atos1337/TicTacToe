#include <iostream>
#include "BoardTest.h"
#include "Test.h"
#include "Board.h"

int Test::failed_num = 0;
int Test::total_num = 0;

int main() {
    BoardTest bt;
    try {
    	bt.Run_all_tests();
	} catch (int& e) {
		std::cerr << "Output Error!!!";
		return 1;
	}
    return !Test::show_final_results();
} 
