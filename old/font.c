#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "font.h"
#include "util.h"

#define N_ROWS 16
#define N_COLS 16
#define N_CHARS N_ROWS * N_COLS

//Font surface
static SDL_Surface * bitmap;

//Characters in the font
static vector2 chars[ N_CHARS ];

int initFont()
{
	//Load font bitmap
	bitmap = SDL_LoadBMP("font.bmp");
	
	//Check the font bitmap loaded ok
	if(bitmap == NULL)
	{
		return 1;
	}
	
	//Set transparency colour
	SDL_SetColorKey( bitmap, SDL_TRUE, SDL_MapRGB( bitmap->format, 0xFF, 0x00, 0xFF ) );

	int currentChar = 0;
	
	//Loop through each character in the bitmap
	for(int row=0; row<N_ROWS; row++)
	{
		for(int col=0; col<N_COLS; col++)
		{
			//Set the location of the character
			chars[currentChar].x = CHAR_WIDTH * col;
			chars[currentChar].y = CHAR_HEIGHT * row;
			
			currentChar++;
		}
	}
	
	return 0;
}

//Calculates the pixel width of a given string
int textWidth(char * text)
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
		width += CHAR_WIDTH;
		
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
int drawText(SDL_Surface * surface, int x, int y, char * text, int amount, int wrap)
{
	//Position on screen
	vector2 pos = { x, y };
	
	//Pointer to last character to be drawn
	char * stopAt = text + amount - 1;

	for(;;)
	{
		//If wrapping is enabled and if the position is past the wrapping width
		if(wrap && pos.x + CHAR_WIDTH > wrap)
		{
			//Wrap the text
			pos.x = x;
			pos.y += CHAR_HEIGHT + CHAR_SPACING;
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
			pos.y += CHAR_HEIGHT + CHAR_SPACING;
		}
		//Tab
		else if(*text == '\t')
		{
			pos.x += (CHAR_SPACING * 4);
		}
		//Ignore CR
		else if(*text == '\r');
		//Space character, so leave a gap
		else if(*text == ' ')
			pos.x += CHAR_WIDTH;
		//Normal character
		else
		{
			//Position of character in bitmap
			SDL_Rect charRect = { chars[(unsigned char) *text].x,
				chars[(unsigned char) *text].y , CHAR_WIDTH, CHAR_HEIGHT};
			//Area on screen to draw
			SDL_Rect posRect = { pos.x, pos.y, CHAR_WIDTH, CHAR_HEIGHT};
			
			SDL_BlitSurface(bitmap, &charRect, surface, &posRect);
			pos.x += CHAR_WIDTH;
		}
		
		//Increment string pointer
		text++;
	}
}

int drawTextCursor(SDL_Surface * surface, vector2 *cursor, char * text, int amount, int wrap)
{
	//X start position
	int startX = cursor->x;
	
	//Pointer to last character to be drawn
	char * stopAt = text + amount - 1;

	for(;;)
	{
		//If wrapping is enabled and if the position is past the wrapping width
		if(wrap && cursor->x + CHAR_WIDTH > wrap)
		{
			//Wrap the text
			cursor->x = startX;
			cursor->y += CHAR_HEIGHT + CHAR_SPACING;
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
			cursor->x = startX;
			cursor->y += CHAR_HEIGHT + CHAR_SPACING;
		}
		//Tab
		else if(*text == '\t')
		{
			cursor->x += (CHAR_SPACING * 4);
		}
		//Ignore CR
		else if(*text == '\r');
		//Space character, so leave a gap
		else if(*text == ' ')
			cursor->x += CHAR_WIDTH;
		//Normal character
		else
		{
			//Position of character in bitmap
			SDL_Rect charRect = { chars[(unsigned char) *text].x,
				chars[(unsigned char) *text].y , CHAR_WIDTH, CHAR_HEIGHT};
			//Area on screen to draw
			SDL_Rect posRect = { cursor->x, cursor->y, CHAR_WIDTH, CHAR_HEIGHT};
			
			SDL_BlitSurface(bitmap, &charRect, surface, &posRect);
			cursor->x += CHAR_WIDTH;
		}
		
		//Increment string pointer
		text++;
	}
}

int drawChar(SDL_Surface * surface, int x, int y, char c)
{
	//Position of character in bitmap
	SDL_Rect charRect = { chars[(unsigned char) c].x,
		chars[(unsigned char) c].y , CHAR_WIDTH, CHAR_HEIGHT};
	//Area on screen to draw
	SDL_Rect posRect = { x, y, CHAR_WIDTH, CHAR_HEIGHT};
	
	SDL_BlitSurface(bitmap, &charRect, surface, &posRect);
}

//void drawText(SDL_Surface * surface, int x, int y, char * text, int wrap)
//{
	//vector2 pos = { x, y };

	//if(bitmap == NULL)
		//return;
		
	//for(;;)
	//{
		////If wrapping is enabled and if the position is past the wrapping width
		//if(wrap && pos.x + CHAR_WIDTH > wrap)
		//{
			////Wrap the text
			//pos.x = x;
			//pos.y += CHAR_HEIGHT + CHAR_SPACING;
		//}
	
		////End of string
		//if(*text == '\0')
			//break;
		////New line
		//else if(*text == '\n')
		//{
			//pos.x = x;
			//pos.y += CHAR_HEIGHT + CHAR_SPACING;
		//}
		////Space
		//else if(*text == ' ')
		//{
			//pos.x += CHAR_WIDTH;
		//}
		//else
		//{
			//SDL_Rect charRect = { chars[(unsigned char) *text].x,
				//chars[(unsigned char) *text].y , CHAR_WIDTH, CHAR_HEIGHT};
			//SDL_Rect posRect = { pos.x, pos.y, CHAR_WIDTH, CHAR_HEIGHT};
			//SDL_BlitSurface(bitmap, &charRect, surface, &posRect);
			//pos.x += CHAR_WIDTH;
		//}
		
		//text++;
	//}
//}
