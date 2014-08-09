#ifndef __util
#define __util

#define MAIN_MENU 0
#define FILE_BROWSER 1

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define ACTION_BAR_HEIGHT 20

typedef struct vector2Struct
{
	int x;
	int y;
} vector2;

typedef struct
{
	int mouseX;
	int mouseY;
	int mouseDown;
	int mouseused;
	int screen;
}UiState;

void drawRect(SDL_Surface * surface, int x, int y, int w, int h, int color);
int regionHit(UiState * uiState, int x, int y, int w, int h);
int lightenColor(int color, int amount);

#endif
