//Button.c
//
//Copyright 2014 Theo Hussey

#include <SDL.h>
#include <stdlib.h>

#include "button.h"
#include "font.h"
#include "util.h"

Button * createTextButton(int x, int y, int width, int height, char * text, int color)
{
	Button * button = malloc(sizeof(Button));
	
	button->x = x;
	button->y = y;
	button->w = width;
	button->h = height;
	button->pressed = 0;
	button->lastPressed = 0;
	button->color = color;
	
	button->surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	
	button->text = text;
	
	//Centre the text in the button
	button->textX = (width - textWidth(text))/2;
	button->textY = (height - CHAR_HEIGHT)/2;
	
	//Draw the button background
	drawRect(button->surface, 0,0, width,height, color);
	
	//Draw the text onto the button surface
	drawText(button->surface, button->textX, button->textY, text, 0, 0);
	
	return button;
}

int updateButton(UiState * uiState, Button * button)
{
	button->lastPressed = button->pressed;
	button->pressed = regionHit(uiState, button->x, button->y, button->w, button->h) & uiState->mouseDown;
	return ~button->lastPressed & button->pressed;
}

void drawButton(SDL_Surface * surface, Button * button)
{
	SDL_Rect posRect;
	
	if(button->pressed && !button->lastPressed){
		//Draw the button background
		drawRect(button->surface, 0,0,button->w,button->h,lightenColor(button->color, -50));
	
		//Draw the text onto the button surface
		drawText(button->surface, button->textX, button->textY, button->text, 0, 0);
	}
	else if(!button->pressed && button->lastPressed)
	{
		//Draw the button background
		drawRect(button->surface, 0,0,button->w,button->h,button->color);
	
		//Draw the text onto the button surface
		drawText(button->surface, button->textX, button->textY, button->text, 0, 0);
	}
	
	posRect.x = button->x;
	posRect.y = button->y;
	SDL_BlitSurface(button->surface, NULL, surface, &posRect);
}
