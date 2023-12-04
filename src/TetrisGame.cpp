//
// Created by namaek_2 on 11/27/23.
//

#include "../include/TetrisGame.h"
#include "cstdlib"
#include "ctime"

#define EMPTY 0
#define LINE 1
#define I 2
#define T 3
#define O 4
#define L 5
#define J 6
#define S 7
#define Z 8

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
    BlockMoveSession(block);
    FixGameStage(block);
    CheckGameStage();
  }
}

void TetrisGame::BlockMoveSession(TetrisBlock *&block) {
  cur_y = START_Y;
  cur_x = START_X;

  float duration = 0;

  TetrisInterface::DrawGameTopBar();

  // guide(); // 가이드 블록 출력

  while (true) { // 무한반복
    // game_level * 10 밀리세컨드 = 블록이 한칸씩 내려오는 시간
    for (int i = 0; i < game_level; i++) {
      if (TetrisInput::_kbhit()) {       // 키보드 입력이 있다면
        int temp = KeyBoardInput(block); // 키보드 입력 처리

        if (temp == 2) {       // 방해받지 않은 하단 이동
          if (start != NULL) { // 땅에 닿고 1초 카운트가 진행중 일 때
            start = NULL;      // 카운트 초기화
            end = NULL;
          }

          i = 0; // 밑으로 이동할 때 지연시간 초기화(0.1초 지났을 때 밑으로
                 // 하강시 다시 0.3초를 기다려야 1칸 하강)
        } else if (temp == 3) // 방해받은 하단 이동시 고정
          return;
      }

      if (start != NULL) { // 땅에 닿고 1초 카운트가 진행중 일 때
        end = clock();     // 현재시각
        duration = (float)(end - start); // 경과 시간 계산

        if (duration >= 1000) { // 1초 이상 경과시
          BlockHardDrop(block); // 하드드랍 후 고정
          return;
        }
      }
      usleep(10000);
    }

    // a*10밀리세컨드 마다 한 칸씩 아래로 이동
    if (!BlockMoveDown(block)) { // 방해받은 이동일 때
      if (start != NULL) {
        start = NULL;
        end = NULL;
        continue;
      }

      start = clock();
    }
  }
}

void TetrisGame::InitGameStage() {
  // 게임 판 경계선 세팅
  for (int i = 0; i < 12; i++) {
    SetGameStage(24, i, LINE);
  }

  for (int i = 0; i < 24; i++) {
    SetGameStage(i, 0, LINE);
    SetGameStage(i, 11, LINE);
  }
}

int TetrisGame::GetGameStage(int y, int x) { return game_stage[y][x]; }

void TetrisGame::SetGameStage(int y, int x, int value) {
  game_stage[y][x] = value;
}

void TetrisGame::DrawGameStage() {
  for (int y = 4; y < 24; y++) {
    TetrisInput::gotoxy(LEFT_BORDER + 1, TOP_BORDER - 3 + y);
    for (int x = 1; x < 11; x++) {
      if (GetGameStage(y, x) == LINE) {
        cout << " ";
      } else if (GetGameStage(y, x) == I) {
        cout << CYAN;
        cout << "▣";
      } else if (GetGameStage(y, x) == T) {
        cout << MAGENTA;
        cout << "▣";
      } else if (GetGameStage(y, x) == O) {
        cout << YELLOW;
        cout << "▣";
      } else if (GetGameStage(y, x) == L) {
        cout << ORANGE;
        cout << "▣";
      } else if (GetGameStage(y, x) == J) {
        cout << BLUE;
        cout << "▣";
      } else if (GetGameStage(y, x) == S) {
        cout << GREEN;
        cout << "▣";
      } else if (GetGameStage(y, x) == Z) {
        cout << RED;
        cout << "▣";
      }
    }
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
  srand((unsigned int)time(nullptr));

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

void TetrisGame::FixGameStage(TetrisBlock *&block) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (block->GetBlock(y, x)) {
        SetGameStage(cur_y - START_Y + y, cur_x - START_X + 4 + x, true);
      }
    }
  }
}

void TetrisGame::CheckGameStage() {
  int combo = 0;
  for (int y = 23; y > 3; y--) {
    for (int x = 1; x < 11; x++) {
      if (GetGameStage(y, x) == EMPTY) {
        LineCompletedScore(combo);
        combo = 0;
        break;
      } else if (x == 10) {
        LineCompleted(y++); // 한 줄씩 당기기
        combo++;
      }
    }
  }
}

void TetrisGame::LineCompleted(int line_y) {
  for (int y = line_y; y > 0; y--) {
    for (int x = 1; x < 11; x++) {
      SetGameStage(y, x, GetGameStage(y - 1, x));
    }
    DrawGameStage();
  }
}

void TetrisGame::LineCompletedScore(int combo) {
  if (combo == 0) {
    return;
  } else if (combo == 1) {
    score += 100;
  } else if (combo == 2) {
    score += 300;
  } else if (combo == 3) {
    score += 500;
  } else {
    score += 800;
  }
}

void TetrisGame::KeyBoardInput(TetrisBlock *&block) {
  int input = TetrisInput::_getch();

  switch (input) {
  case SPACE: { // space
    BlockHardDrop(block);
    return;
  }
  case 83: { // S
    BlockTurnLeft(block);
    return;
  }
  case 115: { // s
    BlockTurnLeft(block);
    return;
  }
  case 68: { // D
    BlockTurnRight(block);
    return;
  }
  case 100: { // d
    BlockTurnRight(block);
    return;
  }
  case ARROW_ESC: {
    ArrowEscInput(block);
  }
  }
}

void TetrisGame::ArrowEscInput(TetrisBlock *&block) {
  int input = TetrisInput::_getch();
  if (input == 91) {
    input = TetrisInput::_getch();
    switch (input) {
    default: { // 예외시
      return;
    }
    case DOWN: { // 방향키 아래
      BlockMoveDown(block);
      return;
    }
    case LEFT: { // 방향키 왼쪽
      BlockMoveLeft(block);
      return;
    }
    case RIGHT: { // 방향키 오른쪽
      BlockMoveRight(block);
      return;
    }
    }
  }
  return; // esc, 예외 작동시
};

void TetrisGame::BlockMoveLeft(TetrisBlock *&block) { // 좌로 이동
  if (!CheckBlockCollisionLeft(block)) {              // 간섭 없을 시
    block->BlockPrintErase(cur_y, cur_x);             // 현재 블록 지우기
    cur_x -= 1;                                       // 좌표 이동
    // guide();                              // 가이드 블록 출력
    block->BlockPrint(cur_y, cur_x); // 블록 출력
  }
}

void TetrisGame::BlockMoveRight(TetrisBlock *&block) { // 좌로 이동
  if (!CheckBlockCollisionRight(block)) {              // 간섭 없을 시
    block->BlockPrintErase(cur_y, cur_x); // 현재 블록 지우기
    cur_x += 1;                           // 좌표 이동
    // guide();                              // 가이드 블록 출력
    block->BlockPrint(cur_y, cur_x); // 블록 출력
  }
}

bool TetrisGame::BlockMoveDown(TetrisBlock *&block) { // 좌로 이동
  if (!CheckBlockCollisionDown(block)) {              // 간섭 없을 시
    block->BlockPrintErase(cur_y, cur_x);             // 현재 블록 지우기
    cur_y += 1;                                       // 좌표 이동
    // guide();                              // 가이드 블록 출력
    block->BlockPrint(cur_y, cur_x); // 블록 출력
    return true;
  }
  return false;
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
      GetGameStage(cur_y - START_Y + y, cur_x - START_X + 4 + x) != EMPTY) {
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
}