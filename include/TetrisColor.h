//
// Created by namaek_2 on 11/21/23.
//
#pragma once

#ifndef TETRIS_TETRISCOLOR_H
#define TETRIS_TETRISCOLOR_H

#include <ostream>

namespace Color {

enum Code {
  FG_RED = 31,
  FG_GREEN = 32,
  FG_YELLOW = 33,
  FG_BLUE = 34,
  FG_MAGENTA = 95,
  FG_CYAN = 96,
  FG_WHITE = 97,
  FG_ORANGE = 93,
};

class Modifier {
  Code code;

public:
  Modifier(Code pCode) : code(pCode) {}
  friend std::ostream &operator<<(std::ostream &os, const Modifier &mod) {
    return os << "\033[" << mod.code << "m";
  }
};
} // namespace Color

#endif // TETRIS_TETRISCOLOR_H
