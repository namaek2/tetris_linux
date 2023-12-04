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
  if (s.GetMenuSelected() == 4) {
    return;
  }
  game_level = 30 - 9 * s.GetMenuSelected();
  s.~TetrisStart();

  GameInit();

  GameMain();

  TetrisInterface::GameOver();
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

void TetrisGame::GameMain() {
  cur_y = START_Y;
  cur_x = START_X;

  TetrisBlock *active_block = que_blocks[0]->Clone();
  PushQueBlock();
  TetrisInterface::DrawQueBlocks(que_blocks);

  while (true) {
    BlockMoveSession(active_block);

    FixGameStage(active_block);
    CheckGameStage();
    if (CheckGameOver()) {
      return;
    }
  }
}

void TetrisGame::InitGameStage() {
  // 게임 판 경계선 세팅
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 12; j++) {
      SetGameStage(i, j, EMPTY);
    }
  }
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
    que_blocks[i] = que_blocks[i + 1]->Clone();
  }
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
        SetGameStage(cur_y - START_Y + y, cur_x - START_X + 4 + x,
                     block->color_code);
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

bool TetrisGame::CheckGameOver() {
  for (int i = 1; i < 11; i++) {
    if (GetGameStage(3, i) != 0)
      return true;
  }
  return false;
}

bool TetrisGame::KeyBoardInput(TetrisBlock *&block) {
  int input = TetrisInput::_getch();

  switch (input) {
  case SPACE: { // space
    BlockHardDrop(block);
    break;
  }
  case 83: { // S
    BlockTurnLeft(block);
    break;
  }
  case 115: { // s
    BlockTurnLeft(block);
    break;
  }
  case 68: { // D
    BlockTurnRight(block);
    break;
  }
  case 100: { // d
    BlockTurnRight(block);
    break;
  }
  case ARROW_ESC: {
    return ArrowEscInput(block);
  }
  }
  return true;
}

bool TetrisGame::ArrowEscInput(TetrisBlock *&block) {
  int input = TetrisInput::_getch();
  if (input == 91) {
    input = TetrisInput::_getch();
    switch (input) {
    default: { // 예외시
      break;
    }
    case DOWN: { // 방향키 아래
      return BlockMoveDown(block);
    }
    case LEFT: { // 방향키 왼쪽
      BlockMoveLeft(block);
      break;
    }
    case RIGHT: { // 방향키 오른쪽
      BlockMoveRight(block);
      break;
    }
    }
    return true;
  }
  return true; // esc, 예외 작동시
}

void TetrisGame::SetWaitTime() {
  start = NULL; // 카운트 초기화
  end_t = NULL;
  time_passed = 0;
}

bool TetrisGame::CheckWaitTime() {
  if (start != NULL) {
    end_t = clock();
    duration = (float)(end_t - start); // 카운트 계산

    if (duration >= 1000) { // 1초 이상 경과시
      return true;
    }
    return false;
  }
  start = clock();
  return false;
}

void TetrisGame::BlockTurnLeft(TetrisBlock *&block) {}
void TetrisGame::BlockTurnRight(TetrisBlock *&block) {}

void TetrisGame::BlockMoveLeft(TetrisBlock *&block) {
  if (!CheckBlockCollisionLeft(block)) {
    BlockEraseGuide(block);
    block->BlockPrintErase(cur_y, cur_x);
    cur_x -= 1;
    BlockPrintGuide(block);
    block->BlockPrint(cur_y, cur_x);
  }
}

void TetrisGame::BlockMoveRight(TetrisBlock *&block) {
  if (!CheckBlockCollisionRight(block)) {
    BlockEraseGuide(block);
    block->BlockPrintErase(cur_y, cur_x);
    cur_x += 1;
    BlockPrintGuide(block);
    block->BlockPrint(cur_y, cur_x);
  }
}

bool TetrisGame::BlockMoveDown(TetrisBlock *&block) { // 좌로 이동
  if (!CheckBlockCollisionDown(block)) {              // 간섭 없을 시
    BlockEraseGuide(block);
    block->BlockPrintErase(cur_y, cur_x); // 현재 블록 지우기
    cur_y += 1;                           // 좌표 이동

    BlockPrintGuide(block);          // 가이드 블록 출력
    block->BlockPrint(cur_y, cur_x); // 블록 출력
    SetWaitTime();
    return true;
  }

  return false;
}

void TetrisGame::BlockHardDrop(TetrisBlock *&block) {
  block->BlockPrintErase(cur_y, cur_x);
  BlockEraseGuide(block);
  while (!CheckBlockCollisionDown(block)) {
    cur_y++;
  }

  block->BlockPrint(cur_y, cur_x);
}

void TetrisGame::BlockPrintGuide(TetrisBlock *&block) {
  int y = cur_y;
  while (!CheckBlockCollisionDown(block)) {
    cur_y++;
  }

  block->BlockPrintGuide(cur_y, cur_x);
  cur_y = y;
}

void TetrisGame::BlockEraseGuide(TetrisBlock *&block) {
  int y = cur_y;
  while (!CheckBlockCollisionDown(block)) {
    cur_y++;
  }

  block->BlockPrintErase(cur_y, cur_x);
  cur_y = y;
}
// x  y
// 11 11
// 20 30

// 01 04
// 10 23
bool TetrisGame::CheckBlockCollision(TetrisBlock *&block, int y, int x, int a,
                                     int b) {
  if (block->GetBlock(y, x) &&
      GetGameStage(cur_y - START_Y + y + a, cur_x - 10 + x + b) != EMPTY) {
    return true;
  }
  return false;
}

bool TetrisGame::CheckBlockCollisionLeft(TetrisBlock *&block) {
  for (int x = 0; x < 4; x++) {
    for (int y = 3; y >= 0; y--) {
      if (CheckBlockCollision(block, y, x, 0, -11)) {
        return true;
      }
    }
  }

  return false;
}

bool TetrisGame::CheckBlockCollisionRight(TetrisBlock *&block) {
  for (int x = 3; x >= 0; x--) {
    for (int y = 3; y >= 0; y--) {
      if (CheckBlockCollision(block, y, x, 0, 1)) {
        return true;
      }
    }
  }

  return false;
}

bool TetrisGame::CheckBlockCollisionDown(TetrisBlock *&block) {
  for (int y = 3; y >= 0; y--) {
    for (int x = 0; x < 4; x++) {
      if (CheckBlockCollision(block, y, x, 1, 0)) {

        return true;
      }
    }
  }

  return false;
}

void TetrisGame::BlockMoveSession(TetrisBlock *&block) const {
  cur_y = START_Y;
  cur_x = START_X;

  // guide(); // 가이드 블록 출력

  while (true) {
    for (time_passed = 0; time_passed < game_level * 4; time_passed++) {
      if (start != NULL) {
        end_t = clock();
        duration = (float)(end_t - start);

        if (duration >= 1000) { // 1초 이상 경과시
          return;
        }
      }

      if (TetrisInput::_kbhit()) { // 키보드 입력이 있다면
        if (!KeyBoardInput(block)) {
          return;
        }
      }

      usleep(5000);
    }

    if (!BlockMoveDown(block)) {
      if (CheckWaitTime()) {
        return;
      }
    }
    TetrisInterface::DrawGameTopBar();
  }
}