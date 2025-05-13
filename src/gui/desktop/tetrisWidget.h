/**
 * @file tetrisWidget.h
 * @brief Заголовочный файл интерфейса игры Tetris с использованием Qt
 */

#pragma once

#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QPalette>
#include <QTimer>
#include <QVBoxLayout>

extern "C" {
#include "../../brick_game/tetris/tetrisBackend.h"
}
/**
 * @class tetrisQTClass
 * @brief Класс интерфейса игры Snake для Qt
 */
class tetrisQTClass : public QWidget {
 public:
  /**
   * @brief Конструктор
   */
  tetrisQTClass();
  /**
   * @brief Деструктор
   */
  ~tetrisQTClass();

  /**
   * @brief Отрисовка всего поля.
   */

 private:
  GameInfo_t game_info;
  Block_t currentFigure;
  UserAction_t act;
  game_state state;
  int pix_size = 30;
  QTimer *timer;
  int timer_val = 0;
  int speed_val;
  QLabel *level_label;
  QLabel *score_label;
  QLabel *high_score_Label;
  QLabel *next;
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