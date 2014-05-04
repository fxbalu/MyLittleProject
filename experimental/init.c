
#include "init.h"

/*Fonction qui initialise le jeu*/

void init(char *title)
{

if(SDL_Init(SDL_INIT_VIDEO)<0)          /*initialise SDL video*/
{
    printf("Could not initialize SDL: %s\n", SDL_GetError());
    exit(1);
}

/* On crée la fenêtre, représentée par le pointeur jeu.screen en utilisant la largeur et la
hauteur définies dans les defines (defs.h). On utilise aussi la mémoire vidéo
(SDL_HWPALETTE) et le double buffer pour éviter que ça scintille
(SDL_DOUBLEBUF) */

jeu.screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,0,SDL_HWPALETTE|SDL_DOUBLEBUF);


if(jeu.screen == NULL)
{
    printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
    exit(1);
}

SDL_WM_SetCaption(title,NULL); /*on affiche le titre de la fenetre*/

SDL_ShowCursor(SDL_DISABLE);

if(TTF_Init()<0)
{
    printf("couldn't initialize  SDL_TTF: %s\n",SDL_GetError());
    exit(1);
}
font = loadFont("font/font1.ttf", 65);
fontMenu = loadFont("font/font1.ttf", 45);


int flags = MIX_INIT_FLAC; // Le mp3 ne marchait pas
int initted = Mix_Init(flags);

printf("%d\n",flags);
printf("%d\n",initted);

if( (initted & flags) != flags)
{
    printf("Mix_Init: Failed to init SDL_Mixer\n");
    printf("Mix_Init: %s\n", Mix_GetError());
    exit(1);
}

/* open 44.1KHz, signed 16bit, system byte order,
       stereo audio, using 1024 byte chunks */
if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1)
{
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
    exit(1);
}

/* Définit le nombre de channels à mixer */
Mix_AllocateChannels(32);

jeu.level = 2;

jeu.onMenu = 1;
jeu.choice = 0;
jeu.menuType = START;



}

void loadGame(void)
{

    /* Charge l'image du fond */
    map.background = loadImage("graphics/backgroundworld1.png");
    map.backgroundMenu = loadImage("graphics/splashScreen.png");
    jeu.tileMenu = loadImage("graphics/spriteSheetMenu.png");

    changeLevel();

    loadSong(-1,"music/Those of Us Who Fight.mp3");

    loadSound();

    jeu.etoiles = 0;
    jeu.life = 1;


    jeu.HUD_vie = loadImage("graphics/lifeHud.png");
    jeu.HUD_etoiles = loadImage("graphics/hud_coins.png");



 }

void cleanup()
{

int i;

/* Libère l'image du background */

if (map.background != NULL)
{
    SDL_FreeSurface(map.background);
}
if (map.tileSet != NULL)
{
    SDL_FreeSurface(map.tileSet);
}


if (map.backgroundMenu != NULL)
{
    SDL_FreeSurface(map.backgroundMenu);
}
if (jeu.tileMenu != NULL)
{
    SDL_FreeSurface(jeu.tileMenu);
}

if(player.sprite != NULL)
{
    SDL_FreeSurface(player.sprite);
}

for(i = 0 ; i < MONSTRES_MAX ; i++)
{
    if (monster[i].sprite != NULL)
    {
        SDL_FreeSurface(monster[i].sprite);
    }
}



if (jeu.HUD_etoiles != NULL)
{
    SDL_FreeSurface(jeu.HUD_etoiles);
}
if (jeu.HUD_vie != NULL)
{
    SDL_FreeSurface(jeu.HUD_vie);
}

if(jeu.musique !=NULL)
{
    Mix_FreeMusic(jeu.musique);
}



Mix_CloseAudio();
Mix_Quit();

freeSound();


closeFont(font);
closeFont(fontMenu);

TTF_Quit();

SDL_Quit();



}







