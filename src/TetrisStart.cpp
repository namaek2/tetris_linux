//
// Created by namaek_2 on Nov/21/23.
//

#include "../include/TetrisGame.h"

// 메뉴 선택 화면
TetrisStart::TetrisStart() {
  system("clear");
  SetCursorY(20);
  SetMenuSelected(0);
  hide();

  PrintTitle();
  PrintMenu();
  SelectMenu();
}

// 메뉴 텍스트
int TetrisStart::GetEnum(int menu_type) {
  if (menu_type == BEGINNER) {
    cout << "Beginner";
    return 1;
  } else if (menu_type == AMATEUR) {
    cout << "Amateur";
    return 2;
  } else if (menu_type == EXPERT) {
    cout << "Expert";
    return 3;
  }
  cout << "Exit";
  return 4;
}

// 타이틀 출력
void TetrisStart::PrintTitle() {
  cout << RED;
  PrintT(39, 6);
  cout << MAGENTA;
  PrintE(53, 6);
  cout << YELLOW;
  PrintT(67, 6);
  cout << GREEN;
  PrintR(81, 6);
  cout << CYAN;
  PrintI(95, 6);
  cout << BLUE;
  PrintS(109, 6);
  cout << WHITE;

  TetrisInput::gotoxy(42, 36);
  cout << "회전 : S, D, 방향키 상 / 이동 : 방향키 좌, 우 ,하 / 하드드랍 : "
          "스페이스 바";
  TetrisInput::gotoxy(69, 40);
  cout << "made by namaek_2";
}

// 메뉴 출력
void TetrisStart::PrintMenu() {
  TetrisInput::gotoxy(74, 20);
  GetEnum(BEGINNER);
  TetrisInput::gotoxy(74, 22);
  GetEnum(AMATEUR);
  TetrisInput::gotoxy(74, 24);
  GetEnum(EXPERT);
  TetrisInput::gotoxy(74, 26);
  GetEnum(EXIT);
  TetrisInput::gotoxy(71, 20);
  cout << ">>\n";
}

// 메뉴 선택
void TetrisStart::SelectMenu() {
  int num = 0;
  while (true) {
    for (int i = 0; i < 100; i++) {
      Session();
      if (GetMenuSelected() == 0) {
        continue;
      }
      return;
    }
    if (num == 0) {
      TetrisInput::gotoxy(71, GetCursorY());
      cout << ">>";
      num = 1;
    }

    else {
      TetrisInput::gotoxy(71, GetCursorY());
      cout << "  ";
      num = 0;
    }
  }
}

// 키보드 입력 세션
void TetrisStart::Session() {
  if (TetrisInput::_kbhit()) {
    int input = TetrisInput::_getch();

    switch (input) {
    case ENTER: {
      MenuSelected(GetCursorY());
      return;
    }
    case ARROW_ESC: {
      input = TetrisInput::_getch();
      CursorMove(input, GetCursorY());
    }
    }
  }

  usleep(1000);
}

// 메뉴 선택 커서 이동
void TetrisStart::CursorMove(int dirrection, int y) {

  if (dirrection != 91) {
    return;
  }
  dirrection = TetrisInput::_getch();
  TetrisInput::gotoxy(71, y);
  cout << "  ";

  if (dirrection == UP) {
    if (y != 20) {
      SetCursorY(GetCursorY() - 2);
      return;
    }
    SetCursorY(26);
  } else if (dirrection == DOWN) {
    if (y != 26) {
      SetCursorY(GetCursorY() + 2);
      return;
    }
    SetCursorY(20);
  }
}

// 선택시 텍스트 반짝거리고, 선택된 메뉴 반환
void TetrisStart::MenuSelected(int y) {
  for (int i = 0; i < 5; i++) {
    TetrisInput::gotoxy(74, y);
    cout << "        ";
    usleep(100000);
    TetrisInput::gotoxy(74, y);
    GetEnum(y);
    usleep(100000);
  }

  SetMenuSelected(GetEnum(y));
}

