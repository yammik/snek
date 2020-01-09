#include "draw.h"
#include "game.h"

#include "scenes/title.h"
#include "scenes/snekgame.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Draw(Game *g)
{
  DrawBackground();
  switch (g->scene)
  {
  case GameScene_None:
    perror("No GameScene");
    exit(1);
    break;
  case GameScene_Title:
    DrawTitleScene(g);
    break;
  case GameScene_Game:
    DrawGameScene(g);
    break;
  }
}

void Update(Game *g)
{
  if (g->nextScene != GameScene_None)
  {
    g->sceneTransitionDuration--;
    if (g->sceneTransitionDuration <= 0)
    {
      g->scene = g->nextScene;
      g->nextScene = GameScene_None;
    }
  }

  switch (g->scene)
  {
  case GameScene_None:
    printf("No GameScene\n");
    exit(1);
    break;
  case GameScene_Title:
    UpdateTitleScene(g);
    break;
  case GameScene_Game:
    UpdateGameScene(g);
    break;
  }

  FRAME++;

  if (IsKeyPressed(KEY_ESCAPE))
  {
    g->scene = GameScene_Title;
  }
}

int main(void)
{
  // Initialize game state
  Game game = {0};
  game.scene = GameScene_Title;
  game.sceneTransitionDuration = 0;

  // Initialize Raylib
  SetExitKey(-1); // disable close via ESC
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
  SetTargetFPS(FPS);

  // Texture for rendering into
  RenderTexture2D canvas = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
  Rectangle src = {0, 0, canvas.texture.width, -canvas.texture.height};
  Rectangle dst = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  Vector2 origin = {0, 0};
  float rotation = 0;

  // Start main game loop
  while (!WindowShouldClose())
  {
    // Draw onto texture
    BeginTextureMode(canvas);
    Draw(&game);
    EndTextureMode();

    // Draw texture to screen
    BeginDrawing();
    DrawTexturePro(canvas.texture, src, dst, origin, rotation, WHITE);
    EndDrawing();

    // Do updates
    Update(&game);
  }

  // Unload textures
  UnloadRenderTexture(canvas);

  // Close window and exit
  CloseWindow();
  return 0;
}