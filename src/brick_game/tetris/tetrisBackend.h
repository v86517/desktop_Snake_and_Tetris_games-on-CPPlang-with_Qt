/**
 * @file tetrisBackend.h
 * @brief Заголовочный файл бизнес-логики игры Tetris
 */

#ifndef TETRISBACKEND_H
#define TETRISBACKEND_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "../../brick_game/snake/structures.h"

/**
 * @brief Генерация блока
 */
int getRandBlockNum();
/**
 * @brief Генерация поворота блока
 */
int getRandBlockRot();
/**
 * @brief Инициализация информации о текущем состоянии игры и КА
 */
void initGameInfo(GameInfo_t *game_info);
/**
 * @brief Контроль истечения игрового таймера
 */
int isTimerOver(struct timeval start_timer, struct timeval finish_timer,
                suseconds_t timer);
/**
 * @brief КА. Принимает на вход пользовательское действие
 */
void userInput(GameInfo_t *game_info, Block_t *current_block,
               UserAction_t action, game_state *tetris_state);
/**
 * @brief Перемещение блока вниз
 */
int moveBlockDown(GameInfo_t *game_info, Block_t *current_block, Block_t *temp);
/**
 * @brief Обработка заполненных линий
 */
void processFullRows(GameInfo_t *game_info);
/**
 * @brief Обновление уровня и скорости
 */
void writeLevelAndSpeed(GameInfo_t *game_info);
/**
 * @brief Запись high_score
 */
void writeHighScore(GameInfo_t *game_info);
/**
 * @brief Проверка на столкновения
 */
int checkCollide(GameInfo_t *game_info, Block_t block);
/**
 * @brief Вращение блока
 */
void rotateBlock(Block_t *block);
/**
 * @brief Копирование блока
 */
Block_t copyBlock(Block_t *current_block);
/**
 * @brief Удаление блока
 */
void delBlock(Block_t *block);
/**
 * @brief Удаление блока с игрового поля
 */
void delBlockFromField(GameInfo_t *game_info, Block_t *current_block);
/**
 * @brief Выделение памяти
 */
void initMemory(GameInfo_t *game_info);
/**
 * @brief Освобождение пасяти
 */
void freeMemory(GameInfo_t *game_info);
/**
 * @brief Инициализация данных игры
 */
void initState(GameInfo_t *game_info);
/**
 * @brief Нанесение блока на игровое поле
 */
void addBlockToField(GameInfo_t *game_info, Block_t *current_block);
/**
 * @brief Получение информации о ширине блока
 */
int getBlockWidth(int block_num);
/**
 * @brief Получение информации о блоке
 */
int getFigureNum(GameInfo_t *game_info);
/**
 * @brief Инициализация блока next
 */
void initNextBlock(GameInfo_t *game_info);
/**
 * @brief Инициализация поворота блока next
 */
void rotateNextBlock(GameInfo_t *game_info, int block_num, int block_rot,
                     int w);
/**
 * @brief Удаление пустых линий в массиве блока
 */
void delUpEmptyLines(GameInfo_t *game_info, int w);
/**
 * @brief Инициализация структуры блока
 */
void initBlockInfo(GameInfo_t *game_info, Block_t *current_block);
/**
 * @brief Получение из файла high_score.
 */
void initHighScoreFromFile(GameInfo_t *game_info);
/**
 * @brief Запись в файл high_score.
 */
void writeHighScoreToFile(GameInfo_t *game_info);

#endif
