#include <stdint.h>
#include <stdio.h>
#include <SDL.h>

#include "TG.h"
#include "TG_Button.h"

TG_Surface * screen;
TG_Button * button;

int main(int argc, char* args[])
{
	printf("TurboGui\n");
	
	
	if((screen = TG_Init()) == NULL)
		return 1;
	
	button = TG_CreateTextButton(10,10,50,50, "Hello", 0xFFFF00);
	
	for(;;)
	{
		if(TG_Update() == TG_QUIT)
			break;
		
		TG_UpdateButton(button);
		TG_DrawButton(button, screen);

		TG_Draw();

		TG_Delay(20);
	}
	
	TG_Quit();

	return 0;
}
