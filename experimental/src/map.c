#include "map.h"
#include "player.h"
#include "draw.h"
#include "object.h"



Map* createMap(){

    Map* map;

    if((map = (Map*)malloc(sizeof(Map))) == NULL){
        fprintf(stderr, "can't allocate memory for a Map\n");
    }
    else{

    map->background = NULL;
    map->xmlLevel = NULL;
    map->tileSet = NULL;
    map->backgroundMenu = NULL;
    map->startX = 0;
    map->startY = 0;
    map->maxX = 0;
    map->maxY = 0;
    map->sizeX = 0;
    map->sizeY = 0;
    map->objects = NULL;
    map->tile = NULL;
    }

    return map;

}

void loadMap (char* name, Map* map, Game* game) {


    map->xmlLevel = loadXMLFile(name);


    //printXMLNode(xmlLevel->root, 2);

    //on recupère les premières infos dans le xml

    int sizeX = atoi(map->xmlLevel->root->attr->next->next->value); //a toi de jouer !
    int sizeY = atoi(map->xmlLevel->root->attr->next->next->next->value); //échec et mat !

    int i,j;


    //printXMLNode(xmlLevel->root, 2);

    //on stocke les premières infos

    map->maxX = (sizeX)*TILE_SIZE;
    map->maxY = (sizeY)*TILE_SIZE;
    map->sizeX = sizeX;
    map->sizeY = sizeY;
    map->startX = map->startY = 0;

    printf("%d",sizeY);



    //on rempli le tableau de tile, puis le tableau des items.
    map->tile = (int**) malloc((map->sizeY)*sizeof(int*)); //colonne puis ligne

    for(i=0 ; i<map->sizeX; i++) {
      map->tile[i] = (int*) malloc(map->sizeX*sizeof(int));
    }

    XML_Node* tileLayer = map->xmlLevel->root->first->next->next;

    for(i=0 ; i<map->sizeY ; i++) {
      for(j=0 ; j<map->sizeX ; j++) {

         map->tile[i][j] = atoi(tileLayer->first->current->attr->value);


         tileLayer->first->current = tileLayer->first->current->next;


      }


    }




    XML_Node* objectLayer = map->xmlLevel->root->last;

    //on compte le nombre d'objets

    game->objectNumber = objectLayer->cc;

    printf("\n\n%d\n\n",game->objectNumber);

    //on rempli le tableau d'objets
    map->objects = (GameObject*) malloc(game->objectNumber*sizeof(GameObject));


    for(i=0 ; i<game->objectNumber; i++){


      map->objects[i].type = atoi(objectLayer->current->attr->value);
      map->objects[i].spe = atoi(objectLayer->current->attr->next->value);
      map->objects[i].gid = atoi(objectLayer->current->attr->next->next->value);
      map->objects[i].x = atoi(objectLayer->current->attr->next->next->next->value);
      map->objects[i].y = atoi(objectLayer->current->attr->next->next->next->next->value);
      map->objects[i].initialized = 0;

      objectLayer->current = objectLayer->current->next;

    }

    checkAllocatedMemory(LOG_TYPE );

}


