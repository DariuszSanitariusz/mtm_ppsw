#include <LPC21xx.H>
#include  "timer.h"

#define ENABLE_bm 1
#define RESET_bm (1<<1)

#define MR0INT_bm 1
#define INTONMR0_bm 1
#define RESETONMR0_bm (1<<1)
#define STOPONMR0_bm (1<<2)

#define UsToClk 15

void InitTimer0()
{
	T0TCR = ENABLE_bm | RESET_bm;
	T0TCR = T0TCR & ~RESET_bm;
}

void WaitOnTimer0(unsigned int uiTime)
{
	T0TCR = T0TCR | RESET_bm;
	T0TCR = T0TCR & ~RESET_bm;
	while((T0TC < uiTime*UsToClk)){}
}

void InitTimer0Match0(unsigned int iDelayTime)
{
	T0MR0 = iDelayTime * UsToClk;
	T0MCR = INTONMR0_bm | RESETONMR0_bm;
	T0TCR = T0TCR | RESET_bm;
	T0TCR = T0TCR & ~RESET_bm;
}

void WaitOnTimer0Match0()
{
	while((T0IR & MR0INT_bm) == 0)
	{
	}
	T0IR = MR0INT_bm;
}
