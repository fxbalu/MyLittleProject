#include "input.h"




Input* createInput(){


    Input* input;

    if((input = (Input*)malloc(sizeof(Input))) == NULL){
        fprintf(stderr, "can't allocate memory for a input\n");
    }
    else{
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



void getInput(Input* input,Game* game){


SDL_Event event;

/* Keymapping : gère les appuis sur les touches et les enregistre
dans la structure input */

while(SDL_PollEvent(&event))
{
    switch(event.type)
    {

        case SDL_QUIT:
        game->go = 0;
        break;

        case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
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
        switch (event.key.keysym.sym)
        {

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



void destroyInput(Input* input){

    if(input != NULL) free(input);
}



