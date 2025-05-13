/**
 * @file tetris_cli.c
 * @brief Основной файл для запуска игры Tetris в консоли
 */
#include "../../gui/cli/frontend.h"
#include "tetrisBackend.h"

void gameLoop();

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

void gameLoop() {
  Block_t current_block;
  UserAction_t action;
  game_state tetris_state = START;
  GameInfo_t game_info;

  initState(&game_info);

  WINDOW *field, *panel;
  field = newwin(ROWS + 2, COLSS * 2 + 2, 0, 0);
  panel = newwin(22, 14, 0, COLSS * 2 + 2);
  initWindows(field, panel);

  nodelay(stdscr, true);
  bool hold = false;

  struct timeval start_timer, finish_timer;

  while (tetris_state != EXIT_STATE) {
    action = get_signal(getch(), &hold);

    if (action == Pause && tetris_state == MOVING) {
      game_info.pause = game_info.pause == TRUE ? FALSE : TRUE;
    }

    if (game_info.pause == FALSE) {
      if (action != NOSIG) {
        userInput(&game_info, &current_block, action, &tetris_state);
        gettimeofday(&start_timer, NULL);
      }

      suseconds_t timer = game_info.speed;

      gettimeofday(&finish_timer, NULL);
      if (isTimerOver(start_timer, finish_timer, timer)) {
        userInput(&game_info, &current_block, action = Down, &tetris_state);
        gettimeofday(&start_timer, NULL);
      }
    }

    printGame(game_info, tetris_state, field, panel);
  }
  freeMemory(&game_info);  //////нужен ли &current_block ????
  clear();
  delwin(field);
  delwin(panel);
}
