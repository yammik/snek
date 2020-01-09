#include "game.h"
#include "draw.h"

#include <raylib.h>
#include <strings.h>

bool GameGoToScene(Game *g, GameScene scene)
{
  if (g->nextScene == scene)
    return false;
  g->nextScene = scene;
  g->sceneTransitionDuration = SCENE_TRANSITION_DURATION;
  return true;
}

static int prev = 0;

void ResetGame(Game *g)
{
}