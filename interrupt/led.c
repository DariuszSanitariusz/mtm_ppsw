#include <LPC21xx.H>
#include "led.h"

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

void LedInit(void){
	IO1DIR=IO1DIR|(LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	IO1SET= LED0_bm;
}
	
void LedOn(unsigned char ucLedIndeks){
	
	IO1CLR = (LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	switch (ucLedIndeks) {
		case 0:
			IO1SET = LED0_bm;
			break;
		case 1:
			IO1SET = LED1_bm;
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
		case 4:
			IO1SET = 0;
		default:
			break;
	}
}

void Led_Step(enum Step Direction){

	static unsigned int uiLed;

	if (Direction == RIGHT ){
		uiLed=uiLed-1;
	}
	else if (Direction==LEFT){
		uiLed=uiLed+1;
	}
	LedOn(uiLed%4);
}

void Led_StepLeft(){
		Led_Step(LEFT);
}

void Led_StepRight(){
		Led_Step(RIGHT);
}
