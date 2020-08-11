#include "keyboard.h"
#include "led.h"
#include <LPC21xx.H>

enum LedState{LED_LEFT, LED_RIGHT, LED_STAY};
enum DirectionState{STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};

enum LedState eLedState = LED_LEFT;
enum DirectionState eDirectionState = STATE0;

unsigned int uiSwitchCounter;
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
				case LED_LEFT:
					eLedState=LED_RIGHT;
					Led_StepRight();
					break;
				default :
					eLedState=LED_LEFT;
					Led_StepLeft();
					break;
			}
			Delay(500);
			
////zadanie 4
			
			switch (eLedState){
				case (LED_RIGHT):
					for(uiCounter=0; uiCounter<3; uiCounter++){
						Led_StepRight();
					}
					if(eKeyboard_Read()==RELASED){
						eLedState=LED_STAY;
					}
					break;
				default:
					if(eKeyboard_Read()==BUTTON_1){
						eLedState=LED_RIGHT;
					}
					break;
			}
			
////zadanie 5
			
			switch (eLedState){
				case (LED_RIGHT):
					Led_StepRight();
					if(eKeyboard_Read()==BUTTON_1){
						eLedState=LED_STAY;
					}
					break;
				default:
					if(eKeyboard_Read()==BUTTON_2){
						eLedState=LED_RIGHT;
					}
					break;
			}
			
////zadanie 6
			
			switch (eLedState){
				case (LED_STAY):
					if (eKeyboard_Read()==BUTTON_1){
						eLedState=LED_LEFT;
					}
					else if (eKeyboard_Read()==BUTTON_3){
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
			Delay(100);
		}
		


}