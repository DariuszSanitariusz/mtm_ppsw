#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define DETEKTOR_bm (1<<10)
#define GET_OFFSET 12 

enum DetectorState{ACTIVE, INACTIVE};

enum ServoState{CALLIB, IDLE, OFFSET, IN_PROGRESS};

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

enum DetectorState eReadDetector()
{
	int iDetectorState = IO0PIN & DETEKTOR_bm;
	if (iDetectorState == 0)
	{
		return ACTIVE;
	}
	return INACTIVE;
}

void Automat()
{
	switch(sServo.eState){
/**********************************************/
		case CALLIB:
			if(eReadDetector() == INACTIVE){
				Led_StepRight();
				sServo.eState = CALLIB;
			}
			else{
				sServo.uiCurrentPosition = 0;
				sServo.uiDesiredPosition = 0;
				sServo.eState = OFFSET;
			}
		break;
/**********************************************/
		case OFFSET:
			if(sServo.uiCurrentPosition == GET_OFFSET){
				sServo.uiCurrentPosition = 0;
				sServo.eState = IDLE;
			}
			else{
				Led_StepRight();
				sServo.uiCurrentPosition++;
				sServo.eState = OFFSET;
			}
		break;
/**********************************************/
		case IDLE:
			if(sServo.uiDesiredPosition != sServo.uiCurrentPosition)
				sServo.eState = IN_PROGRESS;
			else
				sServo.eState = IDLE;
		break;
/**********************************************/
		case IN_PROGRESS:
			if(sServo.uiDesiredPosition != sServo.uiCurrentPosition){
				if(sServo.uiDesiredPosition > sServo.uiCurrentPosition){
					Led_StepRight();
					sServo.uiCurrentPosition++;
					sServo.eState = IN_PROGRESS;
				}
				else if(sServo.uiDesiredPosition < sServo.uiCurrentPosition){
					Led_StepLeft();
					sServo.uiCurrentPosition--;
					sServo.eState = IN_PROGRESS;
				}
			}
			else
				sServo.eState = IDLE;		
		break;
/**********************************************/
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