// T 출력
void TetrisStart::PrintT(int x, int y) {
  TetrisInput::gotoxy(x, y);
  cout << "▣▣▣▣▣▣▣▣";
  TetrisInput::gotoxy(x, y + 1);
  cout << "   ▣▣   ";
  TetrisInput::gotoxy(x, y + 2);
  cout << "   ▣▣   ";
  TetrisInput::gotoxy(x, y + 3);
  cout << "   ▣▣   ";
  TetrisInput::gotoxy(x, y + 4);
  cout << "   ▣▣   ";
  TetrisInput::gotoxy(x, y + 5);
  cout << "   ▣▣   ";
  TetrisInput::gotoxy(x, y + 6);
  cout << "   ▣▣   ";
}

// E 출력
void TetrisStart::PrintE(int x, int y) {
  TetrisInput::gotoxy(x, y);
  cout << "▣▣▣▣▣▣▣▣";
  TetrisInput::gotoxy(x, y + 1);
  cout << "▣▣      ";
  TetrisInput::gotoxy(x, y + 2);
  cout << "▣▣      ";
  TetrisInput::gotoxy(x, y + 3);
  cout << "▣▣▣▣▣▣  ";
  TetrisInput::gotoxy(x, y + 4);
  cout << "▣▣      ";
  TetrisInput::gotoxy(x, y + 5);
  cout << "▣▣      ";
  TetrisInput::gotoxy(x, y + 6);
  cout << "▣▣▣▣▣▣▣▣";
}

// R 출력
void TetrisStart::PrintR(int x, int y) {
  TetrisInput::gotoxy(x, y);
  cout << "▣▣▣▣▣▣▣ ";
  TetrisInput::gotoxy(x, y + 1);
  cout << "▣▣    ▣▣";
  TetrisInput::gotoxy(x, y + 2);
  cout << "▣▣    ▣▣";
  TetrisInput::gotoxy(x, y + 3);
  cout << "▣▣▣▣▣▣▣ ";
  TetrisInput::gotoxy(x, y + 4);
  cout << "▣▣    ▣▣";
  TetrisInput::gotoxy(x, y + 5);
  cout << "▣▣    ▣▣";
  TetrisInput::gotoxy(x, y + 6);
  cout << "▣▣    ▣▣";
}

// I 출력
void TetrisStart::PrintI(int x, int y) {
  TetrisInput::gotoxy(x, y);
  cout << "▣▣▣▣▣▣▣▣";
  TetrisInput::gotoxy(x, y + 1);
  cout << "   ▣▣   ";
  TetrisInput::gotoxy(x, y + 2);
  cout << "   ▣▣   ";
  TetrisInput::gotoxy(x, y + 3);
  cout << "   ▣▣   ";
  TetrisInput::gotoxy(x, y + 4);
  cout << "   ▣▣   ";
  TetrisInput::gotoxy(x, y + 5);
  cout << "   ▣▣   ";
  TetrisInput::gotoxy(x, y + 6);
  cout << "▣▣▣▣▣▣▣▣";
}

// S 출력
void TetrisStart::PrintS(int x, int y) {
  TetrisInput::gotoxy(x, y);
  cout << " ▣▣▣▣▣▣▣";
  TetrisInput::gotoxy(x, y + 1);
  cout << "▣▣      ";
  TetrisInput::gotoxy(x, y + 2);
  cout << " ▣▣▣    ";
  TetrisInput::gotoxy(x, y + 3);
  cout << "   ▣▣   ";
  TetrisInput::gotoxy(x, y + 4);
  cout << "    ▣▣▣ ";
  TetrisInput::gotoxy(x, y + 5);
  cout << "      ▣▣";
  TetrisInput::gotoxy(x, y + 6);
  cout << "▣▣▣▣▣▣▣ ";
}

// 커서 Y 좌표 반환
int TetrisStart::GetCursorY() const { return cursor_y; }

// 커서 Y 좌표 설정
void TetrisStart::SetCursorY(int y) { cursor_y = y; }

// 선택된 메뉴 반환
int TetrisStart::GetMenuSelected() const { return menu_selected; }

// 선택 메뉴 설정
void TetrisStart::SetMenuSelected(int m) { menu_selected = m; }