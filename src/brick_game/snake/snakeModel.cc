/**
 * @file snakeModel.cc
 * @brief Реализация класса snakeModelClass
 */

#include "snakeModel.h"

using namespace s21;

snakeModelClass::snakeModelClass(GameInfo_t *GameInfo_t, game_state *game_state)
    : game_info(GameInfo_t), state(game_state) {
  initState();
}

void snakeModelClass::initState() {
  initMemory();
  initGameInfo();
}

void snakeModelClass::initMemory() {
  game_info->field = NULL;
  snake_tail_col = NULL;
  snake_tail_row = NULL;
  snake_tail_col = new int[ROWS * COLSS];
  snake_tail_row = new int[ROWS * COLSS];
  if (snake_tail_col == NULL || snake_tail_row == NULL) {
    exitError();
  } else {
    snake_tail_col[ROWS * COLSS] = {0};
    snake_tail_row[ROWS * COLSS] = {0};
  }

  if (game_info->field == NULL) {
    game_info->field = new int *[ROWS];
  }
  if (game_info->field == NULL) {
    exitError();
  } else {
    for (int i = 0; i < ROWS; i++) {
      game_info->field[i] = new int[COLSS]();
      if (game_info->field[i] == NULL) {
        for (int j = 0; j < i; j++) {
          delete[] game_info->field[j];
        }
        delete[] game_info->field;
        exitError();
      }
    }
  }
}

snakeModelClass::~snakeModelClass() { freeMemory(); }

void snakeModelClass::initGameInfo() {
  game_info->next = NULL;
  initHighScoreFromFile();
  game_info->score = 0;
  game_info->level = 1;
  game_info->speed = INIT_SPEED;
  game_info->pause = 0;
  *state = START;
}

/**
 * @brief Clears the square matrix.
 * @param[in,out] matrix The pointer to the Matrix for purification.
 * @param H Matrix height parameter.
 */
void snakeModelClass::freeMemory() {
  if (game_info->field != NULL) {
    for (int i = 0; i < ROWS; i++) {
      delete[] game_info->field[i];
    }
    delete[] game_info->field;
  }
  delete[] snake_tail_col;
  delete[] snake_tail_row;
}

void snakeModelClass::exitError() {
  std::perror("Error memory allocation");
  exit(EXIT_FAILURE);
}

void snakeModelClass::initApple() {
  int emptyPlace = 0;
  while (emptyPlace == 0) {
    apple_row = (rand() % (ROWS));
    apple_col = (rand() % (COLSS));
    for (int i = 0; i < snake_len; i++) {
      if (snake_tail_col[i] == apple_col && snake_tail_row[i] == apple_row) {
        emptyPlace = 0;
        break;
      } else
        emptyPlace = 1;
    }
  }
}

void snakeModelClass::startState() {
  snake_len = NEXT_WIDTH;
  snake_direc = Up;
  snake_head_row = 10;
  snake_head_col = 4;

  snake_tail_col[ROWS * COLSS] = {0};
  snake_tail_row[ROWS * COLSS] = {0};

  for (int i = 0; i < snake_len; ++i) {
    snake_tail_col[i] = snake_head_col;
    snake_tail_row[i] = snake_head_row + i;
  }
}

int snakeModelClass::checkCollide() {
  for (int i = 1; i < snake_len; ++i) {
    if (snake_tail_col[i] == snake_head_col &&
        snake_tail_row[i] == snake_head_row)
      return 0;
  }
  if (snake_head_col >= COLSS || snake_head_col < 0 || snake_head_row >= ROWS ||
      snake_head_row < 0)
    return 0;
  return 1;
}

int snakeModelClass::checkApple() {
  if (snake_head_col == apple_col && snake_head_row == apple_row)
    return 0;
  else
    return 1;
}

void snakeModelClass::moveSnake() {
  for (int i = snake_len - 1; i > 0; --i) {
    snake_tail_col[i] = snake_tail_col[i - 1];
    snake_tail_row[i] = snake_tail_row[i - 1];
  }

  if (snake_direc == Left)
    --snake_head_col;
  else if (snake_direc == Right)
    ++snake_head_col;
  else if (snake_direc == Up)
    --snake_head_row;
  else if (snake_direc == Down)
    ++snake_head_row;

  snake_tail_col[0] = snake_head_col;
  snake_tail_row[0] = snake_head_row;
}

