#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "font.h"
#include "button.h"
#include "scroll.h"
#include "textbox.h"
#include "filebrowser.h"
#include "actionbar.h"

#undef main

#define BUTTON_COLOR 0x1E90FF

//Screen Surface
SDL_Window *gScreen;
SDL_Surface *gSurface;

Button *scanButton, *fileButton, *noteButton;
TextBox * textBox;
FileBrowser * fileBrowser = NULL;
ActionBar * actionBar;

UiState uiState = {0,0,0,0,0};
static int bgColor = 0;

void update()
{
	switch(uiState.screen)
	{
		case MAIN_MENU:
		{
			if(updateButton(&uiState, scanButton))
			{
				
				bgColor = (SDL_GetTicks() * 0xc0cac01a) | 0x77;
			}
			if(updateButton(&uiState, fileButton))
			{
				fileBrowser = createFileBrowser();
				uiState.screen = FILE_BROWSER;
			}
			updateButton(&uiState, noteButton);
			updateTextBox(&uiState, textBox);
			break;
		}
		case 45:
		case FILE_BROWSER:
		{
			updateFileBrowser(&uiState, fileBrowser);
			break;
		}
	}
}

void render()
{
	//Clear Screen
	drawRect(gSurface, 0,0,320,240,bgColor);
	
	switch(uiState.screen)
	{
		case MAIN_MENU:
		{
			drawButton(gSurface, scanButton);
			drawButton(gSurface, fileButton);
			drawButton(gSurface, noteButton);
				
			drawTextBox(gSurface, textBox);
			break;
		}
		case 45:
		case FILE_BROWSER:
		{
			drawFileBrowser(gSurface, fileBrowser);
			break;
		}
	}
	
	drawActionBar(gSurface, actionBar);
	
	// update the screen
	SDL_UpdateWindowSurface( gScreen );
	
	//Release CPU
	SDL_Delay(20);
}

int main(int argc, char* args[])
{
	//Start SDL
    SDL_Init( SDL_INIT_VIDEO  );
    
    // Register SDL_Quit to be called at exit; makes sure things are
	// cleaned up when we quit.
	atexit(SDL_Quit);
	
	// Attempt to create a 640x480 window with 32bit pixels.
	gScreen = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_SHOWN );
	
	//Get window surface
    gSurface = SDL_GetWindowSurface( gScreen );
	
	initFont();
	
	scanButton = createTextButton(20, 20, 80, 80, "Scan", BUTTON_COLOR);
	fileButton = createTextButton(120, 20, 80, 80, "Files", BUTTON_COLOR);
	noteButton = createTextButton(220, 20, 80, 80, "Notepad", BUTTON_COLOR);
	
	textBox = createTextBox("Hello this is a text box with a scrollbar,there is much text in this box! One day a dog walked down the road only to encounter a cow!", 20, 120, 80, 80);
	
	actionBar = createActionBar();
	
	while(1)
	{
		update();
		
		render();
		
		// Poll for events, and handle the ones we care about.
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
			case SDL_MOUSEMOTION:
				uiState.mouseX = event.motion.x;
				uiState.mouseY = event.motion.y;
			break;
			
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == 1)
					uiState.mouseDown = 1;
				break;

			case SDL_MOUSEBUTTONUP:
				if (event.button.button == 1)
					uiState.mouseDown = 0;
				break;
				
			case SDL_KEYUP:			
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
				  // If escape is pressed, return (and thus, quit)
				  return 0;
				}
				break;
				
			case SDL_QUIT:
			return(0);
			
			}
		}
	}
    
    return 0;    
}
