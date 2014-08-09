//scroll.c
//
//Copyright 2014 Theo Hussey

#include <SDL.h>
#include <stdlib.h>

#include "scroll.h"
#include "font.h"
#include "util.h"

#define ARROW_OFFSET 5
#define ARROW_OFFSET_Y 4
#define ARROW_HEIGHT 16

char up[2] = {0x1E, 0x00};
char down[2] = {0x1F, 0x00};

ScrollBar * createScrollBar(int x, int y, int h, int color)
{
	ScrollBar * scrollBar = malloc(sizeof(ScrollBar));
		
	scrollBar->x = x;
	scrollBar->y = y;
	scrollBar->h = h;
	scrollBar->buttonPressed = 0;
	scrollBar->lastButtonPressed = 0;
	scrollBar->color = color;
	
	scrollBar->surface = SDL_CreateRGBSurface(0, SCROLLBAR_WIDTH, h, 32, 0, 0, 0, 0);
	
	//Draw the scrollbar up button
	drawRect( scrollBar->surface, 0, 0, SCROLLBAR_WIDTH, ARROW_HEIGHT, color );
	drawText( scrollBar->surface, ARROW_OFFSET, ARROW_OFFSET_Y, up, 0, 0 );
	
	//Draw the scrollbar down button
	drawRect( scrollBar->surface, 0, h - ARROW_HEIGHT, SCROLLBAR_WIDTH, ARROW_HEIGHT, color );
	drawText( scrollBar->surface, ARROW_OFFSET, h - ARROW_HEIGHT + ARROW_OFFSET_Y, down, 0, 0 );
	
	//Draw the center part of the scrollbar
	drawRect( scrollBar->surface, 0, ARROW_HEIGHT, SCROLLBAR_WIDTH, h - ARROW_HEIGHT * 2, lightenColor(color, 100));

	return scrollBar;
}

void drawScrollBar(SDL_Surface * surface, ScrollBar * scrollBar)
{
	SDL_Rect posRect;

	if(scrollBar->buttonPressed == SCROLLBAR_BUTTON_UP && scrollBar->lastButtonPressed != SCROLLBAR_BUTTON_UP)
	{
		//Draw the pressed version scrollbar up button
		drawRect( scrollBar->surface, 0, 0, SCROLLBAR_WIDTH, ARROW_HEIGHT, lightenColor(scrollBar->color, -50) );
		drawText( scrollBar->surface, ARROW_OFFSET, ARROW_OFFSET_Y, up, 0, 0 );
	}
	else if(scrollBar->buttonPressed == SCROLLBAR_BUTTON_DOWN && scrollBar->lastButtonPressed != SCROLLBAR_BUTTON_DOWN)
	{
		//Draw the pressed scrollbar down button
		drawRect( scrollBar->surface, 0, scrollBar->h - ARROW_HEIGHT, SCROLLBAR_WIDTH, ARROW_HEIGHT, lightenColor(scrollBar->color, -50) );
		drawText( scrollBar->surface, ARROW_OFFSET, scrollBar->h - ARROW_HEIGHT + ARROW_OFFSET_Y, down, 0, 0 );
	}
	else if(scrollBar->buttonPressed == 0 && scrollBar->lastButtonPressed == SCROLLBAR_BUTTON_UP)
	{
		//Draw the not pressed scrollbar up button
		drawRect( scrollBar->surface, 0, 0, SCROLLBAR_WIDTH, ARROW_HEIGHT, scrollBar->color );
		drawText( scrollBar->surface, ARROW_OFFSET, ARROW_OFFSET_Y, up, 0, 0 );
	}
	else if(scrollBar->buttonPressed == 0 && scrollBar->lastButtonPressed == SCROLLBAR_BUTTON_DOWN)
	{
		//Draw the not pressed scrollbar down button
		drawRect( scrollBar->surface, 0, scrollBar->h - ARROW_HEIGHT, SCROLLBAR_WIDTH, ARROW_HEIGHT, scrollBar->color );
		drawText( scrollBar->surface, ARROW_OFFSET, scrollBar->h - ARROW_HEIGHT + ARROW_OFFSET_Y, down, 0, 0 );
	}
	
	posRect.x = scrollBar->x;
	posRect.y = scrollBar->y;
	
	SDL_BlitSurface(scrollBar->surface, NULL, surface, &posRect);
}

void updateScrollBar(UiState * uiState, ScrollBar * scrollBar)
{
	scrollBar->lastButtonPressed = scrollBar->buttonPressed;
	
	if(uiState->mouseDown)
	{		
		//up button
		if(regionHit(uiState, scrollBar->x, scrollBar->y, SCROLLBAR_WIDTH, ARROW_HEIGHT))
		{
			scrollBar->buttonPressed = SCROLLBAR_BUTTON_UP;
		}
		//down button
		else if(regionHit(uiState, scrollBar->x, scrollBar->y + scrollBar->h - ARROW_HEIGHT, SCROLLBAR_WIDTH, ARROW_HEIGHT))
		{
			scrollBar->buttonPressed = SCROLLBAR_BUTTON_DOWN;
		}
	}
	else
	{
		scrollBar->buttonPressed = 0;
	}
}
