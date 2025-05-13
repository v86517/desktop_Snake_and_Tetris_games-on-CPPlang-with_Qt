/**
 * @file snake_cli.cpp
 * @brief Файл запуска игры Snake в консоли
 */

extern "C" {
#include "../../gui/cli/frontend.h"
}

#include "snakeController.h"
#include "snakeModel.h"

void gameLoop();

using namespace s21;

int main() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  nodelay(stdscr, true);

  start_color();
  initColor();
  gameLoop();
  endwin();

  return 0;
}

using namespace s21;

void gameLoop() {
  GameInfo_t game_info;
  game_state st = START;
  snakeModelClass sm_class(&game_info, &st);
  snakeControllerClass sc_class(&sm_class);
  UserAction_t action;
  WINDOW *field, *panel;
  field = newwin(ROWS + 2, COLSS * 2 + 2, 0, 0);
  panel = newwin(22, 14, 0, COLSS * 2 + 2);
  initWindows(field, panel);
  bool hold = false;
  struct timeval start_timer, finish_timer;

  while (st != EXIT_STATE) {
    action = get_signal(getch(), &hold);

    if (action == Pause && st == MOVING) {
      game_info.pause = (game_info.pause == 1 ? 0 : 1);
    }
    if (game_info.pause == 0) {
      if (action != NOSIG) {
        sc_class.userInput(action);
        gettimeofday(&start_timer, NULL);
      }

      suseconds_t timer = game_info.speed;
      gettimeofday(&finish_timer, NULL);

      if (sc_class.isTimerOver(start_timer, finish_timer, timer)) {
        sc_class.userInput(sc_class.getDirection());
        gettimeofday(&start_timer, NULL);
      }
    }
    printGame(game_info, st, field, panel);
  }
  clear();
  delwin(field);
  delwin(panel);
}