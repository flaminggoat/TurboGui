#include <SDL.h>
#include <stdlib.h>

#include "textbox.h"
#include "scroll.h"
#include "font.h"
#include "util.h"

void drawTextBoxText(TextBox * t)
{
	int cols = t->w/CHAR_WIDTH - 2;
	int rows = t->h/(CHAR_HEIGHT + CHAR_SPACING);
	int tempY = 0;
	char * tempText = t->text + t->line*cols;
	for(int i = 0;i<=rows;i++)
	{
		//Return 1 if end of string is reached
		if(drawText(t->surface, 0, tempY, tempText, cols, 0))
		{
			t->lastLine = 1;
			return;
		}
		tempY += CHAR_HEIGHT;
		tempText += cols;
	}
	t->lastLine = 0;
}

TextBox * createTextBox(char * text, int x, int y, int w, int h)
{
	TextBox * textBox = malloc(sizeof(TextBox));
	
	textBox->x = x;
	textBox->y = y;
	textBox->w = w;
	textBox->h = h;
	
	textBox->text = text;
	textBox->line = 0;
	
	textBox->surface = SDL_CreateRGBSurface(0, w - SCROLLBAR_WIDTH, h, 32, 0, 0, 0, 0);
	
	drawRect(textBox->surface, 0, 0, textBox->w - SCROLLBAR_WIDTH, textBox->h, 0x666666);
	
	textBox->scrollBar = createScrollBar((textBox->x + textBox->w) - SCROLLBAR_WIDTH, textBox->y, textBox->h, 0xFF0000);
	
	drawTextBoxText(textBox);

	return textBox;
}

void updateTextBox(UiState * uiState, TextBox * t)
{
	updateScrollBar(uiState, t->scrollBar);
}

void drawTextBox(SDL_Surface * surface, TextBox * t)
{
	drawScrollBar(surface, t->scrollBar);
	
	int button = t->scrollBar->buttonPressed;
	int lastButton = t->scrollBar->lastButtonPressed;
	
	if(button == SCROLLBAR_BUTTON_DOWN && lastButton == 0){
		if(!t->lastLine)
		{
			t->line++;
			drawRect(t->surface, 0, 0, t->w - SCROLLBAR_WIDTH, t->h, 0x666666);
			drawTextBoxText(t);
		}
	}
	else if(button == SCROLLBAR_BUTTON_UP && lastButton == 0){
		if(t->line > 0)
		{
			t->line--;
			drawRect(t->surface, 0, 0, t->w - SCROLLBAR_WIDTH, t->h, 0x666666);
			drawTextBoxText(t);
		}
	}
	
	SDL_Rect posRect;
	
	posRect.x = t->x;
	posRect.y = t->y;
	
	SDL_BlitSurface(t->surface, NULL, surface, &posRect);
	
}
