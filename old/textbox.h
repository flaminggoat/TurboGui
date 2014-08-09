#ifndef __textbox
#define __textbox

#include <SDL.h>

#include "scroll.h"

typedef struct
{

	int x, y, w, h;
	SDL_Surface * surface;
	char * text;
	int color, line, lastLine;
	ScrollBar * scrollBar;
	
} TextBox;

TextBox * createTextBox(char * text, int x, int y, int w, int h);
void updateTextBox(UiState * uiState, TextBox * textBox);
void drawTextBox(SDL_Surface * surface, TextBox * textBox);

#endif
