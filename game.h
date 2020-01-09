#pragma once

#include <stdbool.h>

#define TITLE "S n E k"
#define FPS 60

typedef enum GameScene
{
  GameScene_None,
  GameScene_Title,
  GameScene_Game
} GameScene;

typedef struct Game
{
  GameScene scene;
  GameScene nextScene;
  int sceneTransitionDuration;
} Game;

bool GameGoToScene(Game *g, GameScene scene);

void ResetGame(Game *g);