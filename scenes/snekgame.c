#include "snekgame.h"

#include "../draw.h"
#include "../game.h"
#include <raylib.h>
#include <stdio.h>
#include <strings.h>

static void drawSnek(Game *g)
{
  int height = 320;
  DrawText("This is the game scene", 10, 10, 30, SKYBLUE);
}

void DrawGameScene(Game *g)
{
  drawSnek(g);
}

void UpdateGameScene(Game *g)
{
}