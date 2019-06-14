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
