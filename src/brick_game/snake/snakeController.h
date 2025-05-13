/**
 * @file snakeController.h
 * @brief Описание класса snakeControllerClass
 *
 * Контроллер осуществляет модификацию модели по действию пользователя и
 * игровому таймеру
 */

#pragma once

#include <sys/time.h>

#include "snakeModel.h"

namespace s21 {
/**
 * @class snakeControllerClass
 * @brief Класс контроллера игры Snake
 */
class snakeControllerClass {
 public:
  /**
   * @brief Конструктор
   * @param sm_class Указатель на объект snakeModelClass
   */
  snakeControllerClass(snakeModelClass* sm_class) : sm_class(sm_class){};
  /**
   * @brief Деструктор
   */
  ~snakeControllerClass() = default;
  /**
   * @brief Передача пользовательских действий в модель
   * @param action Пользовательское действие
   */
  void userInput(UserAction_t action);
  /**
   * @brief Обращение к модели за получением направления движения
   * @return Возвращает направление
   */
  UserAction_t getDirection();
  /**
   * @brief Контроль истечения игрового таймера
   * @return Возвращает истек ли таймер
   */
  int isTimerOver(struct timeval start_timer, struct timeval finish_timer,
                  suseconds_t timer);

 private:
  snakeModelClass* sm_class;
};
}  // namespace s21