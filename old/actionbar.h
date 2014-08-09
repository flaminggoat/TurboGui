#ifndef __actionbar
#define __actionbar

#include <SDL.h>
#include "util.h"

typedef struct
{
	SDL_Surface * surface;
}ActionBar;

ActionBar * createActionBar();
void drawActionBar(SDL_Surface * s, ActionBar * a);

#endif
