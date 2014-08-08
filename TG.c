//
//
//TODO: fix header file

#include "SDL.h"
#include "TG.h"

SDL_Window *TG_SDL_Screen = NULL;

uint16_t TG_MouseX, TG_MouseY;
uint8_t TG_MouseDown;

TG_Surface * TG_Init(){
	TG_Surface * s = (TG_Surface *) malloc(sizeof(*s));
	
	//Start SDL
    SDL_Init(SDL_INIT_VIDEO);
	
	// Attempt to create a 640x480 window with 32bit pixels.
	TG_SDL_Screen = SDL_CreateWindow("TurboGui", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_SHOWN);
	
	//Check SDL initialised correctly
	if(TG_SDL_Screen == NULL)
	{	
		fprintf(stderr,"[ERROR] TG_Init failed: %s\n", SDL_GetError());
		return NULL;
	}	
	
	//Get window surface
    s->sdl = SDL_GetWindowSurface( TG_SDL_Screen );
    
    return s;
}

void TG_Draw()
{
	SDL_UpdateWindowSurface( TG_SDL_Screen );
}

void TG_DrawRect(TG_Surface * s, TG_Rect * r, uint32_t color)
{	
	SDL_Rect sRect;
	
	sRect.x = r->x;
	sRect.y = r->y;
	sRect.w = r->w;
	sRect.h = r->h;
	
	SDL_FillRect(s->sdl, &sRect, color);
}

void TG_DrawSurface(TG_Surface * src, TG_Surface * dest, TG_Rect * srcRect, int16_t x, int16_t y)
{
	SDL_Rect * pSR = NULL;
	SDL_Rect sR;
	SDL_Rect dR;
	
	if(srcRect != NULL)
	{
		sR.x = srcRect->x;
		sR.y = srcRect->y;
		sR.w = srcRect->w;
		sR.h = srcRect->h;
		pSR = &sR;
	}
	
	dR.x = x;
	dR.y = y;
		
	SDL_BlitSurface(src->sdl, pSR, dest->sdl, &dR);
}

TG_Surface * TG_CreateSurface(uint16_t width, uint16_t height)
{
	TG_Surface * t = (TG_Surface*)malloc(sizeof(t));
	t->sdl = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	return t;
}

int TG_RegionHit(TG_Rect * r)
{
	//Check to see if the pointer is outside
	//of the region
	if(	TG_MouseX < r->x ||
		TG_MouseY < r->y ||
		TG_MouseX >= r->x + r->w ||
		TG_MouseY >= r->y + r->h)
		return 0;
	
	//If not it must be inside the region so return true
	return 1;
}

int TG_LightenColor(int color, int amount)
{
	//lighten the components of the color
	int r = (color >> 16) + amount;
	int g = ((color & 0xFF00) >> 8) + amount;
	int b = (color & 0xFF) + amount;
	
	//clamp to range
	r = r > 255 ? 255 : r;
	g = g > 255 ? 255 : g;
	b = b > 255 ? 255 : b;
	r = r < 0 ? 0 : r;
	g = g < 0 ? 0 : g;
	b = b < 0 ? 0 : b;
	
	return (r << 16) | (g << 8) | b;
}

uint8_t TG_Update()
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type) 
		{
		case SDL_MOUSEMOTION:
			TG_MouseX = event.motion.x;
			TG_MouseY = event.motion.y;
		break;
		
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == 1)
				TG_MouseDown = 1;
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == 1)
				TG_MouseDown = 0;
			break;
			
		case SDL_KEYUP:			
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			  // If escape is pressed, return (and thus, quit)
			  return TG_QUIT;
			}
			break;
			
		case SDL_QUIT:
			return TG_QUIT;
		}
	}
	
	return 0;
}

uint8_t TG_GetMouseDown()
{
	return TG_MouseDown;
}

void TG_Delay(uint16_t ms)
{
	SDL_Delay(ms);
}

void TG_Quit()
{
	SDL_Quit();
}
