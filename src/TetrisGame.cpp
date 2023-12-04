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

  TetrisInterface::DrawQueBlocks(que_blocks);
  //    TetrisInterface::GameOver();

  // for (auto &que_block : que_blocks) {
  //   delete que_block;
  //}
}

void TetrisGame::GameInit() {
  TetrisInterface::ScreenBorder();
  TetrisInterface::GameBorder();
  TetrisInterface::DrawQueBoxBorder();

  for (TetrisBlock *&que_block : que_blocks) {
    SetQueBlock(que_block);
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

void TetrisGame::SetQueBlock(TetrisBlock *&block) {
  switch (SetRandomNum()) {
  case 0: {
    block = new TetrisBlockI();
    break;
  }
  case 1: {
    block = new TetrisBlockT();
    break;
  }
  case 2: {
    block = new TetrisBlockO();
    break;
  }
  case 3: {
    block = new TetrisBlockL();
    break;
  }
  case 4: {
    block = new TetrisBlockJ();
    break;
  }
  case 5: {
    block = new TetrisBlockS();
    break;
  }
  case 6: {
    block = new TetrisBlockZ();
    break;
  }
  }
}

int TetrisGame::SetRandomNum() {
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
