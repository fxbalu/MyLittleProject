/**
 * \file gameOptions.c
 * \brief Functions to handle all the game's options.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

 #include "gameOptions.h"

void initGameOptions(Game* game) {
   game->options = (GameOptions*) malloc(sizeof(GameOptions));
   game->options->fullscreen = false;
   game->options->windowWidth = WINDOW_WIDTH_DEFAULT;
   game->options->windowHeight = WINDOW_HEIGHT_DEFAULT;
}
