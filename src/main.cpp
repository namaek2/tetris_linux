#include "../include/TetrisGame.h"

int main(void) {
  TetrisGame tetris_game;
  tetris_game.~TetrisGame();

  /*
  while (!TetrisInput::_kbhit()) {
    TetrisInput::_getch();
  }*/

  /*
  while (!TetrisInput::_kbhit()) {
    int c = TetrisInput::_getch();
    cout << c << endl;
    c = TetrisInput::_getch();
    if (c == NULL)
      cout << "ffffff";
    else
      cout << "c : " + c << endl;

    break;
    c = TetrisInput::_getch();
    cout << c << endl;
    usleep(100);
  }
*/
  return 0;
}