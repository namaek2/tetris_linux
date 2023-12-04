//
// Created by namaek_2 on 12/1/23.
//
#include "../include/TetrisGame.h"

#define LEFT_BORDER 10
#define RIGHT_BORDER 21
#define TOP_BORDER 10
#define BOTTOM_BORDER 31

#define QUE_LEFT_BORDER 40
#define QUE_RIGHT_BORDER 47
#define QUE_TOP_BORDER 2

void TetrisInterface::ScreenBorder() {
  system("clear");

  // 첫 줄에 세로좌표 끝까지 그리기
  TetrisInput::gotoxy(0, 0);
  for (int i = 0; i < 80; i++) {
    cout << "◈";
  }

  // 두 번째 줄 부터 마지막에서 두 번째 줄 까지는
  // 가장 왼쪽과 가장 오른쪽에만 그리기
  for (int i = 0; i < 39; i++) {
    TetrisInput::gotoxy(0, i);
    cout << "◈";
    TetrisInput::gotoxy(80, i);
    cout << "◈";
  }

  // 마지막 줄의 세로좌표 끝까지 그리기
  TetrisInput::gotoxy(0, 39); // 마지막 줄로 이동
  for (int i = 0; i < 80; i++) {
    cout << "◈";
  }
}

void TetrisInterface::GameBorder() {
  // 세로줄 출력
  for (int i = 1; i < BOTTOM_BORDER - TOP_BORDER; i++) {
    TetrisInput::gotoxy(LEFT_BORDER, i + TOP_BORDER);
    cout << "◈";
    TetrisInput::gotoxy(RIGHT_BORDER, i + TOP_BORDER);
    cout << "◈";
  }

  // 맨 밑 가로줄 출력
  TetrisInput::gotoxy(LEFT_BORDER, BOTTOM_BORDER);
  for (int i = 1; i < RIGHT_BORDER - LEFT_BORDER + 2; i++) {
    cout << "◈";
  }
}

void TetrisInterface::DrawQueBlocks(TetrisBlock **que_blocks) {
  for (int i = 0; i < QUE_BOX_COUNT; ++i) {
    que_blocks[i]->BlockPrint(QUE_LEFT_BORDER + 2,
                              QUE_TOP_BORDER + 2 + i * (QUE_BOX_SIZE + 1));
  }
}

// 대기 블록 인터페이스
// 가로 8칸
void TetrisInterface::DrawQueBoxBorder() {
  TetrisInput::gotoxy(QUE_LEFT_BORDER, QUE_TOP_BORDER);
  cout << WHITE;
  cout << "◈NE  XT◈";

  for (int i = 1; i <= QUE_BOX_COUNT; i++) {
    TetrisInput::gotoxy(QUE_LEFT_BORDER,
                        QUE_TOP_BORDER + i * (QUE_BOX_SIZE + 1));
    for (int j = 0; j < QUE_BOX_SIZE + 2; j++) {
      cout << "◈";
    }
  }

  for (int i = 0; i < QUE_BOX_SIZE * QUE_BOX_COUNT + QUE_BOX_COUNT; i++) {
    TetrisInput::gotoxy(QUE_LEFT_BORDER, QUE_TOP_BORDER + i);
    cout << "◈";
    TetrisInput::gotoxy(QUE_RIGHT_BORDER, QUE_TOP_BORDER + i);
    cout << "◈";
  }
}

void TetrisInterface::GameOver() {
  system("clear"); // 화면 초기화

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