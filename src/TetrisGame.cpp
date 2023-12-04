//
// Created by namaek_2 on 11/27/23.
//

#include "../include/TetrisGame.h"
#include "cstdlib"
#include "ctime"

TetrisGame::TetrisGame() {
  TetrisStart s;
  game_level = s.GetMenuSelected();
  s.~TetrisStart();

  GameInit();

  TetrisInterface::DrawQueBlocks(que_blocks);
  TetrisBlock *active_block = que_blocks[0]->Clone();

  GameMain();

  //  TetrisInterface::GameOver();
}

void TetrisGame::GameInit() {
  TetrisInterface::ScreenBorder();
  TetrisInterface::GameBorder();
  TetrisInterface::DrawQueBoxBorder();

  for (TetrisBlock *&que_block : que_blocks) {
    SetQueBlock(que_block);
  }
}

void TetrisGame::GameMain() { PushQueBlock(); }

void TetrisGame::ControlBlock() {
  int buff = 0;

  float duration = 0;

  TetrisInterface::DrawGameTopBar();

  // guide(); // 가이드 블록 출력
  // start = NULL;
  /*
  while (1) // 무한반복
  {
    for (i = 0; i < a; i++) // a*10 밀리세컨드 = 블록이 한칸씩 내려오는 시간
    {
      if (start != NULL) // 땅에 닿고 1초 카운트가 진행중 일 때
      {
        end = clock();                   // 현재시각
        duration = (float)(end - start); // 카운트 계산

        if (duration >= 1000) // 1초 경과시
        {
          godown(1); // 강제 하드드랍 후 고정
          return;
        }
      }

      if (_kbhit()) // 키보드 입력이 있다면
      {
        buff = kb();

        if (buff == 3) // 방해받지 않은 하단 이동
        {
          if (start != NULL) // 땅에 닿고 1초 카운트가 진행중 일 때
          {
            start = NULL; // 카운트 초기화
            end = NULL;
          }

          i = 0; // 밑으로 이동할 때 지연시간 초기화(0.1초 지났을 때 밑으로
                 // 하강시 다시 0.3초를 기다려야 1칸 하강)
        }

        else if (buff == 1) // 방해받은 하단 이동시 고정
          return;
      }
      Sleep(10);
    }

    buff = moveD(); // a*10밀리세컨드 마다 한 칸씩 아래로 이동

    if (buff == 1) // 방해받은 이동일 때
    {
      if (start == NULL) // 카운트 시작
        start = clock();
    } else // 방해받지 않은 이동일 때
    {
      if (start != NULL) // 카운트 초기화
      {
        start = NULL();
        end = NULL();
      }
    }
  }*/
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

void TetrisGame::PushQueBlock() {
  for (int i = 0; i < QUE_BLOCK_COUNT - 1; i++) {
    // delete que_blocks[i];
    que_blocks[i] = que_blocks[i + 1]->Clone();
  }
  // delete que_blocks[4];
  SetQueBlock(que_blocks[4]);
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
