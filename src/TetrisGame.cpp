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

// 게임 시작
TetrisGame::TetrisGame() {
  TetrisStart s;
  if (s.GetMenuSelected() == 4) {
    return;
  }
  game_level = 30 - 9 * s.GetMenuSelected();

  GameInit();

  GameMain();

  TetrisInterface::GameOver();
}

TetrisGame::~TetrisGame() {
  for (int i = 0; i < 5; i++) {
    delete que_blocks[i];
  }
}

// 게임 초기화
void TetrisGame::GameInit() {
  TetrisInterface::ScreenBorder();
  TetrisInterface::GameBorder();
  TetrisInterface::DrawQueBoxBorder();

  InitGameStage();

  for (TetrisBlock *&que_block : que_blocks) {
    SetQueBlock(que_block);
  }
}

// 게임 진행
void TetrisGame::GameMain() {
  cur_y = START_Y;
  cur_x = START_X;

  TetrisBlock *active_block = que_blocks[0]->Clone();
  PushQueBlock();
  TetrisInterface::DrawQueBlocks(que_blocks);

  while (true) {
    BlockMoveSession(active_block);

    FixGameStage(active_block);
    CheckLineCompleted();
    if (CheckGameOver()) {
      delete active_block;
      return;
    }

    TetrisInterface::EraseQueBlocks(que_blocks);
    active_block = que_blocks[0]->Clone();
    PushQueBlock();
    TetrisInterface::DrawQueBlocks(que_blocks);
  }
}

// 게임 판 초기화
void TetrisGame::InitGameStage() {
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

// 현재까지 쌓인 블록 정보를 저장하는 배열에서 값 가져오기
int TetrisGame::GetGameStage(int y, int x) { return game_stage[y][x]; }

// 현재까지 쌓인 블록 정보를 저장하는 배열에 값 설정
void TetrisGame::SetGameStage(int y, int x, int value) {
  game_stage[y][x] = value;
}

// 게임 스테이지 그리기
void TetrisGame::DrawGameStage() {
  for (int y = 4; y < 24; y++) {
    TetrisInput::gotoxy(LEFT_BORDER + 1, TOP_BORDER - 3 + y);
    for (int x = 1; x < 11; x++) {
      if (GetGameStage(y, x) == EMPTY) {
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

// 랜덤으로 블록 생성해 대기열에 넣기
void TetrisGame::PushQueBlock() {
  for (int i = 0; i < QUE_BLOCK_COUNT - 1; i++) {
    delete que_blocks[i];
    que_blocks[i] = que_blocks[i + 1]->Clone();
  }
  SetQueBlock(que_blocks[4]);
}

// 랜덤으로 블록 모양 할당
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

// 랜덤 숫자 생성
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

// 모든 블록의 종류가 사용됐는지 검사
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

// 블록을 게임판에 고정
void TetrisGame::FixGameStage(TetrisBlock *&block) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (block->GetBlock(y, x)) {
        SetGameStage(cur_y - START_Y + y, cur_x - 10 + x, block->GetCode());
      }
    }
  }
}

// 라인 클리어 검사
void TetrisGame::CheckLineCompleted() {
  int combo = 0;
  for (int y = 23; y > 3; y--) {
    for (int x = 1; x < 11; x++) {
      if (GetGameStage(y, x) == EMPTY) {
        LineCompletedScore(combo);
        combo = 0;
        break;
      } else if (x == 10) {
        LineCompleted(y++);
        combo++;
      }
    }
  }
}

// 라인 클리어
void TetrisGame::LineCompleted(int line_y) {
  for (int y = line_y; y > 0; y--) {
    for (int x = 1; x < 11; x++) {
      SetGameStage(y, x, GetGameStage(y - 1, x));
    }
    DrawGameStage();
  }
}

// 라인 클리어시 점수 증가
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

// 게임이 끝나는 조건이 됐는지 검사
bool TetrisGame::CheckGameOver() {
  for (int i = 1; i < 11; i++) {
    if (GetGameStage(3, i) != 0)
      return true;
  }
  return false;
}

// 키보드 입력시
bool TetrisGame::KeyBoardInput(TetrisBlock *&block) {
  int input = TetrisInput::_getch();

  switch (input) {
  case SPACE: { // space
    BlockHardDrop(block);
    return false;
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

// 방향키 입력시
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
  return true; // esc로 일시정지, 예외키 작동시 기능 추가 필요
}

// 블록 자동 내려가기 시간 초기화
void TetrisGame::SetWaitTime() {
  start = 0;
  end_t = 0;
  duration = 0;
  iteration = 0;
}

// 블록 반시계방향으로 회전 로직
void TetrisGame::BlockTurnLeft(TetrisBlock *&block) {
  BlockEraseGuide(block);
  block->BlockPrintErase(cur_y, cur_x);
  block->BlockTurnReverseClockWise();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (CheckBlockCollision(block, i, j, 0, 0)) {
        block->BlockTurnClockWise();
        BlockPrintGuide(block);
        block->BlockColor();
        block->BlockPrint(cur_y, cur_x);
        return;
      }
    }
  }
  BlockPrintGuide(block);
  block->BlockColor();
  block->BlockPrint(cur_y, cur_x);
}

// 블록 시게방향으로 회전 로직
void TetrisGame::BlockTurnRight(TetrisBlock *&block) {
  BlockEraseGuide(block);
  block->BlockPrintErase(cur_y, cur_x);
  block->BlockTurnClockWise();
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (CheckBlockCollision(block, i, j, 0, 0)) {
        block->BlockTurnReverseClockWise();
        BlockPrintGuide(block);
        block->BlockColor();
        block->BlockPrint(cur_y, cur_x);
        return;
      }
    }
  }
  BlockPrintGuide(block);
  block->BlockColor();
  block->BlockPrint(cur_y, cur_x);
}

