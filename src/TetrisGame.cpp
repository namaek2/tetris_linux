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
  cur_y = START_Y;
  cur_x = START_X;
  TetrisBlock *active_block = que_blocks[0]->Clone();

  GameMain(active_block);

  //  TetrisInterface::GameOver();
}

void TetrisGame::GameInit() {
  TetrisInterface::ScreenBorder();
  TetrisInterface::GameBorder();
  TetrisInterface::DrawQueBoxBorder();

  InitGameStage();
  for (TetrisBlock *&que_block : que_blocks) {
    SetQueBlock(que_block);
  }
}

void TetrisGame::GameMain(TetrisBlock *&block) {
  PushQueBlock();
  while (true) {
    BlockMove(block);
  }
}

/*
void TetrisGame::BlockMove(TetrisBlock *&block) {
  TetrisInterface::DrawGameTopBar();

  cur_y = START_Y;
  cur_x = START_X;

  // guide(); // 가이드 블록 출력

  clock_t start = NULL;
  clock_t end = NULL;
  float duration = 0;

  while (true) // 무한반복
  {
    // game_level * 10 밀리세컨드 = 블록이 한칸씩 내려오는 시간
    for (int i = 0; i < game_level; i++) {
      if (start != NULL) { // 땅에 닿고 1초 카운트가 진행중 일 때
        end = clock();     // 현재시각
        duration = (float)(end - start); // 경과 시간 계산

        if (duration >= 1000) { // 1초 이상 경과시
          BlockHardDrop(block); // 하드드랍 후 고정
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
  }
}
*/
void TetrisGame::InitGameStage() {
  // 게임 판 경계선 세팅
  for (int i = 0; i < 12; i++) {
    SetGameStage(24, i, true);
  }

  for (int i = 0; i < 24; i++) {
    SetGameStage(i, 0, true);
    SetGameStage(i, 11, true);
  }
}

bool TetrisGame::GetGameStage(int y, int x) { return game_stage[y][x]; }

void TetrisGame::SetGameStage(int y, int x, bool value) {
  game_stage[y][x] = value;
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
  for (bool &used_block : used_blocks) {
    if (!used_block) {
      return;
    }
  }

  for (bool &used_block : used_blocks) {
    used_block = false;
  }
}

void TetrisGame::BlockMoveLeft(TetrisBlock *&block) { // 좌로 이동
  if (CheckBlockCollisionLeft(block) != 1) {          // 간섭 없을 시
    block->BlockPrintErase(cur_y, cur_x);             // 현재 블록 지우기
    cur_x -= 1;                                       // 좌표 이동
    // guide();                              // 가이드 블록 출력
    block->BlockPrint(cur_y, cur_x); // 블록 출력
  }
}

void TetrisGame::BlockMoveRight(TetrisBlock *&block) { // 좌로 이동
  if (CheckBlockCollisionRight(block) != 1) {          // 간섭 없을 시
    block->BlockPrintErase(cur_y, cur_x); // 현재 블록 지우기
    cur_x += 1;                           // 좌표 이동
    // guide();                              // 가이드 블록 출력
    block->BlockPrint(cur_y, cur_x); // 블록 출력
  }
}

void TetrisGame::BlockMoveDown(TetrisBlock *&block) { // 좌로 이동
  if (CheckBlockCollisionDown(block) != 1) {          // 간섭 없을 시
    block->BlockPrintErase(cur_y, cur_x);             // 현재 블록 지우기
    cur_y += 1;                                       // 좌표 이동
    // guide();                              // 가이드 블록 출력
    block->BlockPrint(cur_y, cur_x); // 블록 출력
  }
}

void TetrisGame::BlockHardDrop(TetrisBlock *&block) {
  block->BlockPrintErase(cur_y, cur_x);
  while (!CheckBlockCollisionDown(block)) {
    cur_y++;
  }

  block->BlockPrint(cur_y, cur_x);
}

bool TetrisGame::CheckBlockCollision(TetrisBlock *&block, int y, int x) {
  if (block->GetBlock(y, x) &&
      GetGameStage(cur_y - START_Y + y, cur_x - START_X + 4 + x)) {
    return true;
  }
  return false;
}

bool TetrisGame::CheckBlockCollisionLeft(TetrisBlock *&block) {
  for (int x = 0; x < 4; x++) {
    for (int y = 3; y >= 0; y--) {
      if (CheckBlockCollision(block, y, x)) {
        return true;
      }
    }
  }

  return false;
}

bool TetrisGame::CheckBlockCollisionRight(TetrisBlock *&block) {
  for (int x = 3; x >= 0; x--) {
    for (int y = 3; y >= 0; y--) {
      if (CheckBlockCollision(block, y, x)) {
        return true;
      }
    }
  }

  return false;
}

bool TetrisGame::CheckBlockCollisionDown(TetrisBlock *&block) {
  for (int y = 3; y >= 0; y--) {
    for (int x = 0; x < 4; x++) {
      if (CheckBlockCollision(block, y, x)) {
        return true;
      }
    }
  }
  return false;
};

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

