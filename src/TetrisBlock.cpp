//
// Created by namaek_2 on 11/21/23.
//

#include "../include/TetrisGame.h"

TetrisBlock::TetrisBlock(){};
TetrisBlock::~TetrisBlock() { delete this; }

// TetrisBlock TetrisBlock::*Clone() { return new TetrisBlock(*this); }

void TetrisBlock::BlockColor() {}

bool TetrisBlock::GetBlock(int y, int x) { return block[y][x]; }

void TetrisBlock::SetBlock(bool arr[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      block[i][j] = arr[i][j];
    }
  }
}
void TetrisBlock::BlockPrint(int y, int x) {
  BlockColor();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      // if (y + i < 11 || x + j < 11 || y + i > 50 || x + j > 30) {
      //   continue;
      // }
      if (block[i][j]) { // 블록이 있어야 할 공간이면 출력
        TetrisInput::gotoxy(x + j, y + i);
        cout << "▣";
      }
    }
  }
}

void TetrisBlock::BlockPrintGuide(int y, int x) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (block[i][j]) { // 블록이 있어야 할 공간이면 출력
        TetrisInput::gotoxy(x + j, y + i);
        cout << "▣";
      }
    }
  }
}

void TetrisBlock::BlockPrintErase(int y, int x) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (block[i][j]) { // 블록이 없어야 할 공간이면 지우기
        TetrisInput::gotoxy(x + j, y + i);
        cout << " ";
      }
    }
  }
}

// 시계방향 회전 연산
void TetrisBlock::BlockTurnClockWise() {
  // 회전축 기준 꼭짓점 회전
  bool temp = block[2][3];
  block[2][3] = block[0][3];
  block[0][3] = block[0][1];
  block[0][1] = block[2][1];
  block[2][1] = temp;

  // 회전축 기준 모서리 회전
  temp = block[1][3];
  block[1][3] = block[0][2];
  block[0][2] = block[1][1];
  block[1][1] = block[2][2];
  block[2][2] = temp;
}

// 반시계방향 회전 연산
void TetrisBlock::BlockTurnReverseClockWise() {
  // 회전축 기준 꼭짓점 회전
  bool temp = block[2][3];
  block[2][3] = block[2][1];
  block[2][1] = block[0][1];
  block[0][1] = block[0][3];
  block[0][3] = temp;

  // 회전축 기준 모서리 회전
  temp = block[1][3];
  block[1][3] = block[2][2];
  block[2][2] = block[1][1];
  block[1][1] = block[0][2];
  block[0][2] = temp;
}

// I 블록 시계방향 회전 연산
void TetrisBlockI::BlockTurnClockWise() {
  // 회전축 기준 꼭짓점 회전
  bool temp = block[2][3];
  block[2][3] = block[0][3];
  block[0][3] = block[0][1];
  block[0][1] = block[2][1];
  block[2][1] = temp;

  // 회전축 기준 모서리 회전
  temp = block[1][3];
  block[1][3] = block[0][2];
  block[0][2] = block[1][1];
  block[1][1] = block[2][2];
  block[2][2] = temp;

  // I 블록 회전
  temp = block[1][0];
  block[1][0] = block[3][2];
  block[3][2] = temp;
}

// I 블록 반시계방향 회전 연산
void TetrisBlockI::BlockTurnReverseClockWise() {
  // 회전축 기준 꼭짓점 회전
  bool temp = block[2][3];
  block[2][3] = block[2][1];
  block[2][1] = block[0][1];
  block[0][1] = block[0][3];
  block[0][3] = temp;

  // 회전축 기준 모서리 회전
  temp = block[1][3];
  block[1][3] = block[2][2];
  block[2][2] = block[1][1];
  block[1][1] = block[0][2];
  block[0][2] = temp;

  // I 블록 회전
  temp = block[1][0];
  block[1][0] = block[3][2];
  block[3][2] = temp;
}

void TetrisBlockO::BlockTurnClockWise() {}
void TetrisBlockO::BlockTurnReverseClockWise() {}

void TetrisBlockI::BlockColor() { cout << CYAN; }
void TetrisBlockT::BlockColor() { cout << MAGENTA; }
void TetrisBlockO::BlockColor() { cout << YELLOW; }
void TetrisBlockL::BlockColor() { cout << ORANGE; }
void TetrisBlockJ::BlockColor() { cout << BLUE; }
void TetrisBlockS::BlockColor() { cout << GREEN; }
void TetrisBlockZ::BlockColor() { cout << RED; }

TetrisBlockI::TetrisBlockI() {
  SetBlock(default_block);
  color_code = code;
}
TetrisBlockT::TetrisBlockT() {
  SetBlock(default_block);
  color_code = code;
}
TetrisBlockO::TetrisBlockO() {
  SetBlock(default_block);
  color_code = code;
}
TetrisBlockL::TetrisBlockL() {
  SetBlock(default_block);
  color_code = code;
}
TetrisBlockJ::TetrisBlockJ() {
  SetBlock(default_block);
  color_code = code;
}
TetrisBlockS::TetrisBlockS() {
  SetBlock(default_block);
  color_code = code;
}
TetrisBlockZ::TetrisBlockZ() {
  SetBlock(default_block);
  color_code = code;
}

TetrisBlockI::~TetrisBlockI() { delete this; }
TetrisBlockT::~TetrisBlockT() { delete this; }
TetrisBlockO::~TetrisBlockO() { delete this; }
TetrisBlockL::~TetrisBlockL() { delete this; }
TetrisBlockJ::~TetrisBlockJ() { delete this; }
TetrisBlockS::~TetrisBlockS() { delete this; }
TetrisBlockZ::~TetrisBlockZ() { delete this; }