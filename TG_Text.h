#ifndef __font
#define __font

#include "TG.h"

typedef struct
{
	TG_Surface * surface;
	int16_t charWidth, charHeight;
	int16_t charYSpacing, charXSpacing;
	TG_Point chars[256];
	
}TG_Font;

TG_Font * TG_CreateFont(uint8_t * font, int16_t rows, int16_t cols);

uint16_t TG_TextWidth(TG_Font * font, uint8_t * text);

uint8_t TG_DrawText(TG_Surface * surface, TG_Font * font, int16_t x,
	int16_t y, uint8_t * text, int16_t amount, int16_t wrap, uint32_t color);

//int drawTextCursor(SDL_Surface * surface, vector2 *cursor, char * text, int amount, int wrap);

void TG_DrawChar(TG_Surface * surface, TG_Font * font, int16_t x, int16_t y, uint8_t c, uint32_t color);

#endif
