//
// Created by namaek_2 on 11/21/23.
//

#include "../include/TetrisStart.h"

#define ENTER 13
#define ARROW '\033'
#define UP 65
#define DOWN 66

Color::Modifier RED(Color::FG_RED);
Color::Modifier MAGENTA(Color::FG_MAGENTA);
Color::Modifier YELLOW(Color::FG_YELLOW);
Color::Modifier BLUE(Color::FG_BLUE);
Color::Modifier CYAN(Color::FG_CYAN);
Color::Modifier GREEN(Color::FG_GREEN);
Color::Modifier WHITE(Color::FG_WHITE);

TetrisInput kb;

TetrisStart::TetrisStart() {
  system("clear");
  initscr();
  hide();
  PrintTitle();
  PrintMenu();
  SelectMenu();
  endwin();
}

int TetrisStart::GetEnum(int level_type) {
  if (level_type == BEGINNER) {
    cout << "Beginner";
    return 1;
  } else if (level_type == AMATEUR) {
    cout << "Amateur";
    return 2;
  } else if (level_type == EXPERT) {
    cout << "Expert";
    return 3;
  }
  cout << "Exit";
  return 4;
}

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

  kb.gotoxy(42, 36);
  cout << "회전 : S, D, 방향키 상 / 이동 : 방향키 좌, 우 ,하 / 하드드랍 : "
          "스페이스 바";
  kb.gotoxy(70, 40);
  cout << "made by namaek";
}

void TetrisStart::PrintMenu() {
  kb.gotoxy(74, 20);
  GetEnum(BEGINNER);
  kb.gotoxy(74, 22);
  GetEnum(AMATEUR);
  kb.gotoxy(74, 24);
  GetEnum(EXPERT);
  kb.gotoxy(74, 26);
  GetEnum(EXIT);
  kb.gotoxy(71, 20);
  cout << ">>\n";
}

int TetrisStart::SelectMenu() {
  int num = 0;
  while (true) {
    for (int i = 0; i < 100; i++) {
      int temp = Session();
      if (temp == 0) {
        continue;
      }
      return temp;
    }
    if (num == 0) {
      kb.gotoxy(71, GetCursorY());
      printf(">>");
      num = 1;
    }

    else {
      kb.gotoxy(71, GetCursorY());
      printf("  ");
      num = 0;
    }
  }
}

int TetrisStart::Session() {
  if (kb._kbhit()) {
    int input = kb._getch();

    switch (input) {
    case ENTER:
      return MenuSelected(GetCursorY());
    case ARROW:
      input = kb._getch();
      CursorMove(input, GetCursorY());
    }
  }
  usleep(1000);

  return 0;
}

void TetrisStart::CursorMove(int dirrection, int y) {

  if (dirrection != 91) {
    return;
  }
  dirrection = kb._getch();
  kb.gotoxy(71, y);
  printf("  ");

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

// 선택시 반짝거림
int TetrisStart::MenuSelected(int y) {
  for (int i = 0; i < 5; i++) {
    kb.gotoxy(74, y);
    printf("        ");
    usleep(100000);
    kb.gotoxy(74, y);
    GetEnum(y);
    usleep(100000);
  }

  return GetEnum(y);
}

void TetrisStart::PrintT(int x, int y) // T 출력
{
  kb.gotoxy(x, y);
  cout << "▣▣▣▣▣▣▣▣";
  kb.gotoxy(x, y + 1);
  cout << "   ▣▣   ";
  kb.gotoxy(x, y + 2);
  cout << "   ▣▣   ";
  kb.gotoxy(x, y + 3);
  cout << "   ▣▣   ";
  kb.gotoxy(x, y + 4);
  cout << "   ▣▣   ";
  kb.gotoxy(x, y + 5);
  cout << "   ▣▣   ";
  kb.gotoxy(x, y + 6);
  cout << "   ▣▣   ";
}

void TetrisStart::PrintE(int x, int y) // E 출력
{
  kb.gotoxy(x, y);
  cout << "▣▣▣▣▣▣▣▣";
  kb.gotoxy(x, y + 1);
  cout << "▣▣      ";
  kb.gotoxy(x, y + 2);
  cout << "▣▣      ";
  kb.gotoxy(x, y + 3);
  cout << "▣▣▣▣▣▣  ";
  kb.gotoxy(x, y + 4);
  cout << "▣▣      ";
  kb.gotoxy(x, y + 5);
  cout << "▣▣      ";
  kb.gotoxy(x, y + 6);
  cout << "▣▣▣▣▣▣▣▣";
}

void TetrisStart::PrintR(int x, int y) // R 출력
{
  kb.gotoxy(x, y);
  cout << "▣▣▣▣▣▣▣ ";
  kb.gotoxy(x, y + 1);
  cout << "▣▣    ▣▣";
  kb.gotoxy(x, y + 2);
  cout << "▣▣    ▣▣";
  kb.gotoxy(x, y + 3);
  cout << "▣▣▣▣▣▣▣ ";
  kb.gotoxy(x, y + 4);
  cout << "▣▣    ▣▣";
  kb.gotoxy(x, y + 5);
  cout << "▣▣    ▣▣";
  kb.gotoxy(x, y + 6);
  cout << "▣▣    ▣▣";
}

void TetrisStart::PrintI(int x, int y) // I 출력
{
  kb.gotoxy(x, y);
  cout << "▣▣▣▣▣▣▣▣";
  kb.gotoxy(x, y + 1);
  cout << "   ▣▣   ";
  kb.gotoxy(x, y + 2);
  cout << "   ▣▣   ";
  kb.gotoxy(x, y + 3);
  cout << "   ▣▣   ";
  kb.gotoxy(x, y + 4);
  cout << "   ▣▣   ";
  kb.gotoxy(x, y + 5);
  cout << "   ▣▣   ";
  kb.gotoxy(x, y + 6);
  cout << "▣▣▣▣▣▣▣▣";
}

void TetrisStart::PrintS(int x, int y) // S 출력
{
  kb.gotoxy(x, y);
  cout << " ▣▣▣▣▣▣▣";
  kb.gotoxy(x, y + 1);
  cout << "▣▣      ";
  kb.gotoxy(x, y + 2);
  cout << " ▣▣▣    ";
  kb.gotoxy(x, y + 3);
  cout << "   ▣▣   ";
  kb.gotoxy(x, y + 4);
  cout << "    ▣▣▣ ";
  kb.gotoxy(x, y + 5);
  cout << "      ▣▣";
  kb.gotoxy(x, y + 6);
  cout << "▣▣▣▣▣▣▣ ";
}

int TetrisStart::GetCursorY() { return cursor_y; }

void TetrisStart::SetCursorY(int y) { cursor_y = y; }
