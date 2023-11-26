//
// Created by namaek_2 on 11/21/23.
//

#ifndef TETRIS_TETRISBLOCK_H
#define TETRIS_TETRISBLOCK_H

class TetrisBlock {
private:
  const int BLOCK_I[4][4] = {
      {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  const int BLOCK_T[4][4] = {
      {0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 1, 0}, {0, 0, 0, 0}};

  const int BLOCK_O[4][4] = {
      {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};

  const int BLOCK_L[4][4] = {
      {0, 0, 0, 0}, {0, 1, 1, 1}, {0, 1, 0, 0}, {0, 0, 0, 0}};

  const int BLOCK_J[4][4] = {
      {0, 0, 0, 0}, {0, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}};

  const int BLOCK_S[4][4] = {
      {0, 0, 0, 0}, {0, 0, 1, 1}, {0, 1, 1, 0}, {0, 0, 0, 0}};

  const int BLOCK_Z[4][4] = {
      {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 1}, {0, 0, 0, 0}};
};

#endif // TETRIS_TETRISBLOCK_H
