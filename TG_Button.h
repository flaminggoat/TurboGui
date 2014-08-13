#ifndef __button
#define __button

#include <stdint.h>

#include "TG.h"
#include "TG_Text.h"

enum
{
	TG_BUTTON_RELEASED, TG_BUTTON_PRESSED,
	TG_BUTTON_JUST_PRESSED, TG_BUTTON_JUST_RELEASED	
};

typedef struct
{
	TG_Rect rect;
	TG_Point textPos;
	TG_Surface * surface;
	uint8_t status;
	uint32_t color, pressedColor, textColor;
	uint8_t * text;
	TG_Font * font;
} TG_Button;

TG_Button * TG_CreateTextButton(TG_Font * font, int16_t x, int16_t y, int16_t w,
	int16_t h, uint8_t * text, uint32_t color);
	
uint8_t TG_UpdateButton(TG_Button * button);

void TG_DrawButton(TG_Button * button, TG_Surface * s);

void TG_DestroyButton(TG_Button * b);

#endif
