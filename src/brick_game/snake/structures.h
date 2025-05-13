/**
 * @file structures.h
 * @brief Файл содержит объявление структур и констант игр
 */
#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 * @brief Высота игрового поля
 */
#define ROWS 20
/**
 * @brief Ширина игрового поля
 */
#define COLSS 10
/**
 * @brief Ширина блока
 */
#define NEXT_WIDTH 4
/**
 * @brief Пустой пиксель игрового поля
 */
#define EMPTY 0
/**
 * @brief Количество вариантов блоков игры Tetris
 */
#define NUM_BLOCKS 7
/**
 * @brief Количество вариантов вращения блоков игры Tetris
 */
#define NUM_ROTS 4

/**
 * @brief Идентефикатор клавиши Escape
 */
#define ESCAPE_KEY 27
/**
 * @brief Идентефикатор клавиши Enter
 */
#define ENTER_KEY 10
/**
 * @brief Идентефикатор клавиши Space
 */
#define SPACE_KEY ' '
/**
 * @brief Максимальный размер змейки
 */
#define FINAL_LENGTH 200

/**
 * @brief Количество очков за одну линию Tetris
 */
#define LINE_SCORE 100
/**
 * @brief Максимальный уровень игр
 */
#define LAST_LEVEL 10
/**
 * @brief Количество очков для повышения уровня в игре Tetris
 */
#define SCORE_LEVELUP 600
/**
 * @brief Начальная скорорость в играх
 */
#define INIT_SPEED 1000000
/**
 * @brief Изменение скорорости в играх
 */
#define SPEED_LEVELUP 100000
/**
 * @brief Количество очков для повышения уровня в игре Snake
 */
#define SNAKE_SCORE_LEVELUP 5

/**
 * @enum UserAction_t
 * @brief Действия пользователя в играх
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  NOSIG,
} UserAction_t;

/**
 * @enum game_state
 * @brief Состояния КА
 */
typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  REACH,
  GAMEOVER,
  EXIT_STATE
} game_state;
/**
 * @struct GameInfo_t
 * @brief Структура, содержащая информацию о текущем состоянии игры
 */
typedef struct {
  /// @brief Массив для хранения игрового поля
  int **field;
  /// @brief Массив для хранения блока next
  int **next;
  /// @brief Текущее количество набранных очков
  int score;
  /// @brief Рекордное количество очков
  int high_score;
  /// @brief Текущий уровень инры
  int level;
  /// @brief Текущая скорость инры
  int speed;
  /// @brief Состояние паузы
  int pause;
} GameInfo_t;

/**
 * @struct Block_t
 * @brief Структура, содержащая информацию о блоке
 */
typedef struct {
  /// @brief Массив для хранения блока
  int **block_array;
  /// @brief Ширина блока
  int block_width;
  /// @brief Координата блока по высоте
  int block_row;
  /// @brief Координата блока по ширине
  int block_col;
} Block_t;

#endif