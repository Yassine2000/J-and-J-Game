#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "boundigbox.h"


SDL_Surface * initEcran(int largeur, int hauteur)
{
    SDL_Surface *ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("pomme.png"), NULL);
    ecran = SDL_SetVideoMode(largeur, hauteur, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("COLLISION", NULL);

    return ecran;
}

void afficheMessage(SDL_Color textColor, SDL_Rect position)
{
    SDL_Surface *message = NULL;
    TTF_Font *police=NULL;
    textColor={217, 10, 4};
    TTF_Init();
    police = TTF_OpenFont("theme.ttf", 124);
    message = TTF_RenderText_Blended(police, "Boom", textColor);
    SDL_BlitSurface(message, NULL, &position);
    position.x=350;
    position.y=278;
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(message);
}


void blitImageSurSurface(SDL_Surface * surfaceBlit, SDL_Rect *position)
{
    SDL_Surface* loadedImage = NULL;
    loadedImage = IMG_Load("pomme.png");
    position->h = loadedImage->h;
    position->w = loadedImage->w;
    SDL_BlitSurface(loadedImage, NULL, surfaceBlit, position);
    SDL_FreeSurface(loadedImage);
}

void attendreTemps(int millisecondes)
{
    int startTicks = SDL_GetTicks();

    while((SDL_GetTicks() - startTicks) < millisecondes)
    {
        SDL_Delay(1);
    }
}

void deplacement(SDL_Rect * pos, SDL_Event event, int vitesse_x, int vitesse_y)
{
    if(event.type == SDL_KEYDOWN)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_UP:
		 pos->y -= vitesse_y / 2; 
		break;
            case SDLK_DOWN: 
		pos->y += vitesse_y / 2;
		 break;
            case SDLK_LEFT:
		 pos->x -= vitesse_x / 2; 
		break;
            case SDLK_RIGHT: 
		pos->x += vitesse_x / 2;
		 break;
            default: break;
        }
    }
}

int testCollision(SDL_Rect obj1, SDL_Rect obj2, int * typeCollision)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = obj1.x;
    rightA = obj1.x + obj1.w;
    topA = obj1.y;
    bottomA = obj1.y + obj1.h;

    leftB = obj2.x;
    rightB = obj2.x + obj2.w;
    topB = obj2.y;
    bottomB = obj2.y + obj2.h;

    if( bottomA <= topB )
    {
        *typeCollision = BOTTOM;
	return 1;
    }

    if( topA >= bottomB )
    {
        *typeCollision = TOP;
	return 1;
    }

    if( rightA <= leftB )
    {
        *typeCollision = RIGHT;
	return 1;
    }

    if( leftA >= rightB )
    {
        *typeCollision = LEFT;
	return 1;
    }
    return 0;
}

