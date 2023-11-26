//
// Created by namaek_2 on 11/21/23.
//

#include "../include/TetrisInput.h"

void TetrisInput::init_keyboard() {
  tcgetattr(0, &initial_settings);
  new_settings = initial_settings;
  new_settings.c_lflag &= ~ICANON;
  new_settings.c_lflag &= ~ECHO;
  new_settings.c_cc[VMIN] = 1;
  new_settings.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &new_settings);
}

void TetrisInput::close_keyboard() { tcsetattr(0, TCSANOW, &initial_settings); }

int TetrisInput::_kbhit() {
  unsigned char ch;
  int nread;

  if (peek_character != -1)
    return 1;
  new_settings.c_cc[VMIN] = 0;
  tcsetattr(0, TCSANOW, &new_settings);
  nread = read(0, &ch, 1);
  new_settings.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &new_settings);
  if (nread == 1) {
    peek_character = ch;
    return 1;
  }
  return 0;
}

int TetrisInput::_getch() {
  char ch;
  if (peek_character != -1) {
    ch = peek_character;
    peek_character = -1;
    return ch;
  }
  read(0, &ch, 1);
  return ch;
}

int TetrisInput::_putch(int c) {
  putchar(c);
  fflush(stdout);
  return c;
}

void TetrisInput::gotoxy(int x, int y) {
  printf("\033[%d;%df", y, x);
  // printf("%c[%d;%df", 0x1B, y, x);
  fflush(stdout);
}
