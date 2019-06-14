#include "keyboard.h"
#include "led.h"
#include "timer.h"
#include <LPC21xx.H>

enum LedState{LED_LEFT, LED_RIGHT};
enum DirectionState{STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};
enum LedMove{LED_MOVE_LEFT, LED_MOVE_RIGHT, LED_STAY};

enum Step{LEFT, RIGHT};
enum KeyboardState {RELASED,BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4};

enum LedState eLedState = LED_LEFT;
enum DirectionState eDirectionState = STATE0;
enum LedMove eLedMove = LED_STAY;

unsigned int uiSwitchCounter;
unsigned char uiCounter;

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

#define BUT0_bm (1<<4)
#define BUT1_bm (1<<6)
#define BUT2_bm (1<<5)
#define BUT3_bm (1<<7)

enum KeyboardState eKeyboardRead()
{
	int iButtonState;
	
	iButtonState = ~(IO0PIN & (BUT0_bm | BUT1_bm | BUT2_bm | BUT3_bm));
	
	if ((iButtonState & BUT0_bm) != 0) // wcisniety 0x10 & 0x10 = 0x10, puszczony 0x00 & 0x10 == 0x00
	{
		return BUTTON_1;
	}
	
		if ((iButtonState & BUT1_bm) != 0)// wcisniety 0x20 & 0x20 == 0x20, puszczony 0x00 & 0x20 == 00
	{
		return BUTTON_2;
	}
	
		if ((iButtonState & BUT2_bm) != 0)
	{
		return BUTTON_3;
	}
	
		if ((iButtonState & BUT3_bm) != 0)
	{
		return BUTTON_4;
	}
	
	return RELASED;
	
}

void KeyboardInit()
{
		IO0DIR = IO0DIR & ~(BUT0_bm | BUT1_bm | BUT2_bm | BUT3_bm);
}


unsigned int uiLedCounter = 0;

void LedOn(unsigned char ucLedIndeks)
{
	
	IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	
	switch(ucLedIndeks){
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
	}
	
}

void LedStep(eDirection Direction)
{
	static unsigned int uiLedCounter;
	if (Direction == RIGHT)
		uiLedCounter = uiLedCounter - 1;
	else if (Direction == LEFT)
		uiLedCounter = uiLedCounter + 1;
	LedOn(uiLedCounter % 4);
}

void LedStepLeft()
{
	LedStep(LEFT);
}

void LedStepRight()
{
	LedStep(RIGHT);
}

void LedInit()
{
	IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	LedOn(0);
}


void Delay(unsigned int uiWaitTime){
	
	unsigned int uiCounter;
	unsigned int uiCounter2;
	
	for(uiCounter=0; uiCounter<uiWaitTime; uiCounter++){
	  for(uiCounter2=0; uiCounter2<7500; uiCounter2++){}
	}	
}

int main()
{
	InitTimer0();
	LedInit();
	KeyboardInit();
	while(1)
		{
			LedOn(1);
			LedOn(2);
			LedOn(3);
			IO1CLR=0xF0000;
			
			LedOn(0);
			Delay(250);
			LedOn(1);
			Delay(250);
			LedOn(2);
			Delay(250);
			LedOn(3);
			Delay(250);
			
			switch (eKeyboard_Read()) {
				case RELASED:
					LedOn(4);
					break;
				case BUTTON_1:
					LedOn(0);
					break; 
				case BUTTON_2:
					LedOn(1);
					break; 
				case BUTTON_3:
					LedOn(2);
					break; 
				case BUTTON_4:
					LedOn(3);
					break; 
			}
			
			LedOn(0);
			for(uiCounter=0; uiCounter<9; uiCounter++){
				Led_StepRight();
			}
			for(uiCounter=0; uiCounter<9; uiCounter++){
				Led_StepLeft();
			}
			
			switch (eKeyboard_Read()){
				case BUTTON_1:
					Led_StepRight();
					break;
				case BUTTON_2:
					Led_StepLeft();
					break;
				case RELASED:
					break;
				default:
					break;
			}		
		}
		

}
