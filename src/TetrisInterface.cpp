//
// Created by namaek_2 on 12/1/23.
//
#include "../include/TetrisGame.h"

// 화면 테두리 그리기
void TetrisInterface::ScreenBorder() {
  system("clear");

  TetrisInput::gotoxy(0, 0);
  for (int i = 0; i < 80; i++) {
    cout << "◈";
  }

  for (int i = 0; i < 39; i++) {
    TetrisInput::gotoxy(0, i);
    cout << "◈";
    TetrisInput::gotoxy(80, i);
    cout << "◈";
  }

  TetrisInput::gotoxy(0, 39);
  for (int i = 0; i < 80; i++) {
    cout << "◈";
  }
}

// 게임 창 그리기
void TetrisInterface::GameBorder() {
  for (int i = 1; i < BOTTOM_BORDER - TOP_BORDER; i++) {
    TetrisInput::gotoxy(LEFT_BORDER, i + TOP_BORDER);
    cout << "◈";
    TetrisInput::gotoxy(RIGHT_BORDER, i + TOP_BORDER);
    cout << "◈";
  }

  TetrisInput::gotoxy(LEFT_BORDER, BOTTOM_BORDER);
  for (int i = 1; i < RIGHT_BORDER - LEFT_BORDER + 2; i++) {
    cout << "◈";
  }
}

// 대기열 블록들 그리기
void TetrisInterface::DrawQueBlocks(TetrisBlock **que_blocks) {
  for (int i = 0; i < QUE_BLOCK_COUNT; i++) {
    que_blocks[i]->BlockColor();
    que_blocks[i]->BlockPrint(QUE_TOP_BORDER + 2 + i * (QUE_BOX_SIZE + 1),
                              QUE_LEFT_BORDER + 2);
  }
}

// 대기열 블록들 지우기
void TetrisInterface::EraseQueBlocks(TetrisBlock **que_blocks) {
  for (int i = 0; i < QUE_BLOCK_COUNT; i++) {
    que_blocks[i]->BlockPrintErase(QUE_TOP_BORDER + 2 + i * (QUE_BOX_SIZE + 1),
                                   QUE_LEFT_BORDER + 2);
  }
}

// 대기 블록 지우기
void TetrisInterface::DrawQueBoxBorder() {
  TetrisInput::gotoxy(QUE_LEFT_BORDER, QUE_TOP_BORDER);
  cout << WHITE;
  cout << "◈NE  XT◈";

  for (int i = 1; i <= QUE_BLOCK_COUNT; i++) {
    TetrisInput::gotoxy(QUE_LEFT_BORDER,
                        QUE_TOP_BORDER + i * (QUE_BOX_SIZE + 1));
    for (int j = 0; j < QUE_BOX_SIZE + 2; j++) {
      cout << "◈";
    }
  }

  for (int i = 0; i < QUE_BOX_SIZE * QUE_BLOCK_COUNT + QUE_BLOCK_COUNT; i++) {
    TetrisInput::gotoxy(QUE_LEFT_BORDER, QUE_TOP_BORDER + i);
    cout << "◈";
    TetrisInput::gotoxy(QUE_RIGHT_BORDER, QUE_TOP_BORDER + i);
    cout << "◈";
  }
}

// 게임 상단바 그리기
void TetrisInterface::DrawGameTopBar() {
  for (int i = 0; i < RIGHT_BORDER - LEFT_BORDER + 1; i++) {
    cout << WHITE;
    TetrisInput::gotoxy(LEFT_BORDER + i, TOP_BORDER);
    cout << "◈";
  }
}

// 게임 화면 그리기
void TetrisInterface::GameOver() {
  system("clear");

  TetrisInput::gotoxy(56, 6);
  cout << " ▣▣▣▣▣▣      ▣▣▣▣▣▣     ▣▣    ▣▣    ▣▣▣▣▣▣▣▣";
  TetrisInput::gotoxy(56, 6 + 1);
  cout << "▣▣    ▣▣    ▣▣    ▣▣    ▣▣▣  ▣▣▣    ▣▣      ";
  TetrisInput::gotoxy(56, 6 + 2);
  cout << "▣▣    ▣▣    ▣▣    ▣▣    ▣▣ ▣▣ ▣▣    ▣▣      ";
  TetrisInput::gotoxy(56, 6 + 3);
  cout << "▣▣          ▣▣▣▣▣▣▣▣    ▣▣ ▣▣ ▣▣    ▣▣▣▣▣▣▣▣";
  TetrisInput::gotoxy(56, 6 + 4);
  cout << "▣▣  ▣▣▣▣    ▣▣    ▣▣    ▣▣    ▣▣    ▣▣      ";
  TetrisInput::gotoxy(56, 6 + 5);
  cout << "▣▣    ▣▣    ▣▣    ▣▣    ▣▣    ▣▣    ▣▣      ";
  TetrisInput::gotoxy(56, 6 + 6);
  cout << " ▣▣▣▣▣▣     ▣▣    ▣▣    ▣▣    ▣▣    ▣▣▣▣▣▣▣▣";

  TetrisInput::gotoxy(56, 6 + 8);
  cout << " ▣▣▣▣▣▣     ▣▣    ▣▣    ▣▣▣▣▣▣▣▣    ▣▣▣▣▣▣▣ ";
  TetrisInput::gotoxy(56, 6 + 9);
  cout << "▣▣    ▣▣    ▣▣    ▣▣    ▣▣          ▣▣    ▣▣";
  TetrisInput::gotoxy(56, 6 + 10);
  cout << "▣▣    ▣▣    ▣▣    ▣▣    ▣▣          ▣▣    ▣▣";
  TetrisInput::gotoxy(56, 6 + 11);
  cout << "▣▣    ▣▣    ▣▣    ▣▣    ▣▣▣▣▣▣▣▣    ▣▣▣▣▣▣▣ ";
  TetrisInput::gotoxy(56, 6 + 12);
  cout << "▣▣    ▣▣    ▣▣    ▣▣    ▣▣          ▣▣    ▣▣";
  TetrisInput::gotoxy(56, 6 + 13);
  cout << "▣▣    ▣▣     ▣▣  ▣▣     ▣▣          ▣▣    ▣▣";
  TetrisInput::gotoxy(56, 6 + 14);
  cout << " ▣▣▣▣▣▣       ▣▣▣▣      ▣▣▣▣▣▣▣▣    ▣▣    ▣▣";

  // TetrisInput::gotoxy(70, 25);
  //  cout << "YOUR SCORE : %d", score; // 최종 점수 출력

  TetrisInput::gotoxy(65, 30);
  cout << "Press any key to go to menu";

  // TetrisInput::_getch(); // 후 아무 키 입력시 메인화면으로 복귀
}