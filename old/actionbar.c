#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "font.h"
#include "util.h"
#include "actionbar.h"

#define AB_BACK_CHAR 0x11
#define AB_HOME_CHAR 0x08
#define AB_MENU_CHAR 0xF0
#define AB_CHAR_OFFSET ACTION_BAR_HEIGHT/2 - CHAR_HEIGHT/2

ActionBar * createActionBar()
{
	ActionBar * a = (ActionBar*)malloc(sizeof(a));
	
	a->surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH,
		SCREEN_HEIGHT - ACTION_BAR_HEIGHT, 32, 0, 0, 0, 0);
	
	drawRect(a->surface, 0, 0, SCREEN_WIDTH, ACTION_BAR_HEIGHT, 0x0);
	//Draw back button
	drawChar(a->surface, SCREEN_WIDTH/4, AB_CHAR_OFFSET, AB_BACK_CHAR);
	drawChar(a->surface, SCREEN_WIDTH/2, AB_CHAR_OFFSET, AB_HOME_CHAR);
	drawChar(a->surface, SCREEN_WIDTH/4 * 3, AB_CHAR_OFFSET, AB_MENU_CHAR);
	
	return a;
}

void drawActionBar(SDL_Surface * s, ActionBar * a)
{
	SDL_Rect posRect;
	
	posRect.x = 0;
	posRect.y = SCREEN_HEIGHT - ACTION_BAR_HEIGHT;
	
	SDL_BlitSurface(a->surface, NULL, s, &posRect);
}
