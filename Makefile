all: hw_02 test_hw_02

hw_02: obj src/main.cpp obj/Board.o obj/View.o obj/StdioBoardView.o obj/NcursesBoardView.o obj/Controller.o
	g++ -std=c++17 -Iinclude -o hw_02 -Wall -Wextra -Werror src/main.cpp obj/Board.o obj/View.o obj/StdioBoardView.o obj/NcursesBoardView.o obj/Controller.o -lncurses
	
test_hw_02: obj test/test.cpp obj/Board.o obj/Test.o obj/BoardTest.o
	g++ -std=c++17 -Iinclude -o test_hw_02 -Wall -Wextra -Werror test/test.cpp obj/Test.o obj/BoardTest.o obj/Board.o

clean: 
	rm -f hw_02
	rm -f test_hw_02
	rm -rf obj

obj: 
	mkdir obj

obj/Board.o: src/Board.cpp
	g++ -std=c++17 -Iinclude -c -Wall -Wextra -Werror src/Board.cpp -o obj/Board.o
	
obj/View.o: src/View.cpp
	g++ -std=c++17 -Iinclude -c -Wall -Wextra -Werror src/View.cpp -o obj/View.o

obj/StdioBoardView.o: src/StdioBoardView.cpp obj/View.o obj/Board.o 
	g++ -std=c++17 -Iinclude -c -Wall -Wextra -Werror  src/StdioBoardView.cpp -o obj/StdioBoardView.o
	
obj/NcursesBoardView.o: src/NcursesBoardView.cpp obj/View.o obj/Board.o 
	g++ -std=c++17 -Iinclude -c -Wall -Wextra -Werror  src/NcursesBoardView.cpp -o obj/NcursesBoardView.o -lncurses

obj/Controller.o: src/Controller.cpp obj/NcursesBoardView.o obj/StdioBoardView.o obj/View.o obj/Board.o
	g++ -std=c++17 -Iinclude -c -Wall -Wextra -Werror  src/Controller.cpp -o obj/Controller.o -lncurses
	
obj/Test.o: test/Test.cpp
	g++ -std=c++17 -Iinclude -c -Wall -Wextra -Werror test/Test.cpp -o obj/Test.o

obj/BoardTest.o: test/BoardTest.cpp obj/Test.o obj/Board.o
	g++ -std=c++17 -Iinclude -c -Wall -Wextra -Werror test/BoardTest.cpp -o obj/BoardTest.o
