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
	T0TCR = ENABLE_bm | RESET_bm;   //zresetowanie timera 0
	T0TCR = T0TCR & ~RESET_bm;			//wylaczenie resetu na timerze 0
}

void WaitOnTimer0(unsigned int uiDelay)
{
	T0TCR = T0TCR | RESET_bm;						//zresetowanie timera 0
	T0TCR = T0TCR & ~RESET_bm;					//wylaczenie resetu na timerze 0
	while((T0TC != uiDelay*UsToClk)){}	//dopoki timer przekroczy zadana wartosc(mikrosekundy)
}

void InitTimer0Match0(unsigned int iDelayTime)
{
	T0MR0 = iDelayTime * UsToClk;					//ustawienie rejestru porownojacego na zadana wartosc(mikrosekundy)
	T0MCR = INTONMR0_bm | RESETONMR0_bm;	//wlaczenie funkcji przerwania i funkcji resetowania timera 0, gdy wartosc timera bedzie zgodna z wartoscia w rejestrze MR0
	T0TCR = T0TCR | RESET_bm;							//zresetowanie timera 0
	T0TCR = T0TCR & ~RESET_bm;						//wylaczenie resetu na timerze 0
}

void WaitOnTimer0Match0()
{
	while((T0IR & MR0INT_bm) == 0)				//dopoki nie ma ustawionej flagi przerwania
	{
	}
	T0IR = MR0INT_bm;											//zresetowanie flagi przerwania
}
