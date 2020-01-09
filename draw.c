#include "draw.h"
#include <raylib.h>

Color BG_COLOR = {13, 19, 33, 255};
Color FG_COLOR = {57, 61, 73, 255};
Color ERROR_COLOR = RED;
int FONT_SIZE_H1 = 72;
int FONT_SIZE_H2 = 60;
int FONT_SIZE_H3 = 54;
int FONT_SIZE_LARGE = 36;
int FONT_SIZE_DEFAULT = 24;
int FONT_SIZE_SMALL = 18;
int FRAME = 0;
int DEFAULT_BLINK_RATE = 64;
int SCENE_TRANSITION_DURATION = 64;
int KEY_REPEAT_RATE = 4;
float SCREEN_WIDTH = 1600;
float SCREEN_HEIGHT = 800;
float SCREEN_CENTER_X = 800;
float SCREEN_CENTER_Y = 400;

void DrawBackground(void)
{
  ClearBackground(BG_COLOR);
}

void DrawHeading(DrawHeadingProps *p)
{
  int size = p->level == H1 ? FONT_SIZE_H1 : p->level == H2 ? FONT_SIZE_H2 : FONT_SIZE_H3;
  DrawText(p->text, p->x, p->y, size, p->invert ? BG_COLOR : FG_COLOR);
}

void DrawButton(DrawButtonProps *p)
{
  if (p->blink > 0 && (FRAME % p->blink) < (p->blink / 2))
  {
    return;
  }
  DrawText(p->text, p->x, p->y, FONT_SIZE_H3, p->invert ? BG_COLOR : FG_COLOR);
}

void DrawTextBox(DrawTextBoxProps *p)
{
  int size = p->size == LARGE ? FONT_SIZE_LARGE : p->size == SMALL ? FONT_SIZE_SMALL : FONT_SIZE_DEFAULT;
  int pad = p->padding;
  int pad2x = pad * 2;
  int x = p->x;
  int y = p->y;
  int width = p->width;
  int height = p->height;
  Rectangle rectBounds = {
      .x = x,
      .y = y,
      .width = width,
      .height = height,
  };
  Rectangle textBounds = {
      .x = x + pad,
      .y = y + pad,
      .width = width - pad2x,
      .height = height - pad2x,
  };
  if (p->borderWidth > 0)
  {
    DrawRectangleLinesEx(rectBounds, 3, FG_COLOR);
    // DrawRectangleLinesEx(textBounds, 3, LIGHTGRAY); // DEBUG
  }
  DrawTextRec(
      GetFontDefault(),
      p->text,
      textBounds,
      size,
      4.0f,
      true,
      p->color.a == 0 ? FG_COLOR : p->color);
}