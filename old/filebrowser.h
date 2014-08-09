#ifndef __filebrowser
#define __filebrowser

#include <SDL.h>
#include <stdint.h>

#include "scroll.h"

typedef struct
{
	uint8_t ** files;
	uint16_t nFiles;
	uint16_t currentLine, lastLine;
	SDL_Surface * surface;
	ScrollBar * scrollBar;
	
} FileBrowser;

FileBrowser * createFileBrowser();
void updateFileBrowser(UiState * u, FileBrowser * f);
void drawFileBrowser(SDL_Surface * s, FileBrowser * f);
void removeFileBrowser(FileBrowser * f);

#endif
