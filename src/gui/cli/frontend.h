/**
 * @file frontend.h
 * @brief Заголовочный файл интерфейса игры Tetris.
 */
#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>

#include "../../brick_game/snake/structures.h"

/**
 * @brief Определение кастомного цвета RED
 */
#define MY_COLOR_RED_I (12)
/**
 * @brief Определение кастомного цвета ORANGE
 */
#define MY_COLOR_ORANGE_J (13)
/**
 * @brief Определение кастомного цвета YELLOW
 */
#define MY_COLOR_YELLOW_L (14)
/**
 * @brief Определение кастомного цвета PINK
 */
#define MY_COLOR_PINK_O (15)
/**
 * @brief Определение кастомного цвета GREEN
 */
#define MY_COLOR_GREEN_S (16)
/**
 * @brief Определение кастомного цвета BLUE
 */
#define MY_COLOR_BLUE_T (17)
/**
 * @brief Определение кастомного цвета MAGENTA
 */
#define MY_COLOR_MAGENTA_Z (18)

/**
 * @brief Псевдоним пустого пикселя
 */
#define EMPTY_CELL 'E'
/**
 * @brief Псевдоним заполненного пикселя
 */
#define FULL_CELL 'F'

/**
 * @brief Получение пользовательмкого сигнала с клавиатуры
 * @return Возвращает полученный сигнал
 */
UserAction_t get_signal(int user_input, bool *hold);
/**
 * @brief Изображение прямоугольника
 */
void printRectangle(WINDOW *w, int topR, int bottomR, int leftC, int rightC);
/**
 * @brief Инициализация кастомных цветов
 */
void initColor();
/**
 * @brief Оформление окон
 */
void initWindows(WINDOW *field, WINDOW *panel);
/**
 * @brief Вывод изображения
 */
void printGame(GameInfo_t actual_game_info, game_state tetris_state,
               WINDOW *field, WINDOW *panel);
/**
 * @brief Вывод изображения информационных полей
 */
void printGameInfo(GameInfo_t actual_game_info, WINDOW *panel);
/**
 * @brief Удаление изображения в поле next
 */
void clearNext(WINDOW *panel);
/**
 * @brief Вывод изображения начала игры
 */
void printStartState(WINDOW *field);
/**
 * @brief Вывод изображения паузы игры
 */
void printPauseState(WINDOW *field);
/**
 * @brief Вывод изображения окончания игры
 */
void printGameOverState(WINDOW *field);
/**
 * @brief Вывод изображения игрового поля
 */
void printFieldState(GameInfo_t actual_game_info, WINDOW *field);

#endif