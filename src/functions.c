#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "main.h"

snake initSnake(int length, char c, int x, int y) {
  static snake s;
  s.length = length;
  s.nodes = (snakeNode *) malloc(s.length * (sizeof(snakeNode)));
  for (int i = 0; i < s.length; i++) {
    s.nodes[i].x = x-i;
    s.nodes[i].y = y;
    s.nodes[i].c = c;
  }
  return s;
}

void drawSnake(WINDOW *w, snake *s) {
  for (int i = 0; i < s->length; i++) {
    snakeNode curNode = s->nodes[i];
    mvwaddch(w, curNode.y, curNode.x, curNode.c);
    mvwaddch(w, s->lastY, s->lastX, ' ');
  }
  wrefresh(w);
}

void placeFruit(WINDOW *w, fruit *f) {
  srand(time(0));
  int fruitX = rand()%swWidth;
  int fruitY = rand()%swHeight;
  f->x = fruitX;
  f->y = fruitY;
  mvwaddch(w, fruitY, fruitX, f->c);
}

void growSnake(snake *s) {
  int sLength = s->length;
  s->nodes = (snakeNode *) realloc(s->nodes, (sLength+1)*(sizeof(snakeNode)));
  s->nodes[sLength].x = s->nodes[sLength-1].x;
  s->nodes[sLength].y = s->nodes[sLength-1].y;
  s->nodes[sLength].c = s->nodes[sLength-1].c;
  s->length++;
}

void quit(WINDOW *w, snake *s) {
  endwin();
  delwin(w);
  free(s->nodes);
  exit(0);
}

void moveSnake(WINDOW *w, snake *s, int dX, int dY, fruit *f) {
  for (int i = s->length-1; i >= 0; i--) {
    snakeNode *curNode = &(s->nodes[i]);
    snakeNode *nextNode = &(s->nodes[i-1]);
    if (i == s->length-1) {
      s->lastX = curNode->x;
      s->lastY = curNode->y;
    }
    if (i == 0) {
      int newX = curNode->x+dX;
      int newY = curNode->y+dY;
      curNode->x = newX >= 0 ? (newX)%(swWidth) : swWidth;
      curNode->y = newY >= 0 ? (newY)%(swHeight) : swHeight;

      // check if the head touches any part of the body
      for (int k = 1; k < s->length-1; k++) {
	if (newX == s->nodes[k].x && newY == s->nodes[k].y) {
	  quit(w, s);
	}
      }
      if (newX == f->x && newY == f->y) {
	growSnake(s);
	placeFruit(w, f);
      }
    } else {
      curNode->x = nextNode->x;
      curNode->y = nextNode->y;
    };
  }
  drawSnake(w, s);
}
