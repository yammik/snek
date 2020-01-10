#include "snekgame.h"

#include "../draw.h"
#include "../game.h"
#include <raylib.h>
#include <stdio.h>
#include <strings.h>

int TEXT_X_POS = 10;
bool LTR = true;
int SPEED = 1;
int X_VELOCITY = 1;
int Y_VELOCITY = 0;

// snek conformations
char SNEK_RIGHT[7] = {'<', '-', '-', '-', ':', '>', '\0'};
char SNEK_LEFT[7] = {'<', ':', '-', '-', '-', '>', '\0'};
char SNEK_DOWN[7] = {'^', '|', '|', '|', '..', 'v', '\0'};
char SNEK_UP[7] = {'^', '..', '|', '|', '|', 'v', '\0'};

int SQUARE_SIZE = 25;
int SNEK_X = 0;
int SNEK_Y = 0;

bool CAN_MOVE = true;

static void drawSnek(Game *g)
{
  for (int i = 0; i < sizeof(SNEK_RIGHT) - 1; i++)
  {
    char c = SNEK_RIGHT[i];
    if (X_VELOCITY < 0)
    {
      c = SNEK_LEFT[i];
    }
    if (Y_VELOCITY > 0)
    {
      c = SNEK_DOWN[i];
    }
    if (Y_VELOCITY < 0)
    {
      c = SNEK_UP[i];
    }

    if (X_VELOCITY != 0)
    {
      DrawText(&c, SNEK_X + (i * SQUARE_SIZE), SNEK_Y, 50, GREEN);
    }

    if (Y_VELOCITY != 0)
    {
      DrawText(&c, SNEK_X, SNEK_Y + (i * SQUARE_SIZE), 50, GREEN);
    }
  }
}

void DrawGameScene(Game *g)
{
  drawSnek(g);
}

void UpdateGameScene(Game *g)
{
  SNEK_X += X_VELOCITY;
  SNEK_Y += Y_VELOCITY;

  CAN_MOVE = true;

  if (IsKeyPressed(KEY_LEFT) && X_VELOCITY == 0 && CAN_MOVE)
  {
    X_VELOCITY = -SPEED;
    Y_VELOCITY = 0;
    CAN_MOVE = false;
  }

  if (IsKeyPressed(KEY_RIGHT) && X_VELOCITY == 0 && CAN_MOVE)
  {
    X_VELOCITY = SPEED;
    Y_VELOCITY = 0;
    CAN_MOVE = false;
  }

  if (IsKeyPressed(KEY_UP) && Y_VELOCITY == 0)
  {
    X_VELOCITY = 0;
    Y_VELOCITY = -SPEED;
    CAN_MOVE = false;
  }

  if (IsKeyPressed(KEY_DOWN) && Y_VELOCITY == 0 && CAN_MOVE)
  {
    X_VELOCITY = 0;
    Y_VELOCITY = SPEED;
    CAN_MOVE = false;
  }
}