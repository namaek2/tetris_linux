//
// Created by namaek_2 on 11/21/23.
//
#pragma once

#ifndef TETRIS_TETRISINPUT_H
#define TETRIS_TETRISINPUT_H

#define hide() printf("\e[?25l")

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>

static int peek_character = -1;
static struct termios new_settings; //, initial_settings;

class TetrisInput {
private:
public:
  // void init_keyboard();
  // void close_keyboard();
  // int _putch(int c);
  
  static int _kbhit();
  static int _getch();
  static void gotoxy(int x, int y);
};

#endif // TETRIS_TETRISINPUT_H
