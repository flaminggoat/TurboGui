#include <stdint.h>
#include <stdio.h>

#include "TG.h"
#include "TG_Button.h"
#include "TG_Text.h"

#include "TG_ActionBar.c"

TG_Surface * screen;
TG_Button *scanButton, *fileButton, *noteButton;
TG_Font *smallFont;

void quit(int status)
{
	TG_DestroyButton(scanButton);
	TG_DestroyButton(fileButton);
	TG_DestroyButton(noteButton);
	
	TG_Quit();
	exit(status);
}

void init(void)
{
	printf("TurboGui\n");
	
	//Initialise TurboGui
	if((screen = TG_Init()) == NULL)
		quit(1);
		
	smallFont = TG_CreateFont("font.bmp", 16, 16);
	
	scanButton = TG_CreateTextButton(smallFont, 20, 20, 80, 80, "Scan", 0x30B3FF);
	fileButton = TG_CreateTextButton(smallFont, 120, 20, 80, 80, "Files", 0x0083FF);
	noteButton = TG_CreateTextButton(smallFont, 220, 20, 80, 80, "Notepad", 0x0083FF);
	
	TG_InitActionBar(smallFont);
	
	uint8_t c = 0;
	for(uint8_t j = 0; j < 30; j++)
	{
		for(uint8_t i = 0; i < 40; i++)
		{	
			//heart = 0x03
			TG_DrawChar(screen, smallFont, i*8, j*8, c, rand() & 0x505050);
			if(++c > 128)
				c = 0;
		}
	}
	
}

int main(int argc, char* args[])
{
	init();
	
	for(;;)
	{
		if(TG_Update() == TG_QUIT)
			break;
		
		TG_UpdateButton(scanButton);
		TG_UpdateButton(fileButton);
		TG_UpdateButton(noteButton);
		TG_UpdateActionBar();
		
		TG_DrawButton(scanButton, screen);
		TG_DrawButton(fileButton, screen);
		TG_DrawButton(noteButton, screen);
		TG_DrawActionBar(screen);

		TG_Draw();

		TG_Delay(20);
	}
	
	quit(0);

	return 0;
}
