//
// Created by namaek_2 on 12/1/23.
//
#include "../include/TetrisGame.h"

TetrisInterface::TetrisInterface() {
  ScreenBorder();
  GameBorder();
  DrawQueBorder();
}

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
  for (int i = 1; i < bottom_border - top_border; i++) {
    TetrisInput::gotoxy(left_border, i + top_border);
    cout << "◈";
    TetrisInput::gotoxy(right_border, i + top_border);
    cout << "◈";
  }

  // 맨 밑 가로줄 출력
  TetrisInput::gotoxy(left_border, bottom_border);
  for (int i = 1; i < right_border - left_border + 2; i++) {
    cout << "◈";
  }
}

// 대기 블록 인터페이스
// 가로 8칸
void TetrisInterface::DrawQueBorder() {
  TetrisInput::gotoxy(38, 6);

  cout << WHITE;
  cout << "◈NE  XT◈";

  for (int i = 0; i < 5; i++) {
    TetrisInput::gotoxy(38, 11 + i * 5);
    for (int j = 0; j < 8; j++) {
      cout << "◈";
    }
  }

  for (int i = 0; i < 26; i++) {
    TetrisInput::gotoxy(38, 6 + i);
    cout << "◈";
    TetrisInput::gotoxy(45, 6 + i);
    cout << "◈";
  }
}

void TetrisInterface::GameOver() {
  system("clear"); // 화면 초기화

  TetrisInput::gotoxy(56, 6);
  printf(" ▣▣▣▣▣▣      ▣▣▣▣▣▣     ▣▣    ▣▣    ▣▣▣▣▣▣▣▣");
  TetrisInput::gotoxy(56, 6 + 1);
  printf("▣▣    ▣▣    ▣▣    ▣▣    ▣▣▣  ▣▣▣    ▣▣      ");
  TetrisInput::gotoxy(56, 6 + 2);
  printf("▣▣    ▣▣    ▣▣    ▣▣    ▣▣ ▣▣ ▣▣    ▣▣      ");
  TetrisInput::gotoxy(56, 6 + 3);
  printf("▣▣          ▣▣▣▣▣▣▣▣    ▣▣ ▣▣ ▣▣    ▣▣▣▣▣▣▣▣");
  TetrisInput::gotoxy(56, 6 + 4);
  printf("▣▣  ▣▣▣▣    ▣▣    ▣▣    ▣▣    ▣▣    ▣▣      ");
  TetrisInput::gotoxy(56, 6 + 5);
  printf("▣▣    ▣▣    ▣▣    ▣▣    ▣▣    ▣▣    ▣▣      ");
  TetrisInput::gotoxy(56, 6 + 6);
  printf(" ▣▣▣▣▣▣     ▣▣    ▣▣    ▣▣    ▣▣    ▣▣▣▣▣▣▣▣");

  TetrisInput::gotoxy(56, 6 + 8);
  printf(" ▣▣▣▣▣▣     ▣▣    ▣▣    ▣▣▣▣▣▣▣▣    ▣▣▣▣▣▣▣ ");
  TetrisInput::gotoxy(56, 6 + 9);
  printf("▣▣    ▣▣    ▣▣    ▣▣    ▣▣          ▣▣    ▣▣");
  TetrisInput::gotoxy(56, 6 + 10);
  printf("▣▣    ▣▣    ▣▣    ▣▣    ▣▣          ▣▣    ▣▣");
  TetrisInput::gotoxy(56, 6 + 11);
  printf("▣▣    ▣▣    ▣▣    ▣▣    ▣▣▣▣▣▣▣▣    ▣▣▣▣▣▣▣ ");
  TetrisInput::gotoxy(56, 6 + 12);
  printf("▣▣    ▣▣    ▣▣    ▣▣    ▣▣          ▣▣    ▣▣");
  TetrisInput::gotoxy(56, 6 + 13);
  printf("▣▣    ▣▣     ▣▣  ▣▣     ▣▣          ▣▣    ▣▣");
  TetrisInput::gotoxy(56, 6 + 14);
  printf(" ▣▣▣▣▣▣       ▣▣▣▣      ▣▣▣▣▣▣▣▣    ▣▣    ▣▣");

  // TetrisInput::gotoxy(70, 25);
  //  printf("YOUR SCORE : %d", score); // 최종 점수 출력

  TetrisInput::gotoxy(65, 30);
  cout << "Press any key to go to menu";

  // TetrisInput::_getch(); // 후 아무 키 입력시 메인화면으로 복귀
}