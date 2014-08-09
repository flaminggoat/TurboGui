#ifndef __scroll
#define __scroll

#include "util.h"

#define SCROLLBAR_BUTTON_UP -1
#define SCROLLBAR_BUTTON_DOWN 1

#define SCROLLBAR_WIDTH (CHAR_WIDTH + 9)

typedef struct
{

	int x, y, h;
	SDL_Surface * surface;
	int buttonPressed, lastButtonPressed;
	int color;
	
} ScrollBar;

ScrollBar * createScrollBar(int x, int y, int h, int color);
void drawScrollBar(SDL_Surface * surface, ScrollBar * scrollBar);
void updateScrollBar(UiState * uiState, ScrollBar * scrollBar);

#endif
