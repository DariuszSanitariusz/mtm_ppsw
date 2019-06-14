#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define DETEKTOR_bm (1<<10)

struct Servo
{
enum ServoState eState;
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
}sServo;

void DetectorInit()
{
	IO0DIR = IO0DIR & (~DETEKTOR_bm);
}

void ServoCallib(void)
{
	sServo.eState = CALLIB;
}

void Automat()
{
	switch(sServo.eState){
		case CALLIB:
			if(eReadDetector() == INACTIVE)
				LedStepRight();
			else
			{
				LedStepRight();
				sServo.eState = IDLE;
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPosition = 0;
			}
			break;
			
		case IN_PROGRESS:
			if(sServo.uiDesiredPosition > sServo.uiCurrentPosition){
				LedStepRight();
				sServo.uiCurrentPosition++;
			}
			else if(sServo.uiDesiredPosition < sServo.uiCurrentPosition){
				LedStepLeft();
				sServo.uiCurrentPosition--;
			}
			else
				sServo.eState = IDLE;		
		break;
		
		case IDLE:
			if(sServo.uiDesiredPosition != sServo.uiCurrentPosition)
				sServo.eState = IN_PROGRESS;
		break;
		}
}

void ServoInit(unsigned int uiServoFrequency)
{
	unsigned int uiPeriod = (unsigned int) (1000000/uiServoFrequency);
	DetectorInit();
	sServo.eState = CALLIB;
	LedInit();
	Timer0Interrupts_Init(uiPeriod,&Automat);
}

void ServoGoTo(unsigned int uiPosition){
	sServo.uiDesiredPosition = uiPosition;
}

enum DetectorState eReadDetector()
{
	int iDetectorState = IO0PIN & DETEKTOR_bm;
	if (iDetectorState == 0)
	{
		return ACTIVE;
	}
	return INACTIVE;
}
