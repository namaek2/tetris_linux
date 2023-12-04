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

#define LEFT_BORDER 10
#define RIGHT_BORDER 21
#define TOP_BORDER 10
#define BOTTOM_BORDER 31

#define QUE_LEFT_BORDER 40
#define QUE_RIGHT_BORDER 47
#define QUE_TOP_BORDER 2

#define QUE_BLOCK_COUNT 5
#define QUE_BOX_SIZE 6

#define START_X 15
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
  void BlockSet(bool arr[4][4]);
  void BlockPrint(int x, int y);
  void BlockPrintErase(int x, int y);

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
  bool game_stage[25][12] = {false};
  bool used_blocks[7] = {false};
  // unique_ptr<TetrisBlock> block[5];
  TetrisBlock *que_blocks[5];

public:
  TetrisGame();
  void GameInit();
  void GameMain();
  void ControlBlock();
  void SetGameStageValue(int y, int x, bool value);
  void SetGameStage();
  void PushQueBlock();
  void SetQueBlock(TetrisBlock *&block);
  int SetRandomNum();
  void CheckAllBlockUsed();
};

#endif // TETRIS_TETRISGAME_H
