#include "keyboard.h"
#include "led.h"
#include "timer.h"
#include "servo.h"
#include "timer_interrupts.h"

int main()
{
	LedInit();
	KeyboardInit();
	ServoInit(25000);
	
	while(1){
		if(eKeyboard_Read()==BUTTON_1){
			ServoCallib();
		}
		if(eKeyboard_Read()==BUTTON_2){
			ServoGoTo(12);
		}
		if(eKeyboard_Read()==BUTTON_3){
			ServoGoTo(24);
		}
		if(eKeyboard_Read()==BUTTON_4){
			ServoGoTo(36);
		}
	}
}
