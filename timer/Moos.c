#include "keyboard.h"
#include "led.h"
#include "timer.h"
#include <LPC21xx.H>

enum LedState{LED_LEFT, LED_RIGHT, LED_STAY};

enum LedState eLedState = LED_STAY;


int main()
{
	InitTimer0();
	LedInit();
	KeyboardInit();
	InitTimer0Match0(250000);
	
	while(T0IR!=1){
		Led_StepLeft();
		WaitOnTimer0Match0();
	}
}
