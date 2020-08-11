#include "keyboard.h"
#include "led.h"
#include "timer.h"


int main()
{
	InitTimer0();
	LedInit();
	KeyboardInit();
	InitTimer0Match0(2500);
	while(1)
		{		
			Led_StepLeft();
			//WaitOnTimer0(2500);
			WaitOnTimer0Match0();
		}
}
