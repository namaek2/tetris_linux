//
// Created by namaek_2 on 11/27/23.
//

#include "../include/TetrisGame.h"
#include "cstdlib"
#include "ctime"

TetrisGame::TetrisGame() {
  // TetrisStart s;
  // s.~TetrisStart();

  GameInit();
  // TetrisInterface::GameOver();
}

void TetrisGame::GameInit() {
  TetrisInterface draw_borders;
  SetGameStage();

  for (int i = 0; i < 5; i++) {
    SetQueBlock(&que_blocks[i]);
  }
}

void TetrisGame::SetGameStageValue(int y, int x, bool value) {
  game_stage[y][x] = value;
}

void TetrisGame::SetGameStage() {
  // 게임 판 경계선 세팅
  for (int i = 0; i < 12; i++) {
    SetGameStageValue(24, i, true);
  }

  for (int i = 0; i < 24; i++) {
    SetGameStageValue(i, 0, true);
    SetGameStageValue(i, 11, true);
  }
}

void TetrisGame::SetQueBlock(TetrisBlock **que_block) {
  int random_num = SetRandomBlock();

  switch (random_num) {
  case 0: {
    *que_block = new TetrisBlockI();
    break;
  }
  case 1: {
    *que_block = new TetrisBlockT();
    break;
  }
  case 2: {
    *que_block = new TetrisBlockO();
    break;
  }
  case 3: {
    *que_block = new TetrisBlockL();
    break;
  }
  case 4: {
    *que_block = new TetrisBlockJ();
    break;
  }
  case 5: {
    *que_block = new TetrisBlockS();
    break;
  }
  case 6: {
    *que_block = new TetrisBlockZ();
    break;
  }
  }
}

int TetrisGame::SetRandomBlock() {
  srand((unsigned int)time(NULL));

  int num = rand() % 7;
  while (used_blocks[num]) {
    num = rand() % 7;
  }
  used_blocks[num] = true;

  CheckAllBlockUsed();

  return num;
}

void TetrisGame::CheckAllBlockUsed() {
  for (bool used_block : used_blocks) {
    if (!used_block) {
      return;
    }
  }

  for (bool used_block : used_blocks) {
    used_block = false;
  }
}

/*



void EraseQueBlock(void) {
  BlockPrintErase(blocksetprint[0], 40, 7); // 첫번째 대기

  y = 12;
  rvprintsq(blocksetprint[1]);

  y = 17;
  rvprintsq(blocksetprint[2]);

  y = 22;
  rvprintsq(blocksetprint[3]);

  y = 27;
  rvprintsq(blocksetprint[4]); // 다섯번째 대기
}

// 대기중인 블록 한칸씩 앞으로 당기기
void NewActiveBlock(int num) {
  TetrisBlock::BlockPrintErase(); // 대기중인 블록 잔상 제거
  blockprintwall();               // 대기중인 블록 경계선 출력

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      acblock[i][j] = blocksetprint[0][i][j];
      blocksetprint[0][i][j] = blocksetprint[1][i][j];
      blocksetprint[1][i][j] = blocksetprint[2][i][j];
      blocksetprint[2][i][j] = blocksetprint[3][i][j];
      blocksetprint[3][i][j] = blocksetprint[4][i][j];
      blocksetprint[4][i][j] = block[num][i][j];
    }
  }

  blockprint(); // 대기중인 블록 출력
}*/
