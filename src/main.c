#include <curses.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"
#include "structs.h"
#include "main.h"

int swWidth;
int swHeight;
int swX;
int swY;

int main() {
  // setting up the locale
  setlocale(LC_ALL, "en_US.UTF-8");

  initscr(); // initialize screen
  keypad(stdscr, TRUE); // enable arrow keys
  noecho(); // don't echo user input
  cbreak(); // don't wait for newline or EOL
  curs_set(0); // hide cursor
  box(stdscr, 0, 0); // draw main border
  timeout(0); // use non blocking user input

  // sw stands for "Snake Window"
  swWidth = COLS-2; swHeight = LINES-2; swX = 1; swY = 1;
  snake theSnake = initSnake(1, 'o', 0, 0);
  fruit theFruit = {0, 0, '@'};
  WINDOW *snakeWindow = newwin(swHeight, swWidth, swY, swX);
  drawSnake(snakeWindow, &theSnake);
  placeFruit(snakeWindow, &theFruit);

  int dX = STEP_MULTIPLIER, dY = 0, ch;
  while ((char)(ch = getch()) != 'q') {
    moveSnake(snakeWindow, &theSnake, dX, dY, &theFruit);
    switch(ch) {
    case KEY_W:
    case KEY_K:
    case KEY_UP:
      dX = 0; dY = dY != 1 ? -1 * STEP_MULTIPLIER : 1;
      break;
    case KEY_S:
    case KEY_J:
    case KEY_DOWN:
      dX = 0; dY = dY != -1 ? STEP_MULTIPLIER : -1;
      break;
    case KEY_A:
    case KEY_H:
    case KEY_LEFT:
      dX = dX != 1 ? -1 * STEP_MULTIPLIER : 1; dY = 0;
      break;
    case KEY_D:
    case KEY_L:
    case KEY_RIGHT:
      dX = dX != -1 ? STEP_MULTIPLIER : -1; dY = 0;
      break;
    }
    usleep(PAUSE);
  }
  quit(snakeWindow, &theSnake);
  return 0;
}
