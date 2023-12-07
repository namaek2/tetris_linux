//
// Created by namaek_2 on 11/21/23.
//
#pragma once

#ifndef TETRIS_TETRISCOLOR_H
#define TETRIS_TETRISCOLOR_H

#include <ostream>

namespace Color {

enum ColorCode {
  FG_RED = 31,
  FG_GREEN = 32,
  FG_YELLOW = 33,
  FG_BLUE = 34,
  FG_MAGENTA = 35,
  FG_CYAN = 36,
  FG_WHITE = 37,
  FG_BLACK = 30,
  FG_ORANGE = 33,
};

class Modifier {
  ColorCode code;

public:
  Modifier(ColorCode pCode) : code(pCode) {}
  friend std::ostream &operator<<(std::ostream &os, const Modifier &mod) {
    if (mod.code == FG_BLACK || mod.code == FG_ORANGE) {
      return os << "\033[1m\033[" << mod.code << "m";
    }
    return os << "\033[" << mod.code << "m";
  }
};
} // namespace Color

#endif // TETRIS_TETRISCOLOR_H
