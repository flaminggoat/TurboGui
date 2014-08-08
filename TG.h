#ifndef _TG
#define _TG

#include <SDL.h>
#include <stdint.h>

#define MAIN_MENU 0
#define FILE_BROWSER 1

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define ACTION_BAR_HEIGHT 20

enum
{
	TG_QUIT = 1
};

typedef struct
{
	int16_t x, y;
}TG_Point;

typedef struct
{
	int16_t x, y, w, h;
}TG_Rect;

typedef struct
{
	SDL_Surface * sdl;
}TG_Surface;

TG_Surface * TG_Init();

void TG_DrawRect(TG_Surface * s, TG_Rect * r, uint32_t color);

int TG_RegionHit(TG_Rect * r);

int TG_LightenColor(int color, int amount);

void TG_Quit();

uint8_t TG_Update();

void TG_Delay(uint16_t ms);

void TG_DrawSurface(TG_Surface * src, TG_Surface * dest,
	TG_Rect * srcRect, int16_t x, int16_t y);
	
TG_Surface * TG_CreateSurface(uint16_t width, uint16_t height);

void TG_Draw();

uint8_t TG_GetMouseDown();

#endif
