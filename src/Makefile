CC=g++
C_CC=gcc
CCFLAGS=-Wall -Werror -Wextra -std=c++17
C_CCFLAGS=-Wall -Werror -Wextra -std=c11
LCOVFLAGS=-fprofile-arcs -ftest-coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
	LIBSCHECK = -lcheck -pthread -lrt -lm -lsubunit
	LIBSGTEST = -lgtest -pthread
	LEAK = valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all
else
	LIBSCHECK = -lcheck
	LIBSGTEST = -lgtest
	LEAK = leaks -atExit --
endif

all: install cli gcov_report

install: build cli
	cmake gui/desktop -B build
	make -C build/

build:
	rm -rf build/
	mkdir build

uninstall: clean
	rm -rf snake_high_score.txt tetris_high_score.txt *.tar build doxygen

cli: snake.a tetris.a
	$(C_CC) $(C_CCFLAGS) -c gui/cli/*.c
	$(CC) $(CCFLAGS) -o build/snake_cli brick_game/snake/*.cpp *.o snake.a tetris.a -lncurses
	$(C_CC) $(C_CCFLAGS) -o build/tetris_cli brick_game/tetris/tetris_cli.c *.o tetris.a -lncurses
	rm -f *.o

tetris.a:
	$(C_CC) $(C_CC_FALGS) -c brick_game/tetris/tetrisBackend.c
	ar rc tetris.a *.o
	ranlib tetris.a
	rm -f *.o

snake.a:
	$(CC) $(CCFLAGS) -c brick_game/snake/*.cc
	ar rc snake.a *.o
	ranlib snake.a
	rm -f *.o

gcov_report: tests
	lcov -t "test" -o test/test.info -c -d . --no-external
	genhtml -o report test/test.info
	xdg-open report/index.html

tests: tetris_test snake_test

tetris_test:
	$(C_CC) $(C_CCFLAGS) $(LCOVFLAGS) test/*.c brick_game/tetris/tetrisBackend.c -o tetris_test $(LIBSCHECK)
	./tetris_test
	mv *.gcda *.gcno test/

snake_test:
	$(CC) $(CCFLAGS) $(CC_test) $(LCOVFLAGS) test/*.cpp brick_game/snake/snakeModel.cc -o snake_test $(LIBSGTEST)
	./snake_test
	mv *.gcda *.gcno test/

valgrind_tetris: tetris.a
	$(C_CC) $(C_CCFLAGS) $(LCOVFLAGS) -g test/*.c tetris.a -o tetris_test $(LIBSCHECK)
	valgrind --tool=memcheck --leak-check=yes ./tetris_test
	mv *.gcda *.gcno test/

valgrind_snake: clean snake.a
	$(CC) $(CCFLAGS) $(CC_test) $(LCOVFLAGS) -g test/*.cpp snake.a -o snake_test $(LIBSGTEST)
	valgrind --tool=memcheck --leak-check=yes ./snake_test
	mv *.gcda *.gcno test/

clean:
	rm -f snake.a tetris.a *.o
	rm -f test/*.gcda test/*.gcno test/test.info test/*.o
	rm -rf report tetris_test snake_test *.tar

clang:
	cp ../materials/linters/.clang-format .
	find . -type f -name "*.cc" -exec clang-format -i {} +
	find . -type f -name "*.h" -exec clang-format -i {} +
	find . -type f -name "*.c" -exec clang-format -i {} +
	rm -f .clang-format

dvi:
	doxygen
	open descriptionFSM.png
	open doxygen/html/index.html

dist:
#	$(shell find . -name '*.c') $(shell find . -name '*.cc') $(shell find . -name '*.h') ./Makefile
#	tar -czf BrickGame_v2.0-1.tar.gz $^
	tar -cvzf BrickGames_tetris_snake.tar Makefile descriptionFSM.png Doxyfile brick_game/*/*.* gui/*/*.* test/*.*

.PHONY: tests gcov_report valgrind clean clang install uninstall cli tetris_test snake_test valgrind_snake valgrind_tetris dvi dist