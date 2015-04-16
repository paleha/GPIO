#include "stm32f1xx.h" // File name depends on device used
#include "Lib.h"
#include "Led.h"
int main (void) 
{ // initialize peripherals here 
	//Initialize (); // Initialize device 
	SetSysClockToHSE((uint32_t) 8000000);
	SysTick_Init (); // Initialize SysTick Timer 
	LED_Initialize (); // Initialize LEDs 
	while (1) 
		{ LED_On (); // Switch on 
//			Delay (500); // Delay 
			if (GPIOC->IDR & GPIO_IDR_IDR0)
			{Delay(500);}
			else
			{Delay(500);}
			LED_Off (); // Switch off 
			Delay (150); // Delay 
  	} 
}

