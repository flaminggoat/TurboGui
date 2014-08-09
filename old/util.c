#include "SDL.h"
#include "util.h"

void drawRect(SDL_Surface * surface, int x, int y, int w, int h, int color)
{
	SDL_Rect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	SDL_FillRect(surface, &r, color);
}

int regionHit(UiState * uiState, int x, int y, int w, int h)
{
	//Check to see if the pointer is outside
	//of the region
	if(uiState->mouseX < x ||
		uiState->mouseY < y ||
		uiState->mouseX >= x + w ||
		uiState->mouseY >= y + h)
		return 0;
	
	//If not it must be inside the region so return true
	return 1;
}

int lightenColor(int color, int amount)
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
