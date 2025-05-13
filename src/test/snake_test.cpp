#include <gtest/gtest.h>

#include "../brick_game/snake/snakeController.h"

TEST(model, test1) {
  GameInfo_t game_info;
  game_state state;
  s21::snakeModelClass sm_class(&game_info, &state);
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLSS; j++) {
      EXPECT_EQ(game_info.field[i][j], 0);
    }
  }
  EXPECT_EQ(game_info.score, 0);
  EXPECT_EQ(game_info.level, 1);
  EXPECT_EQ(game_info.speed, INIT_SPEED);
  EXPECT_EQ(game_info.pause, 0);
  EXPECT_EQ(state, START);
}

TEST(model, test2) {
  GameInfo_t game_info;
  game_state state;
  s21::snakeModelClass sm_class(&game_info, &state);
  sm_class.userInput(Start);
  EXPECT_EQ(state, MOVING);
  EXPECT_EQ(game_info.field[10][4], 2);
  EXPECT_EQ(game_info.field[11][4], 4);
  EXPECT_EQ(game_info.field[12][4], 4);
  EXPECT_EQ(game_info.field[13][4], 4);
}

TEST(model, test3) {
  GameInfo_t game_info;
  game_state state;
  s21::snakeModelClass sm_class(&game_info, &state);
  sm_class.userInput(Terminate);
  EXPECT_EQ(state, EXIT_STATE);
}

TEST(model, test4) {
  GameInfo_t game_info;
  game_state state;
  s21::snakeModelClass sm_class(&game_info, &state);
  sm_class.userInput(Start);
  sm_class.userInput(Left);
  sm_class.userInput(Left);
  sm_class.userInput(Left);
  sm_class.userInput(Left);
  sm_class.userInput(Left);
  EXPECT_EQ(state, GAMEOVER);
  sm_class.userInput(Start);
  EXPECT_EQ(state, MOVING);
}

TEST(model, test5) {
  GameInfo_t game_info;
  game_state state;
  s21::snakeModelClass sm_class(&game_info, &state);
  sm_class.userInput(Start);
  sm_class.setApple(9, 4);
  sm_class.userInput(Up);
  EXPECT_EQ(state, SPAWN);
}

TEST(model, test6) {
  GameInfo_t game_info;
  game_state state;
  s21::snakeModelClass sm_class(&game_info, &state);
  sm_class.userInput(Start);
  sm_class.setTail(10, 5);
  sm_class.userInput(Right);
  EXPECT_EQ(state, GAMEOVER);
  sm_class.userInput(Terminate);
  EXPECT_EQ(state, EXIT_STATE);
}

TEST(model, test7) {
  GameInfo_t game_info;
  game_state state;
  s21::snakeModelClass sm_class(&game_info, &state);
  sm_class.userInput(Start);
  sm_class.userInput(Left);
  sm_class.userInput(Down);
  EXPECT_EQ(state, MOVING);
  sm_class.userInput(Terminate);
  EXPECT_EQ(state, GAMEOVER);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}