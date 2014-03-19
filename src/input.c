/**
 * \file input.c
 * \brief Functions to analyse and process the user's input.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 18 mars 2014
 */

#include "input.h"

void initInput(Game* game) {

   game->input = (Input*) malloc(sizeof(Input));
   game->input->event = (SDL_Event*) malloc(sizeof(SDL_Event));
   clearInput(game);
}

void clearInput(Game* game) {

   game->input->left = false;
   game->input->up = false;
   game->input->right = false;
   game->input->down = false;

   game->input->enter = false;
   game->input->jump = false;
   game->input->crouch = false;
   game->input->shoot = false;

   game->input->escape = false;
   game->input->exit = false;
}

/*obtient les touches appuyés pendat un cycle de la boucle ( en partant du dernier getInput)*/
/*a modifier : comparer les touches avec les options de controlees de jeu + gérer manette*
+ utilise des edefines de valeur par défault :*/
/*regarder précisement au débuggeur si tout marche !!!*/

/* solution : on peut stocker une input e,n appuyant enlever en relachant (sdlk_up), et clear les input quand on en a besoin,
lors d'une transistion par ex (pour éviter de faire échap échap et donc quitter le jeu en 2frames.*/
void getInput(Game* game) {

   /*On analyse tous  les événements entrés*/
   while(SDL_PollEvent(game->input->event)) {
      switch (game->input->event->type) {
      case SDL_QUIT :
         game->input->exit = true;
         break;

      case SDL_KEYDOWN : /*gérer plus tard la manette*/

         switch (game->input->event->key.keysym.sym) {
         case SDLK_LEFT :
            game->input->left = true;
            break;
         case SDLK_UP :
            game->input->up = true;
            break;
         case SDLK_RIGHT :
            game->input->right = true;
            break;
         case SDLK_DOWN :
            game->input->down = true;
            break;

         case SDLK_RETURN :
            game->input->enter = true;
            break;
         case SDLK_SPACE :
            game->input->jump = true;
            break;
         case SDLK_RCTRL :
            game->input->crouch = true;
            break;
         case SDLK_RSHIFT :
            game->input->shoot = true;
            break;

         case SDLK_ESCAPE :
            game->input->escape = true;
            break;
         case SDLK_BACKSPACE :
            game->input->escape = true; /*deuxieme touche escape*/
            break;
         default :
            ;
         }
         break;

      case SDL_KEYUP :

         switch (game->input->event->key.keysym.sym) {
         case SDLK_LEFT :
            game->input->left = false;
            break;
         case SDLK_UP :
            game->input->up = false;
            break;
         case SDLK_RIGHT :
            game->input->right = false;
            break;
         case SDLK_DOWN :
            game->input->down = false;
            break;

         case SDLK_RETURN :
            game->input->enter = false;
            break;
         case SDLK_SPACE :
            game->input->jump = false;
            break;
         case SDLK_RCTRL :
            game->input->crouch = false;
            break;
         case SDLK_RSHIFT :
            game->input->shoot = false;
            break;

         case SDLK_ESCAPE :
            game->input->escape = false;
            break;
         case SDLK_BACKSPACE :
            game->input->escape = false; /*deuxieme touche escape*/
            break;
         default :
            ;
         }

      }
   }
}