void mapCollision(GameObject *entity, Map *map, Game* game)
{

    int i, x1, x2, y1, y2;

    /* D'abord, on place le joueur en l'air jusqu'à temps d'être sûr qu'il touche le sol */

    entity->onGround = 0;


    if(entity->h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->h;

    //On lance alors une boucle for infinie car on l'interrompra selon les résultats de nos calculs

    for (;;)
    {
        //On va calculer ici les coins de notre sprite à gauche et à droite pour voir quelle tile ils
        //touchent.

        x1 = (entity->x + entity->dirX) / TILE_SIZE;
        x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

        //Même chose avec y, sauf qu'on va monter au fur et à mesure pour tester toute la hauteur
        //de notre sprite, grâce à notre fameuse variable i.

        y1 = (entity->y) / TILE_SIZE;
        y2 = (entity->y + i - 1) / TILE_SIZE;

        //De là, on va tester les mouvements initiés dans updatePlayer grâce aux vecteurs
        //dirX et dirY, tout en testant avant qu'on se situe bien dans les limites de l'écran.

        if (x1 >= 0 && x2 < map->maxX && y1 >= 0 && y2 < map->maxY)
        {
            //Si on a un mouvement à droite

            if (entity->dirX > 0)
            {

                //On vérifie si les tiles recouvertes sont solides

                if (map->tile[y1][x2] > BLANK_TILE || map->tile[y2][x2] > BLANK_TILE)
                {
                    // Si c'est le cas, on place le joueur aussi près que possible
                    // de ces tiles, en mettant à jour ses coordonnées. Enfin, on réinitialise
                    //son vecteur déplacement (dirX).

                    entity->x = x2 * TILE_SIZE;

                    entity->x -= entity->w + 1;

                    entity->dirX = 0;

                }

            }

            //Même chose à gauche

            else if (entity->dirX < 0)
            {



                if ( map->tile[y1][x1] > BLANK_TILE ||  map->tile[y2][x1] > BLANK_TILE)
                {

                    entity->x = (x1 + 1) * TILE_SIZE;

                    entity->dirX = 0;
                }


            }

        }

        //On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite.
        if (i == entity->h)
        {
            break;
        }

        //Sinon, on teste les tiles supérieures en se limitant à la heuteur du sprite.
        i += TILE_SIZE;

        if (i > entity->h)
        {
            i = entity->h;
        }
    }

    //On recommence la même chose avec le mouvement vertical (axe des Y)
    if(entity->w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->w;


    for (;;)
    {
        x1 = (entity->x) / TILE_SIZE;
        x2 = (entity->x + i) / TILE_SIZE;

        y1 = (entity->y + entity->dirY) / TILE_SIZE;
        y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

        if (x1 >= 0 && x2 < map->maxX && y1 >= 0 && y2 < map->maxY)
        {
            if (entity->dirY > 0)
            {
                /* Déplacement en bas */



                if ( map->tile[y2][x1] > BLANK_TILE || map->tile[y2][x2] > BLANK_TILE)
                {
                    //Si la tile est solide, on y colle le joueur et
                    //on le déclare sur le sol (onGround).
                    entity->y = y2 * TILE_SIZE;
                    entity->y -= entity->h;

                    entity->dirY = 0;

                    entity->onGround = 1;
                }

            }

            else if (entity->dirY < 0)
            {
                /* Déplacement vers le haut */




                if ( map->tile[y1][x1] > BLANK_TILE ||  map->tile[y1][x2] > BLANK_TILE)
                {

                    entity->y = (y1 + 1) * TILE_SIZE;

                    entity->dirY = 0;

                }

            }
        }

        //On teste la largeur du sprite (même technique que pour la hauteur précédemment)
        if (i == entity->w)
        {
            break;
        }

        i += TILE_SIZE;

        if (i > entity->w)
        {
            i = entity->w;
        }
    }

    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
    entity->x += entity->dirX;
    entity->y += entity->dirY;

    //Et on contraint son déplacement aux limites de l'écran, comme avant.
    if (entity->x < 0)
    {
        entity->x = 0;
    }

    else if (entity->x + entity->w >= map->maxX)
    {
        entity->x = map->maxX - entity->w - 1;
    }

    //Maintenant, s'il sort de l'écran par le bas (chute dans un trou sans fond), on lance le timer
    //qui gère sa mort et sa réinitialisation (plus tard on gèrera aussi les vies).
    if (entity->y  >  map->maxY - 2*TILE_SIZE)
    {
        game->life--;
        entity->timerMort = 1;
        if(game->life < 1) playerGameover(game);
    }
}



void drawMap(Map* map, Game* game)
{

    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

    /*Gestion du scrolling*/

    /* On initialise mapX à la première colonne que l'on doit blitter*/
    mapX = map->startX / TILE_SIZE;
    /*Coordonnées de départ pour l'affichage de la map*/
    x1 = (map->startX % TILE_SIZE) * -1 ;
    /*coordonnées de fin de blittage*/
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    /*de même pour mapY*/
    mapY = map->startY / TILE_SIZE;
    y1 = (map->startY % TILE_SIZE) * -1 ;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);



    /* Dessine la carte en commençant par startX et startY */

    /* On dessine ligne par ligne en commençant par y1 (0) jusqu'à y2 (480)
    A chaque fois, on rajoute TILE_SIZE (donc 70), car on descend d'une ligne
    de tile (qui fait 70 pixels de hauteur) */

    for (y = y1; y < y2; y += TILE_SIZE)
    {
        /* A chaque début de ligne, on réinitialise mapX qui contient la colonne
        (0 au début puisqu'on ne scrolle pas) */

        mapX = map->startX / TILE_SIZE;

        /* A chaque colonne de tile, on dessine la bonne tile en allant
        de x = 0 à x = 1050*/

        for (x = x1; x < x2; x += TILE_SIZE)
        {

            /* Suivant le numéro de notre tile, on découpe le tileset */

            a = map->tile[mapY][mapX]-1;

            /* Calcul pour obtenir son y (pour un tileset de 10 tiles
            par ligne, d'où le 10 */

            ysource = a / 10 * TILE_SIZE;

            /* Et son x */

            xsource = a % 10 * TILE_SIZE;

            /* Fonction qui blitte la bonne tile au bon endroit */

            drawTile(map->tileSet, x, y, xsource, ysource, game);

            mapX++;
        }

        mapY++;
    }

}

void monsterCollisionToMap(GameObject* entity, Map* map)
{

    int i, x1, x2, y1, y2;

    entity->onGround = 0;

    if(entity->h > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->h;

    for (;;)
    {
        x1 = (entity->x + entity->dirX) / TILE_SIZE;
        x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

        y1 = (entity->y) / TILE_SIZE;
        y2 = (entity->y + i - 1) / TILE_SIZE;

        if (x1 >= 0 && x2 < map->maxX && y1 >= 0 && y2 < map->maxY)
        {
            //Si on a un mouvement à droite
            if (entity->dirX > 0)
            {
                //On vérifie si les tiles recouvertes sont solides
                if (map->tile[y1][x2] > BLANK_TILE || map->tile[y2][x2] > BLANK_TILE)
                {
                    entity->x = x2 * TILE_SIZE;
                    entity->x -= entity->w + 1;
                    entity->dirX = 0;

                }

            }

            //Même chose à gauche
            else if (entity->dirX < 0)
            {

                if (map->tile[y1][x1] > BLANK_TILE || map->tile[y2][x1] > BLANK_TILE)
                {
                    entity->x = (x1 + 1) * TILE_SIZE;
                    entity->dirX = 0;
                }

            }

        }

        //On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite.
        if (i == entity->h)
        {
            break;
        }

        //Sinon, on teste les tiles supérieures en se limitant à la heuteur du sprite.
        i += TILE_SIZE;

        if (i > entity->h)
        {
            i = entity->h;
        }
    }

    //On recommence la même chose avec le mouvement vertical (axe des Y)
    if(entity->w > TILE_SIZE)
        i = TILE_SIZE;
    else
        i = entity->w;


    for (;;)
    {
        x1 = (entity->x) / TILE_SIZE;
        x2 = (entity->x + i) / TILE_SIZE;

        y1 = (entity->y + entity->dirY) / TILE_SIZE;
        y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

        if (x1 >= 0 && x2 < map->maxX && y1 >= 0 && y2 < map->maxY)
        {
            if (entity->dirY > 0)
            {

                /* Déplacement en bas */

                if (map->tile[y2][x1] > BLANK_TILE || map->tile[y2][x2] > BLANK_TILE)
                {
                    entity->y = y2 * TILE_SIZE;
                    entity->y -= entity->h;
                    entity->dirY = 0;
                    entity->onGround = 1;
                }

            }

            else if (entity->dirY < 0)
            {

                /* Déplacement vers le haut */

                if (map->tile[y1][x1] > BLANK_TILE || map->tile[y1][x2] > BLANK_TILE)
                {
                    entity->y = (y1 + 1) * TILE_SIZE;
                    entity->dirY = 0;
                }

            }
        }

        //On teste la largeur du sprite (même technique que pour la hauteur précédemment)
        if (i == entity->w)
        {
            break;
        }

        i += TILE_SIZE;

        if (i > entity->w)
        {
            i = entity->w;
        }
    }

    /* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
    entity->x += entity->dirX;
    entity->y += entity->dirY;

    //Et on contraint son déplacement aux limites de l'écran, comme avant.
    if (entity->x < 0)
    {
        entity->x = 0;
    }

    else if (entity->x + entity->w >= map->maxX)
    {
        entity->x = map->maxX - entity->w - 1;
    }


}

void destroyMap(Map* map){


    int i;


    if(map != NULL){

        destroyXMLFile(map->xmlLevel);
        SDL_FreeSurface(map->background);
        SDL_FreeSurface(map->backgroundMenu);
        SDL_FreeSurface(map->tileSet);
        for(i=0;i<map->sizeX;i++) free(map->tile[i]);
        free(map->objects);
        free(map);

    }

}



