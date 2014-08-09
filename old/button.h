#ifndef __button
#define __button

#include <SDL.h>

#include "util.h"

typedef struct
{

	int x, y, w, h, textX, textY;
	SDL_Surface * surface;
	int pressed, lastPressed;
	int color;
	char * text;
	
} Button;

Button * createTextButton(int x, int y, int width, int height, char * text, int color);
void drawButton(SDL_Surface * surface, Button * button);
int updateButton(UiState * uiState, Button * button);

#endif
