#include "GameStatus.h"


void initGameStatus(GameStatus* status) {
   status->gameIsRunning = TRUE;

   status->options = (GameOptions*) malloc(sizeof(GameOptions));

   status->options->fullscreen = FALSE;
   status->options->windowWidth = WINDOW_WIDTH_DEFAULT;
   status->options->windowHeight = WINDOW_HEIGTH_DEFAULT;

   status->nextTick = status->sleepTime = 0;
}
