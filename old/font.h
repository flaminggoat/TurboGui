#ifndef __font
#define __font

#include <SDL.h>
#include "util.h"

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8
#define CHAR_SPACING 2

int initFont();
int textWidth(char * text);
int drawText(SDL_Surface * surface, int x, int y, char * text, int amount, int wrap);
int drawTextCursor(SDL_Surface * surface, vector2 *cursor, char * text, int amount, int wrap);
int drawChar(SDL_Surface * surface, int x, int y, char c);int drawChar(SDL_Surface * surface, int x, int y, char c);
//int drawChars(SDL_Surface * surface, int x, int y, char * text, int amount);

#endif
