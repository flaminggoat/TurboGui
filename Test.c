#include <stdint.h>
#include <stdio.h>

#include "TG.h"
#include "TG_Button.h"

TG_Surface * screen;
TG_Button * button;

void quit(int status)
{
	TG_DestroyButton(button);
	TG_Quit();
	exit(status);
}

void init(void)
{
	printf("TurboGui\n");
	
	//Initialise TurboGui
	if((screen = TG_Init()) == NULL)
		quit(1);
	
	button = TG_CreateTextButton(10,10,50,50, "Hello", 0xFFFF00);
	
}

int main(int argc, char* args[])
{
	init();
	
	for(;;)
	{
		if(TG_Update() == TG_QUIT)
			break;
		
		TG_UpdateButton(button);
		TG_DrawButton(button, screen);

		TG_Draw();

		TG_Delay(20);
	}
	
	quit(0);

	return 0;
}
