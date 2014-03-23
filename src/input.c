/**
 * \file input.c
 * \brief Functions to analyse and process the user's input.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 18 mars 2014
 */

#include "input.h"


/*ici on utilise toute la strucure Input*/

void initInput(Input* input) {

   input->event = (SDL_Event*) malloc(sizeof(SDL_Event));

   input->left = (Control*) malloc(sizeof(Control));
   input->up = (Control*) malloc(sizeof(Control));
   input->right = (Control*) malloc(sizeof(Control));
   input->down = (Control*) malloc(sizeof(Control));

   input->enter = (Control*) malloc(sizeof(Control));
   input->jump = (Control*) malloc(sizeof(Control));
   input->crouch = (Control*) malloc(sizeof(Control));
   input->shoot = (Control*) malloc(sizeof(Control));

   input->escape = (Control*) malloc(sizeof(Control));
   input->exit = (Control*) malloc(sizeof(Control));

input->left->down = input->left->pressed = false;
   clearInput(input);

}

void freeInput(Input* input) {
   clearInput(input);
   free(input->event);
   free(input);

   //rajouter tout le reste
}

/*au moins utile pour l'initialisation !*/
void clearInput(Input* input) {

   input->left->down = input->left->pressed = false;
   input->up->down = input->up->pressed = false; /*remplacer les noms down et pressed*/
   input->right->down = input->right->pressed = false;
   input->down->down = input->down->pressed = false;

   input->enter->down = input->enter->pressed = false;
   input->jump->down = input->jump->pressed = false;
   input->crouch->down = input->crouch->pressed = false;
   input->shoot->down = input->shoot->pressed = false;

   input->escape->down = input->escape->pressed = false;
   input->exit->down = input->exit->pressed = false;

}

//remet a zero les évenement d'appui, mais pas le maintient d'appui
void clearInputPressed(Input* input) {

   input->left->pressed = false;
   input->up->pressed = false; /*remplacer les noms down et pressed, trouver mieux*/
   input->right->pressed = false;
   input->down->pressed = false;

   input->enter->pressed = false;
   input->jump->pressed = false;
   input->crouch->pressed = false;
   input->shoot->pressed = false;

   input->escape->pressed = false;
   input->exit->pressed = false;

}


void getInput(Input* input, GameOptions* options) {

   clearInputPressed(input);

   while(SDL_PollEvent(input->event)) {

      switch (input->event->type) {
      case SDL_QUIT :
          input->exit->down = true;
          break;
            case SDL_KEYDOWN : /*gérer plus tard la manette*/

         switch ( input->event->key.keysym.sym) {
         case SDLK_LEFT :
             input->left->down = true;
             input->left->pressed = true;
            break;
         case SDLK_UP :
             input->up->down = true;
             input->up->pressed = true;
            break;
         case SDLK_RIGHT :
             input->right->down = true;
             input->right->pressed = true;
            break;
         case SDLK_DOWN :
             input->down->down = true;
             input->down->pressed = true;
            break;

         case SDLK_RETURN :
             input->enter->down = true;
             input->enter->pressed = true;
            break;
         case SDLK_SPACE :
             input->jump->down = true;
             input->jump->pressed = true;
            break;
         case SDLK_RCTRL :
             input->crouch->down = true;
             input->crouch->pressed = true;
            break;
         case SDLK_RSHIFT :
             input->shoot->down = true;
             input->shoot->pressed = true;
            break;

         case SDLK_ESCAPE :
             input->escape->down = true;
             input->escape->pressed = true;
            break;
         default :
            ;
         }
         break;

      case SDL_KEYUP :

         switch ( input->event->key.keysym.sym) {
         case SDLK_LEFT :
             input->left->down = false;
            break;
         case SDLK_UP :
             input->up->down = false;
            break;
         case SDLK_RIGHT :
             input->right->down = false;
            break;
         case SDLK_DOWN :
             input->down->down = false;
            break;

         case SDLK_RETURN :
             input->enter->down = false;
            break;
         case SDLK_SPACE :
             input->jump->down = false;
            break;
         case SDLK_RCTRL :
             input->crouch->down = false;
            break;
         case SDLK_RSHIFT :
             input->shoot->down = false;
            break;

         case SDLK_ESCAPE :
             input->escape->down = false;
            break;
         default :
            ;
         }
         default :
            ;





      /*case options->controlerDown :
          switch (input->event->key.keysym.sym) {//gerer la manette ici

          case options->left :
              input->left.down = true;
              input->left.pressed = true; //pressed : le fait d'appuyer, down pour la tenu de la touche
              break;
          case options->up :
              input->up.down = true;
              input->up.pressed = true;
              break;
          case options->right :
              input->right.down = true;
              input->right.pressed = true;
              break;
          case options->down :
              input.down = true;
              input.pressed = true;
              break;

          case options->enter :
              input.enter.down = true;
              input.enter.pressed = true;
              break;
          case options->jump :
              input->jump.down = true;
              input->jump.pressed = true;
              break;
          case options->crouch :
              input->crouch.down = true;
              input->crouch.pressed = true;
              break;
          case options->shoot :
              input->shoot.down = true;
              input->shoot.pressed = true;
              break;

          case options->escape :
              input->escape.down = true;
              input->escape.pressed = true;
              break;
          default :
              ;
          }
          break;

      case options->controlerUp :
          switch (input->event->key.keysym.sym) { //gerer la manette ici

          case options->left :
              input->left.pressed = false; //pressed : le fait d'appuyer, down pour la tenu de la touche
              break;
          case options->up :
              input->up.pressed = false;
              break;
          case options->right :
              input->right.pressed = false;
              break;
          case options->down :
              input.pressed = false;
              break;

          case options->enter :
              input.enter.pressed = false;
              break;
          case options->jump :
              input->jump.pressed = false;
              break;
          case options->crouch :
              input->crouch.pressed = false;
              break;
          case options->shoot :
              input->shoot.pressed = false;
              break;

          case options->escape :
              input->escape.pressed = false;
              break;
          default :
              ;
          }*/

      }
   }
}
/*obtient les touches appuyés pendat un cycle de la boucle ( en partant du dernier getInput)*/
/*a modifier : comparer les touches avec les options de controlees de jeu + gérer manette*
*/