void snakeModelClass::addBlocksToField() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLSS; ++j) {
      game_info->field[i][j] = 0;
      if (apple_row == i && apple_col == j) {
        if (!(apple_row == snake_head_row && apple_col == snake_head_col))
          game_info->field[i][j] = 5;
      }

      for (int k = 0; k < snake_len; ++k) {
        if (snake_tail_col[k] == j && snake_tail_row[k] == i) {
          game_info->field[i][j] = 4;
          break;
        }
      }
      if (snake_head_row == i && snake_head_col == j)
        game_info->field[i][j] = 2;
    }
  }
}

void snakeModelClass::userInput(UserAction_t action) {
  if (*state == GAMEOVER) {
    switch (action) {
      case Start:
        initGameInfo();
        startState();
        *state = SPAWN;
        break;
      case Terminate:
        *state = EXIT_STATE;
        break;
      default:
        break;
    }
  }
  if (*state == START) {
    switch (action) {
      case Start:
        startState();
        *state = SPAWN;
        break;
      case Terminate:
        *state = EXIT_STATE;
        break;
      default:
        break;
    }
  }
  if (*state == SPAWN) {
    initApple();
    *state = MOVING;
  }
  if (*state == MOVING) {
    switch (action) {
      case Left:
        if (snake_direc != Right) {
          snake_direc = Left;
          moveSnake();
          if (!checkApple()) *state = REACH;
          addBlocksToField();
          if (checkCollide() == 0) *state = GAMEOVER;
        }
        break;
      case Right:
        if (snake_direc != Left) {
          snake_direc = Right;
          moveSnake();
          if (!checkApple()) *state = REACH;
          addBlocksToField();
          if (checkCollide() == 0) *state = GAMEOVER;
        }
        break;
      case Up:
        if (snake_direc != Down) {
          snake_direc = Up;
          moveSnake();
          if (!checkApple()) *state = REACH;
          addBlocksToField();
          if (checkCollide() == 0) *state = GAMEOVER;
        }
        break;
      case Down:
        if (snake_direc != Up) {
          snake_direc = Down;
          moveSnake();
          if (!checkApple()) *state = REACH;
          addBlocksToField();
          if (checkCollide() == 0) *state = GAMEOVER;
        }
        break;
      case Terminate:
        *state = GAMEOVER;
        break;
      default:
        addBlocksToField();
        break;
    }
  }
  if (*state == REACH) {
    ++snake_len;
    writeLevelAndSpeed();
    writeHighScore();
    if (game_info->level > LAST_LEVEL)
      *state = GAMEOVER;
    else
      *state = SPAWN;
  }
}

void snakeModelClass::writeLevelAndSpeed() {
  game_info->score++;
  game_info->level = game_info->score / SNAKE_SCORE_LEVELUP + 1;
  game_info->speed = INIT_SPEED - (SPEED_LEVELUP * (game_info->level - 1));
}

void snakeModelClass::writeHighScore() {
  if (game_info->score > game_info->high_score) {
    game_info->high_score = game_info->score;
    writeHighScoreToFile();
  }
}

void snakeModelClass::initHighScoreFromFile() {
  FILE *file = fopen("snake_high_score.txt", "r");
  if (file) {
    fscanf(file, "%d", &(game_info->high_score));
    fclose(file);
  } else {
    game_info->high_score = 0;
  }
}

void snakeModelClass::writeHighScoreToFile() {
  FILE *file = fopen("snake_high_score.txt", "w");
  if (file) {
    fprintf(file, "%d", game_info->high_score);
    fclose(file);
  }
}

void snakeModelClass::setApple(int r, int c) {
  apple_row = r;
  apple_col = c;
}

void snakeModelClass::setTail(int r, int c) {
  snake_tail_row[2] = r;
  snake_tail_col[2] = c;
}
// int snakeModelClass::getSpeed() { return game_info->speed; }
UserAction_t snakeModelClass::getDirection() { return snake_direc; }

/*int main() {
  snakeModelClass m;
  std::cout << sizeof(*m.game_info->field) << std::endl;
  std::cout << sizeof(*m.snake_tail_col) << std::endl;
  std::cout << sizeof(*m.snake_tail_col) << std::endl;

  std::cout << std::endl;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLSS; j++) {
      std::cout << m.game_info->field[i][j] << " ";
    }
    std::cout << std::endl;
  }

  for (int i = 0; i < ROWS * COLSS; i++) {
    std::cout << m.snake_tail_col[i] << " ";
  }
  std::cout << std::endl;

  for (int i = 0; i < ROWS * COLSS; i++) {
    std::cout << m.snake_tail_row[i] << " ";
  }
  std::cout << std::endl;

  m.~snakeModelClass();

  return 0;
}*/