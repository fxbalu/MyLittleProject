/**
 * \file input.h
 * \brief header of input.c
 *
 * Declaration of createInput, getInput and destroyInput.
 *
 */

#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "game.h"

void getInput(Input* input,Game* game);
Input* createInput();
void destroyInput(Input* input);


#endif
