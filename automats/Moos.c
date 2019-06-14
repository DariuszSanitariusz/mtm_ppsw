#include "keyboard.h"
#include "led.h"
#include <LPC21xx.H>

enum LedState{LED_LEFT, LED_RIGHT};
enum DirectionState{STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};
enum LedMove{LED_MOVE_LEFT, LED_MOVE_RIGHT, LED_STAY};

enum LedState eLedState = LED_LEFT;
enum DirectionState eDirectionState = STATE0;
enum LedMove eLedMove = LED_STAY;

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
	InitTimer0();
	LedInit();
	KeyboardInit();
		while(1)
		{
			switch (eLedState){
				case LED_LEFT:
					eLedState=LED_RIGHT;
					Led_StepRight();
					break;
				case LED_RIGHT:
					eLedState=LED_LEFT;
					Led_StepLeft();
					break;
			}
			Delay(500);
		
			switch (eDirectionState){
				case (STATE0):
					eDirectionState=STATE1;
					Led_StepRight();
					break;
				case (STATE1):
					eDirectionState=STATE2;
					Led_StepRight();
					break;
				case (STATE2):
					eDirectionState=STATE3;
					Led_StepRight();
					break;
				case (STATE3):
					eDirectionState=STATE4;
					Led_StepLeft();
					break;
				case (STATE4):
					eDirectionState=STATE5;
					Led_StepLeft();
					break;
				case (STATE5):
					eDirectionState=STATE0;
					Led_StepLeft();
					break;
			}
			Delay(500);
			
////zadanie 4
			
			switch (eLedMove){
				case (LED_MOVE_RIGHT):
					for(uiCounter=0; uiCounter<3; uiCounter++){
						Led_StepRight();
					}
					if(eKeyboard_Read()==RELASED){
						eLedMove=LED_STAY;
					}
					break;
				default:
					if(eKeyboard_Read()==BUTTON_1){
						eLedMove=LED_MOVE_RIGHT;
					}
					break;
			}
			
////zadanie 5
			
			switch (eLedMove){
				case (LED_MOVE_RIGHT):
					Led_StepRight();
					if(eKeyboard_Read()==BUTTON_1){
						eLedMove=LED_STAY;
					}
					break;
				default:
					if(eKeyboard_Read()==BUTTON_2){
						eLedMove=LED_MOVE_RIGHT;
					}
					break;
			}
			
////zadanie 6
			
			switch (eLedMove){
				case (LED_STAY):
					if (eKeyboard_Read()==BUTTON_1){
						eLedMove=LED_MOVE_LEFT;
					}
					else if (eKeyboard_Read()==BUTTON_3){
						eLedMove=LED_MOVE_RIGHT;
					}
					break;
				case (LED_MOVE_LEFT):
					Led_StepLeft();
					if(eKeyboard_Read()==BUTTON_2){
						eLedMove=LED_STAY;
					}
					break;
				case (LED_MOVE_RIGHT):
					if (eKeyboard_Read()==BUTTON_2){
						eLedMove=LED_STAY;
					}
					break;
			}
			Delay(100);
		}
}
