//
// Created by namaek_2 on 11/21/23.
//

#ifndef TETRIS_TETRISINPUT_H
#define TETRIS_TETRISINPUT_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

static int peek_character = -1;
static struct termios initial_settings, new_settings;

class TetrisInput {
private:
public:
  void init_keyboard();
  void close_keyboard();
  int _kbhit();
  int _getch();
  int _putch(int c);
  void gotoxy(int x, int y);
};

#endif // TETRIS_TETRISINPUT_H
