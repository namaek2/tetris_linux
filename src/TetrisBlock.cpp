//
// Created by namaek_2 on 11/21/23.
//

#include "../include/TetrisGame.h"

int TetrisBlock::GetCode() { return code; }

void TetrisBlock::SetCode(int value) { code = value; }

// 블록의 x, y 좌표의 값 반환
bool TetrisBlock::GetBlock(int y, int x) { return block[y][x]; }

// 블록의 x, y 좌표의 값을 설정
void TetrisBlock::SetBlock(bool value, int y, int x) { block[y][x] = value; }

// 블록 출력
void TetrisBlock::BlockPrint(int y, int x) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (y + i < 11 && x + j > 10 && x + j < 31) {
        continue;
      } else if (GetBlock(i, j)) {
        TetrisInput::gotoxy(x + j, y + i);
        cout << "▣";
      }
    }
  }
  TetrisInput::gotoxy(1, 2);
}

// 블록 지우기
void TetrisBlock::BlockPrintErase(int y, int x) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (GetBlock(i, j)) {
        TetrisInput::gotoxy(x + j, y + i);
        cout << " ";
      }
    }
  }
}

// 시계방향 회전 연산
void TetrisBlock::BlockTurnClockWise() {
  bool temp = GetBlock(2, 3);
  SetBlock(GetBlock(0, 3), 2, 3);
  SetBlock(GetBlock(0, 1), 0, 3);
  SetBlock(GetBlock(2, 1), 0, 1);
  SetBlock(temp, 2, 1);

  temp = GetBlock(1, 3);
  SetBlock(GetBlock(0, 2), 1, 3);
  SetBlock(GetBlock(1, 1), 0, 2);
  SetBlock(GetBlock(2, 2), 1, 1);
  SetBlock(temp, 2, 2);
}

// 반시계방향 회전 연산
void TetrisBlock::BlockTurnReverseClockWise() {
  bool temp = GetBlock(2, 3);
  SetBlock(GetBlock(2, 1), 2, 3);
  SetBlock(GetBlock(0, 1), 2, 1);
  SetBlock(GetBlock(0, 3), 0, 1);
  SetBlock(temp, 0, 3);

  temp = GetBlock(1, 3);
  SetBlock(GetBlock(2, 2), 1, 3);
  SetBlock(GetBlock(1, 1), 2, 2);
  SetBlock(GetBlock(0, 2), 1, 1);
  SetBlock(temp, 0, 2);
}

// I 블록 시계방향 회전 연산 오버라이딩
void TetrisBlockI::BlockTurnClockWise() {
  bool temp = GetBlock(2, 3);
  SetBlock(GetBlock(0, 3), 2, 3);
  SetBlock(GetBlock(0, 1), 0, 3);
  SetBlock(GetBlock(2, 1), 0, 1);
  SetBlock(temp, 2, 1);

  temp = GetBlock(1, 3);
  SetBlock(GetBlock(0, 2), 1, 3);
  SetBlock(GetBlock(1, 1), 0, 2);
  SetBlock(GetBlock(2, 2), 1, 1);
  SetBlock(temp, 2, 2);

  temp = GetBlock(1, 0);
  SetBlock(GetBlock(3, 2), 1, 0);
  SetBlock(temp, 3, 2);
}

// I 블록 반시계방향 회전 연산 오버라이딩
void TetrisBlockI::BlockTurnReverseClockWise() {
  bool temp = GetBlock(2, 3);
  SetBlock(GetBlock(2, 1), 2, 3);
  SetBlock(GetBlock(0, 1), 2, 1);
  SetBlock(GetBlock(0, 3), 0, 1);
  SetBlock(temp, 0, 3);

  temp = GetBlock(1, 3);
  SetBlock(GetBlock(2, 2), 1, 3);
  SetBlock(GetBlock(1, 1), 2, 2);
  SetBlock(GetBlock(0, 2), 1, 1);
  SetBlock(temp, 0, 2);

  temp = GetBlock(1, 0);
  SetBlock(GetBlock(3, 2), 1, 0);
  SetBlock(temp, 3, 2);
}

// O 블록 회전 연산 생략 오버라이딩
void TetrisBlockO::BlockTurnClockWise() {}
void TetrisBlockO::BlockTurnReverseClockWise() {}

// 블록별 색깔 출력 오버라이딩
void TetrisBlock::BlockColor() {}
void TetrisBlockI::BlockColor() { cout << CYAN; }
void TetrisBlockT::BlockColor() { cout << MAGENTA; }
void TetrisBlockO::BlockColor() { cout << YELLOW; }
void TetrisBlockL::BlockColor() { cout << ORANGE; }
void TetrisBlockJ::BlockColor() { cout << BLUE; }
void TetrisBlockS::BlockColor() { cout << GREEN; }
void TetrisBlockZ::BlockColor() { cout << RED; }

// 블록 생성자들
TetrisBlockI::TetrisBlockI() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      SetBlock(block_i[i][j], i, j);
    }
  }
  SetCode(code_i);
}

TetrisBlockT::TetrisBlockT() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      SetBlock(block_t[i][j], i, j);
    }
  }
  SetCode(code_t);
}

TetrisBlockO::TetrisBlockO() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      SetBlock(block_o[i][j], i, j);
    }
  }
  SetCode(code_o);
}

TetrisBlockL::TetrisBlockL() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      SetBlock(block_l[i][j], i, j);
    }
  }
  SetCode(code_l);
}

TetrisBlockJ::TetrisBlockJ() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      SetBlock(block_j[i][j], i, j);
    }
  }
  SetCode(code_j);
}

TetrisBlockS::TetrisBlockS() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      SetBlock(block_s[i][j], i, j);
    }
  }
  SetCode(code_s);
}

TetrisBlockZ::TetrisBlockZ() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      SetBlock(block_z[i][j], i, j);
    }
  }
  SetCode(code_z);
}

// 블록 소멸자
TetrisBlock::~TetrisBlock() {}
TetrisBlockI::~TetrisBlockI() {}
TetrisBlockT::~TetrisBlockT() {}
TetrisBlockO::~TetrisBlockO() {}
TetrisBlockL::~TetrisBlockL() {}
TetrisBlockJ::~TetrisBlockJ() {}
TetrisBlockS::~TetrisBlockS() {}
TetrisBlockZ::~TetrisBlockZ() {}