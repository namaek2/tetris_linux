//
// Created by namaek_2 on 11/27/23.
//
#pragma once

#ifndef TETRIS_TETRISGAME_H
#define TETRIS_TETRISGAME_H

#include "TetrisColor.h"
#include "TetrisInput.h"

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

enum menu { BEGINNER = 20, AMATEUR = 22, EXPERT = 24, EXIT = 26 };

// 게임 진행 : 가로 10칸 세로 20칸
// 외곽 테두리 : 양 옆 1칸, 상단 1칸

class TetrisStart {
private:
  int cursor_y;
  int menu_selected;

  static int GetEnum(int menu_type);

  void PrintTitle();
  void PrintMenu();

  void SelectMenu();
  void Session();
  void CursorMove(int dirrection, int y);
  void MenuSelected(int y);

  int GetCursorY() const;
  void SetCursorY(int y);

  void SetMenuSelected(int m);

  static void PrintT(int x, int y);
  static void PrintE(int x, int y);
  static void PrintR(int x, int y);
  static void PrintI(int x, int y);
  static void PrintS(int x, int y);

public:
  TetrisStart();
  int GetMenuSelected() const;
};

class TetrisBlock {
private:
  int code;
  bool block[4][4];

protected:
  void SetCode(int code);
  void SetBlock(bool value, int y, int x);

public:
  int GetCode();
  bool GetBlock(int y, int x);

  virtual ~TetrisBlock();
  virtual TetrisBlock *Clone() { return new TetrisBlock(*this); };

  void BlockPrint(int y, int x);
  void BlockPrintErase(int y, int x);

  virtual void BlockColor();
  virtual void BlockTurnClockWise();
  virtual void BlockTurnReverseClockWise();
};

class TetrisBlockI : public TetrisBlock {
private:
  int code_i = 2;
  bool block_i[4][4] = {{false, false, false, false},
                        {true, true, true, true},
                        {false, false, false, false},
                        {false, false, false, false}};

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
  int code_t = 3;
  bool block_t[4][4] = {{false, false, true, false},
                        {false, true, true, true},
                        {false, false, false, false},
                        {false, false, false, false}};

public:
  TetrisBlockT();
  ~TetrisBlockT() override;
  TetrisBlockT *Clone() override { return new TetrisBlockT(*this); };

  void BlockColor() override;
};

class TetrisBlockO : public TetrisBlock {
private:
  int code_o = 4;
  bool block_o[4][4] = {{false, false, false, false},
                        {false, true, true, false},
                        {false, true, true, false},
                        {false, false, false, false}};

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
  int code_l = 5;
  bool block_l[4][4] = {{false, false, false, true},
                        {false, true, true, true},
                        {false, false, false, false},
                        {false, false, false, false}};

public:
  TetrisBlockL();
  ~TetrisBlockL() override;
  TetrisBlockL *Clone() override { return new TetrisBlockL(*this); };

  void BlockColor() override;
};

class TetrisBlockJ : public TetrisBlock {
private:
  int code_j = 6;
  bool block_j[4][4] = {{false, true, false, false},
                        {false, true, true, true},
                        {false, false, false, false},
                        {false, false, false, false}};

public:
  TetrisBlockJ();
  ~TetrisBlockJ() override;
  TetrisBlockJ *Clone() override { return new TetrisBlockJ(*this); };

  void BlockColor() override;
};

class TetrisBlockS : public TetrisBlock {
private:
  int code_s = 7;
  bool block_s[4][4] = {{false, false, true, true},
                        {false, true, true, false},
                        {false, false, false, false},
                        {false, false, false, false}};

public:
  TetrisBlockS();
  ~TetrisBlockS() override;
  TetrisBlockS *Clone() override { return new TetrisBlockS(*this); }

  void BlockColor() override;
};

class TetrisBlockZ : public TetrisBlock {
private:
  int code_z = 8;
  bool block_z[4][4] = {{false, true, true, false},
                        {false, false, true, true},
                        {false, false, false, false},
                        {false, false, false, false}};

public:
  TetrisBlockZ();
  ~TetrisBlockZ() override;
  TetrisBlockZ *Clone() override { return new TetrisBlockZ(*this); };

  void BlockColor() override;
};

class TetrisInterface {
public:
  static void ScreenBorder();
  static void GameBorder();
  static void DrawQueBoxBorder();
  static void DrawGameTopBar();

  static void DrawQueBlocks(TetrisBlock **que_blocks);
  static void EraseQueBlocks(TetrisBlock **que_blocks);

  static void GameOver();
};

class TetrisGame {
private:
  int game_stage[25][12] = {0};
  TetrisBlock *que_blocks[5];

  bool used_blocks[7] = {false};
  int game_level = 0;

  clock_t start = 0;
  clock_t end_t = 0;
  float duration = 0;
  int iteration = 0;

  int cur_y = 0;
  int cur_x = 0;

  int score = 0;

  int GetGameStage(int y, int x);
  void SetGameStage(int y, int x, int value);

  void GameInit();
  void GameMain();

  void InitGameStage();
  void DrawGameStage();
  void SetQueBlock(TetrisBlock *&block);
  int SetRandomNum();
  void CheckAllBlockUsed();

  void PushQueBlock();
  bool KeyBoardInput(TetrisBlock *&block);
  bool ArrowEscInput(TetrisBlock *&block);
  void SetWaitTime();

  void BlockMoveSession(TetrisBlock *&block);
  void BlockMoveLeft(TetrisBlock *&block);
  void BlockMoveRight(TetrisBlock *&block);
  bool BlockMoveDown(TetrisBlock *&block);
  void BlockHardDrop(TetrisBlock *&block);

  void BlockTurnLeft(TetrisBlock *&block);
  void BlockTurnRight(TetrisBlock *&block);

  bool CheckBlockCollisionLeft(TetrisBlock *&block);
  bool CheckBlockCollisionRight(TetrisBlock *&block);
  bool CheckBlockCollisionDown(TetrisBlock *&block);
  bool CheckBlockCollision(TetrisBlock *&block, int y, int x, int a, int b);

  void BlockPrintGuide(TetrisBlock *&block);
  void BlockEraseGuide(TetrisBlock *&block);

  void FixGameStage(TetrisBlock *&block);
  void CheckLineCompleted();
  void LineCompleted(int line_y);
  void LineCompletedScore(int combo);
  bool CheckGameOver();

public:
  TetrisGame();
};

#endif // TETRIS_TETRISGAME_H
