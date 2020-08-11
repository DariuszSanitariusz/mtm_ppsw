#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

enum LedState{LED_LEFT, LED_RIGHT, LED_STAY};

enum LedState eLedState = LED_LEFT;

void Automat(){
	switch (eLedState){
				case (LED_STAY):
					if (eKeyboard_Read()==BUTTON_1){
						eLedState=LED_LEFT;
					}
					if (eKeyboard_Read()==BUTTON_3){
						eLedState=LED_RIGHT;
					}
					break;
				case (LED_LEFT):
					Led_StepLeft();
					if(eKeyboard_Read()==BUTTON_2){
						eLedState=LED_STAY;
					}
					break;
				case (LED_RIGHT):
					if (eKeyboard_Read()==BUTTON_2){
						eLedState=LED_STAY;
					}
					break;
			}
}

int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	Timer0Interrupts_Init(20000,&Automat);

	while(1){
		iMainLoopCtr++;
		//a
		//b
		//c
		//d
	}
	
}
