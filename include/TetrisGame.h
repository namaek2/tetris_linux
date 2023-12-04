//
// Created by namaek_2 on 11/27/23.
//
#pragma once

#ifndef TETRIS_TETRISGAME_H
#define TETRIS_TETRISGAME_H

#include "TetrisColor.h"
#include "TetrisInput.h"
#include <iostream>

#define left_border 10
#define right_border 21
#define top_border 10
#define bottom_border 31

#define RED Color::Modifier(Color::FG_RED);
#define MAGENTA Color::Modifier(Color::FG_MAGENTA);
#define YELLOW Color::Modifier(Color::FG_YELLOW);
#define BLUE Color::Modifier(Color::FG_BLUE);
#define CYAN Color::Modifier(Color::FG_CYAN);
#define GREEN Color::Modifier(Color::FG_GREEN);
#define WHITE Color::Modifier(Color::FG_WHITE);
#define ORANGE Color::Modifier(Color::FG_ORANGE);

using namespace std;

enum level { BEGINNER = 20, AMATEUR = 22, EXPERT = 24, EXIT = 26 };

// 게임 진행 : 가로 10칸 세로 20칸
// 외곽 테두리 : 양 옆 1칸, 상단 1칸

class TetrisInterface {
private:
public:
  TetrisInterface();

  static void ScreenBorder();
  static void GameBorder();
  static void GameOver();
  static void DrawQueBorder();
};

class TetrisStart {
private:
  int cursor_y = 20;
  int menu_selected = 0;

public:
  static int GetEnum(int level_type);
  TetrisStart();
  ~TetrisStart();

  static void PrintTitle();
  static void PrintMenu();

  void SelectMenu();
  int Session();
  void CursorMove(int dirrection, int y);
  int MenuSelected(int y);

  int GetCursorY() const;
  void SetCursorY(int y);

  int GetMenuSelected() const;
  void SetMenuSelected(int y);

  static void PrintT(int x, int y);
  static void PrintE(int x, int y);
  static void PrintR(int x, int y);
  static void PrintI(int x, int y);
  static void PrintS(int x, int y);
};

class TetrisBlock {
private:
  bool block[4][4]{};

public:
  void BlockPrint(int x, int y);
  void BlockPrintErase(int x, int y);

  virtual ~TetrisBlock();
  virtual void BlockColor();
  virtual void BlockTurnClockWise();
  virtual void BlockTurnReverseClockWise();
};

class TetrisBlockI : public TetrisBlock {
private:
  bool block[4][4] = {{false, false, false, false},
                      {true, true, true, true},
                      {false, false, false, false},
                      {false, false, false, false}};

public:
  ~TetrisBlockI() override;
  void BlockColor() override;
  void BlockTurnClockWise() override;
  void BlockTurnReverseClockWise() override;
};

class TetrisBlockT : public TetrisBlock {
private:
  bool block[4][4] = {{false, false, true, false},
                      {false, true, true, true},
                      {false, false, false, false},
                      {false, false, false, false}};

public:
  ~TetrisBlockT() override;
  void BlockColor() override;
};

class TetrisBlockO : public TetrisBlock {
private:
  bool block[4][4] = {{false, false, false, false},
                      {false, true, true, false},
                      {false, true, true, false},
                      {false, false, false, false}};

public:
  ~TetrisBlockO() override;
  void BlockColor() override;
  void BlockTurnClockWise() override;
  void BlockTurnReverseClockWise() override;
};

class TetrisBlockL : public TetrisBlock {
private:
  bool block[4][4] = {{false, false, false, true},
                      {false, true, true, true},
                      {false, false, false, false},
                      {false, false, false, false}};

public:
  ~TetrisBlockL() override;
  void BlockColor() override;
};

class TetrisBlockJ : public TetrisBlock {
private:
  bool block[4][4] = {{false, true, false, false},
                      {false, true, true, true},
                      {false, false, false, false},
                      {false, false, false, false}};

public:
  ~TetrisBlockJ() override;
  void BlockColor() override;
};

class TetrisBlockS : public TetrisBlock {
private:
  bool block[4][4] = {{false, false, true, true},
                      {false, true, true, false},
                      {false, false, false, false},
                      {false, false, false, false}};

public:
  ~TetrisBlockS() override;
  void BlockColor() override;
};

class TetrisBlockZ : public TetrisBlock {
private:
  bool block[4][4] = {{false, true, true, false},
                      {false, false, true, true},
                      {false, false, false, false},
                      {false, false, false, false}};

public:
  ~TetrisBlockZ() override;
  void BlockColor() override;
};

class TetrisGame {
private:
  bool game_stage[25][12] = {false};
  bool used_blocks[7] = {false};
  TetrisBlock *que_blocks[5];

public:
  TetrisGame();
  void GameInit();
  void NewActiveBlock();
  void SetGameStageValue(int y, int x, bool value);
  void SetGameStage();
  void SetQueBlock(TetrisBlock **que_block);
  int SetRandomBlock();
  void CheckAllBlockUsed();
};

#endif // TETRIS_TETRISGAME_H
