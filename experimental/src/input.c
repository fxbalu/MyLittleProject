/**
 * \file input.c
 * \brief  Functions to manage the user's inputs
 *
 *	Implementation of CreateInput, getInput and destroyInput.
 *
 * \author François-Xavier Balu, Gwendal Henry, Martin Parisot, Vincent Werner
 */

#include "input.h"

/**
 * \fn Input* createInput()
 * \brief Create the Input structure
 *
 * the Input structure is allocate and initialized.
 * If the allocation failed the function returns NULL.
 */
Input* createInput() {

   Input* input;

   if ((input = (Input*)malloc(sizeof(Input))) == NULL) {
      fprintf(stderr, "can't allocate memory for a input\n");
   } else {
      input->left = 0;
      input->right = 0;
      input->up = 0;
      input->down = 0;
      input->use = 0;
      input->enter = 0;
      input->pause = 0;
      input->jump = 0;
   }

   return input;

}


/**
 * \fn void getInput(Input* input,Game* game)
 * \brief Get the user's inputs
 *
 * \param[in] input Input structure
 * \param[in] game Game structure
 *
 * The Input structure is updated.
 * If a key is pressed the corresponding integer is set to 1, else if it's released, the integer is set to 0.
 */
void getInput(Input* input,Game* game) {

   SDL_Event event;

   while(SDL_PollEvent(&event)) {
      switch(event.type) {

      case SDL_QUIT:
         game->go = 0;
         break;

      case SDL_KEYDOWN:
         switch (event.key.keysym.sym) {
         case SDLK_ESCAPE:

            exit(0);
            break;

         case SDLK_SPACE:
            input->jump = 1;
            break;

         case SDLK_e:
            input->use = 1;
            break;

         case SDLK_LEFT:
            input->left = 1;
            break;

         case SDLK_RIGHT:
            input->right = 1;
            break;

         case SDLK_DOWN:
            input->down = 1;
            break;

         case SDLK_UP:
            input->up = 1;
            break;

         case SDLK_RETURN:
            input->enter = 1;
            break;

         default:
            break;
         }
         break;

      case SDL_KEYUP:
         switch (event.key.keysym.sym) {

         case SDLK_e:
            input->use = 0;
            break;


         case SDLK_SPACE:
            input->jump = 0;
            break;

         case SDLK_LEFT:
            input->left = 0;
            break;

         case SDLK_RIGHT:
            input->right = 0;
            break;

         case SDLK_DOWN:
            input->down = 0;
            break;

         case SDLK_UP:
            input->up = 0;
            break;


         default:
            break;
         }
         break;

      }

   }
}


/**
 * \fn destroyInput(Input* input)
 * \brief Free the Input structure
 *
 * \param[in] input Input structure to free.
 *
 * The Input structure is freed.
 */
void destroyInput(Input* input) {

   if(input != NULL) {
      free(input);
   }
}



