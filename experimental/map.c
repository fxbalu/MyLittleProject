#include "map.h"
#include "xml/xml.h" /* XML_File, loadXMLFile(), getXMLInt()... */

/**
 * \brief Load a map from a TMX file.
 * \warning WIP, doesn't work.
 */
void loadMapXML(char* path){
   XML_File* xml;

   if((xml = loadXMLFile(path)) == NULL){
      printf("Failed to open file\n");
      destroyXMLFile(xml);
   }
   else {
      checkFirstLineXMLFile(xml);
   }


   if((map.maxX = getXMLInt("map/layer?name=foreground:width", xml, 0)) >= MAX_MAP_X){
      printf("Too many tiles on X\n");
   }
   else if((map.maxY = getXMLInt("map/layer?name=foreground:height", xml, 0)) >= MAX_MAP_Y){
      printf("Too many tiles on Y\n");
   }
   else{
      getXMLIntTable(*(map.tile), "map/layer?name=foreground/data/tile:gid", xml);
   }

   map.maxX = (map.maxX + 1) * TILE_SIZE;
   map.maxY = (map.maxY + 1) * TILE_SIZE;
   map.startX = map.startY = 0;

   destroyXMLFile(xml);
}

void loadMap(char* name)
{

    int x,y;
    FILE *fp;

    fp = fopen(name, "rb");

    if(fp == NULL)
    {
        printf("Failed to open map %s\n", name);
        exit(1);
    }

    map.maxX = map.maxY =0;

    for(y=0;y<MAX_MAP_Y;y++)
    {
        for(x=0;x<MAX_MAP_X;x++)
        {
            fscanf(fp,"%d", &map.tile[y][x]);

            if(map.tile[y][x]>0)
            {
                if(x>map.maxX) map.maxX = x;
                if(y>map.maxY) map.maxY = y;
            }
        }
    }

    map.maxX = (map.maxX+1)*TILE_SIZE;
    map.maxY = (map.maxY+1)*TILE_SIZE;

    map.startX = map.startY = 0;

    fclose(fp);
}

