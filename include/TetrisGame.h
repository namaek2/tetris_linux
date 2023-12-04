//
// Created by namaek_2 on 11/27/23.
//
#pragma once

#ifndef TETRIS_TETRISGAME_H
#define TETRIS_TETRISGAME_H

#include "TetrisColor.h"
#include "TetrisInput.h"
#include <iostream>
#include <memory>

#define RED Color::Modifier(Color::FG_RED);
#define MAGENTA Color::Modifier(Color::FG_MAGENTA);
#define YELLOW Color::Modifier(Color::FG_YELLOW);
#define BLUE Color::Modifier(Color::FG_BLUE);
#define CYAN Color::Modifier(Color::FG_CYAN);
#define GREEN Color::Modifier(Color::FG_GREEN);
#define WHITE Color::Modifier(Color::FG_WHITE);
#define ORANGE Color::Modifier(Color::FG_ORANGE);

#define ENTER 13
#define SPACE 32
#define ARROW_ESC 27
#define UP 65
#define DOWN 66
#define LEFT 68
#define RIGHT 67

#define LEFT_BORDER 10
#define RIGHT_BORDER 21
#define TOP_BORDER 10
#define BOTTOM_BORDER 31

#define QUE_LEFT_BORDER 40
#define QUE_RIGHT_BORDER 47
#define QUE_TOP_BORDER 2

#define QUE_BLOCK_COUNT 5
#define QUE_BOX_SIZE 6

#define START_X 14
#define START_Y 7

using namespace std;

enum level { BEGINNER = 20, AMATEUR = 22, EXPERT = 24, EXIT = 26 };

// 게임 진행 : 가로 10칸 세로 20칸
// 외곽 테두리 : 양 옆 1칸, 상단 1칸

class TetrisStart {
private:
  int cursor_y;
  int menu_selected;

public:
  static int GetEnum(int level_type);
  TetrisStart();
  //~TetrisStart();

  // static int Init();

  void PrintTitle();
  void PrintMenu();

  void SelectMenu();
  void Session();
  void CursorMove(int dirrection, int y);
  void MenuSelected(int y);

  int GetCursorY();
  void SetCursorY(int y);

  int GetMenuSelected();
  void SetMenuSelected(int m);

  static void PrintT(int x, int y);
  static void PrintE(int x, int y);
  static void PrintR(int x, int y);
  static void PrintI(int x, int y);
  static void PrintS(int x, int y);
};

class TetrisBlock {
private:
public:
  bool block[4][4]{};
  int color_code;
  bool GetBlock(int y, int x);
  void SetBlock(bool arr[4][4]);
  void BlockPrint(int y, int x);
  void BlockPrintErase(int y, int x);

  TetrisBlock();
  virtual ~TetrisBlock();
  virtual TetrisBlock *Clone() { return new TetrisBlock(*this); };

  virtual void BlockColor();
  virtual void BlockTurnClockWise();
  virtual void BlockTurnReverseClockWise();
};

class TetrisBlockI : public TetrisBlock {
private:
  bool default_block[4][4] = {{false, false, false, false},
                              {true, true, true, true},
                              {false, false, false, false},
                              {false, false, false, false}};
  int code = 2;

public:
  TetrisBlockI();
  ~TetrisBlockI() override;
  TetrisBlockI *Clone() override { return new TetrisBlockI(*this); };
  void BlockColor() override;
  void BlockTurnClockWise() override;
  void BlockTurnReverseClockWise() override;
};

class TetrisBlockT : public TetrisBlock {
private:
  bool default_block[4][4] = {{false, false, true, false},
                              {false, true, true, true},
                              {false, false, false, false},
                              {false, false, false, false}};
  int code = 3;

public:
  TetrisBlockT();
  ~TetrisBlockT() override;
  TetrisBlockT *Clone() override { return new TetrisBlockT(*this); };
  void BlockColor() override;
};

