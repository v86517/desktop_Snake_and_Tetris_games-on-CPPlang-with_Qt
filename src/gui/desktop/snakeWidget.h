/**
 * @file snakeWidget.h
 * @brief Заголовочный файл интерфейса игры Snake с использованием Qt
 */

#pragma once

#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QPalette>
#include <QTimer>
#include <QVBoxLayout>

#include "../../brick_game/snake/snakeController.h"
#include "../../brick_game/snake/snakeModel.h"

namespace s21 {
/**
 * @class snakeQTClass
 * @brief Класс интерфейса игры Snake для Qt
 */
class snakeQTClass : public QWidget {
  //  Q_OBJECT
  // private:
 public:
  /**
   * @brief Конструктор.
   * @param sc_class Указатель на объект контроллера игры
   * @param game_info Указатель на структуру информации о текущем состоянии
   * игры
   * @param state Указатель на структуру информации о текущем состоянии КА
   */
  snakeQTClass(snakeControllerClass *sc_class, GameInfo_t *game_info,
               game_state *state);
  /**
   * @brief Деструктор
   */
  ~snakeQTClass();

 private:
  snakeControllerClass *sc_class;
  GameInfo_t *game_info;
  UserAction_t act;
  game_state *state;
  int pix_size = 30;
  QTimer *timer;
  int timer_val = 0;
  int speed_val;
  QLabel *level_label;
  QLabel *score_label;
  QLabel *high_score_Label;
  QLabel *test1;
  QLabel *test2;
  /**
   * @brief Отрисовка игрового и информационных полей
   */
  void paintEvent(QPaintEvent *event);
  /**
   * @brief Обработка сигналов с клавиатуры
   */
  void keyPressEvent(QKeyEvent *event);
  /**
   * @brief Обновление состояния игры по игровому таймеру
   */
  void timerEvent(QTimerEvent *event);

  /**
   * @brief Создание информационного поля
   */
  void addLabel(QVBoxLayout *info, QLabel *label, const QFont &font);
  /**
   * @brief Задание фоновых элементов игрового интерфейса
   */
  void layout();
  /**
   * @brief Печать информации информационных полей
   */
  void printGameInfo();
  /**
   * @brief Отрисовка элементов игры
   */
  void printFieldState(QPainter *p);
  /**
   * @brief Сигнал для отрисовки
   */
  void updatePrint();
  /**
   * @brief Инициализация информации о текущем состоянии игры и КА
   */
  void startState();
  /**
   * @brief Установка цвета элементов игрового поля
   */
  void chooseColor(int color, QPainter *p);
  /**
   * @brief Создание сообщений о начале, окончании и паузы инры
   */
  void printStateBanner(QColor color, QPaintEvent *event, QPainter *painter,
                        const QString &text);
};
}  // namespace s21