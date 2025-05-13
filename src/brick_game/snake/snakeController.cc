/**
 * @file snakeController.cpp
 * @brief Реализация класса snakeControllerClass
 */

#include "snakeController.h"

using namespace s21;

void snakeControllerClass::userInput(UserAction_t action) {
  sm_class->userInput(action);
}

UserAction_t snakeControllerClass::getDirection() {
  return sm_class->getDirection();
}

int snakeControllerClass::isTimerOver(struct timeval start_timer,
                                      struct timeval finish_timer,
                                      suseconds_t timer) {
  suseconds_t finish_time =
      finish_timer.tv_sec * 1000000 + finish_timer.tv_usec;
  suseconds_t start_time = start_timer.tv_sec * 1000000 + start_timer.tv_usec;
  int res = finish_time - start_time > timer ? 1 : 0;
  return res;
}