//
// Created by namaek_2 on 11/27/23.
//

#include "../include/TetrisGame.h"

TetrisGame::TetrisGame() {
  // TetrisStart s;
  // s.~TetrisStart();

  GameInit();
  // TetrisInterface::GameOver();
}

void TetrisGame::GameInit() {
  TetrisInterface draw_borders;
  SetGameStage();
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
