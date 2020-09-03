#include <cstring>
#include <iostream>
#include <memory>
#include "Controller.h"

int main(int argc, char* argv[]) {
	Board game;
	std::unique_ptr<View> view;
	if (argc > 1) {
		if (strcmp(argv[1], "silent") == 0) {
			view = std::unique_ptr<View> (new StdioBoardView (game, View::Mode::SILENT));
		} else {
			view = std::unique_ptr<View> (new NcursesBoardView (game, View::Mode::DEFAULT));
		}
	} else {
		view = std::unique_ptr<View> (new StdioBoardView (game, View::Mode::DEFAULT));
	}
	try {
		Controller controll(*view, game);
		controll.Run_game();
	} catch (int& e) {
		std::cerr << "Output Error!";
		return 1;
	}
	return 0;
} 
