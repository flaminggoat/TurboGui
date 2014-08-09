#include <SDL.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <stdint.h>

#include "filebrowser.h"
#include "scroll.h"
#include "font.h"
#include "util.h"

#define BROWSER_WIDTH SCREEN_WIDTH - SCROLLBAR_WIDTH
#define BROWSER_HEIGHT SCREEN_HEIGHT - ACTION_BAR_HEIGHT
#define FILE_POINTER_CHUNK 32

int fileCompare(const void * elem1, const void * elem2)
{
	char *a = *((char**)elem1);
	char *b = *((char**)elem2);

	return strcasecmp(a, b);
}

void redraw(FileBrowser * f)
{
	drawRect(f->surface,0,0,BROWSER_WIDTH, BROWSER_HEIGHT, 0x555555);
	
	int y = 0;
	for(int i=f->currentLine; i<f->nFiles; i++)
	{
		if(y > BROWSER_HEIGHT - CHAR_HEIGHT)
			break;
		drawText(f->surface, 0, y, f->files[i], BROWSER_WIDTH, 0);
		y += CHAR_HEIGHT;
	}
}

FileBrowser * createFileBrowser(){
	FileBrowser * f = malloc(sizeof(FileBrowser));
	
	f->surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH,
		BROWSER_HEIGHT, 32, 0, 0, 0, 0);
	
	drawRect(f->surface, 0, 0, BROWSER_WIDTH, BROWSER_HEIGHT, 0x666666);
	
	f->scrollBar = createScrollBar(BROWSER_WIDTH, 0, SCREEN_HEIGHT - 20, 0x444444);
	
	//Allocate 32 pointers for storing file names
	f->files = malloc(FILE_POINTER_CHUNK * sizeof(uint8_t *));
	
	f->currentLine = f->lastLine = 0;
	
	DIR * d;
	struct dirent * dir;
	d = opendir(".");
	
	//Check directory has been opened sucessfully
	if (d == NULL)
		return NULL;
	
	//Current file
	int16_t file = 0;
	//Currently allocated space for pointers to filenames
	uint16_t filesPointers = FILE_POINTER_CHUNK;
	
	while ((dir = readdir(d)) != NULL)
	{
		//If there are more files in the directory than allowed for in
		//the intial allocation, allocate some more memory
		if(file > filesPointers)
		{
			filesPointers += FILE_POINTER_CHUNK;
			if(realloc(f->files, filesPointers * sizeof(uint8_t *)) == NULL)
			{
				//The current filename has not been allocated so decrement
				//the amount of files allocated
				file--;
				
				//Clean up
				closedir(d);
				removeFileBrowser(f);
				return NULL;
			}
		}
		
		//Get length of filename
		unsigned int fileNameLength = strlen(dir->d_name) + 1;
		
		//Copy filename into allocated space
		f->files[file] = malloc(fileNameLength * sizeof(char));
		strcpy(f->files[file], dir->d_name);
		
		file++;
	}

	closedir(d);
	
	f->nFiles = file;
	
	//Sort the directory
	qsort(f->files, file, sizeof(uint8_t *), fileCompare);
	
	redraw(f);
	
	return f;
}

void updateFileBrowser(UiState * u, FileBrowser * f)
{
	static uint8_t status;
	static uint8_t selection;
	
	updateScrollBar(u, f->scrollBar);
	
	f->lastLine = f->currentLine;
	f->currentLine += (f->scrollBar->buttonPressed != f->scrollBar->lastButtonPressed) ? f->scrollBar->buttonPressed : 0;
	
	if(u->screen != 45)
	{
		if(u->mouseDown)
			return;
		else
			u->screen = 45;
	}
		
	
	//check if mouse is clicked in selection region
	if(u->mouseY < BROWSER_HEIGHT && u->mouseX < BROWSER_WIDTH)
	{
		if(u->mouseDown)
		{
			selection = u->mouseY / CHAR_HEIGHT;
		}
		if(!u->mouseDown)
		{
			if(selection == u->mouseY / CHAR_HEIGHT)
			{
				FILE * fp = fopen(f->files[selection], "r");
				uint8_t buffer[1000];
				
				drawRect(f->surface,0,0,BROWSER_WIDTH, BROWSER_HEIGHT, 0x555555);
				
				vector2 cursor = {0, 0};
				for(;;)
				{
					if(fgets(buffer, 1000, fp) == NULL)
						break;
					drawTextCursor(f->surface, &cursor, buffer, 0, BROWSER_WIDTH);
					//cursor.y += CHAR_HEIGHT;
				}
				
				fclose(fp);
				
				
			}
			
		}		
		
		
	}
}

void drawFileBrowser(SDL_Surface * s, FileBrowser * f)
{	
	if(f->currentLine != f->lastLine)
		redraw(f);
	
	SDL_BlitSurface(f->surface, NULL, s, NULL);
	drawScrollBar(f->surface, f->scrollBar);
}

void removeFileBrowser(FileBrowser * f)
{
	SDL_FreeSurface(f->surface);
	
	for(int i = 0; i<f->nFiles; i++)
	{
		free(f->files[i]);
	}
	
	free(f->files);
	free(f);
}