// 블록 왼쪽으로 이동
void TetrisGame::BlockMoveLeft(TetrisBlock *&block) {
  if (!CheckBlockCollisionLeft(block)) {
    BlockEraseGuide(block);
    block->BlockPrintErase(cur_y, cur_x);
    cur_x -= 1;
    BlockPrintGuide(block);
    block->BlockColor();
    block->BlockPrint(cur_y, cur_x);
  }
}

// 블록 오른쪽으로 이동
void TetrisGame::BlockMoveRight(TetrisBlock *&block) {
  if (!CheckBlockCollisionRight(block)) {
    BlockEraseGuide(block);
    block->BlockPrintErase(cur_y, cur_x);
    cur_x += 1;
    BlockPrintGuide(block);
    block->BlockColor();
    block->BlockPrint(cur_y, cur_x);
  }
}

// 블록 아래로 이동
bool TetrisGame::BlockMoveDown(TetrisBlock *&block) {
  if (!CheckBlockCollisionDown(block)) {
    BlockEraseGuide(block);
    block->BlockPrintErase(cur_y, cur_x);
    cur_y += 1;

    BlockPrintGuide(block);
    block->BlockColor();
    block->BlockPrint(cur_y, cur_x);
    SetWaitTime();
    return true;
  }

  return false;
}

// 블록 하드 드랍
void TetrisGame::BlockHardDrop(TetrisBlock *&block) {
  block->BlockPrintErase(cur_y, cur_x);
  BlockEraseGuide(block);
  while (!CheckBlockCollisionDown(block)) {
    cur_y++;
  }
  block->BlockColor();
  block->BlockPrint(cur_y, cur_x);
}

// 가이드 블록 출력
void TetrisGame::BlockPrintGuide(TetrisBlock *&block) {
  int y = cur_y;
  while (!CheckBlockCollisionDown(block)) {
    cur_y++;
  }

  cout << WHITE;
  block->BlockPrint(cur_y, cur_x);
  cur_y = y;
}

// 가이드 블록 지우기
void TetrisGame::BlockEraseGuide(TetrisBlock *&block) {
  int y = cur_y;
  while (!CheckBlockCollisionDown(block)) {
    cur_y++;
  }

  block->BlockPrintErase(cur_y, cur_x);
  cur_y = y;
}

// 현재 움직이는 블록이 다른 블록과 겹치는지 검사
bool TetrisGame::CheckBlockCollision(TetrisBlock *&block, int y, int x, int a,
                                     int b) {
  if (block->GetBlock(y, x) &&
      GetGameStage(cur_y - START_Y + y + a, cur_x - 10 + x + b) != EMPTY) {
    return true;
  }
  return false;
}

// 블록이 왼쪽 벽에 닿았는지 검사
bool TetrisGame::CheckBlockCollisionLeft(TetrisBlock *&block) {
  for (int x = 0; x < 4; x++) {
    for (int y = 3; y >= 0; y--) {
      if (CheckBlockCollision(block, y, x, 0, -1)) {
        return true;
      }
    }
  }

  return false;
}

// 블록이 오른쪽 벽에 닿았는지 검사
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

// 블록이 바닥에 닿았는지 검사
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

// 한 개의 블록이 생성되어 바닥에 가기까지의 과정
void TetrisGame::BlockMoveSession(TetrisBlock *&block) {
  cur_y = START_Y;
  cur_x = START_X;

  SetWaitTime();

  while (true) {
    for (iteration = 0; iteration < game_level * 4; iteration++) {
      TetrisInterface::DrawGameTopBar();
      if (start != 0) {
        end_t = clock();
        duration = (float)(end_t - start);

        if (duration >= 1000) {
          duration = 0;
          return;
        }

        duration = 0;
      }

      if (TetrisInput::_kbhit()) {
        if (!KeyBoardInput(block)) {
          return;
        }
      }

      usleep(10000);
    }

    if (!BlockMoveDown(block)) {
      if (start == 0) {
        start = clock();
      }
    }
  }
}