class TetrisBlockO : public TetrisBlock {
private:
  bool default_block[4][4] = {{false, false, false, false},
                              {false, true, true, false},
                              {false, true, true, false},
                              {false, false, false, false}};
  int code = 4;

public:
  TetrisBlockO();
  ~TetrisBlockO() override;
  TetrisBlockO *Clone() override { return new TetrisBlockO(*this); };
  void BlockColor() override;
  void BlockTurnClockWise() override;
  void BlockTurnReverseClockWise() override;
};

class TetrisBlockL : public TetrisBlock {
private:
  bool default_block[4][4] = {{false, false, false, true},
                              {false, true, true, true},
                              {false, false, false, false},
                              {false, false, false, false}};
  int code = 5;

public:
  TetrisBlockL();
  ~TetrisBlockL() override;
  TetrisBlockL *Clone() override { return new TetrisBlockL(*this); };
  void BlockColor() override;
};

class TetrisBlockJ : public TetrisBlock {
private:
  bool default_block[4][4] = {{false, true, false, false},
                              {false, true, true, true},
                              {false, false, false, false},
                              {false, false, false, false}};
  int code = 6;

public:
  TetrisBlockJ();
  ~TetrisBlockJ() override;
  TetrisBlockJ *Clone() override { return new TetrisBlockJ(*this); };
  void BlockColor() override;
};

class TetrisBlockS : public TetrisBlock {
private:
  bool default_block[4][4] = {{false, false, true, true},
                              {false, true, true, false},
                              {false, false, false, false},
                              {false, false, false, false}};
  int code = 7;

public:
  TetrisBlockS();
  ~TetrisBlockS() override;
  TetrisBlockS *Clone() override { return new TetrisBlockS(*this); };
  void BlockColor() override;
};

class TetrisBlockZ : public TetrisBlock {
private:
  bool default_block[4][4] = {{false, true, true, false},
                              {false, false, true, true},
                              {false, false, false, false},
                              {false, false, false, false}};
  int code = 8;

public:
  TetrisBlockZ();
  ~TetrisBlockZ() override;
  TetrisBlockZ *Clone() override { return new TetrisBlockZ(*this); };
  void BlockColor() override;
};

class TetrisInterface {
private:
public:
  static void ScreenBorder();
  static void GameBorder();
  static void GameOver();
  static void DrawQueBlocks(TetrisBlock **que_blocks);
  static void DrawQueBoxBorder();
  static void DrawGameTopBar();
};

class TetrisGame {
private:
  int game_level = 0;
  int score = 0;
  int cur_y = 0;
  int cur_x = 0;
  int game_stage[25][12] = {0};
  bool used_blocks[7] = {false};
  // unique_ptr<TetrisBlock> block[5];
  TetrisBlock *que_blocks[5];

  clock_t start = NULL;
  clock_t end = NULL;

public:
  TetrisGame();
  void GameInit();

  void InitGameStage();
  int GetGameStage(int y, int x);
  void SetGameStage(int y, int x, int value);
  void DrawGameStage();
  void SetQueBlock(TetrisBlock *&block);
  int SetRandomNum();
  void CheckAllBlockUsed();

  void GameMain(TetrisBlock *&block);
  void PushQueBlock();

  void FixGameStage(TetrisBlock *&block);
  void CheckGameStage();
  void LineCompleted(int line_y);
  void LineCompletedScore(int combo);

  void KeyBoardInput(TetrisBlock *&block);
  void ArrowEscInput(TetrisBlock *&block);

  void BlockTurnLeft(TetrisBlock *&block);
  void BlockTurnRight(TetrisBlock *&block);

  void BlockMoveSession(TetrisBlock *&block);
  void BlockMoveLeft(TetrisBlock *&block);
  void BlockMoveRight(TetrisBlock *&block);
  bool BlockMoveDown(TetrisBlock *&block);
  void BlockHardDrop(TetrisBlock *&block);

  bool CheckBlockCollisionLeft(TetrisBlock *&block);
  bool CheckBlockCollisionRight(TetrisBlock *&block);
  bool CheckBlockCollisionDown(TetrisBlock *&block);
  bool CheckBlockCollision(TetrisBlock *&block, int y, int x);
};

#endif // TETRIS_TETRISGAME_H