void mapCollision(GameObject *entity)
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

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //Si on a un mouvement à droite

            if (entity->dirX > 0)
            {



                if(map.tile[y1][x2] == TILE_COIN)
                {
                    getItem();
                    map.tile[y1][x2] = 0;
                }

                else if(map.tile[y2][x2] == TILE_COIN)
                {
                    getItem();
                    map.tile[y2][x2] = 0;
                }

                if(map.tile[y1][x2] == TILE_DOOR)
                {
                    jeu.level++;
                    //Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
                    if(jeu.level > LEVEL_MAX)
                    {
                        jeu.level = LEVEL_MAX;
                        entity->x = map.maxX - entity->w - 1;
                    }
                    //Sion, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
                    else
                    {
                        changeLevel();
                        initializePlayer();
                    }
                }

                else if(map.tile[y2][x2] == TILE_DOOR)
                {
                    jeu.level++;
                    //Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
                    if(jeu.level > LEVEL_MAX)
                    {
                        jeu.level = LEVEL_MAX;
                        entity->x = map.maxX - entity->w - 1;
                    }
                    //Sion, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
                    else
                    {
                        changeLevel();
                        initializePlayer();
                    }
                }

                //On vérifie si les tiles recouvertes sont solides

                if (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
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

                if(map.tile[y1][x1] == TILE_COIN)
                {
                    getItem();
                    map.tile[y1][x1] = 0;
                }

                else if(map.tile[y2][x1] == TILE_COIN)
                {
                    getItem();
                    map.tile[y2][x1] = 0;
                }

                if(map.tile[y1][x1] == TILE_DOOR)
                {
                    jeu.level++;
                    //Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
                    if(jeu.level > LEVEL_MAX)
                    {
                        jeu.level = LEVEL_MAX;
                        entity->x = map.maxX - entity->w - 1;
                    }
                    //Sion, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
                    else
                    {
                        changeLevel();
                        initializePlayer();
                    }
                }

                else if(map.tile[y2][x1] == TILE_DOOR)
                {
                    jeu.level++;
                    //Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
                    if(jeu.level > LEVEL_MAX)
                    {
                        jeu.level = LEVEL_MAX;
                        entity->x = map.maxX - entity->w - 1;
                    }
                    //Sion, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
                    else
                    {
                        changeLevel();
                        initializePlayer();
                    }
                }

                if ( map.tile[y1][x1] > BLANK_TILE ||  map.tile[y2][x1] > BLANK_TILE)
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

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (entity->dirY > 0)
            {
                /* Déplacement en bas */

                if(map.tile[y2][x1] == TILE_COIN)
                {
                    getItem();
                    map.tile[y2][x1] = 0;
                }
                else if(map.tile[y2][x2] == TILE_COIN)
                {
                    getItem();
                    map.tile[y2][x2] = 0;
                }

                if(map.tile[y2][x1] == TILE_DOOR)
                {
                    jeu.level++;
                    //Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
                    if(jeu.level > LEVEL_MAX)
                    {
                        jeu.level = LEVEL_MAX;
                        entity->x = map.maxX - entity->w - 1;
                    }
                    //Sion, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
                    else
                    {
                        changeLevel();
                        initializePlayer();
                    }
                }

                else if(map.tile[y2][x2] == TILE_DOOR)
                {
                    jeu.level++;
                    //Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
                    if(jeu.level > LEVEL_MAX)
                    {
                        jeu.level = LEVEL_MAX;
                        entity->x = map.maxX - entity->w - 1;
                    }
                    //Sion, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
                    else
                    {
                        changeLevel();
                        initializePlayer();
                    }
                }

                if ( map.tile[y2][x1] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
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

                if(map.tile[y2][x1] == TILE_COIN)
                {
                    getItem();
                    map.tile[y2][x1] = 0;
                }

                else if(map.tile[y2][x2] == TILE_COIN)
                {
                    getItem();
                    map.tile[y2][x2] = 0;
                }

                if(map.tile[y2][x1] == TILE_DOOR)
                {
                    jeu.level++;
                    //Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
                    if(jeu.level > LEVEL_MAX)
                    {
                        jeu.level = LEVEL_MAX;
                        entity->x = map.maxX - entity->w - 1;
                    }
                    //Sion, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
                    else
                    {
                        changeLevel();
                        initializePlayer();
                    }
                }

                else if(map.tile[y2][x2] == TILE_DOOR)
                {
                    jeu.level++;
                    //Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
                    if(jeu.level > LEVEL_MAX)
                    {
                        jeu.level = LEVEL_MAX;
                        entity->x = map.maxX - entity->w - 1;
                    }
                    //Sion, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
                    else
                    {
                        changeLevel();
                        initializePlayer();
                    }
                }


                if ( map.tile[y1][x1] > BLANK_TILE ||  map.tile[y1][x2] > BLANK_TILE)
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

    else if (entity->x + entity->w >= map.maxX)
    {
        entity->x = map.maxX - entity->w - 1;
    }

    //Maintenant, s'il sort de l'écran par le bas (chute dans un trou sans fond), on lance le timer
    //qui gère sa mort et sa réinitialisation (plus tard on gèrera aussi les vies).
    if (entity->y > map.maxY)
    {
        jeu.life--;
        entity->timerMort = 60;
        if(jeu.life < 1) playerGameover();
    }
}

void changeLevel(void)
{
    char file[200];

    /* Charge la map depuis le fichier */
    sprintf(file, "map/map%d.txt", jeu.level );
    loadMapXML("level1.tmx");

    if(map.tileSet == NULL)    map.tileSet = loadImage("graphics/all_tileset.png");


}

void drawMap(void)
{

    int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

    /*Gestion du scrolling*/

    /* On initialise mapX à la première colonne que l'on doit blitter*/
    mapX = map.startX / TILE_SIZE;
    /*Coordonnées de départ pour l'affichage de la map*/
    x1 = (map.startX % TILE_SIZE) * -1 ;
    /*coordonnées de fin de blittage*/
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    /*de même pour mapY*/
    mapY = map.startY / TILE_SIZE;
    y1 = (map.startY % TILE_SIZE) * -1 ;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);



    /* Dessine la carte en commençant par startX et startY */

    /* On dessine ligne par ligne en commençant par y1 (0) jusqu'à y2 (480)
    A chaque fois, on rajoute TILE_SIZE (donc 70), car on descend d'une ligne
    de tile (qui fait 70 pixels de hauteur) */

    for (y = y1; y < y2; y += TILE_SIZE)
    {
        /* A chaque début de ligne, on réinitialise mapX qui contient la colonne
        (0 au début puisqu'on ne scrolle pas) */

        mapX = map.startX / TILE_SIZE;

        /* A chaque colonne de tile, on dessine la bonne tile en allant
        de x = 0 à x = 1050*/

        for (x = x1; x < x2; x += TILE_SIZE)
        {

            if(map.tile[mapY][mapX]!=0)
            {
                if(map.tile[mapY][mapX] == TILE_MONSTER1)
                {
                    initializeMonsters(mapX*TILE_SIZE, mapY*TILE_SIZE);

                    map.tile[mapY][mapX] = 0;
                }
            }

            /* Suivant le numéro de notre tile, on découpe le tileset */

            a = map.tile[mapY][mapX];

            /* Calcul pour obtenir son y (pour un tileset de 10 tiles
            par ligne, d'où le 10 */

            ysource = a / 10 * TILE_SIZE;

            /* Et son x */

            xsource = a % 10 * TILE_SIZE;

            /* Fonction qui blitte la bonne tile au bon endroit */

            drawTile(map.tileSet, x, y, xsource, ysource);

            mapX++;
        }

        mapY++;
    }

}

void monsterCollisionToMap(GameObject* entity)
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

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            //Si on a un mouvement à droite
            if (entity->dirX > 0)
            {
                //On vérifie si les tiles recouvertes sont solides
                if (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
                {
                    entity->x = x2 * TILE_SIZE;
                    entity->x -= entity->w + 1;
                    entity->dirX = 0;

                }

            }

            //Même chose à gauche
            else if (entity->dirX < 0)
            {

                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y2][x1] > BLANK_TILE)
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

        if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
        {
            if (entity->dirY > 0)
            {

                /* Déplacement en bas */

                if (map.tile[y2][x1] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
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

                if (map.tile[y1][x1] > BLANK_TILE || map.tile[y1][x2] > BLANK_TILE)
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

    else if (entity->x + entity->w >= map.maxX)
    {
        entity->x = map.maxX - entity->w - 1;
    }

    //Maintenant, s'il sort de l'écran par le bas (chute dans un trou sans fond), on lance le timer
    //qui gère sa mort et sa réinitialisation (plus tard on gèrera aussi les vies).
    if (entity->y > map.maxY)
    {
        if(jeu.life > 0)
        {
            jeu.life--;
            player.timerMort = 10;
            if(jeu.life<1) playerGameover();
        }
    }

}





