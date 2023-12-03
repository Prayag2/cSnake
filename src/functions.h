#include <ncurses.h>
#include "structs.h"

extern snake initSnake(int length, char c, int x, int y);
extern void drawSnake(WINDOW *w, snake *s);
extern void moveSnake(WINDOW *w, snake *s, int dX, int dY, fruit *f);
extern void growSnake(snake *s);
extern void quit(WINDOW *w, snake *s);
extern void placeFruit(WINDOW *w, fruit *f);
