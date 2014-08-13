#include "TG.h"
#include "TG_Button.h"
//#include "TG_ActionBar.h"
#include "TG_Text.h"

TG_Button *backButton;
TG_Button *homeButton;
TG_Button *menuButton;

uint8_t TG_InitActionBar(TG_Font * font)
{
	backButton = TG_CreateTextButton(font, 0, 220, 106, 20, "\x11", 0);
	homeButton = TG_CreateTextButton(font, 106, 220, 108, 20, "\x08", 0);
	menuButton = TG_CreateTextButton(font, 214, 220, 106, 20, "\xF0", 0);
}

void TG_UpdateActionBar()
{
	TG_UpdateButton(backButton);
	TG_UpdateButton(homeButton);
	TG_UpdateButton(menuButton);
}

void TG_DrawActionBar(TG_Surface * s)
{
	TG_DrawButton(backButton, s);
	TG_DrawButton(homeButton, s);
	TG_DrawButton(menuButton, s);
}
