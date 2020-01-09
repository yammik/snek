#include "title.h"

#include "../draw.h"
#include "../game.h"
#include <raylib.h>
#include <stdio.h>
#include <string.h>

void DrawTitleScene(Game *g)
{
  DrawHeading(&(DrawHeadingProps){
      .level = H1,
      .text = TITLE,
      .x = SCREEN_CENTER_X - (MeasureText(TITLE, FONT_SIZE_H1) / 2),
      .y = 32,
  });

  DrawButton(&(DrawButtonProps){
      .text = "Press ENTER to s N e K",
      .x = SCREEN_CENTER_X - (MeasureText("Press ENTER to s N e K", FONT_SIZE_H3) / 2),
      .y = SCREEN_CENTER_Y - (FONT_SIZE_H3 / 2),
      .blink = g->nextScene != GameScene_None
                   ? DEFAULT_BLINK_RATE / 4
                   : DEFAULT_BLINK_RATE,
  });
  return;
}

void UpdateTitleScene(Game *g)
{
  if (IsKeyPressed(KEY_ENTER))
  {
    if (GameGoToScene(g, GameScene_Game))
    {
      DrawHeading(&(DrawHeadingProps){
          .level = H2,
          .text = "You did press Enter",
          .x = SCREEN_CENTER_X - (MeasureText("You did press Enter", FONT_SIZE_H2) / 2),
          .y = 32,
      });
      return;
    };
  };
}