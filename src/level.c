/**
 * \file level.c
 * \brief Functions to draw the level on the screen.
 * \author fx.balu & a.dufac & gw.henry & m.parisot & v.werner
 * \date 14.03.2014
 */

#include "level.h"


void initLevel (Level* level) {

   level->rectSrc = (SDL_Rect*) malloc(sizeof(SDL_Rect));
   level->rectDst = (SDL_Rect*) malloc(sizeof(SDL_Rect));

   level->rectSrc->x = 0;
   level->rectSrc->y = 0;
   level->rectSrc->w = 70;
   level->rectSrc->h = 70;

   level->camera = (Camera*) malloc(sizeof(Camera));
   level->camera->x = 30;
   level->camera->y = 650;

   //a rajouter le chargement du tileset dans load level
   level->tileset = loadImage("res/image/tileset/tilesetLevel.png");

   loadLevel(level);
   //rajouter int pour savoir quel level charger

   /*charger le niveau avec le parseur xml*/
}

void updateLevel (Level* level, Input* input) {

}

void displayLevel (Level* level, SDL_Surface* screen) {

   displayBackground(level, screen);

   int firstTileX = level->camera->x / 70;
   int firstTileY = level->camera->y / 70;

   int lastTileX = level->camera->x / 70 + WINDOW_WIDTH_DEFAULT / 70 + 1;
   int lastTileY = level->camera->y / 70 + WINDOW_HEIGHT_DEFAULT / 70 + 1;

   int i,j;

   for (i=firstTileY ; i<lastTileY ; i++) {
      for(j=firstTileX ; j<lastTileX ; j++) {


         level->rectDst->y = i*70 - level->camera->y;
         level->rectDst->x = j*70 - level->camera->x;

         selectTile(level->rectSrc, level->tab[i][j]);

         SDL_BlitSurface(level->tileset, level->rectSrc, screen, level->rectDst);
         //  printf("%d ", level->tab[i][j]);
      }
      //  printf("\n");
   }

}

// nom de var à revoir
void selectTile (SDL_Rect* src, int gid) {

   if(gid == 0) {
      src->x = 0;
      src->y = 0;
   } else if (gid == 2) {
      src->x = 70;
      src->y = 0;
   } else if (gid == 4) {
      src->x = 210;
      src->y = 0;
   } else if (gid == 54) {
      src->x = 210;
      src->y = 350;
   } else {
      src->x = 0;
      src->y = 0;
   }
}

void displayBackground (Level* level, SDL_Surface* screen) {
   SDL_BlitSurface(level->background, NULL, screen, NULL);/*il faudra gérer la caméra plus tard, double scrolling ?*/
}

//test xml parseur :
void loadLevel (Level* level) {
   XML_File* xmlLevel = createXMLFile();
   setXMLFilePath("res/data/level/level1.tmx", xmlLevel); // resetXMLFile pour recharger un autre niveau ! ty fx
   openXMLFile(xmlLevel);
   checkFirstLineXMLFile(xmlLevel);

   xmlLevel->root = parseXMLFile(xmlLevel->file);

   printXMLNode(xmlLevel->root, 2);

   //on recupère les premières infos dans le xml
   char* pathBackground = xmlLevel->root->first->next->first->attr->value;
   int sizeX = atoi(xmlLevel->root->attr->next->next->value); //a toi de jouer !
   int sizeY = atoi(xmlLevel->root->attr->next->next->next->value); //échec et mat !

   int i,j;

   //printXMLNode(xmlLevel->root, 2);

   //on stocke les premières infos
   level->background = loadImage(pathBackground);
   level->sizeX = sizeX;
   level->sizeY = sizeY;

   //on rempli le tableau de tile, puis le tableau des items.
   level->tab = (char**) malloc(level->sizeY*sizeof(char*)); //colonne puis ligne

   for(i=0 ; i<level->sizeY ; i++) {
      level->tab[i] = (char*) malloc(level->sizeX*sizeof(char));
   }

   XML_Node* tileLayer = xmlLevel->root->first->next->next;

   for(i=0 ; i<level->sizeY ; i++) {
      for(j=0 ; j<level->sizeX ; j++) {

         level->tab[i][j] = atoi(xmlLevel->root->first->next->next->first->current->attr->value);
         tileLayer->first->current = tileLayer->first->current->next;

         //printf("%d", level->tab[i][j]);
      }
      //printf("\n");
   }

   XML_Node* objectLayer = xmlLevel->root->last;

   //on compte le nombre d'objets
   int objectNumber = 1;

   while(objectLayer->current != objectLayer->last) {
      objectNumber++;
      objectLayer->current = objectLayer->current->next;
   }
   objectLayer->current = objectLayer->first;

//on rempli le tableau d'objets
   level->objects = (GameObject**) malloc(objectNumber*sizeof(GameObject*));

   for(i=0 ; i<objectNumber ; i++){
      *(level->objects + i) = (GameObject*) malloc(sizeof(GameObject));
      level->objects[i]->name = objectLayer->current->attr->value;
      level->objects[i]->id = atoi(objectLayer->current->attr->next->value);
      level->objects[i]->x = atoi(objectLayer->current->attr->next->next->value);
      level->objects[i]->y = atoi(objectLayer->current->attr->next->next->next->value);

      //printf("%s    ", level->objects[i]->name);
      objectLayer->current = objectLayer->current->next;

   }

   //printf("\n%d objects\n", i);

   closeXMLFile(xmlLevel);
   destroyXMLFile(xmlLevel);
}
