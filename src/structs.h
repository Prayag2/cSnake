#ifndef STRUCTS
typedef struct {
  int x, y;
  char c;
} snakeNode;

typedef struct {
  int length, lastX, lastY;
  snakeNode *nodes;
} snake;

typedef struct {
  int x, y;
  char c;
} fruit;

#define STRUCTS
#endif
