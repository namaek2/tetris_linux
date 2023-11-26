//
// Created by namaek_2 on 11/21/23.
//

#ifndef TETRIS_TETRISSTART_H
#define TETRIS_TETRISSTART_H
#include "../include/TetrisColor.h"
#include "../include/TetrisInput.h"
#include "../include/TetrisTerminal.h"
#include <iostream>

using namespace std;

enum level { BEGINNER = 20, AMATEUR = 22, EXPERT = 24, EXIT = 26 };

class TetrisStart {
private:
  int cursor_y = 20;

public:
  static int GetEnum(int level_type);
  TetrisStart();

  void PrintTitle();
  static void PrintMenu();

  int SelectMenu();
  int Session();
  void CursorMove(int dirrection, int y);
  int MenuSelected(int y);

  int GetCursorY();
  void SetCursorY(int y);

  void PrintT(int x, int y);
  void PrintE(int x, int y);
  void PrintR(int x, int y);
  void PrintI(int x, int y);
  void PrintS(int x, int y);
};

#endif // TETRIS_TETRISSTART_H
