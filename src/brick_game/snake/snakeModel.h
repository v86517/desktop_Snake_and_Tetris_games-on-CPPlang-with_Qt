/**
 * @file snakeModel.h
 * @brief Описание класса snakeModelClass
 *
 * Модель содержит бизнес-логику игры
 */

#pragma once

#include <iostream>

#include "structures.h"

namespace s21 {
/**
 * @class snakeModelClass
 * @brief Класс модели игры Snake
 */
class snakeModelClass {
 public:
  /**
   * @brief Конструктор
   * @param GameInfo_t Указатель на структуру информации о текущем состоянии
   * игры
   * @param state Указатель на структуру информации о текущем состоянии КА
   */
  snakeModelClass(GameInfo_t *GameInfo_t, game_state *state);
  /**
   * @brief Деструктор.
   */
  ~snakeModelClass();
  /**
   * @brief Получение параметра направления змейки
   * @return Возвращает направление
   */
  UserAction_t getDirection();
  /**
   * @brief КА. Принимает на вход пользовательское действие
   */
  void userInput(UserAction_t action);

  void setApple(int r, int c);
  void setTail(int r, int c);

 private:
  GameInfo_t *game_info;
  game_state *state;
  int *snake_tail_col;
  int *snake_tail_row;
  int snake_head_col;
  int snake_head_row;
  int snake_len;
  int apple_col;
  int apple_row;
  UserAction_t snake_direc;
  /**
   * @brief Инициализация информации о текущем состоянии игры и КА
   */
  void initGameInfo();

  /**
   * @brief Генерация яблока
   */
  void initApple();
  /**
   * @brief Инициализация данных класса snakeModelClass
   */
  void initState();
  /**
   * @brief Освобождение памяти
   */
  void freeMemory();
  /**
   * @brief Остановка программы при сбое выделения памяти
   */
  void exitError();
  /**
   * @brief Выделение памяти
   */
  void initMemory();
  /**
   * @brief Предпусковое состояние элементов игры Snake
   */
  void startState();
  /**
   * @brief Проверка на столкновения
   * @return Возвращает наличие столкновения с границами игрового поля или с
   * телом змейки
   */
  int checkCollide();
  /**
   * @brief Проверка наезда на яблоко
   * @return Возвращает наличие наезда на яблоко
   */
  int checkApple();
  /**
   * @brief Перемещение тела змейки
   */
  void moveSnake();
  /**
   * @brief Запись состояния игрового поля
   */
  void addBlocksToField();
  /**
   * @brief Обновление уровня и скорости
   */
  void writeLevelAndSpeed();
  /**
   * @brief Запись high_score
   */
  void writeHighScore();
  /**
   * @brief Получение из файла high_score
   */
  void initHighScoreFromFile();
  /**
   * @brief Запись в файл high_score
   */
  void writeHighScoreToFile();
};
}  // namespace s21