typedef void (* PointerType)();

__irq void Timer0IRQHandler(void);
void Timer0Interrupts_Init(unsigned int,PointerType);
