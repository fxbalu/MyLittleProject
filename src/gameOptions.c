#include "gameOptions.h"

void initGameOptions(Game* game) {
   game->options = (GameOptions*) malloc(sizeof(GameOptions));
   game->options->fullscreen = false;
   game->options->windowWidth = WINDOW_WIDTH_DEFAULT;
   game->options->windowHeight = WINDOW_HEIGHT_DEFAULT;
}
