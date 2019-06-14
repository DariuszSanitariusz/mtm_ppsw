typedef enum DetectorState{
	ACTIVE,
	INACTIVE
} DetectorState;

typedef enum ServoState{
CALLIB, 
IDLE,
IN_PROGRESS
} ServoState;

void ServoCallib(void);
void ServoInit(unsigned int uiServoFrequency);
void DetectorInit(void);
void ServoGoTo(unsigned int uiPosition);
enum DetectorState eReadDetector(void);
