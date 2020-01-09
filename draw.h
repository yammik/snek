#pragma once

#include <raylib.h>

Color BG_COLOR;
Color FG_COLOR;
Color ERROR_COLOR;
int FONT_SIZE_H1;
int FONT_SIZE_H2;
int FONT_SIZE_H3;
int FONT_SIZE_LARGE;
int FONT_SIZE_DEFAULT;
int FONT_SIZE_SMALL;
int FRAME;
int DEFAULT_BLINK_RATE;
int SCENE_TRANSITION_DURATION;
int KEY_REPEAT_RATE;
float SCREEN_WIDTH;
float SCREEN_HEIGHT;
float SCREEN_CENTER_X;
float SCREEN_CENTER_Y;

//------------------------------------------------------------------------------
// Background
//------------------------------------------------------------------------------

void DrawBackground(void);

//------------------------------------------------------------------------------
// Heading
//------------------------------------------------------------------------------

typedef struct DrawHeadingProps
{
  enum
  {
    H1,
    H2,
    H3
  } level;
  char *text;
  int x;
  int y;
  bool invert;
} DrawHeadingProps;

void DrawHeading(DrawHeadingProps *p);

//------------------------------------------------------------------------------
// Button
//------------------------------------------------------------------------------

typedef struct DrawButtonProps
{
  char *text;
  int x;
  int y;
  int blink;
  bool invert;
} DrawButtonProps;

void DrawButton(DrawButtonProps *p);

//------------------------------------------------------------------------------
// TextBox
//------------------------------------------------------------------------------

typedef struct DrawTextBoxProps
{
  enum
  {
    DEFAULT,
    SMALL,
    LARGE
  } size;
  const char *text;
  int padding;
  int x;
  int y;
  int width;
  int height;
  int borderWidth;
  Color color;
} DrawTextBoxProps;

void DrawTextBox(DrawTextBoxProps *p);
