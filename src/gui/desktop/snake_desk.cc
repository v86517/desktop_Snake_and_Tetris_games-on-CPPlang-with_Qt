/**
 * @file snake_desk.cpp
 * @brief Файл для запуска игры Snake с использованием Qt
 */

#include "snakeWidget.h"

using namespace s21;

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  GameInfo_t game_info;
  game_state state;
  snakeModelClass sm_class(&game_info, &state);
  snakeControllerClass sc_class(&sm_class);
  snakeQTClass sQT_class(&sc_class, &game_info, &state);
  sQT_class.show();
  return app.exec();
}