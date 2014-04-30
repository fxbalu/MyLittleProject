
#include "player.h"


void initializePlayer(void)
{

    /* Charge le sprite de notre héros */
    changeAnimation(&player,"graphics/walkright.png");

    //Indique l'état et la direction de notre héros
    player.direction = RIGHT;
    player.etat = IDLE;


  /* Coordonnées de démarrage de notre héros */
   player.x = 60;
   player.y = 460;

   player.w = PLAYER_WIDTH;
   player.h = PLAYER_HEIGTH;

   player.onGround = 0;
   player.timerMort = 0;

   jeu.nombreMonstres = 0;




}


void updatePlayer(void)
{

   //On rajoute un timer au cas où notre héros mourrait lamentablement en tombant dans un trou...
   //Si le timer vaut 0, c'est que tout va bien, sinon, on le décrémente jusqu'à 0, et là,
   //on réinitialise.
   //C'est pour ça qu'on ne gère le joueur que si ce timer vaut 0.
  if (player.timerMort == 0)
  {

    //On réinitialise notre vecteur de déplacement latéral (X), pour éviter que le perso
    //ne fonce de plus en plus vite pour atteindre la vitesse de la lumière ! ;)
    //Essayez de le désactiver pour voir !
    player.dirX = 0;

    // La gravité fait toujours tomber le perso : on incrémente donc le vecteur Y
    player.dirY += GRAVITY_SPEED;

    //Mais on le limite pour ne pas que le joueur se mette à tomber trop vite quand même
    if (player.dirY >= MAX_FALL_SPEED)
    {
        player.dirY = MAX_FALL_SPEED;
    }

    //Voilà, au lieu de changer directement les coordonnées du joueur, on passe par un vecteur
    //qui sera utilisé par la fonction mapCollision(), qui regardera si on peut ou pas déplacer
    //le joueur selon ce vecteur et changera les coordonnées du player en fonction.
     if (input.left == 1)
    {
        player.dirX -= PLAYER_SPEED;
        player.direction = LEFT;

        //On teste le sens pour l'animation : si le joueur allait dans le sens contraire
        //précédemment, il faut recharger le spritesheet pour l'animation.
        if(player.etat != WALK_LEFT && player.onGround ==1)
        {
            player.etat = WALK_LEFT;
            changeAnimation(&player, "graphics/walkleft.png");
        }
    }

    else if (input.right == 1)
    {
        player.dirX += PLAYER_SPEED;
        player.direction = RIGHT;

        if(player.etat != WALK_RIGHT && player.onGround == 1)
        {
            player.etat =  WALK_RIGHT;
            changeAnimation(&player, "graphics/walkright.png");

        }

    }
    else if(input.right == 0 && input.left ==0 && player.onGround == 1)
    {
        if(player.etat!=IDLE)
        {
            player.etat = IDLE;
            changeAnimation(&player, "graphics/idle.png");
        }

    }

    //Et voici la fonction de saut très simple :
    //Si on appuie sur la touche saut (C par défaut) et qu'on est sur le sol, alors on attribue une valeur
    //négative au vecteur Y
    //parce que sauter veut dire se rapprocher du haut de l'écran et donc de y=0.
    if (input.jump == 1 && player.onGround)
    {
        player.dirY = -JUMP_HEIGHT;
        player.onGround = 0;
        playSoundFx(JUMP);

    }

    if(player.onGround ==0)
    {
       if(player.direction == RIGHT && player.etat != JUMP_RIGHT)
       {
            player.etat = JUMP_RIGHT;
            changeAnimation(&player, "graphics/jumpright.png");


       }
       else if(player.direction == LEFT && player.etat != JUMP_LEFT)
       {
            player.etat = JUMP_LEFT;
            changeAnimation(&player, "graphics/jumpleft.png");

       }

    }



    //On rajoute notre fonction de détection des collisions qui va mettre à jour les coordonnées
    //de notre super lapin, puis on centre le scrolling comme avant.
    mapCollision(&player);
    centerScrollingOnPlayer();

  }

    //Gestion de la mort quand le héros tombe dans un trou :
    //Si timerMort est différent de 0, c'est qu'il faut réinitialiser le joueur.
    //On ignore alors ce qui précède et on joue cette boucle (un wait en fait) jusqu'à ce que
    // timerMort == 1. A ce moment-là, on le décrémente encore -> il vaut 0 et on réinitialise
    //le jeu avec notre bonne vieille fonction d'initialisation ;) !
    if (player.timerMort > 0)
    {
        player.timerMort--;

        if (player.timerMort == 0)
        {
            /* Si on est mort */
            jeu.etoiles = 0;
            initializePlayer();
            changeLevel();



        }
    }

  }


void centerScrollingOnPlayer(void)
{
    //On définit les coordonnées du début de l'affichage de la map par rapport à celles
    //du joueur.
    //Pour centrer le joueur, la map doit donc s'afficher à un demi-écran avant la position
    //du joueur.
    //Puis on "clamp" (limite) l'affichage de l'écran pour ne pas sortir de la map.

    map.startX = player.x - (SCREEN_WIDTH/4);

    if(map.startX < 0)
    {
        map.startX = 0;
    }

    else if(map.startX + SCREEN_WIDTH >= map.maxX)
    {
        map.startX = map.maxX - SCREEN_WIDTH;
    }

    map.startY = player.y - (SCREEN_HEIGHT/4);

    if(map.startY < 0)
    {
        map.startY = 0;
    }
    else if(map.startY + SCREEN_HEIGHT>= map.maxY)
    {
        map.startY = map.maxY - SCREEN_HEIGHT;
    }

}


void getItem(void)
{
    jeu.etoiles++;
    playSoundFx(COIN);
}

void playerGameover()
{
    int i;
    char text[200];
    sprintf(text, "Press ENTER");
    loadSong(1,"sounds/gameover.mp3");

    SDL_Surface *gameover = loadImage("graphics/gameover.jpg");

    drawImage(gameover,0,0);


    SDL_Flip(jeu.screen);

    while(input.enter == 0)
    {
    i = SDL_GetTicks();

    drawImage(gameover,0,0);
    drawString(text, 350, 400, 150, 150, 150, fontGameover);
    SDL_Flip(jeu.screen);
    while(SDL_GetTicks()-i != 500);
    drawImage(gameover,0,0);
    SDL_Flip(jeu.screen);
    while(SDL_GetTicks()-i != 1000);
    getInput();

    }
    input.enter = 0;


    loadGame();

    jeu.onMenu = 1;
    jeu.menuType = START;

}





