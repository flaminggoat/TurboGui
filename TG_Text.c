#include <stdio.h>
#include <stdlib.h>

#include "TG.h"
#include "TG_Text.h"

#define N_ROWS 16
#define N_COLS 16
#define N_CHARS N_ROWS * N_COLS

//Font surface
static TG_Surface * bitmap;

TG_Font * TG_CreateFont(uint8_t * font, int16_t charWidth, int16_t charHeight)
{
	TG_Font * t = (TG_Font*)malloc(sizeof(*t));
	
	//Load font bitmap
	t->surface = TG_LoadBmp(font);
	
	//Check the font bitmap loaded ok
	if(t->surface == NULL)
	{
		return NULL;
	}
	
	t->charWidth = charWidth;
	t->charHeight = charHeight;
	t->charXSpacing = 0;
	t->charYSpacing = 0;
	
	int currentChar = 0;
	
	//Loop through each character in the bitmap
	for(int row=0; row<N_ROWS; row++)
	{
		for(int col=0; col<N_COLS; col++)
		{
			//Set the location of the character
			t->chars[currentChar].x = t->charWidth * col;
			t->chars[currentChar].y = t->charHeight * row;
			
			currentChar++;
		}
	}
	
	return t;
}

//Calculates the pixel width of a given string
uint16_t TG_TextWidth(TG_Font * font, uint8_t * text)
{
	int width = 0, maxWidth = 0;

	for(;;){
	
		//Return when end of string is reached
		if(*text == '\0')
			return (maxWidth > width) ? maxWidth : width;
		//New line
		else if(*text == '\n')
		{
			if(width > maxWidth)
				maxWidth = width;
			width = 0;
		}
		width += font->charWidth;
		
		//Increment character pointer
		text++;
	}
}

/*
 * Draws the given amount of characters to a surface
 * 
 * Returns 1 if end of string occurs before the given amount of 
 * characters have been drawn, otherwise returns 0.
 */
uint8_t TG_DrawText(TG_Surface * surface, TG_Font * font, int16_t x, int16_t y, uint8_t * text, int16_t amount, int16_t wrap)
{
	//Position on screen
	TG_Point pos = { x, y };
	
	//Pointer to last character to be drawn
	uint8_t * stopAt = text + amount - 1;

	for(;;)
	{
		//If wrapping is enabled and if the position is past the wrapping width
		if(wrap && pos.x + font->charWidth > wrap)
		{
			//Wrap the text
			pos.x = x;
			pos.y += font->charHeight + font->charYSpacing;
		}
		
		//End of string
		if(*text == '\0')
			return 1;
		//If limited number of characters and limit reached
		else if(amount && text > stopAt)
			return 0;
		//New line
		else if(*text == '\n')
		{
			pos.x = x;
			pos.y += font->charHeight + font->charYSpacing;
		}
		//Tab
		else if(*text == '\t')
		{
			pos.x += (font->charXSpacing * 4);
		}
		//Ignore CR
		else if(*text == '\r');
		//Space character, so leave a gap
		else if(*text == ' ')
			pos.x += font->charWidth;
		//Normal character
		else
		{
			TG_DrawChar(surface, font, pos.x, pos.y, *text, 0xFFFFFFFF);
			pos.x += font->charWidth;
		}
		
		//Increment string pointer
		text++;
	}
}

/*int drawTextCursor(SDL_Surface * surface, vector2 *cursor, char * text, int amount, int wrap)
{
	X start position
	int startX = cursor->x;
	
	Pointer to last character to be drawn
	char * stopAt = text + amount - 1;

	for(;;)
	{
		If wrapping is enabled and if the position is past the wrapping width
		if(wrap && cursor->x + CHAR_WIDTH > wrap)
		{
			Wrap the text
			cursor->x = startX;
			cursor->y += CHAR_HEIGHT + CHAR_SPACING;
		}
		
		End of string
		if(*text == '\0')
			return 1;
		If limited number of characters and limit reached
		else if(amount && text > stopAt)
			return 0;
		New line
		else if(*text == '\n')
		{
			cursor->x = startX;
			cursor->y += CHAR_HEIGHT + CHAR_SPACING;
		}
		Tab
		else if(*text == '\t')
		{
			cursor->x += (CHAR_SPACING * 4);
		}
		Ignore CR
		else if(*text == '\r');
		Space character, so leave a gap
		else if(*text == ' ')
			cursor->x += CHAR_WIDTH;
		Normal character
		else
		{
			Position of character in bitmap
			SDL_Rect charRect = { chars[(unsigned char) *text].x,
				chars[(unsigned char) *text].y , CHAR_WIDTH, CHAR_HEIGHT};
			Area on screen to draw
			SDL_Rect posRect = { cursor->x, cursor->y, CHAR_WIDTH, CHAR_HEIGHT};
			
			SDL_BlitSurface(bitmap, &charRect, surface, &posRect);
			cursor->x += CHAR_WIDTH;
		}
		
		Increment string pointer
		text++;
	}
}*/

void TG_DrawChar(TG_Surface * surface, TG_Font * font, int16_t x, int16_t y, uint8_t c, uint32_t color)
{
	//Position of character in bitmap
	uint16_t cX = font->chars[c].x;
	uint16_t cY = font->chars[c].y;
	
	//Set the starting position of the destination pointer
	uint32_t * destPixel = surface->pixels + (y * surface->width);
	//set the starting position of the src pointer	
	uint32_t * srcPixel = font->surface->pixels + (cY * font->surface->width);
	
	uint16_t total = font->charWidth * font->charHeight;
	uint16_t srcX = cX;
	uint16_t destX = x;
	
	for(uint16_t i = 0; i < total; i++)
	{
			//copy the source pixel to the destination pixel
			if(*(srcPixel + srcX) != 0xFFFF00FF)
				//*(destPixel + destX) = *(srcPixel + srcX);
				*(destPixel + destX) = color;
				
			//increment the pixel x positions
			srcX++;
			destX++;
			
			//move to the next row of pixels
			if(srcX == cX + font->charWidth)
			{
				srcPixel += font->surface->width;
				destPixel += surface->width;
				srcX = cX;
				destX = x;
			}

	}
}

