#include "../include/TetrisGame.h"

int main(void) {

  // TetrisStart tetris_start;
  // tetris_start.~TetrisStart();
  TetrisGame tetris_game;
  tetris_game.~TetrisGame();
  //  TetrisGame::GameOver();
  while (!TetrisInput::_kbhit())
    TetrisInput::_getch();

  return 0;
}