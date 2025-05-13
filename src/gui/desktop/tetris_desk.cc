/**
 * @file tetris_desk.cpp
 * @brief Файл для запуска игры Tetris с использованием Qt
 */

#include "tetrisWidget.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  tetrisQTClass tQT_class;
  tQT_class.show();
  return app.exec();
}