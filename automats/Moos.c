#include "keyboard.h"
#include "led.h"
#include <LPC21xx.H>

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

enum LedState{LED_LEFT, LED_RIGHT, LED_STAY, LED_ON, LED_OFF};

enum LedState eLedState = LED_STAY;

unsigned int uiSwitchCounter=0;
unsigned char uiCounter;

void Delay(unsigned int uiWaitTime){
	
	unsigned int uiCounter;
	unsigned int uiCounter2;
	
	for(uiCounter=0; uiCounter<uiWaitTime; uiCounter++){
	  for(uiCounter2=0; uiCounter2<7500; uiCounter2++){}
	}	
}

int main()
{
	LedInit();
	KeyboardInit();
		while(1)
		{
			switch (eLedState){
				case (LED_STAY):
					if (eKeyboard_Read()==BUTTON_2){
						eLedState=LED_LEFT;
					}
					else if (eKeyboard_Read()==BUTTON_1){
						eLedState=LED_RIGHT;
					}
					else if (eKeyboard_Read()==BUTTON_4){
						eLedState=LED_ON;
					}
					else
						eLedState=LED_STAY;
					break;
				case (LED_LEFT):
					if(eKeyboard_Read()==BUTTON_3){
						eLedState=LED_STAY;
					}
					else
						eLedState=LED_LEFT;
						Led_StepLeft();
					break;
				case (LED_RIGHT):
					if (eKeyboard_Read()==BUTTON_3){
						eLedState=LED_STAY;
					}
					else
						eLedState=LED_RIGHT;
						Led_StepRight();
					break;
				case (LED_ON):
					if (uiSwitchCounter==20){
							eLedState=LED_STAY;
							uiSwitchCounter=0;
							break;
					}
					else
						LedOn(3);
						uiSwitchCounter++;
						eLedState=LED_OFF;
					break;
				case (LED_OFF):
					if (uiSwitchCounter==20){
							eLedState=LED_STAY;
							uiSwitchCounter=0;
							break;
					}
					else
						LedOn(4);
						eLedState=LED_ON;
						uiSwitchCounter++;
					break;
			}
			Delay(100);
		}
}
